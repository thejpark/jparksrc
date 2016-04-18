//
//  SavedDetailView.swift
//  BabyName
//
//  Created by Park Jung Gyu on 18/04/2016.
//  Copyright © 2016 pyfamily. All rights reserved.
//

import UIKit

class SavedDetailViewController: UIViewController {
    
    @IBOutlet weak var detailDescriptionLabel: UILabel!
    @IBOutlet weak var saju: UILabel!
    @IBOutlet weak var dob: UILabel!
    @IBOutlet weak var ilgangangyag: UILabel!
    @IBOutlet weak var jawonohang: UILabel!
    @IBOutlet weak var heeyong: UILabel!
    @IBOutlet weak var helpohang: UILabel!

    
    var detailItem: Elem?
    
    func configureView() {
        // Update the user interface for the detail item.
        if let detail = self.detailItem {
            if let label = self.detailDescriptionLabel {
                label.text = detail.desc()
            }
            if let saju = self.saju {
                saju.text = detail.getSaju()
            }
            if let dob = self.dob {
                dob.text = detail.getDob()
            }
            if let ilgangangyag = self.ilgangangyag {
                ilgangangyag.text = detail.getIlganGangYag()
            }
            if let jawonohang = self.jawonohang {
                jawonohang.text = detail.getJaWonOHang()
            }
            if let heeyong = self.heeyong {
                heeyong.text = detail.getHeeYong()
            }
            if let helpohang = self.helpohang {
                helpohang.text = detail.getHelpOhang()
            }
            
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.configureView()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
}
