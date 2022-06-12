//
//  DeeplinkManager.swift
//  NewFeatures
//
//  Created by Kaushal on 25/5/2022.
//

import Foundation

class DeepLinkConstants {
  static let scheme = "featuresApp"
  static let host = "hackathon.com"
  //static let detailsPath = "/details"
  //static let query = "id"
}

enum DeeplinkTarget: Equatable {
  case home
  case headsup
  case inspection
  case issues
  case actions
  case assets
}

class DeeplinkManager {
  func manage(url: URL) -> DeeplinkTarget {
    guard url.scheme == DeepLinkConstants.scheme,
          url.host == DeepLinkConstants.host
          //let components = URLComponents(url: url, resolvingAgainstBaseURL: true),
          //let queryItems = components.queryItems
    else { return .home }


    switch url.path {
    case "/headsup":
      return .headsup
    case "/inspection":
      return .inspection
    case "/issues":
      return .issues
    case "/actions":
      return .actions
    case "/assets":
      return .assets
    default:
      return .home
    }

//    let query = queryItems.reduce(into: [String: String]()) { (result, item) in
//        result[item.name] = item.value
//    }
//
//    guard let id = query[DeepLinkConstants.query] else { return .home }
//
//    return .details(reference: id)
  }
}
