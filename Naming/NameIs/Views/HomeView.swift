//
//  HomeView.swift
//  NewFeatures
//
//  Created by Kaushal on 25/5/2022.
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
          .frame(height: 220)
          .listRowInsets(EdgeInsets())
          .alert("출생정보를 등록하세요", isPresented: $showingPopover) {
            Button("OK", role: .cancel){}
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

struct HomeView_Previews: PreviewProvider {
    static var previews: some View {
        HomeView()
    }
}
