//
//  ViewController.swift
//  singleview
//
//  Created by Park Jung Gyu on 23/09/2015.
//  Copyright © 2015 pyfamily. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    let q = ["capital?", "best?"]
    let a = ["canbarra", "Sydney"]

    var index = 0
    
    @IBOutlet weak var qButton: UILabel?
    @IBOutlet weak var aButton: UILabel?
    
    @IBAction func showQuestion(sender: UIButton) {
        index += 1
        if index == 2 {
            index = 0
        }
        qButton?.text = q[index]
    }
    @IBAction func showAnswer(sender: UIButton) {
        aButton?.text = a[index]
    }
}

