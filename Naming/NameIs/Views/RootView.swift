//
//  RootView.swift
//  NewFeatures
//
//

import SwiftUI

struct RootView: View {
  @State private var selection = 0
  @Binding var deeplinkTarget: DeeplinkTarget?
  @State private var showingSheet: Bool = false

  let loadedElem = loadElem()

  var body: some View {
    TabView(selection: $selection) {
      NavigationView {
        HomeView()
          .navigationTitle("Home")
      }.tabItem {
        if selection == 0 {
//          Image("overview_tab_selected")
//          Text("Home").font(.system(size:120))
                    Label("Home", image: "overview_tab_selected")
        } else {
          Label("Home", image: "overview_tab")
//          Image("overview_tab")
//          Text("Home").font(.system(size:120))
        }
      }.tag(0)


      NavigationView {
        SuggestedNamesView()
          .navigationTitle("이름목록")
      }.tabItem {
        if selection == 1 {
          Label("이름목록", image: "inspections_tab_selected")
        } else {
          Label("이름목록", image: "inspections_tab")
        }

      }.tag(1)

      NavigationView {
        SelfNameInputView()
          .navigationTitle("셀프작명")
      }.tabItem {
        if selection == 2 {
          Label("셀프작명", image: "actions_tab_selected")
        } else {
          Label("셀프작명", image: "actions_tab")
        }

      }.tag(2)

      NavigationView {
        RegisterView()
          .navigationTitle("출생정보등록")
      }.tabItem {
        if selection == 3 {
          Label("출생정보등록", image: "incidents_tab_selected")
        } else {
          Label("출생정보등록", image: "incidents_tab")
        }

      }.tag(3)

      NavigationView {
        MoreView()
          .navigationTitle("도움말")
      }.tabItem {
        if selection == 4 {
          Label("도움말", image: "more_tab_selected")
        } else {
          Label("도움말", image: "more_tab")
        }

      }.tag(4)
    }
    // todo: delete
    .sheet(isPresented: $showingSheet) {
      AssetsView()


    }
    // todo: delete
    .onOpenURL { url in
      let target = DeeplinkManager().manage(url: url)
      deeplinkTarget = target

      switch target {

      case .home:
        selection = 0
      case .headsup:
        selection = 0
      case .inspection:
        selection = 1
      case .issues:
        selection = 2
      case .actions:
        selection = 3
      case .assets:
        showingSheet = true
        break

      }
    }
  }
}
