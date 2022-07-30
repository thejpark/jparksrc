//
//  FeaturesView.swift
//  NewFeatures
//
//  Created by Kaushal on 24/5/2022.
//

import SwiftUI

struct FeaturesView: View {
  var features: [Feature] = ApiClient.fetchFeatures()

  var body: some View {
    List(features) { feat in
      NavigationLink {
        FeatureDetailView(detail: feat.detail)
      } label: {
        FeatureCellView(title: feat.title)
      }
    }.navigationTitle("New Features")
  }
}

//struct FeaturesView_Previews: PreviewProvider {
//    static var previews: some View {
//        FeaturesView()
//    }
//}
