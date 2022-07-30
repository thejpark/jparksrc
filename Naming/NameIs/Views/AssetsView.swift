//
//  AssetsView.swift
//  NewFeatures
//
//  Created by Kaushal on 25/5/2022.
//

import SwiftUI

struct AssetsView: View {
  @State var queryString: String = ""

    var body: some View {
      NavigationView {
        List {
          //AssetsRowView(title: "Truck")
          AssetsRowView(title: "Bulldozer")
          AssetsRowView(title: "Fork Lift")
          AssetsRowView(title: "Machine")
          AssetsRowView(title: "Washing machine")
          AssetsRowView(title: "Toaster")
          AssetsRowView(title: "Scooter")
          AssetsRowView(title: "Bike")
          AssetsRowView(title: "Shovel")
          AssetsRowView(title: "Ice maker")
          AssetsRowView(title: "BBQ")
          //AssetsRowView(title: "Scissor")
        }
        .navigationTitle("Assets")
      }
      .searchable(text: $queryString, placement: .navigationBarDrawer(displayMode: .always)) {

      }
    }
}

struct AssetsRowView: View {
  var title: String

  var body: some View {
    HStack {
      Image("wrench")
        .resizable()
        .frame(width: 40, height: 40)
      Text(title)
    }
  }
}
