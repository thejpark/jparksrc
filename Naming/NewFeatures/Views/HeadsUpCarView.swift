//
//  HeadsUpCarView.swift
//  NewFeatures
//
//  Created by Kaushal on 25/5/2022.
//

import SwiftUI

struct HeadsUpCarView: View {
    var body: some View {
      VStack(alignment: .leading) {
        Image("hawaii")
          .resizable()
          .aspectRatio(contentMode: .fill)
          .frame(height: 70)
          .padding(.all, 0)
        Spacer(minLength: 40)
        VStack(alignment: .leading) {
          Text("Sydney shipit flights info ✈️")
            .font(.subheadline)
          Text("1 week ago")
            .font(.caption)
        }.padding()
      }
    }
}

struct HeadsUpCarView_Previews: PreviewProvider {
    static var previews: some View {
        HeadsUpCarView()
    }
}
