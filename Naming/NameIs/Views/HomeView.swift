//
//  HomeView.swift
//  NewFeatures
//
//  Created by Kaushal on 25/5/2022.
//

import SwiftUI

struct HomeView: View {
//  @State var names: [Elem] = [Elem]()

    var body: some View {
      ScrollView {
        HeadsUpCarView()
          .fixedSize(
            horizontal: false,
            vertical: true)
          .frame(height: 220)
          .listRowInsets(EdgeInsets())
          //todo: text saju info
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
