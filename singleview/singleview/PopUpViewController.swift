//
//  PopUpViewController.swift
//  BabyName
//
//  Created by Park Jung Gyu on 14/04/2016.
//  Copyright © 2016 pyfamily. All rights reserved.
//

 
import UIKit

class PopUpViewController: UIViewController {
    
    @IBOutlet weak var lastName: UILabel!
    @IBOutlet weak var dob: UILabel!
    @IBOutlet weak var place: UILabel!
    
    
    @IBOutlet weak var messageLabel: UILabel!
    @IBOutlet weak var popUpView: UIView!
    
    required init(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)!
    }
    
    override init(nibName nibNameOrNil: String!, bundle nibBundleOrNil: NSBundle!) {
        super.init(nibName: nibNameOrNil, bundle: nibBundleOrNil)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.backgroundColor = UIColor.blackColor().colorWithAlphaComponent(0.6)
        self.popUpView.layer.cornerRadius = 5
        self.popUpView.layer.shadowOpacity = 0.8
        self.popUpView.layer.shadowOffset = CGSizeMake(0.0, 0.0)
    }
    
    /*
    func showInView(aView: UIView!, withImage image : UIImage!, withMessage message: String!, animated: Bool)
    {
        aView.addSubview(self.view)
        logoImg!.image = image
        messageLabel!.text = message
        if animated
        {
            self.showAnimate()
        }
    }
     */
  
    
    func showInView(message: String!, animated: Bool)
    {
        messageLabel!.text = message
        if animated
        {
            self.showAnimate()
        }
    }
    
    
    func showAnimate()
    {
        self.view.transform = CGAffineTransformMakeScale(1.3, 1.3)
        self.view.alpha = 0.0;
        UIView.animateWithDuration(0.25, animations: {
            self.view.alpha = 1.0
            self.view.transform = CGAffineTransformMakeScale(1.0, 1.0)
        });
    }
    
    func removeAnimate()
    {
        UIView.animateWithDuration(0.25, animations: {
            self.view.transform = CGAffineTransformMakeScale(1.3, 1.3)
            self.view.alpha = 0.0;
            }, completion:{(finished : Bool)  in
                if (finished)
                {
                    self.view.removeFromSuperview()
                }
        });
    }
    
    @IBAction func closePopup(sender: UIButton) {
        self.removeAnimate()
    }

    @IBAction func registerNewInfo(sender: UIButton) {
        self.removeAnimate()
        let vc : AnyObject! = self.storyboard!.instantiateViewControllerWithIdentifier("RegisterView")
        self.showViewController(vc as! UIViewController, sender: vc)
    }
    
    var selectedDate: String = ""
    var surName: String = ""
    var surNameH: String = ""
    var gender: String = ""
    var birthPlace: String = ""

    @IBAction func returnToMain(sender: UIButton) {
        self.removeAnimate()
        
        // store info
        let defaults = NSUserDefaults.standardUserDefaults()
        defaults.setValue(surName, forKey: RegisterInfoKeys.surName)
        defaults.setValue(surNameH, forKey: RegisterInfoKeys.surNameH)
        defaults.setValue(selectedDate, forKey: RegisterInfoKeys.dob)
        defaults.setValue(gender, forKey: RegisterInfoKeys.gender)
        defaults.setValue(birthPlace, forKey: RegisterInfoKeys.place)

        defaults.synchronize()
        
        navigationController?.popToRootViewControllerAnimated(true)
    }
}

