//
//  AdBannerView.swift
//  NameIs
//
//  Created by Jung Gyu Park on 26/2/2023.
//

import SwiftUI
import GoogleMobileAds
//https://developers.google.com/admob/ios/swiftui

// Delegate methods for receiving width update messages.
protocol BannerViewControllerWidthDelegate: AnyObject {
  func bannerViewController(_ bannerViewController: BannerViewController, didUpdate width: CGFloat)
}

class BannerViewController: UIViewController {
  weak var delegate: BannerViewControllerWidthDelegate?

  override func viewDidAppear(_ animated: Bool) {
    super.viewDidAppear(animated)

    // Tell the delegate the initial ad width.
    delegate?.bannerViewController(
      self, didUpdate: view.frame.inset(by: view.safeAreaInsets).size.width)
  }

  override func viewWillTransition(
    to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator
  ) {
    coordinator.animate { _ in
      // do nothing
    } completion: { _ in
      // Notify the delegate of ad width changes.
      self.delegate?.bannerViewController(
        self, didUpdate: self.view.frame.inset(by: self.view.safeAreaInsets).size.width)
    }
  }
}

struct BannerView: UIViewControllerRepresentable {
  @State private var viewWidth: CGFloat = .zero
  private let bannerView = GADBannerView(adSize: GADAdSizeBanner)
  // this is for production
  private let adUnitID = "ca-app-pub-3867377628219243/3496030873"
  // this is for testing
//  private let adUnitID = "ca-app-pub-3940256099942544/2934735716"

  func makeUIViewController(context: Context) -> some UIViewController {
    let bannerViewController = BannerViewController()
    bannerView.adUnitID = adUnitID
    bannerView.rootViewController = bannerViewController
    bannerView.delegate = context.coordinator
    bannerViewController.view.addSubview(bannerView)

    // Tell the bannerViewController to update our Coordinator when the ad
    // width changes.
    bannerViewController.delegate = context.coordinator

    return bannerViewController
  }

  func makeCoordinator() -> Coordinator {
    Coordinator(self)
  }

  internal class Coordinator: NSObject, BannerViewControllerWidthDelegate, GADBannerViewDelegate {
    let parent: BannerView

    init(_ parent: BannerView) {
      self.parent = parent
    }

    // MARK: - BannerViewControllerWidthDelegate methods

    func bannerViewController(_ bannerViewController: BannerViewController, didUpdate width: CGFloat) {
      // Pass the viewWidth from Coordinator to BannerView.
      parent.viewWidth = width
    }
    // MARK: - GADBannerViewDelegate methods
    func bannerViewDidReceiveAd(_ bannerView: GADBannerView) {
      print("DID RECEIVE AD")
    }

    func bannerView(_ bannerView: GADBannerView, didFailToReceiveAdWithError error: Error) {
      print("DID NOT RECEIVE AD: \(error.localizedDescription)")
    }
  }

  func updateUIViewController(_ uiViewController: UIViewControllerType, context: Context) {
    // Request a banner ad with the updated viewWidth.
    if viewWidth != .zero {
      bannerView.adSize = GADCurrentOrientationAnchoredAdaptiveBannerAdSizeWithWidth(viewWidth)
    }
    let request = GADRequest()
    request.scene = UIApplication.shared.connectedScenes.first as? UIWindowScene
    bannerView.load(request)
  }
}

struct AdBannerView: View {

  var body: some View {
    BannerView()
  }
}
