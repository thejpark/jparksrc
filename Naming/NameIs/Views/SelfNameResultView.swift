//
//  SelfNameResultView.swift
//  NameIs
//
//  Created by Jung Gyu Park on 13/8/2022.
//

import SwiftUI

fileprivate func search() {
//  Search.obj.search(surName: RegisterInfo.obj.lastName,
//                          surNameH: RegisterInfo.obj.lastNameHanja,
//                          givenName: pendingHangulName,
//                          selectedDate: RegisterInfo.obj.datetime,
//                          birthPlace: RegisterInfo.obj.birthPlace)
}

struct SelfNameResultView: View {
//  var names: [Elem] = Search.obj.getNames()

  var body: some View {
    List(Search.obj.getNames()) { name in
      NavigationLink {
        NameDetailView(elem: name)
      } label: {
        FeatureCellView(title: name.desc())
      }
    }.navigationTitle("Names")
  }
}
