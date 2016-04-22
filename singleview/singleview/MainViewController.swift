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
    
    
    @IBAction func enterInfo(sender: UIButton)
    {
        let defaults = NSUserDefaults.standardUserDefaults()
        
        if let str = defaults.stringForKey(RegisterInfoKeys.surName) {
            // popup window
            
            let vc = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpView") as! PopUpViewController
            self.addChildViewController(vc)
            self.view.addSubview(vc.view)
            vc.showInView("이미 등록하셨습니다.",  animated: true)
           
        }
        else {
            let vc : AnyObject! = self.storyboard!.instantiateViewControllerWithIdentifier("RegisterView")
            self.showViewController(vc as! UIViewController, sender: vc)
        }
    }
    
    
    @IBAction func enterName(sender: UIButton) {

        // load register info
        let defaults = NSUserDefaults.standardUserDefaults()
            
        if let str = defaults.stringForKey(RegisterInfoKeys.surName) {
            self.surName = str
        }
        else {
            let vc = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpView") as! PopUpViewController
            self.addChildViewController(vc)
            self.view.addSubview(vc.view)
            vc.showInView("등록을 하셔야 합니다.",  animated: true)
            
            return
        }
        if let str1 = defaults.stringForKey(RegisterInfoKeys.surNameH) {
            self.surNameH = str1
        }
        if let str2 = defaults.stringForKey(RegisterInfoKeys.dob) {
            self.dob = str2
        }

        let vc = self.storyboard!.instantiateViewControllerWithIdentifier("EnterNameView") as!
            ViewController

        vc.surName = self.surName
        vc.surNameH = self.surNameH
        vc.selectedDate = self.dob
     
        self.showViewController(vc as UIViewController, sender: vc)
  
    }
    
    @IBAction func clearInfo(sender: UIButton) {
        let defaults = NSUserDefaults.standardUserDefaults()
        defaults.removeObjectForKey(RegisterInfoKeys.surName)
        defaults.synchronize()
        clearElem()
    }
    
    
    @IBAction func LoadSelectedNames(sender: UIButton)
    {
        if savedElements.count == 0 {
            if let s = loadElem() {
                savedElements = s
                if savedElements.count == 0 {
                    let vc2 = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpEmpty") as! PopUpViewController
                    
                    self.addChildViewController(vc2)
                    self.view.addSubview(vc2.view)
                    vc2.showInView("저장된 이름이 없습니다",  animated: true)
                    return
                }
            }
        }

        let vc = self.storyboard!.instantiateViewControllerWithIdentifier("SavedNames") as!
            SavedViewTableController
                
        vc.LoadTable()
        self.showViewController(vc as SavedViewTableController, sender: vc)
    }
}

