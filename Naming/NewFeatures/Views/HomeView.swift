//
//  HomeView.swift
//  NewFeatures
//
//  Created by Kaushal on 25/5/2022.
//

import SwiftUI

struct HomeView: View {
    var body: some View {
      List {
        HeadsUpCarView()
          .fixedSize(
            horizontal: false,
            vertical: true)
          .frame(height: 180)
          .listRowInsets(EdgeInsets())
      }
    }
}

struct HomeView_Previews: PreviewProvider {
    static var previews: some View {
        HomeView()
    }
}
