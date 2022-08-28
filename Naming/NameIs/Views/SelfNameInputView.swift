//
//  SelfNameInput.swift
//  NameIs
//
//  Created by Jung Gyu Park on 31/7/2022.
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

struct HangulNameComponent: View {
  @State private var hangulName: String = ""

  var body: some View {
//    VStack {
//      Button {
//        viewModel.editPressed(action: item.action)
//      } label: {

      HStack(spacing: base * 3) {
//          Image(image)
//            .frame(width: base * 6, height: base * 6)
          Text("이름")
            .lineLimit(1).foregroundColor(.black)
          Spacer()
          Spacer()
          TextField("이름을 한글로 입력하세요", text: $hangulName)
            .lineLimit(1).foregroundColor(.blue)
            .onChange(of: hangulName) {
              onChangeHangulName(n: $0)
            }

          Spacer()
        }
        .frame(height: base * 14)
        .padding(.horizontal, base * 3)
//      }
//    }
  }

//  var text: String
//  var image: String
}

func onChangeHangulName(n: String) -> String {
  Search.obj.setName(name: n)
  return n
}


struct SelfNameInputView: View {

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

          HangulNameComponent()
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
      leading: Button("취소", action: cancelSearch),
//        .foregroundColor(Colors.Accent.Content.primary),
      trailing: NavigationLink("찾기", destination: SelfNameResultView()) //{
//      }.simultaneousGesture { search() } //.onAppear {search()})
//        Text("찾기").onTapGesture { search() }
//      }

//      }.onTapGesture { search() } //.onAppear {search()})
      //        .foregroundColor(
//          viewModel.canCreate
//            ? Colors.Accent.Content.primary
//            : Colors.Neutral.Content.disabled)
//        .disabled(!viewModel.canCreate))
   )
  }
}

func cancelSearch() {
}

struct SelfNameInputView_Previews: PreviewProvider {
    static var previews: some View {
        SelfNameInputView()
    }
}
