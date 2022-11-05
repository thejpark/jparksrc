//
//  HomeView.swift
//  NewFeatures
//

import SwiftUI

struct HomeView: View {
  @State private var showingPopover = false

    var body: some View {
      ScrollView {
        HeadsUpCarView()
          .fixedSize(
            horizontal: false,
            vertical: true)
//          .frame(height: 220)
//          .listRowInsets(EdgeInsets())
          .padding(.top, 40)
          .padding(.leading, 60)
          .padding(.trailing, 60)
          .padding(.bottom, 60)
          .alert("출생정보를 등록하세요!", isPresented: $showingPopover) {
            Button("OK"){
              gotoRegister()
            }
          }
          //todo: text saju info
      }.onAppear() {
        showingPopover = RegisterInfo.obj.surName == "" || RegisterInfo.obj.surNameHanja == ""
      }
//        Text("Names")
//          .font(.title)
//          .bold()
//          .multilineTextAlignment(.leading)
//        List(names) { name in
//          NavigationLink {
//            NameDetailView(elem: name)
//          } label: {
//            FeatureCellView(title: name.desc())
//          }
//        }.onAppear() {
//            names = savedElements
//          }
    }
}

func gotoRegister() {
  UIApplication.shared.open(URL(string: "featuresApp://hackathon.com/actions")!)
}

struct HomeView_Previews: PreviewProvider {
    static var previews: some View {
        HomeView()
    }
}
