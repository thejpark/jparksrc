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
        
        pickerData = []
        currData = ""
        gender = "여자"
        place = "서울"
        
        let dateFormatter = NSDateFormatter()
        dateFormatter.dateFormat = "dd MM yyyy HH mm"
        self.selectedDate = dateFormatter.stringFromDate(self.myDatePicker.date)
        
        placePicker.selectRow(placePickerData.count - 1, inComponent: 0, animated: true)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBOutlet weak var lastName: UITextField!
    @IBOutlet weak var picker: UIPickerView!
    @IBOutlet weak var myDatePicker: UIDatePicker!
    @IBOutlet weak var genderPicker: UIPickerView!
    @IBOutlet weak var placePicker: UIPickerView!
    
    
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
    var genderPickerData: [String] = ["여자", "남자"]
    var placePickerData: [String] = ["해외", "백령도", "울릉", "김천", "서산", "군산", "여수", "원주", "청주", "통영", "경주", "평택", "수원", "춘천", "목포", "전주", "제주", "울산", "강릉", "대전", "용인", "인천", "광주", "대구", "부산", "서울"]

    var currData: String = "이"
    var gender: String = "여자"
    var place: String = "서울"
    
    func numberOfComponentsInPickerView(pickerView: UIPickerView) -> Int {
        return 1
    }
    func pickerView(pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        if pickerView == self.picker {
            return pickerData.count
        }
        else if pickerView == self.genderPicker {
            return genderPickerData.count
        }
        else if pickerView == self.placePicker {
            return placePickerData.count
        }
        return 0
    }
    
    // The data to return for the row and component (column) that's being passed in
    func pickerView(pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        if pickerView == self.picker {
            currData = pickerData[row]
            return pickerData[row]
        }
        else if pickerView == self.genderPicker {
            gender = genderPickerData[row]
            return genderPickerData[row]
        }
        else if pickerView == self.placePicker {
            place = placePickerData[row]
            return placePickerData[row]
        }

        return nil
    }
    
    func pickerView(pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {

        if pickerView == self.picker {
            currData = pickerData[row]
        }
        else if pickerView == self.genderPicker {
            gender = genderPickerData[row]
        }
        else if pickerView == self.placePicker {
            place = placePickerData[row]
        }

        return
    }
    
    /*
    
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
 */
    
    @IBAction func checkInfo(sender: UIButton)
    {
        // check if some info is nil
        var sName:String = ""
        var sNameH:String = ""
        var dob:String = ""
        
        if let s = lastName.text {
            if s.characters.count > 0 {
                sName = s
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
            sNameH = self.currData
        }
        else {
            let vc2 = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpEmpty") as! PopUpViewController

            self.addChildViewController(vc2)
            self.view.addSubview(vc2.view)
            vc2.showInView("성을 입력하세요",  animated: true)
            return
        }
        if self.selectedDate.characters.count > 0 {
            dob = self.selectedDate
        }
        else {
            let vc2 = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpEmpty") as! PopUpViewController

            self.addChildViewController(vc2)
            self.view.addSubview(vc2.view)
            vc2.showInView("생일을 입력하세요",  animated: true)
            return
        }
        
        if sName.characters.count == 2 {
            if sName == "황보" && currData == "皇" {
                sNameH += "甫"
            }
            else if sName == "남궁" && currData == "南" {
                sNameH += "宮"
            }
            else if sName == "강전" && currData == "岡" {
                sNameH += "田"
            }
            else if sName == "독고" && currData == "獨" {
                sNameH += "孤"
            }
            else if sName == "동방" && currData == "東" {
                sNameH += "方"
            }
            else if sName == "망절" && currData == "網" {
                sNameH += "切"
            }
            else if sName == "사공" && currData == "司" {
                sNameH += "空"
            }
            else if sName == "서문" && currData == "西" {
                sNameH += "門"
            }
            else if sName == "선우" && currData == "鮮" {
                sNameH += "于"
            }
            else if sName == "소봉" && currData == "小" {
                sNameH += "峰"
            }
            else if sName == "장곡" && currData == "長" {
                sNameH += "谷"
            }
            else if sName == "제갈" && currData == "諸" {
                sNameH += "葛"
            }
        }
        
        let vc = self.storyboard!.instantiateViewControllerWithIdentifier("PopUpConfirmView") as! PopUpViewController
        self.addChildViewController(vc)
        self.view.addSubview(vc.view)
        
        vc.lastName.text = "성: " + sName + "(" + sNameH + ")  성별: " + gender
        // set date and time of birth
        var str = self.selectedDate.componentsSeparatedByString(" ")
        vc.dob.text = "생일: " + str[2] + "년" + str[1] + "월" + str[0] + "일 " + str[3] + ":" + str[4]
        vc.place.text = "출생지: " + place
        
        vc.surName = sName
        vc.surNameH = sNameH
        vc.selectedDate = self.selectedDate
        vc.gender = gender
        vc.birthPlace = place
        
        vc.showInView("입력 내용이 정확한가요?",  animated: true)

    }
}

