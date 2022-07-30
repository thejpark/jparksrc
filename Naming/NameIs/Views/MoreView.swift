//
//  MoreView.swift
//  NewFeatures
//
//  Created by Kaushal on 24/5/2022.
//

import SwiftUI

struct MoreView: View {
    var body: some View {
      NavigationView {
        List {
          Section {
            NavigationLink {
              FeaturesView()
            } label: {
              Label("New Features", image: "red-new")
            }
            Label("Sensors", image: "more_menu_sensors_icon")
            Label("Assets", image: "more_menu_assets_icon")
            Label("Analytics", image: "more_menu_analytics_icon")
            Label("Public template library", image: "more_menu_public_library_icon")
            Label("Refer iAuditor", image: "more_menu_refer_iauditor_icon")
            Label("Heads Up", image: "more_menu_heads_up_icon")

          }

          Section("Account") {
            Text("Settings")
            Text("Logout")
          }
        }
        .listStyle(.grouped)
      }
      .navigationTitle("More")
    }
}

struct MoreView_Previews: PreviewProvider {
    static var previews: some View {
        MoreView()
    }
}
