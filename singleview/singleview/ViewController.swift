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
        
        lastName.text = "성: " + self.surName + "(" + self.surNameH + ")"
        
        
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

    @IBOutlet weak var firstName: UITextField!

    var selectedDate: String = ""
    var surName: String = ""
    var surNameH: String = ""
  
    // keyboard should disappear
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
    
    
    // MARK: - Segues
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "showList" {

            let controller = segue.destinationViewController as! MasterViewController
            controller.search(surName, surNameH: surNameH, givenName: firstName.text!, selectedDate: self.selectedDate)
          
        }
    }

}

