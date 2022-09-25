//
//  Permission.swift
//  NameIs
//
//  Created by Jung Gyu Park on 24/9/2022.
//

import Foundation


enum Permission { }

// The following can be different file.
import CoreLocation

extension Permission {

  struct Location {

    // MARK: Internal

    static var status: CLAuthorizationStatus {
      let manager = CLLocationManager()
      return manager.authorizationStatus
    }

    static var isAuthorized: Bool {
      manager.authorizationStatus == .authorizedAlways
        || manager.authorizationStatus == .authorizedWhenInUse
    }

    static func shouldRequest(isUserInitiated: Bool) -> Bool {
      if isUserInitiated {
        return status != .authorizedAlways && status != .authorizedWhenInUse
      } else {
        return status == .notDetermined
      }
    }

    static func request(completion: @escaping (Bool) -> Void) {

      let status = Location.manager.authorizationStatus
      handle(locationStatus: status) { auth in
        switch auth {
        case .undetermined:
          Location.completionHandler = completion
          Location.manager.requestWhenInUseAuthorization()
        case .granted:
          completion(true)
        case .denied:
          completion(false)
        }
      }
    }

    // MARK: Private

    private static var delegate = LocationManagerDelegate()
    private static var completionHandler: ((Bool) -> Void)?

    private static var manager: CLLocationManager = {
      let result = CLLocationManager()
      result.delegate = Location.delegate
      return result
    }()

    private static func handle(
      locationStatus: CLAuthorizationStatus,
      onResult: @escaping (AuthorizationStatus) -> Void)
    {
      switch locationStatus {
      case .restricted, .denied:
        onResult(.denied)
      case .authorizedAlways, .authorizedWhenInUse, .authorized:
        onResult(.granted)
      case .notDetermined:
        onResult(.undetermined)
      @unknown default:
        break
      }
    }
  }
}

// MARK: - Authorisation Status

extension Permission.Location {
  private enum AuthorizationStatus {
    case undetermined, granted, denied
  }
}

// MARK: - CLLocationManagerDelegate

extension Permission.Location {

  private class LocationManagerDelegate: NSObject, CLLocationManagerDelegate {
    func locationManager(
      _: CLLocationManager,
      didChangeAuthorization status: CLAuthorizationStatus)
    {
      Permission.Location.handle(locationStatus: status) { auth in
        guard auth != .undetermined else { return }

        let isPermissionGranted = auth == .granted
        Permission.Location.completionHandler?(isPermissionGranted)
        Permission.Location.completionHandler = nil
      }
    }
  }
}
