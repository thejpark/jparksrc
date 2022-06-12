//
//  NewFeaturesTests.swift
//  NewFeaturesTests
//
//  Created by Kaushal on 24/5/2022.
//

import XCTest
@testable import NewFeatures

class NewFeaturesTests: XCTestCase {

  func test_fetchFeatures() {
    let expectation = XCTestExpectation(description: "decoding")
    ApiClient.fetchFeatures { result in
      expectation.fulfill()
    }

    waitForExpectations(timeout: 10)
  }

}
