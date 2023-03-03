//
//  HeadsUpCarView.swift
//  NewFeatures
//
//  Created by Kaushal on 25/5/2022.
//

import SwiftUI
//import PhotosUI

struct HeadsUpCarView: View {
  @State private var surName: String = ""
  @State private var gender: String = ""
  @State private var birthPlace: String = ""
  @State private var dob: String = ""
  @State private var saju: String = ""
//  @State private var selectedItem: PhotosPickerItem?
  @State private var selectedImage: Image = getRegisteredImage()

    var body: some View {
      VStack(alignment: .leading) {
        //        Image("sunny")
        selectedImage.resizable()
          .aspectRatio(contentMode: .fit)
          .frame(height: 300)
//          .padding(.all, 0)
//        Spacer(minLength: 40)

//        HStack() {
//          Spacer()
//          PhotosPicker(selection: $selectedItem, matching: .images) {
//            Label("사진 변경", systemImage: "photo")
//          }
//          .tint(.purple)
//          .controlSize(.large)
//          .buttonStyle(.borderedProminent)
//          .onChange(of: selectedItem) { newValue in
//            Task {
//              if let imageData = try? await newValue?.loadTransferable(type: Data.self), let image = UIImage(data: imageData) {
//                selectedImage = Image(uiImage: image)
//                setRegisteredImage(selectedImage)
//                pendingRegisterInfo.image = imageData
//              }
//            }
//          }
//          Spacer()
//        }
//


        VStack(alignment: .leading) {
        Spacer(minLength: 40)
        Divider()
          .background(.black)
        Text("출생정보")
          .font(.title)
          .foregroundColor(.black)
          .multilineTextAlignment(.leading)
        Divider()
          .background(.black)

//        Spacer(minLength: 20)
        Text(surName)
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
          Text(saju)
          .font(.body)
          .multilineTextAlignment(.leading)
        Spacer(minLength: 40)
//          Text("Sydney shipit flights info ✈️")
//            .font(.subheadline)
//          Text("1 week ago")
//            .font(.caption)
        } 
          .onAppear() {
          if RegisterInfo.obj.surName !=  ""  {
          self.surName = "성: " + RegisterInfo.obj.surName + "(" + RegisterInfo.obj.surNameHanja + ")"
          self.gender = "성별: " + RegisterInfo.obj.gender.rawValue
          self.birthPlace = "출생지: " + RegisterInfo.obj.birthPlace
          let dob = getStringFromDate(RegisterInfo.obj.datetime)
          let str = dob.components(separatedBy: " ")
          self.dob = "시간 : " + str[0] + "년 " + str[1] + "월 " + str[2] + "일 " + str[3] + "시 " + str[4] + "분"
          let year = Int(str[0])!
          let month = Int(str[1])!
          let day = Int(str[2])!
          let hour = Int(str[3])!
          let minute = Int(str[4])!

          self.saju = "사주: " + getSaju(year, month: month, day: day, hour: hour, minute: minute);
          self.selectedImage = getRegisteredImage()
          }
        }

      }
    }

}

struct HeadsUpCarView_Previews: PreviewProvider {
    static var previews: some View {
        HeadsUpCarView()
    }
}
