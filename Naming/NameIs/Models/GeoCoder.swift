//
//  GeoCoder.swift
//  NameIs
//
//  Created by Jung Gyu Park on 24/9/2022.
//
import CoreLocation
import Foundation

typealias ReverseGeocoderCompletionHandler = (_ location: GeoLocation?) -> Void

class ReverseGeocoder: NSObject {

    static func reverseGeocodeLocation(withCoordinate geoLocation: GeoLocation, completion: @escaping ReverseGeocoderCompletionHandler ) {

        let location = CLLocation(latitude: geoLocation.latitude, longitude: geoLocation.longitude)
        let geocoder = CLGeocoder()

        geocoder.reverseGeocodeLocation(location) { (placemarks, error) in
            guard error == nil else {
              completion(nil)
                return
            }

            guard let placemarks = placemarks, !placemarks.isEmpty else {
                completion(nil)
                return
            }

            let sorted = placemarks.sorted(by: { lhs, rhs -> Bool in
                guard let lhsLocation = lhs.location else { return false }
                guard let rhsLocation = rhs.location else { return true }
                return lhsLocation.horizontalAccuracy < rhsLocation.horizontalAccuracy
            })

            let placemarkGeoLocation = sorted.first!
            var name = placemarkGeoLocation.locality
            if let country = placemarkGeoLocation.country {
              name! += ", " + country
            }

          var result = geoLocation
          if let name = name {
            result.name = name
          }
          completion(result)
        }
    }
}
