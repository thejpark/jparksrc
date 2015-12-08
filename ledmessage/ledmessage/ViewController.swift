//
//  ViewController.swift
//  ledmessage
//
//  Created by Park Jung Gyu on 7/12/2015.
//  Copyright © 2015 pyfamily. All rights reserved.
//

import UIKit
import MobileCoreServices


class ViewController: UIViewController, UINavigationControllerDelegate, UIImagePickerControllerDelegate {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
//    @IBOutlet weak var start: UIButton!
//    @IBOutlet weak var stop: UIButton!
    @IBOutlet weak var message: UILabel!
    @IBOutlet weak var imageView: UIImageView!
    var imagePicker: UIImagePickerController!
    var newMedia: Bool?
    
    
   // @IBAction func startCamera(sender: AnyObject?) {
   //    self.message.text = "Start"
   // }

    @IBAction func stopCamera(sender: AnyObject?) {
        self.message.text = "Stop"
    }
    
    @IBAction func startCamera(sender: AnyObject?) {
        if UIImagePickerController.isSourceTypeAvailable(
            UIImagePickerControllerSourceType.Camera) {
                
                imagePicker = UIImagePickerController()

                imagePicker.delegate = self
                imagePicker.sourceType =
                    UIImagePickerControllerSourceType.Camera
                imagePicker.mediaTypes = [kUTTypeVideo as String]
                imagePicker.allowsEditing = false
                
                self.presentViewController(imagePicker, animated: true, 
                    completion: nil)
                newMedia = true
        }
        else
        {
            self.message.text = "Start"
        }
    }
    
    func imagePickerController(picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : AnyObject]) {
        
        let mediaType = info[UIImagePickerControllerMediaType] as! String
        
        self.dismissViewControllerAnimated(true, completion: nil)
        
        if mediaType.isEqual([kUTTypeImage as String]) {
            let image = info[UIImagePickerControllerOriginalImage]
                as! UIImage
            
            imageView.image = image
            
            if (newMedia == true) {
                UIImageWriteToSavedPhotosAlbum(image, self,
                    "image:didFinishSavingWithError:contextInfo:", nil)
            }
        } else if mediaType.isEqual([kUTTypeMovie as String]) {
                // Code to support video here
            
        }
        
    }
}

