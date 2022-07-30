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
    "title": "Heads Up",
    "detail": {
      "title": "Welcome to our new Heads Up feature",
      "description": "Introducing Heads Up, your one-stop messaging broadcast center so everyone can stay in the know all from the iAuditor platform. There’s no need to worry about sending that “all staff” email or posting that note on the bulletin board that people will most certainly miss. With Heads Up, you can record quick video or image-based messages and send them out to your team members at the click of a button. From here, frontline teams receive and view engaging content in a format they’re used to, all while acknowledging they understood the message. ",
      "image": "headsup_image",
      "link": "featuresApp://hackathon.com/headsup"
    }
  },
  {
    "id": 2,
    "title": "Share inspection templates via QR code",
    "detail": {
      "title": "Share inspection templates via QR code",
      "description": "Download an inspection template's unique QR code in two clicks and start getting creative on how to share it with your team. You can place the QR code within process documents, or print and display posters reminding your team to complete inspections where the work needs to get done. Team members will be able to scan it to begin an inspection immediately from any device with the iAuditor app.",
      "image": "Inspection_qr_code",
      "link": "featuresApp://hackathon.com/inspection"
    }
  },
  {
    "id": 3,
    "title": "Welcome to our new feature 'Assets'",
    "detail": {
      "title": "Welcome to our new feature 'Assets'",
      "description": "An asset inventory software is a tool utilized by companies to record, track, and maintain the performance and quality of fixed assets and intangible assets. Also called asset inventory management software, personnel responsible for asset inventory management can also use it to verify company assets lifecycle and records. With the iAuditor Asset Inventory Software, you can take advantage of free assets inventory templates to take account of assets and conduct preventive maintenance. Use iAuditor to easily determine the existence of an asset while ensuring top functionality throughout its usable life.",
      "image": "asset_image",
      "link": "featuresApp://hackathon.com/assets"
    }
  },
]

""".data(using: .utf8)
