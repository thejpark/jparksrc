//
//  NameDetailView.swift
//  NameIs
//
//  Created by Jung Gyu Park on 13/8/2022.
//

import SwiftUI

struct NameDetailView: View {
  var elem: Elem

  var body: some View {
    Group {
    ScrollView {
      VStack(alignment: .leading) {
//        Image(detail.image ?? "")
//          .resizable()
//          .aspectRatio(contentMode: .fit)

//        Spacer(minLength: 40)
        let title = elem.desc()
        let saju = elem.getSaju()
        let dob = elem.getDob()
        let ilgangangyag = elem.getIlganGangYag()
        let heeyong = elem.getHeeYong()
        let jawonohang = elem.getJaWonOHang() + "사주의 부족한 오행을 보충합니다"
        let umyang = elem.getUmYang() + "음(짝수) 양(홀수) 조화를 이룹니다"
        let barumEnd = elem.isBarumInHeeYong() ? "이며 사주에 부족한 오행을 보충합니다" : "입니다"
        let barum = elem.getBarumOhang() + barumEnd

        Text(title)
          .font(.title)
          .bold()
          .multilineTextAlignment(.leading)

        Spacer(minLength: 20)

        Text(saju)
          .font(.body)
          .multilineTextAlignment(.leading)
        Text(dob)
          .font(.body)
          .multilineTextAlignment(.leading)
        Text(ilgangangyag)
          .font(.body)
          .multilineTextAlignment(.leading)
        Text(heeyong)
          .font(.body)
          .multilineTextAlignment(.leading)
        Text(jawonohang)
          .font(.body)
          .multilineTextAlignment(.leading)
        Text(umyang)
          .font(.body)
          .multilineTextAlignment(.leading)
        Text(barum)
          .font(.body)
          .multilineTextAlignment(.leading)

        Spacer(minLength: 40)

//        Link("Tap to see ↗", destination: detail.link!)
//            .font(.title)
//
//        Spacer(minLength: 80)

      }
      .padding(.top, 10)
      .padding(.leading, 20)
      .padding(.trailing, 20)
      .padding(.bottom, 40)
    }
    }
    .navigationBarItems(
      trailing: Button("저장", action: elem.save)
   )
}
}
