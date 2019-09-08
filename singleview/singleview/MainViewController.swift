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
    static let gender = "gender"
    static let place = "place"
    static let editCount = "editCount"
}

// I think only insane person may try
var gEditCount = 1000

class MainViewController: UIViewController {

    var surName: String = ""
    var surNameH: String = ""
    var dob: String = ""
    var gender: String = ""
    var place: String = ""

    @IBOutlet weak var settings: UIBarItem!

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.

        // load register info
        let defaults = UserDefaults.standard

        if let str = defaults.string(forKey: RegisterInfoKeys.surName) {
            self.surName = str
        }
        if let str1 = defaults.string(forKey: RegisterInfoKeys.surNameH) {
            self.surNameH = str1
        }
        if let str2 = defaults.string(forKey: RegisterInfoKeys.dob) {
            self.dob = str2
        }
        if let str2 = defaults.string(forKey: RegisterInfoKeys.gender) {
            self.gender = str2
        }
        if let str2 = defaults.string(forKey: RegisterInfoKeys.place) {
            self.place = str2
            // set timediff
            timeDiff = timeDiffMap[self.place]!
        }
        if let str2 = defaults.string(forKey: RegisterInfoKeys.editCount) {
            gEditCount = Int(str2)!
        }



/*
        self.settings.title = NSString(string: "\u{2699}") as String
        if let font = UIFont(name: "Helvetica", size: 18.0) {
            self.settings.setTitleTextAttributes([NSFontAttributeName: font], forState: UIControlState.Normal)
        }
 */

    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


    @IBAction func enterInfo(_ sender: UIButton)
    {
        let defaults = UserDefaults.standard

        if defaults.string(forKey: RegisterInfoKeys.surName) != nil {

            if let str1 = defaults.string(forKey: RegisterInfoKeys.surName) {
                self.surName = str1
            }
            if let str1 = defaults.string(forKey: RegisterInfoKeys.surNameH) {
                self.surNameH = str1
            }
            if let str2 = defaults.string(forKey: RegisterInfoKeys.dob) {
                self.dob = str2
            }
            if let str2 = defaults.string(forKey: RegisterInfoKeys.gender) {
                self.gender = str2
            }
            if let str2 = defaults.string(forKey: RegisterInfoKeys.place) {
                self.place = str2
                // set timediff
                timeDiff = timeDiffMap[self.place]!
            }


            let vc = self.storyboard!.instantiateViewController(withIdentifier: "RegisterInfoView") as! RegisterConfirmViewController

            vc.surName = self.surName
            vc.surNameH = self.surNameH
            vc.selectedDate = self.dob
            vc.gender = self.gender
            vc.place = self.place

            self.show(vc as UIViewController, sender: vc)
        }
        else {

            let vc = self.storyboard!.instantiateViewController(withIdentifier: "PopUpView") as! PopUpViewController
            self.addChild(vc)
            self.view.addSubview(vc.view)
            vc.showInView("출생 정보를 등록할까요?",  animated: true)
        }
    }


    @IBAction func enterName(_ sender: UIButton) {

        // load register info
        let defaults = UserDefaults.standard

        if let str = defaults.string(forKey: RegisterInfoKeys.surName) {
            self.surName = str
        }
        else {
            let vc = self.storyboard!.instantiateViewController(withIdentifier: "PopUpEmpty") as! PopUpViewController
            self.addChild(vc)
            self.view.addSubview(vc.view)
            vc.showInView("개인 정보를 등록하세요",  animated: true)

            return
        }
        if let str1 = defaults.string(forKey: RegisterInfoKeys.surNameH) {
            self.surNameH = str1
        }
        if let str2 = defaults.string(forKey: RegisterInfoKeys.dob) {
            self.dob = str2
        }
        if let str2 = defaults.string(forKey: RegisterInfoKeys.gender) {
            self.gender = str2
        }
        if let str2 = defaults.string(forKey: RegisterInfoKeys.place) {
            self.place = str2
            // set timediff
            timeDiff = timeDiffMap[self.place]!
        }

        let vc = self.storyboard!.instantiateViewController(withIdentifier: "EnterNameView") as!
            ViewController

        vc.surName = self.surName
        vc.surNameH = self.surNameH
        vc.selectedDate = self.dob
        vc.gender = self.gender
        vc.place = self.place

        self.show(vc as UIViewController, sender: vc)

    }

    /*
    @IBAction func clearInfo(sender: UIBarItem) {
        let defaults = NSUserDefaults.standardUserDefaults()
        defaults.removeObjectForKey(RegisterInfoKeys.surName)
        defaults.synchronize()
        clearElem()
    }
    */

    @IBAction func LoadSelectedNames(_ sender: UIBarItem)
    {
        if savedElements.count == 0 {
            if let s = loadElem() {
                savedElements = s
                if savedElements.count == 0 {
                    let vc2 = self.storyboard!.instantiateViewController(withIdentifier: "PopUpEmpty") as! PopUpViewController

                    self.addChild(vc2)
                    self.view.addSubview(vc2.view)
                    vc2.showInView("저장된 이름이 없습니다",  animated: true)
                    return
                }
            }
        }

        let vc = self.storyboard!.instantiateViewController(withIdentifier: "SavedNames") as!
            SavedViewTableController

        vc.LoadTable()
        self.show(vc as SavedViewTableController, sender: vc)
    }

    /*
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "showOhang" {


        }
        else if segue.identifier == "showTheories" {


        }

    }
 */

    let male: [String] = ["민준","서준","주원","하준","예준","준우","도윤","지후","준서","지호","서진"]
    let female: [String] = ["서윤","서연","민서","지우","지민","서진","지아","지우","지유","하윤","하은","서현","지원"]

    @IBAction func getRecommendedNames(_ sender: UIButton) {

        // load register info
        let defaults = UserDefaults.standard

        if let str = defaults.string(forKey: RegisterInfoKeys.surName) {
            self.surName = str
        }
        else {
            let vc = self.storyboard!.instantiateViewController(withIdentifier: "PopUpEmpty") as! PopUpViewController
            self.addChild(vc)
            self.view.addSubview(vc.view)
            vc.showInView("개인 정보를 등록하세요",  animated: true)

            return
        }
        if let str1 = defaults.string(forKey: RegisterInfoKeys.surNameH) {
            self.surNameH = str1
        }
        if let str2 = defaults.string(forKey: RegisterInfoKeys.dob) {
            self.dob = str2
        }
        if let str2 = defaults.string(forKey: RegisterInfoKeys.gender) {
            self.gender = str2
        }
        if let str2 = defaults.string(forKey: RegisterInfoKeys.place) {
            self.place = str2
            // set timediff
            timeDiff = timeDiffMap[self.place]!
        }

        var objects = [AnyObject]()
        let vc = self.storyboard!.instantiateViewController(withIdentifier: "CandidateView") as!
        MasterViewController

        var names:[String]
        if self.gender == "남자" {
            names = male
        }
        else {
            names = female
        }

        for givenName in names {
            vc.search(surName, surNameH: surNameH, givenName: givenName, selectedDate: self.dob)
            if vc.objects.count > 0 {
                objects.append(vc.objects[0])
            }
        }

        if objects.count > 0 {
            vc.objects = objects
            self.show(vc as MasterViewController, sender: vc)
            return
        }
        else {
            let vc2 = self.storyboard!.instantiateViewController(withIdentifier: "PopUpEmpty") as! PopUpViewController

            self.addChild(vc2)
            self.view.addSubview(vc2.view)
            vc2.showInView("찾는 이름이 없습니다",  animated: true)
            return
        }
    }

}
