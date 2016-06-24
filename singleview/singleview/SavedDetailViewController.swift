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
    @IBOutlet weak var jawonohangend: UILabel!
    @IBOutlet weak var umyang: UILabel!
    @IBOutlet weak var umyangend: UILabel!
    @IBOutlet weak var heeyong: UILabel!
    @IBOutlet weak var maininfo: UILabel!
    @IBOutlet weak var barum: UILabel!
    @IBOutlet weak var barumend: UILabel!
    
    
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
                jawonohangend.text = "사주의 부족한 오행을 보충합니다"
            }
            if let umyang = self.umyang {
                umyang.text = detail.getUmYang()
                umyangend.text = "음(짝수) 양(홀수) 조화를 이룹니다"
            }
            if let heeyong = self.heeyong {
                heeyong.text = detail.getHeeYong()
            }
            if let barum = self.barum {
                barum.text = detail.getBarumOhang()
                if (detail.isBarumInHeeYong()) {
                    barumend.text = "이며 사주에 부족한 오행을 보충합니다"
                }
                else {
                    barumend.text = "입니다"
                }
            }
            if let maininfo = self.maininfo {
                maininfo.layer.masksToBounds = true
                maininfo.layer.cornerRadius = 5
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
    
    @IBAction func goHome(sender: UIBarItem)
    {
        navigationController?.popToRootViewControllerAnimated(true)
    }
}
