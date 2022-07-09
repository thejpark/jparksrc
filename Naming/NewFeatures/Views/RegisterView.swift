//
//  RegisterView.swift
//  NewFeatures
//
//  Created by Jung Gyu Park on 13/6/2022.
//

import SwiftUI

struct TextEditingView: View {
  @State private var fullText: String = ""
  let placeholderString : String = "태명을 지어주세요"

  var body: some View {
      TextEditor(text: self.$fullText)
      .onAppear(perform: {
        if self.fullText.isEmpty {
          self.fullText = placeholderString
        }
      })
      .foregroundColor(self.fullText == placeholderString ? .gray : .primary)
      .onTapGesture(perform: {
        if self.fullText == placeholderString {
            self.fullText = ""
        }})
  }
}

enum Gender: String, CaseIterable, Identifiable {
    case male, female
    var id: Self { self }
}


private let base: CGFloat = 4.0

struct FamilynameComponent: View {
  @State private var familyName: String = ""
  @State private var selectedSurnameIndex = 0

  var body: some View {
    VStack {
      Button {
//        viewModel.editPressed(action: item.action)
      } label: {
        HStack(spacing: base * 3) {
//          Image(image)
//            .frame(width: base * 6, height: base * 6)
          Text("성")
            .lineLimit(1).foregroundColor(.black)
          TextField("성을 한글로 입력하세요", text: $familyName)
//          Spacer()
          let pickerData = getLastNameFromHangul(familyName)
          if pickerData.count == 1 {
              Text(pickerData[selectedSurnameIndex])
          }
          else if pickerData.count > 1 {
            Picker("성", selection: $selectedSurnameIndex, content: {
              ForEach(0..<pickerData.count, content: {index in //
                Text(pickerData[index])
              })
            })
//            Text("Selected Surname: \(pickerData[selectedSurnameIndex])")
          }
        }
        .frame(height: base * 14)
        .padding(.horizontal, base * 3)
      }
    }
  }

//  var text: String
//  var image: String
}

struct GenderComponent: View {
  @State private var selectedGender: Gender = .male
  var body: some View {
    VStack {
      Button {
//        viewModel.editPressed(action: item.action)
      } label: {
        HStack(spacing: base * 3) {
//          Image(image)
//            .frame(width: base * 6, height: base * 6)
          Text("성별")
            .lineLimit(1).foregroundColor(.black)
//          Spacer()
          Picker("성별", selection: $selectedGender) {
            Text("여").tag(Gender.female)
            Text("남").tag(Gender.male)
          }
        }
        .frame(height: base * 14)
        .padding(.horizontal, base * 3)
      }
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
          TextEditingView()

          Divider()
            .background(.black)

          FamilynameComponent()
          Divider()
            .background(.black)

          GenderComponent()
          Divider()
            .background(.black)

        }
        .padding(.top, 10)
        .padding(.leading, 20)
        .padding(.trailing, 20)
        .padding(.bottom, 40)
      }
    }
    .navigationBarItems(
      leading: Button("취소", action: register),
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

func register() {}

struct RegisterView_Previews: PreviewProvider {
    static var previews: some View {
        RegisterView()
    }
}
