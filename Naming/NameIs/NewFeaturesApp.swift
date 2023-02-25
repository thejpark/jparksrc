//
//  NewFeaturesApp.swift
//  NewFeatures
//
//  Created by Kaushal on 24/5/2022.
//

import SwiftUI
import Firebase
import GoogleMobileAds

class AppDelegate: NSObject, UIApplicationDelegate {
  func application(_ application: UIApplication,
                   didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey : Any]? = nil) -> Bool {
    print("application is starting up. ApplicationDelegate didFinishLaunchingWithOptions.")
    FirebaseApp.configure()
    GADMobileAds.sharedInstance().start(completionHandler: nil)
    return true
  }
}

@main
struct NewFeaturesApp: App {
  @State var deeplinkTarget: DeeplinkTarget?

  //https://developers.google.com/admob/ios/quick-start
  //https://firebase.google.com/docs/admob/ios/quick-start
  //https://firebase.google.com/docs/ios/learn-more#swiftui
  //https://peterfriese.dev/posts/swiftui-new-app-lifecycle-firebase/
  @UIApplicationDelegateAdaptor(AppDelegate.self) var delegate
  var body: some Scene {
    WindowGroup {
      RootView(deeplinkTarget: $deeplinkTarget)
//        .onOpenURL { url in
//          let target = DeeplinkManager().manage(url: url)
//          self.deeplinkTarget = target
//        }
    }
  }
}
