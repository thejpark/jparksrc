//
//  ViewController.swift
//  ledmessage
//
//  Created by Park Jung Gyu on 7/12/2015.
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
    
    
//    @IBOutlet weak var start: UIButton!
//    @IBOutlet weak var stop: UIButton!
    @IBOutlet weak var message: UILabel!
    
    
    @IBAction func startCamera(sender: AnyObject?) {
        self.message.text = "Start"
    }

    @IBAction func stopCamera(sender: AnyObject?) {
        self.message.text = "Stop"
    }
}

