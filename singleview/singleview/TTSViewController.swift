//
//  TTSViewController.swift
//  BabyName
//
//  Created by Park Jung Gyu on 23/04/2016.
//  Copyright © 2016 pyfamily. All rights reserved.
//

import UIKit
import AVFoundation

class TTSViewController: UIViewController {


    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBOutlet weak var firstName: UITextField!
    
    // keyboard should disappear
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
    
    @IBAction func SayName(sender: UIButton)
    {
        let synthesizer = AVSpeechSynthesizer()
        let utterance = AVSpeechUtterance(string: firstName.text!)
        utterance.rate = 0.3
        // utterance.voice = AVSpeechSynthesisVoice(language: "fr-FR")
        synthesizer.speakUtterance(utterance)
    }
}