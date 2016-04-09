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
    
    
    @IBAction func textFieldEdited(sender: UITextField) {
        self.pickerData = getHanjaFromHangul(lastName.text!)
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
    
    // MARK: - Segues
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "enterName" {
            let controller = segue.destinationViewController as! ViewController
            controller.surName = lastName.text!
            controller.surNameH = currData
            controller.selectedDate =  self.selectedDate
        }
    }
    
}

