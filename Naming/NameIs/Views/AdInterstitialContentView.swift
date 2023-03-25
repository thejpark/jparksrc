//
//  AdInterstitialContentView.swift
//  NameIs
//
//  Created by Jung Gyu Park on 19/3/2023.
//

import GoogleMobileAds
import SwiftUI

// MARK: - Helper to present Interstitial Ad
struct AdViewControllerRepresentable: UIViewControllerRepresentable {
  let viewController = UIViewController()

  func makeUIViewController(context: Context) -> some UIViewController {
    return viewController
  }

  func updateUIViewController(_ uiViewController: UIViewControllerType, context: Context) {}
}

class InterstitialAdCoordinator: NSObject, GADFullScreenContentDelegate {
  private var interstitial: GADInterstitialAd?

  func loadAd() {
    // for Production
     let adUnitID = "ca-app-pub-3867377628219243/5803068357"
    // for Testing
//    let adUnitID = "ca-app-pub-3940256099942544/4411468910"
    GADInterstitialAd.load(
      withAdUnitID: adUnitID, request: GADRequest()
    ) { ad, error in
      self.interstitial = ad
      self.interstitial?.fullScreenContentDelegate = self
    }
  }

  func adDidDismissFullScreenContent(_ ad: GADFullScreenPresentingAd) {
    interstitial = nil
  }

  func showAd(from viewController: UIViewController) {
    guard let interstitial = interstitial else {
      return print("Ad wasn't ready")
    }

    interstitial.present(fromRootViewController: viewController)
  }
}
