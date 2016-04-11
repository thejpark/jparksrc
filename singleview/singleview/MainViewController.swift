//
//  MainViewController.swift
//  BabyName
//
//  Created by Park Jung Gyu on 10/04/2016.
//  Copyright © 2016 pyfamily. All rights reserved.
//

import UIKit

class MainViewController: UIViewController {
    
    var surName: String = ""
    var surNameH: String = ""
    var dob: String = ""
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
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

