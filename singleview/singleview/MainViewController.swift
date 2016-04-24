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
            vc.showInView("새로 등록 할까요?",  animated: true)
           
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
            let vc = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpEmpty") as! PopUpViewController
            self.addChildViewController(vc)
            self.view.addSubview(vc.view)
            vc.showInView("개인 정보를 등록하세요",  animated: true)
            
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
    
    @IBAction func clearInfo(sender: UIBarItem) {
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

    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "showTTS" {
            

        }
    }
 
    
    let male: [String] = ["민준","서준","주원","하준","예준","준우","도윤","지후","준서","지호","서진"]
    let female: [String] = ["서윤","서연","민서","지우","지민","서진","지아","지우","지유","하윤","하은","서현","지원"]
    
    @IBAction func getRecommendedNames(sender: UIButton) {
        
        // load register info
        let defaults = NSUserDefaults.standardUserDefaults()
        
        if let str = defaults.stringForKey(RegisterInfoKeys.surName) {
            self.surName = str
        }
        else {
            let vc = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpEmpty") as! PopUpViewController
            self.addChildViewController(vc)
            self.view.addSubview(vc.view)
            vc.showInView("개인 정보를 등록하세요",  animated: true)
            
            return
        }
        if let str1 = defaults.stringForKey(RegisterInfoKeys.surNameH) {
            self.surNameH = str1
        }
        if let str2 = defaults.stringForKey(RegisterInfoKeys.dob) {
            self.dob = str2
        }
        ///
        
        var objects = [AnyObject]()
        let vc = self.storyboard!.instantiateViewControllerWithIdentifier("CandidateView") as!
        MasterViewController
        
        for givenName in male {
            vc.search(surName, surNameH: surNameH, givenName: givenName, selectedDate: self.dob)
            if vc.objects.count > 0 {
                objects.append(vc.objects[0])
            }
        }
        
        if objects.count > 0 {
            vc.objects = objects
            self.showViewController(vc as MasterViewController, sender: vc)
            return
        }
        else {
            let vc2 = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpEmpty") as! PopUpViewController
            
            self.addChildViewController(vc2)
            self.view.addSubview(vc2.view)
            vc2.showInView("찾는 이름이 없습니다",  animated: true)
            return
        }
    }

}

