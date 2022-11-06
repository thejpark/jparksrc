//
//  CoordinateInput.swift
//  NameIs
//
//  Created by Jung Gyu Park on 25/9/2022.
//

import SwiftUI

struct CoordinateInputView: View {
  @State private var latitude: String = ""
  @State private var longitude: String = ""
  @State private var currentLocation: String = pendingRegisterInfo.birthPlace
  let locationProvider: ProvidesCurrentLocationProvider = CurrentLocationProvider()
  var body: some View {
    VStack (alignment: .center){
      Spacer()
      VStack {
        HStack {
          Text("현재 위치:")
          Text(currentLocation)
        }
        Divider()
        Text("현재 위치와 다를 경우")
        Text("위도와 경로를 직접 입력하세요!")
        Text("서울 37.5665, 126.9780").foregroundColor(.gray)
        Text("뉴욕 40.7128, -74.0060").foregroundColor(.gray)
        Divider()
      }

      Spacer()
      HStack {
        Spacer(minLength: 100)
        Text("위도")
          .foregroundColor(.black)
        Spacer()
        Spacer()
        TextField("37.5665", text: $latitude)
          .lineLimit(1).foregroundColor(.blue)
          .onChange(of: latitude) { newValue in
            pendingRegisterInfo.latitude = Double(newValue) ?? 0
          }
      }

      HStack {
        Spacer(minLength: 100)
        Text("경도")
          .foregroundColor(.black)
        Spacer()
        Spacer()
        TextField("126.9780", text: $longitude)
          .lineLimit(1).foregroundColor(.blue)
          .onChange(of: longitude) { newValue in
            pendingRegisterInfo.longitude = Double(newValue) ?? 0
          }
      }
      Spacer()
      Spacer()
    }.onAppear {
      populateLocation()
    }
  }


  func populateLocation() {
    getCurrentLocation { location in
      guard let location = location
      else { return }
      self.currentLocation = location.name
      pendingRegisterInfo.birthPlace = location.name
      pendingRegisterInfo.latitude = location.latitude
      pendingRegisterInfo.longitude = location.longitude
    }
  }

  func getCurrentLocation(_ completion: @escaping (GeoLocation?) -> Void) {
    locationProvider.getCurrentLocation { result in
      switch result {
      case .updatedLocation(let currentLocation):
        guard let currentLocation = currentLocation else {
          completion(nil)
          return
        }
        ReverseGeocoder.reverseGeocodeLocation(withCoordinate: currentLocation) { location in
          completion(location)
        }
      case .deniedAccess, .error:
        completion(nil)
      }
    }
  }

}

struct CoordinateInputView_Previews: PreviewProvider {
    static var previews: some View {
        CoordinateInputView()
    }
}
