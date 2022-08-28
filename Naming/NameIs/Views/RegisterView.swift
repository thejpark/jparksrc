//
//  RegisterView.swift
//  NewFeatures
//
//  Created by Jung Gyu Park on 13/6/2022.
//

import SwiftUI

//struct TextEditingView: View {
//  @State private var fullText: String = ""
//  let placeholderString : String = "태명을 지어주세요"
//
//  var body: some View {
////    VStack {
//    HStack(spacing: base * 3) {
////          Image(image)
////            .frame(width: base * 6, height: base * 6)
////      Text("태명")
////        .lineLimit(1).foregroundColor(.black)
//      TextEditor(text: self.$fullText)
//        .onAppear(perform: {
//          if self.fullText.isEmpty {
//            self.fullText = placeholderString
//          }
//        })
//        .foregroundColor(self.fullText == placeholderString ? .gray : .primary)
//        .onTapGesture(perform: {
//          if self.fullText == placeholderString {
//              self.fullText = ""
//          }})
//    }
//    .frame(height: base * 14)
//    .padding(.horizontal, base * 3)
////  }
//  }
//}


private let base: CGFloat = 4.0

struct FamilynameComponent: View {
  @State private var familyName: String = ""
  @State private var selectedSurnameIndex = 0

  var body: some View {
//    VStack {
//      Button {
//        viewModel.editPressed(action: item.action)
//      } label: {
      let binding = Binding(
        get: { self.selectedSurnameIndex },
        set: { self.selectedSurnameIndex = $0
        }
       )

      HStack(spacing: base * 3) {
//          Image(image)
//            .frame(width: base * 6, height: base * 6)
          Text("성씨")
            .lineLimit(1).foregroundColor(.black)
          Spacer()
          Spacer()
          TextField("성을 한글로 입력하세요", text: $familyName)
            .lineLimit(1).foregroundColor(.blue)

          //          Spacer()
          let pickerData = getLastNameFromHangul(familyName)
//          hanjaSurname = pickerData
          if pickerData.count == 1 {
            Text(onChangeLastName(n: familyName, h: pickerData[0], s: pickerData[0]))
            Spacer()
            Spacer()

          }
          else if pickerData.count > 1 {
            Picker("", selection: binding, content: {
              ForEach(0..<pickerData.count, content: {index in //
                Text(onChangeLastName(n: familyName, h: pickerData[index], s: pickerData[selectedSurnameIndex]))
//                Text(pickerData[index])
              })
            })
//            Text("Selected Surname: \(pickerData[selectedSurnameIndex])")
            Spacer()
            Spacer()
          }
        }
        .frame(height: base * 14)
        .padding(.horizontal, base * 3)
//      }
//    }
  }

//  var text: String
//  var image: String
}
var pendingRegisterInfo = RegisterInfo(surName: "", surNameHanja:"", gender: Gender.male, datetime: Date(), birthPlace: Place.서울)

func onChangeGender(g: Gender) {
  pendingRegisterInfo.gender = g
}

func onChangeDate(d: Date) {
  pendingRegisterInfo.datetime = d
}

func onChangePlace(p: Place) {
  pendingRegisterInfo.birthPlace = p
}

func onChangeLastName(n: String, h: String, s: String) -> String {
  pendingRegisterInfo.surName = n
  pendingRegisterInfo.surNameHanja = s
  return h
}

struct GenderComponent: View {
  @State private var selectedGender: Gender = .male
//  @State var selectedGender: Gender
  var body: some View {
//    VStack {
//      Button {
////        viewModel.editPressed(action: item.action)
//      } label: {
        let binding = Binding(
          get: { self.selectedGender },
          set: { self.selectedGender = $0
            onChangeGender(g: $0)
          }
         )
        HStack(spacing: base * 3) {
//          Image(image)
//            .frame(width: base * 6, height: base * 6)
          Text("성별")
            .lineLimit(1).foregroundColor(.black)
          Spacer()
          Picker("성별", selection: binding) {
            Text("여").tag(Gender.female)
            Text("남").tag(Gender.male)
          }

          Spacer()
          Spacer()
        }
        .frame(height: base * 14)
        .padding(.horizontal, base * 3)
    }
}


struct DobComponent: View {
  @State private var date = Date()
  let dateRange: ClosedRange<Date> = {
      let calendar = Calendar.current
      let startComponents = DateComponents(year: 1940, month: 1, day: 1)
      let endComponents = DateComponents(year: 2022, month: 12, day: 31, hour: 23, minute: 59, second: 59)
      return calendar.date(from:startComponents)!
          ...
          calendar.date(from:endComponents)!
  }()
  var body: some View {
//    VStack {
//      Button {
////        viewModel.editPressed(action: item.action)
//      } label: {

        let binding = Binding(
          get: { self.date },
          set: { self.date = $0
            onChangeDate(d: $0)
          }
         )

    HStack(spacing: base * 3) {
//          Image(image)
//            .frame(width: base * 6, height: base * 6)
          Text("생일")
            .lineLimit(1).foregroundColor(.black)
//          Spacer()
          DatePicker(
              "",
               selection: binding,
               in: dateRange,
               displayedComponents: [.date, .hourAndMinute]
          )
          Spacer()
        }
        .frame(height: base * 14)
        .padding(.horizontal, base * 3)

  }
//  }

}


struct PlaceComponent: View {
  @State private var selectedPlace: Place = .서울
  var body: some View {
    VStack {
//      Button {
////        viewModel.editPressed(action: item.action)
//      } label: {

        let binding = Binding(
          get: { self.selectedPlace },
          set: { self.selectedPlace = $0
            onChangePlace(p: $0)
          }
         )
        HStack(spacing: base * 3) {
//          Image(image)
//            .frame(width: base * 6, height: base * 6)
          Text("출생지")
            .lineLimit(1).foregroundColor(.black)
          Spacer()
//          List {
          Picker("", selection: binding) {
            Group {
            Text("강릉").tag(Place.강릉)
            Text("경주").tag(Place.경주)
            Text("고양").tag(Place.고양)
            Text("광주").tag(Place.광주)
            Text("구미").tag(Place.구미)
            Text("군산").tag(Place.군산)
            Text("김천").tag(Place.김천)
            Text("김해").tag(Place.김해)
            Text("남양주").tag(Place.남양주)
            Text("대구").tag(Place.대구)
            }
            Group {
            Text("대전").tag(Place.대전)
            Text("동해").tag(Place.동해)
            Text("목포").tag(Place.목포)
            Text("부산").tag(Place.부산)
            Text("백령도").tag(Place.백령도)
            Text("서울").tag(Place.서울)
            Text("서산").tag(Place.서산)
            Text("서귀포").tag(Place.서귀포)
            Text("성남").tag(Place.성남)
            Text("세종").tag(Place.세종)
            }
            Group {
            Text("수원").tag(Place.수원)
            Text("순천").tag(Place.순천)
            Text("여수").tag(Place.여수)
            Text("용인").tag(Place.용인)
            Text("원주").tag(Place.원주)
            Text("울릉").tag(Place.울릉)
            Text("울산").tag(Place.울산)
            Text("익산").tag(Place.익산)
            Text("인천").tag(Place.인천)
            Text("전주").tag(Place.전주)
            }
            Group {
            Text("제주").tag(Place.제주)
            Text("창원").tag(Place.창원)
            Text("춘천").tag(Place.춘천)
            Text("파주").tag(Place.파주)
            Text("평택").tag(Place.평택)
            Text("포항").tag(Place.포항)
            Text("포천").tag(Place.포천)
            Text("통영").tag(Place.통영)
            Text("청주").tag(Place.청주)
            Text("홍천").tag(Place.홍천)
            }
            Group {
            Text("해외").tag(Place.해외)
            }
          }

          Spacer()
          Spacer()
        }
        .frame(height: base * 14)
        .padding(.horizontal, base * 3)
    }
  }

  //  var text: String
//  var image: String
}



struct RegisterView: View {

  var body: some View {
    Group {
      ScrollView {
        VStack(alignment: .leading) {
          Image("hawaii")
            .resizable()
            .aspectRatio(contentMode: .fit)

          Spacer(minLength: 40)

//          Text("출생정보등록")
//            .font(.title)
//            .bold()
//            .multilineTextAlignment(.leading)

          Divider()
            .background(.black)

          FamilynameComponent()
          Divider()
            .background(.black)

          GenderComponent()
          Divider()
            .background(.black)

          DobComponent()

          Divider()
            .background(.black)

          PlaceComponent()
        }
        .padding(.top, 10)
        .padding(.leading, 20)
        .padding(.trailing, 20)
        .padding(.bottom, 40)
      }
    }
    .navigationBarItems(
      leading: Button("취소", action: cancelRegister),
//        .foregroundColor(Colors.Accent.Content.primary),
      trailing: Button("등록", action: register)
//        .foregroundColor(
//          viewModel.canCreate
//            ? Colors.Accent.Content.primary
//            : Colors.Neutral.Content.disabled)
//        .disabled(!viewModel.canCreate))
   )
  }
}

func register() {
  RegisterInfo.obj = pendingRegisterInfo

  // store info
  let defaults = UserDefaults.standard
  defaults.setValue(RegisterInfo.obj.surName, forKey: RegisterInfoKeys.surName)
  defaults.setValue(RegisterInfo.obj.surNameHanja, forKey: RegisterInfoKeys.surNameH)
  defaults.setValue(RegisterInfo.obj.datetime, forKey: RegisterInfoKeys.dob)
  defaults.setValue(RegisterInfo.obj.gender.rawValue, forKey: RegisterInfoKeys.gender)
  defaults.setValue(RegisterInfo.obj.birthPlace.rawValue, forKey: RegisterInfoKeys.place)
  gEditCount -= 1
  defaults.setValue(String(gEditCount), forKey: RegisterInfoKeys.editCount)

  defaults.synchronize()

  // clear previously stored names
//  clearElem()


  UIApplication.shared.open(URL(string: "featuresApp://hackathon.com/headsup")!)
}

func cancelRegister() {
  UIApplication.shared.open(URL(string: "featuresApp://hackathon.com/headsup")!)
}

struct RegisterView_Previews: PreviewProvider {
    static var previews: some View {
        RegisterView()
    }
}
