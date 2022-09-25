//
//  RegisterInfo.swift
//  NewFeatures
//
//  Created by Jung Gyu Park on 9/7/2022.
//

import Foundation

enum Gender: String, CaseIterable, Identifiable {
    case male = "남"
    case female = "여"
    var id: Self { self }
}

enum Place: String, CaseIterable, Identifiable {
  case  강릉, 경주, 고양, 광주, 구미, 군산, 김천, 김해, 남양주, 대구, 대전, 동해, 목포, 부산, 백령도, 서울, 서산, 서귀포, 성남, 세종, 수원, 순천, 여수, 용인, 원주, 울산, 울릉, 인천, 익산, 전주, 제주, 창원, 청주, 춘천, 통영, 파주, 평택, 포항, 포천, 홍천, 해외
  var id: Self { self }
}

struct RegisterInfo {
  var surName: String
  var surNameHanja: String
  var gender: Gender
  var datetime: Date
  var birthPlace: Place
  var latitude: Double = 0
  var longitude: Double = 0
  static var obj = RegisterInfo(surName: "", surNameHanja: "", gender: Gender.male, datetime: Date(), birthPlace: Place.서울)
}

func getStringFromDate(_ date: Date) -> String {
  let dateFormatter : DateFormatter = DateFormatter()
  dateFormatter.dateFormat = "yyyy M d HH mm"
  return dateFormatter.string(from: date)
}

struct RegisterInfoKeys {
    static let surName = "surName"
    static let surNameH = "surNameH"
    static let dob = "dob"
    static let gender = "gender"
    static let place = "place"
    static let editCount = "editCount"
}

// I think only insane person may try
var gEditCount = 100

func loadUserInfo() -> Bool {
      // load register info
  let defaults = UserDefaults.standard

  if let str = defaults.string(forKey: RegisterInfoKeys.surName) {
      RegisterInfo.obj.surName = str
  }
  if let str1 = defaults.string(forKey: RegisterInfoKeys.surNameH) {
      RegisterInfo.obj.surNameHanja = str1
  }
  if let datetime = defaults.object(forKey: RegisterInfoKeys.dob) {
    RegisterInfo.obj.datetime = datetime as! Date
  }
  if let gender = defaults.string(forKey: RegisterInfoKeys.gender) {
    RegisterInfo.obj.gender = Gender(rawValue: gender)!
  }
  if let place = defaults.string(forKey: RegisterInfoKeys.place) {
    RegisterInfo.obj.birthPlace = Place(rawValue: place)!
      // set timediff
//          timeDiff = timeDiffMap[RegisterInfo.obj.birthPlace]!
  }
  if let str2 = defaults.string(forKey: RegisterInfoKeys.editCount) {
      gEditCount = Int(str2)!
  }

  return true
}
