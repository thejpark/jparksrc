//
//  FeatureDetailView.swift
//  NewFeatures
//
//  Created by Kaushal on 24/5/2022.
//

import SwiftUI

struct FeatureDetailView: View {
  var detail: FeatureDetail

  var body: some View {
    ScrollView {
      VStack(alignment: .leading) {
        Image(detail.image ?? "")
          .resizable()
          .aspectRatio(contentMode: .fit)

        Spacer(minLength: 40)

        Text(detail.title)
          .font(.title)
          .bold()
          .multilineTextAlignment(.leading)

        Spacer(minLength: 20)

        Text(detail.description)
          .font(.body)
          .multilineTextAlignment(.leading)

        Spacer(minLength: 40)

        Link("Tap to see ↗", destination: detail.link!)
            .font(.title)

        Spacer(minLength: 80)

      }
      .padding(.top, 10)
      .padding(.leading, 20)
      .padding(.trailing, 20)
      .padding(.bottom, 40)
    }
  }
}

