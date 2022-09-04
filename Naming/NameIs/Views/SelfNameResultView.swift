//
//  SelfNameResultView.swift
//  NameIs
//
//  Created by Jung Gyu Park on 13/8/2022.
//

import SwiftUI


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
