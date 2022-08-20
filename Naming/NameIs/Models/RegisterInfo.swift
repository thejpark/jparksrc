//
//  RegisterInfo.swift
//  NewFeatures
//
//  Created by Jung Gyu Park on 9/7/2022.
//

import Foundation

struct RegisterInfo {
  var lastName: String
  var lastNameHanja: String
  var gender: Gender
  var datetime: Date
  var birthPlace: Place
  static var obj = RegisterInfo(lastName: "", lastNameHanja: "", gender: Gender.male, datetime: Date(), birthPlace: Place.서울)
}


