//
//  NewFeaturesApp.swift
//  NewFeatures
//
//  Created by Kaushal on 24/5/2022.
//

import SwiftUI

@main
struct NewFeaturesApp: App {
  @State var deeplinkTarget: DeeplinkTarget?

  var body: some Scene {
    let result = loadUserInfo()
    WindowGroup {
      RootView(deeplinkTarget: $deeplinkTarget)
//        .onOpenURL { url in
//          let target = DeeplinkManager().manage(url: url)
//          self.deeplinkTarget = target
//        }
    }
  }
}
