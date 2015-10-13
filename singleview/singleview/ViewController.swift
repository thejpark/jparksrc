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

    @IBOutlet weak var a: UILabel?
    @IBOutlet weak var b: UILabel?
    @IBOutlet weak var lastName: UITextField!
    @IBOutlet weak var firstName: UITextField!
    
    @IBAction func showAnswer(sender: UIButton) {
        a?.text = lastName.text
        b?.text = firstName.text
    }
}

