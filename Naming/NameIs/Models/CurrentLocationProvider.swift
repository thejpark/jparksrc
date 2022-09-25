//
//  CurrentLocationProvider.swift
//  NameIs
//
//  Created by Jung Gyu Park on 24/9/2022.
//

import CoreLocation
import Foundation

struct GeoLocation: Equatable {
  let latitude: CLLocationDegrees
  let longitude: CLLocationDegrees
  let accuracy: CLLocationAccuracy
  var name: String = ""
}

protocol ProvidesCurrentLocationProvider: AnyObject {
  func getCurrentLocation(_ handler: @escaping (CurrentLocationProvider.Result) -> Void)
}

// MARK: - CurrentLocationProvider

final class CurrentLocationProvider: NSObject, ProvidesCurrentLocationProvider {
  init(
    maximumReadings max: Int = 5,
    accuracy: CLLocationAccuracy = kCLLocationAccuracyBest)
  {
    maxReadings = max
    locationManager = CLLocationManager()
    super.init()

    locationManager.desiredAccuracy = accuracy
    locationManager.delegate = self
  }

  // MARK: Internal

  enum Result {
    case updatedLocation(GeoLocation?)
    case deniedAccess
    case error(Error)
  }

  let locationManager: CLLocationManager
  let maxReadings: Int

  var readingCount: Int = 0
  var location: GeoLocation?
  var heading: CLHeading?

  var shouldRequestAccess: Bool {
    return true
  }

  func getCurrentLocation(_ handler: @escaping (Result) -> Void) {
    DispatchQueue.main.async {
      self.completionHandler = handler
      self.start()
    }
  }

  func start() {
    readingCount = 0
    if Permission.Location.isAuthorized {
      getNextLocation()
    } else {
      requestAccess()
    }
  }

  func stop() {
    locationManager.stopUpdatingLocation()
    locationManager.stopUpdatingHeading()
  }

  // MARK: Private

  private enum Constants {
    static let maxReadings = 5
  }

  private var completionHandler: ((Result) -> Void)?

  private var shouldGetLocation: Bool {
    if location == nil { return true }

    if let location = location, location.accuracy <= locationManager.desiredAccuracy { return false }
    if readingCount > Constants.maxReadings { return false }
    return true
  }

  private func requestAccess() {
    guard Permission.Location.shouldRequest(isUserInitiated: false) else {
      completionHandler?(.deniedAccess)
      return
    }

    guard shouldRequestAccess else {
      completionHandler?(.deniedAccess)
      return
    }

    Permission.Location.request { [weak self] granted in
      if granted {
        self?.getNextLocation()
      } else {
        self?.completionHandler?(.deniedAccess)
      }
    }
  }

  private func getNextLocation() {
    guard shouldGetLocation else {
      completionHandler?(.updatedLocation(location))
      return
    }

    locationManager.startUpdatingLocation()
    locationManager.startUpdatingHeading()
  }

}

// MARK: CLLocationManagerDelegate

extension CurrentLocationProvider: CLLocationManagerDelegate {

  // MARK: Public

  public func locationManager(_: CLLocationManager, didFailWithError error: Error) {
    stop()
    completionHandler?(.error(error))
  }

  // MARK: Internal

  func locationManager(_: CLLocationManager, didUpdateLocations locations: [CLLocation]) {

    // Get the most accurate geolocation provided
    var geolocations = locations.compactMap { GeoLocation(latitude: $0.coordinate.latitude,
                                                          longitude: $0.coordinate.longitude,
                                                          accuracy: $0.horizontalAccuracy) }

    geolocations.sort(by: { $0.accuracy < $1.accuracy })

    guard let geolocation = geolocations.first else { return }

    if let lastRecorded = location {
      if (geolocation.accuracy) <= lastRecorded.accuracy {
        location = geolocation
      }
    } else {
      location = geolocation
    }

    readingCount += 1

    locationManager.stopUpdatingLocation()
    getNextLocation()
  }

  func locationManager(_: CLLocationManager, didUpdateHeading newHeading: CLHeading) {
    heading = newHeading
  }

}
