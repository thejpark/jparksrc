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

struct RegisterInfo {
  var surName: String
  var surNameHanja: String
  var gender: Gender
  var datetime: Date
  var birthPlace: String
  var latitude: Double = 0
  var longitude: Double = 0
  var image: Data?
  static var obj = RegisterInfo(surName: "", surNameHanja: "", gender: Gender.male, datetime: Date(), birthPlace: "서울")
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
    static let latitude = "latitude"
    static let longitude = "longitude"
    static let image = "image"
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
    RegisterInfo.obj.birthPlace = place
  }

  RegisterInfo.obj.latitude = defaults.double(forKey: RegisterInfoKeys.latitude)
  RegisterInfo.obj.longitude = defaults.double(forKey: RegisterInfoKeys.longitude)

  if let image = defaults.object(forKey: RegisterInfoKeys.image) as? Data {
    RegisterInfo.obj.image = image
  }
  if let str2 = defaults.string(forKey: RegisterInfoKeys.editCount) {
      gEditCount = Int(str2)!
  }

  return true
}
