//
//  BorderedButton.swift
//  BabyName
//
//  Created by Park Jung Gyu on 15/04/2016.
//  Copyright © 2016 pyfamily. All rights reserved.
//


import UIKit

class BorderedButton: UIButton {
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        layer.borderWidth = 1.0
        layer.borderColor = tintColor.cgColor
        layer.cornerRadius = 5.0
        clipsToBounds = true
        contentEdgeInsets = UIEdgeInsets(top: 8, left: 8, bottom: 8, right: 8)
        setTitleColor(tintColor, for: UIControlState())
        setTitleColor(UIColor.white, for: .highlighted)
    }
}

class RoundedLabel: UILabel {
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        self.layer.masksToBounds = true
        self.layer.cornerRadius = 5
    }
}

class RoundedBorderLabel: UILabel {
        required init?(coder aDecoder: NSCoder) {
            super.init(coder: aDecoder)
            self.layer.masksToBounds = true
            self.layer.cornerRadius = 5
            self.layer.borderWidth = 1.0
        }
}
