//
//  HeadsUpCarView.swift
//  NewFeatures
//
//  Created by Kaushal on 25/5/2022.
//

import SwiftUI

struct HeadsUpCarView: View {
  @State private var surName: String = ""
  @State private var surNameHanja: String = ""
  @State private var gender: String = ""
  @State private var birthPlace: String = ""
  @State private var dob: String = ""
    var body: some View {
      VStack(alignment: .leading) {
        Image("hawaii")
          .resizable()
          .aspectRatio(contentMode: .fill)
          .frame(height: 70)
          .padding(.all, 0)
        Spacer(minLength: 40)
        VStack(alignment: .leading) {
          Text(surName)
          .font(.body)
          .multilineTextAlignment(.leading)
          Text(surNameHanja)
          .font(.body)
          .multilineTextAlignment(.leading)
          Text(gender)
          .font(.body)
          .multilineTextAlignment(.leading)
          Text(birthPlace)
          .font(.body)
          .multilineTextAlignment(.leading)
          Text(dob)
          .font(.body)
          .multilineTextAlignment(.leading)
          Spacer(minLength: 40)
//          Text("Sydney shipit flights info ✈️")
//            .font(.subheadline)
//          Text("1 week ago")
//            .font(.caption)
        }.padding()
        .onAppear() {
          self.surName = RegisterInfo.obj.surName
          self.surNameHanja = RegisterInfo.obj.surNameHanja
          self.gender = RegisterInfo.obj.gender.rawValue
          self.birthPlace = RegisterInfo.obj.birthPlace.rawValue
          self.dob = getStringFromDate(RegisterInfo.obj.datetime)
        }

      }
    }

}

struct HeadsUpCarView_Previews: PreviewProvider {
    static var previews: some View {
        HeadsUpCarView()
    }
}
