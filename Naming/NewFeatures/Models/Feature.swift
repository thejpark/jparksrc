//
//  Feature.swift
//  NewFeatures
//
//  Created by Kaushal on 24/5/2022.
//

import Foundation

struct Feature: Decodable, Identifiable {
  let id: Int
  let title: String
  let detail: FeatureDetail
}

struct FeatureDetail: Decodable {
  let title: String
  let description: String
  let image: String?
  let link: URL?
}
