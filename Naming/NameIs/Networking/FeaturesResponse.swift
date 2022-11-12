//
//  FeaturesResponse.swift
//  NewFeatures
//
//  Created by Kaushal on 24/5/2022.
//

import Foundation


let featuresData =
"""
[
  {
    "id": 1,
    "title": "우선 출생정보를 등록하세요",
    "detail": {
      "title": "우선 출생정보를 등록하세요",
      "description": "아이의 성과 생년월일 등의 기본 정보를 등록하세요. 복성은 성의 음을 한글 (예: 남궁)로 입력 한 후 한자 선택은 복성의 첫 번째 한자 (예: 南)를 선택하시면 됩니다. 출생지역은 인근 도시의 위도와 경도를 이용하여 설정할 수 있습니다. 태어난 시간은 썸머타임이 아닌 원래의 시간을 사용합니다.",
      "image": "headsup_image",
      "link": "featuresApp://hackathon.com/headsup"
    }
  },
 {
    "id": 2,
    "title": "셀프작명 메뉴로 작명하세요",
    "detail": {
      "title": "셀프작명 메뉴로 작명하세요" ,
      "description": "셀프작명은 원하는 한글 이름을 이용하여 사주에 적합한 한자 이름을 조합해 줍니다. 한글 이름을 입력하신 후 '찾기' 버튼을 누르면 적합한 한자 이름을 찾을 수 있습니다. 한글 이름을 입력하지 않고 '찾기'버튼을 누르면, 요즘 인기있는 한글 이름 중에서 사주에 적합한 한자 이름 조합을 제공합니다. 이름 작성 중 마음에 드는 이름이 있으면 저장 메뉴를 선택하여 저장하고, 저장목록 메뉴를 선택하여 확인할 수 있습니다. 대법원 인명 용 한자중에서 일반적으로 사용되는 6000자를 이용하였습니다. 한글 이름의 표준 영어 표기와 발음을 제공합니다. 영문이름을 지을 경우 활용하시면 됩니다.",
      "image": "Inspection_qr_code",
      "link": "featuresApp://hackathon.com/inspection"
    }
  },
  {
    "id": 3,
    "title": "글로벌 작명법",
    "detail": {
      "title": "글로벌 작명법",
      "description": "한국 이름 중에서는 외국 사람들이 발음하기 힘든 이름들이 있습니다. '수현' 처럼 '현' 자가 들어간 이름은 영어를 사용하는 외국인들이 발음하기 힘듭니다. 현을 Hyun이라고 쓰면 '하이언' 처럼 발음하게 됩니다. '혁'도 마찬가지로 어려운데, 쉽게 '척' 이라고 발음 하기도 합니다. 또한, '재석'의 '석'자는 영어로 발음하기에 매우 조심스러운 글자 입니다. 일본인들은 'ㅁ' 받침을 발음하기 힘들어 합니다. 외국인들이 발음하기에 쉬운 이름은 다음과 같은 특징이 있습니다. 우선 모음이 간단해야 합니다. '아', '오', '우', '이' 정도가 쉬운데, 복모음의 경우 외국인들이 발음하기 힘들어 하는 경우가 많습니다. 여자의 경우 '은'을 많이 사용하는데, 이것 역시 발음하기 힘든 모음 입니다. 받침은 없는 것이 좋지만, 'ㄴ' 은 괜찮습니다. 'ㅇ' 과 'ㄱ' 받침은 발음하기 힘든 경우가 많습니다. '승' 이나 '정', '혁' 등의 예가 있습니다. 발음 이외에도 요즘 작명을 할 때 고려해야 할 것이 있는데, 너무 복잡한 한자는 피하는게 좋다는 것입니다. 복잡한 한자중에서 중국, 일본, 대만, 홍콩 등에서는 사용 되지 않는 글자들도 많기 때문입니다.",
      "image": "asset_image",
      "link": "featuresApp://hackathon.com/assets"
    }
  },
  {
    "id": 4,
    "title": "작명은 음양과 오행을 주로 이용합니다",
    "detail": {
      "title": "작명은 음양과 오행을 주로 이용합니다",
      "description": "오늘날 이름학에서 가장 중요하게 고려하는 내용은 음양과 오행입니다. 음양은 글자 획수의 음양을 고려할 수 있는데, 이름의 획수가 전부 음(짝수)이 되거나 양(홀수)이 되지 않고 조화되어야 합니다. 획수는 원획 (부수의 원획)을 사용합니다. 오행은 글자의 뜻의 오행 (자원오행)과 발음의 오행 (발음오행)을 고려할 수 있는데, 사주에서 부족한 오행을 이름의 뜻이나 발음을 통해서 보충하려는 것입니다. 자원오행은 한자를 그 뜻에 따라서 오행 (木, 火, 土, 金, 水)으로 분류한 후 작명에 사용하며, 발음오행은 한글 자음과 모음으로 오행을 분류하여 작명에 사용합니다. 예를 들어, 在錫(재석) 이라는 이름의 자원 오행은 土와 金이 되며 발음 오행은 金과 金이 됩니다. 사주에서 土와 金이 부족한 경우에 좋은 이름이 될 수 있으나, 반대로 土와 金이 많을 경우에는 좋지 않은 이름입니다.",
      "image": "asset_image",
      "link": "featuresApp://hackathon.com/assets"
    }
  },
  {
    "id": 5,
    "title": "발음오행은 참고로 사용하세요",
    "detail": {
      "title": "발음오행은 참고로 사용하세요",
      "description": "한글의 자음 소리에 따라서 오행 (木, 火, 土, 金, 水)으로 분류할 수 있습니다. 예를 들면 'ㄱ'과 'ㅋ'은 木, 'ㅅ'과 'ㅈ'은 金이 됩니다. 본 app에서는 음양과 자원오행을 기준으로 작명을 하되, 발음오행은 참고로 사용합니다. 발음이 중요하기는 하나, 순수 한글 이름이 아닌 이상 글자의 뜻 이 더 중요하다는 것이 저자의 견해입니다. 하지만 만약 자원오행을 기준으로 만족할만한 이름을 찾을 수 없다면 발음오행을 고려해 볼 수 있다고 봅니다.",
      "image": "asset_image",
      "link": "featuresApp://hackathon.com/assets"
    }
  },
  {
    "id": 6,
    "title": "고려하지 않은 작명 이론들",
    "detail": {
      "title": "고려하지 않은 작명 이론들",
      "description": "수리오행, 81수리, 그리고 삼원오행 등은 근거가 없는 것으로 알려져 있으며, 오히려 나쁜 이름을 좋은 이름으로 만들 수 있어서 본 app에서는 고려하지 않도록 하였습니다.",
      "image": "asset_image",
      "link": "featuresApp://hackathon.com/assets"
    }
  },
{
    "id": 7,
    "title": "영어 이름 듣기",
    "detail": {
      "title": "영어 이름 듣기",
      "description": "영어 이름 듣기 (Tap to listen)를 선택해도 아무 소리가 나오지 않으면, 진동 모두 (silent mode)를 해제한 후 다시 선택해 보세요.",
      "image": "asset_image",
      "link": "featuresApp://hackathon.com/assets"
    }
  },
]

""".data(using: .utf8)