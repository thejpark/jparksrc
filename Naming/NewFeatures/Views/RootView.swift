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

  var body: some View {
    TabView(selection: $selection) {
      NavigationView {
        HomeView()
          .navigationTitle("출생정보")
      }.tabItem {
        if selection == 0 {
          Label("Home", image: "overview_tab_selected")
        } else {
          Label("Home", image: "overview_tab")
        }
      }.tag(0)


      NavigationView {
        EmptyView()
          .navigationTitle("추천작명")
      }.tabItem {
        if selection == 1 {
          Label("추천작명", image: "inspections_tab_selected")
        } else {
          Label("추천작명", image: "inspections_tab")
        }

      }.tag(1)

      NavigationView {
        EmptyView()
          .navigationTitle("셀프작명")
      }.tabItem {
        if selection == 2 {
          Label("셀프작명", image: "actions_tab_selected")
        } else {
          Label("셀프장명", image: "actions_tab")
        }

      }.tag(2)

      NavigationView {
        RegisterView()
          .navigationTitle("등록")
      }.tabItem {
        if selection == 3 {
          Label("등록", image: "incidents_tab_selected")
        } else {
          Label("등록", image: "incidents_tab")
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
