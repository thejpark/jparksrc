//
//  MainViewController.swift
//  BabyName
//
//  Created by Park Jung Gyu on 10/04/2016.
//  Copyright © 2016 pyfamily. All rights reserved.
//

import UIKit

struct RegisterInfoKeys {
    static let surName = "surName"
    static let surNameH = "surNameH"
    static let dob = "dob"
}

class MainViewController: UIViewController {
    
    var surName: String = ""
    var surNameH: String = ""
    var dob: String = ""
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        // load register info
        let defaults = NSUserDefaults.standardUserDefaults()
        
        if let str = defaults.stringForKey(RegisterInfoKeys.surName) {
            self.surName = str
        }
        if let str1 = defaults.stringForKey(RegisterInfoKeys.surNameH) {
            self.surNameH = str1
        }
        if let str2 = defaults.stringForKey(RegisterInfoKeys.dob) {
            self.dob = str2
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    // MARK: - Segues
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "enterInfo" {
            
            let controller = segue.destinationViewController as! RegisterViewController
            controller.m_parent = self
        }
        else if segue.identifier == "enterName" {
            let controller = segue.destinationViewController as! ViewController
            controller.surName = self.surName
            controller.surNameH = self.surNameH
            controller.selectedDate = self.dob
        }
    }
}

