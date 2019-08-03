//
//  DetailViewController.swift
//  singleview
//
//  Created by Park Jung Gyu on 17/10/2015.
//  Copyright © 2015 pyfamily. All rights reserved.
//

import UIKit

class DetailViewController: UIViewController {
    
    @IBOutlet weak var detailDescriptionLabel: UILabel!
    @IBOutlet weak var saju: UILabel!
    @IBOutlet weak var dob: UILabel!
    @IBOutlet weak var ilgangangyag: UILabel!
    @IBOutlet weak var jawonohang: UILabel!
    @IBOutlet weak var jawonohangend: UILabel!
    @IBOutlet weak var umyang: UILabel!
    @IBOutlet weak var umyangend: UILabel!
    @IBOutlet weak var heeyong: UILabel!
    @IBOutlet weak var barum: UILabel!
    @IBOutlet weak var barumend: UILabel!
    @IBOutlet weak var name: UILabel!
    
    
    
    var detailItem: Elem?
    
    func configureView() {
        // Update the user interface for the detail item.
        if let detail = self.detailItem {
            if let label = self.detailDescriptionLabel {
                label.text = detail.desc()
            }
            if let name = self.name {
                name.text = detail.desc()
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
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.navigationItem.rightBarButtonItem = UIBarButtonItem(title: "저장", style: .plain, target: self, action:#selector(DetailViewController.saveOne))
        self.configureView()
    }
    
    @objc func saveOne() {
        if let detail = self.detailItem {
            detail.save()
            
            let vc = self.storyboard!.instantiateViewController(withIdentifier: "PopUpEmpty") as! PopUpViewController
            self.addChild(vc)
            self.view.addSubview(vc.view)
            vc.showInView("저장되었습니다.",  animated: true)
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func goHome(_ sender: UIBarItem)
    {
        navigationController?.popToRootViewController(animated: true)
    }
    
    @IBAction func LoadSelectedNames(_ sender: UIBarItem)
    {
        if savedElements.count == 0 {
            if let s = loadElem() {
                savedElements = s
                if savedElements.count == 0 {
                    let vc2 = self.storyboard!.instantiateViewController(withIdentifier: "PopUpEmpty") as! PopUpViewController
                    
                    self.addChild(vc2)
                    self.view.addSubview(vc2.view)
                    vc2.showInView("저장된 이름이 없습니다",  animated: true)
                    return
                }
            }
        }
        
        let vc = self.storyboard!.instantiateViewController(withIdentifier: "SavedNames") as!
        SavedViewTableController
        
        vc.LoadTable()
        self.show(vc as SavedViewTableController, sender: vc)
    }
}
