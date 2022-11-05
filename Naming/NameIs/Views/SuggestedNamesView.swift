//
//  SuggestedNames.swift
//  NameIs
//
//  Created by Jung Gyu Park on 4/9/2022.
//

import SwiftUI


struct SuggestedNamesView: View {
  @State var names: [Elem] = [Elem]()
  @State private var showingPopover = false

  var body: some View {
    List {
      ForEach(names) {name in
      NavigationLink {
        SavedNamesView(elem: name)
      } label: {
        FeatureCellView(title: name.desc())
      }
    }
    .onDelete(perform: delete)
    }
    .onAppear() {
      names = savedElements
      showingPopover = names.isEmpty
    }
    .alert("저장된 이름이 없습니다.", isPresented: $showingPopover) {
      Button("OK", role: .cancel){}
    }
  }

  func delete(at offsets: IndexSet) {
    names.remove(atOffsets: offsets)
    savedElements.remove(atOffsets: offsets)
    saveElem()
  }
}
