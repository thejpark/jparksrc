//
//  RegisterChildren.swift
//  BabyName
//
//  Created by Park Jung Gyu on 9/04/2016.
//  Copyright © 2016 pyfamily. All rights reserved.
//

import UIKit

class RegisterViewController: UIViewController, UIPickerViewDelegate, UIPickerViewDataSource, UITextFieldDelegate {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        pickerData = getHanjaFromHangul("이")
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBOutlet weak var lastName: UITextField!
    @IBOutlet weak var picker: UIPickerView!
    @IBOutlet weak var myDatePicker: UIDatePicker!
    
    var selectedDate: String = ""
    weak var m_parent: MainViewController?
    

    @IBAction func textFieldEdited(sender: UITextField) {
        let tmp:String = lastName.text!
        // first character only
        if tmp.characters.count == 0 {
            return
        }
        let index = tmp.startIndex.advancedBy(0)
        self.pickerData = getLastNameFromHangul(String(tmp[index]))
        self.picker.reloadAllComponents()
    }
    
    @IBAction func datePickerAction(sender: AnyObject) {
        let dateFormatter = NSDateFormatter()
        dateFormatter.dateFormat = "dd MM yyyy HH mm"
        self.selectedDate = dateFormatter.stringFromDate(self.myDatePicker.date)
    }
    
    // keyboard should disappear
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
    
    var pickerData: [String] = [String]()
    var currData: String = "이"
    
    func numberOfComponentsInPickerView(pickerView: UIPickerView) -> Int {
        return 1
    }
    func pickerView(pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return pickerData.count
    }
    
    // The data to return for the row and component (column) that's being passed in
    func pickerView(pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        currData = pickerData[row]
        return pickerData[row]
    }
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "confirmInfo" {
            let controller = segue.destinationViewController as! RegisterConfirmViewController
            
            controller.surName = lastName.text!
            controller.surNameH = currData
            if controller.surName.characters.count == 2 {
                if controller.surName == "황보" && currData == "皇" {
                    controller.surNameH += "甫"
                }
                else if controller.surName == "남궁" && currData == "南" {
                    controller.surNameH += "宮"
                }
                else if controller.surName == "강전" && currData == "岡" {
                    controller.surNameH += "田"
                }
                else if controller.surName == "독고" && currData == "獨" {
                    controller.surNameH += "孤"
                }
                else if controller.surName == "동방" && currData == "東" {
                    controller.surNameH += "方"
                }
                else if controller.surName == "망절" && currData == "網" {
                    controller.surNameH += "切"
                }
                else if controller.surName == "사공" && currData == "司" {
                    controller.surNameH += "空"
                }
                else if controller.surName == "서문" && currData == "西" {
                    controller.surNameH += "門"
                }
                else if controller.surName == "선우" && currData == "鮮" {
                    controller.surNameH += "于"
                }
                else if controller.surName == "소봉" && currData == "小" {
                    controller.surNameH += "峰"
                }
                else if controller.surName == "장곡" && currData == "長" {
                    controller.surNameH += "谷"
                }
                else if controller.surName == "제갈" && currData == "諸" {
                    controller.surNameH += "葛"
                }
                
            }
            controller.selectedDate = self.selectedDate
        }
    }
    
    @IBAction func checkInfo(sender: UIButton)
    {
        // check if some info is nil
        let vc = self.storyboard!.instantiateViewControllerWithIdentifier("RegisterConfirmView") as!
        RegisterConfirmViewController

        if let s = lastName.text {
            if s.characters.count > 0 {
                vc.surName = s
            } else {
                let vc2 = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpEmpty") as! PopUpViewController
                
                self.addChildViewController(vc2)
                self.view.addSubview(vc2.view)
                vc2.showInView("성을 입력하세요",  animated: true)
                return
            }
        }
        else {
            let vc2 = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpEmpty") as! PopUpViewController

            self.addChildViewController(vc2)
            self.view.addSubview(vc2.view)
            vc2.showInView("성을 입력하세요",  animated: true)
            return
        }
        
        if self.currData.characters.count > 0 {
            vc.surNameH = self.currData
        }
        else {
            let vc2 = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpEmpty") as! PopUpViewController

            self.addChildViewController(vc2)
            self.view.addSubview(vc2.view)
            vc2.showInView("성을 입력하세요",  animated: true)
            return
        }
        if self.selectedDate.characters.count > 0 {
            vc.selectedDate = self.selectedDate
        }
        else {
            let vc2 = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpEmpty") as! PopUpViewController

            self.addChildViewController(vc2)
            self.view.addSubview(vc2.view)
            vc2.showInView("생일을 입력하세요",  animated: true)
            return
        }
        
        if vc.surName.characters.count == 2 {
            if vc.surName == "황보" && currData == "皇" {
                vc.surNameH += "甫"
            }
            else if vc.surName == "남궁" && currData == "南" {
                vc.surNameH += "宮"
            }
            else if vc.surName == "강전" && currData == "岡" {
                vc.surNameH += "田"
            }
            else if vc.surName == "독고" && currData == "獨" {
                vc.surNameH += "孤"
            }
            else if vc.surName == "동방" && currData == "東" {
                vc.surNameH += "方"
            }
            else if vc.surName == "망절" && currData == "網" {
                vc.surNameH += "切"
            }
            else if vc.surName == "사공" && currData == "司" {
                vc.surNameH += "空"
            }
            else if vc.surName == "서문" && currData == "西" {
                vc.surNameH += "門"
            }
            else if vc.surName == "선우" && currData == "鮮" {
                vc.surNameH += "于"
            }
            else if vc.surName == "소봉" && currData == "小" {
                vc.surNameH += "峰"
            }
            else if vc.surName == "장곡" && currData == "長" {
                vc.surNameH += "谷"
            }
            else if vc.surName == "제갈" && currData == "諸" {
                vc.surNameH += "葛"
            }
        }
        
        self.showViewController(vc as RegisterConfirmViewController, sender: vc)
    }
}

