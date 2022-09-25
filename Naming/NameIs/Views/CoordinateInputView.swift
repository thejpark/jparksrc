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
  var body: some View {
    VStack (alignment: .center){
      Spacer()
      Text("위도와 경로를 입력하세요!")
      Text("서울 37.5665, 126.9780").foregroundColor(.gray)
      Text("뉴욕 40.7128, -74.0060").foregroundColor(.gray)

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
    }
  }
}

struct CoordinateInputView_Previews: PreviewProvider {
    static var previews: some View {
        CoordinateInputView()
    }
}
