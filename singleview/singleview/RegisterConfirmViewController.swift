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
        
        
        // set date and time of birth
        var str = self.selectedDate.componentsSeparatedByString(" ")
        
        DOB.text = "생년월일: " + str[2] + "년" + str[1] + "월" + str[0] + "일 " + str[3] + ":" + str[4]
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBOutlet weak var lastName: UILabel!
    @IBOutlet weak var DOB: UILabel!

    
    var selectedDate: String = ""
    var surName: String = ""
    var surNameH: String = ""
    var gender: String = ""
    
    
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

}
