//
//  RegisterConfirmViewController.swift
//  BabyName
//
//  Created by Park Jung Gyu on 12/04/2016.
//  Copyright © 2016 pyfamily. All rights reserved.
//

import UIKit

class RegisterConfirmViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        lastName.text = "성: " + self.surName + "(" + self.surNameH + ")  성별: " + self.gender
        birthPlace.text = "출생지: " + place
        
        // set date and time of birth
        var str = self.selectedDate.components(separatedBy: " ")
        
        DOB.text = "생년월일: " + str[2] + "년" + str[1] + "월" + str[0] + "일 " + str[3] + ":" + str[4]
        
        
        self.day = Int(str[0])!
        self.month = Int(str[1])!
        self.year = Int(str[2])!
        self.hour = Int(str[3])!
        self.minute = Int(str[4])!
        saju.text = "사주(시일월년): " + getSaju(self.year, month:self.month, day:self.day, hour:self.hour, minute:self.minute)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBOutlet weak var lastName: UILabel!
    @IBOutlet weak var birthPlace: UILabel!
    @IBOutlet weak var DOB: UILabel!
    @IBOutlet weak var saju: UILabel!

    
    var day: Int = 0
    var month: Int = 0
    var year: Int = 0
    var hour: Int = 0
    var minute: Int = 0
    var selectedDate: String = ""
    var surName: String = ""
    var surNameH: String = ""
    var gender: String = ""
    var place: String = ""

    
 /*
    @IBAction func goback(sender: UIButton)
    {
        navigationController?.popViewControllerAnimated(true)
    }

    @IBAction func storeInfo(sender: UIButton)
    {
        // store info
        let defaults = NSUserDefaults.standardUserDefaults()
        defaults.setValue(surName, forKey: RegisterInfoKeys.surName)
        defaults.setValue(surNameH, forKey: RegisterInfoKeys.surNameH)
        defaults.setValue(selectedDate, forKey: RegisterInfoKeys.dob)
        defaults.synchronize()
        
        navigationController?.popToRootViewControllerAnimated(true)
    }
  */
    @IBAction func registerInfo(_ sender: UIBarButtonItem)
    {
        if (gEditCount > 0)
        {
            let vc = self.storyboard!.instantiateViewController(withIdentifier: "PopUpView") as! PopUpViewController
            self.addChildViewController(vc)
            self.view.addSubview(vc.view)
            vc.showInView("새로 등록 할까요?",  animated: true)
        }
        else
        {
            let vc2 = self.storyboard!.instantiateViewController(withIdentifier: "PopUpEmpty") as! PopUpViewController
            
            self.addChildViewController(vc2)
            self.view.addSubview(vc2.view)
            vc2.showInView("한도 초과 입니다",  animated: true)
            return
        }
    }

}
