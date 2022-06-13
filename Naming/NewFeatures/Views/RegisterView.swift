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

struct RegisterView: View {

  var body: some View {
    Group {
      ScrollView {
        VStack(alignment: .leading) {
          Image("hawaii")
            .resizable()
            .aspectRatio(contentMode: .fit)

          Spacer(minLength: 40)

          Text("출생정보등록")
            .font(.title)
            .bold()
            .multilineTextAlignment(.leading)

          Divider()
            .background(.black)
          TextEditingView()

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
