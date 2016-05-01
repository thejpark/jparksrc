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

    @IBOutlet weak var firstName: UITextField!

    var selectedDate: String = ""
    var surName: String = ""
    var surNameH: String = ""
    var gender: String = ""
  
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
    
    
    @IBAction func checkName(sender: UIButton)
    {
        // check if name is valid or not
        var givenName: String
        
        if let s = firstName.text {
            
            givenName = s
            
            if givenName.characters.count > 0 {
                let vc = self.storyboard!.instantiateViewControllerWithIdentifier("CandidateView") as!
                MasterViewController

                vc.search(surName, surNameH: surNameH, givenName: givenName, selectedDate: self.selectedDate)
                if vc.objects.count > 0 {
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
        else {
            let vc2 = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpEmpty") as! PopUpViewController
            
            self.addChildViewController(vc2)
            self.view.addSubview(vc2.view)
            vc2.showInView("이름을 입력하세요",  animated: true)
        }
    }
}
