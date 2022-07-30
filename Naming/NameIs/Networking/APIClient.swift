//
//  APIClient.swift
//  NewFeatures
//
//  Created by Kaushal on 24/5/2022.
//

import Foundation

class ApiClient {
  static func fetchFeatures() -> [Feature] {
    do {
      let features = try JSONDecoder().decode([Feature].self, from: featuresData!)
      return features
    } catch {
      return []
    }
  }
}


