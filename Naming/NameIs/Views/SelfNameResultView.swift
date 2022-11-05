//
//  SelfNameResultView.swift
//  NameIs
//
//  Created by Jung Gyu Park on 13/8/2022.
//

import SwiftUI


struct SelfNameResultView: View {
  @State private var showingPopover = false
  @State var names: [Elem] = [Elem]()

  var body: some View {
    List(names) { name in
      NavigationLink {
        NameDetailView(elem: name)
      } label: {
        FeatureCellView(title: name.desc())
      }
    }.navigationTitle("Search Results")
      .onAppear() {
        names = Search.obj.getNames()
        showingPopover = names.isEmpty
      }
      .alert("찾는 이름이 없습니다", isPresented: $showingPopover) {
        Button("OK", role: .cancel){}
      }
  }
}

struct SelfNameResultView_Previews: PreviewProvider {
    static var previews: some View {
        SelfNameResultView()
    }
}
