//
//  SuggestedNames.swift
//  NameIs
//
//  Created by Jung Gyu Park on 4/9/2022.
//

import SwiftUI


struct SuggestedNamesView: View {
  @State var names: [Elem] = [Elem]()

  var body: some View {
    List {
      ForEach(names) {name in
      NavigationLink {
        NameDetailView(elem: name)
      } label: {
        FeatureCellView(title: name.desc())
      }
    }
    .onDelete(perform: delete)
    }
      .onAppear() {
        names = savedElements
      }
  }

  func delete(at offsets: IndexSet) {
    names.remove(atOffsets: offsets)
    savedElements.remove(atOffsets: offsets)
    saveElem()
  }
}
