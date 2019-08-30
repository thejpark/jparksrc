//
//  MasterViewController.swift
//  singleview
//
//  Created by Park Jung Gyu on 15/10/2015.
//  Copyright © 2015 pyfamily. All rights reserved.
//

import UIKit

struct PropertyKey {
    static let surNameKey = "surName"
    static let surName1Key = "surName1"
    static let givenNameKey = "givenName"
    static let givenName1Key = "givenName1"
    static let sajuKey = "saju"
    static let dobKey = "dob"
    static let ilganKey = "ilgan"
    static let gangYagKey = "gangYag"
    static let antiIlganKey = "antiIlgan"
    static let antiGangYagKey = "antiGangYag"
    static let hyKey = "hy"
}



class Elem: NSObject, NSCoding {
    var surName : [Hanja]
    var surName1: String // hangul
    var givenName : [Hanja]
    var givenName1: String // hangul
    var saju: String
    var dob: String
    var ilganGangYag: (Int, Double, Int, Double)
    var hy: [Int]
    @objc var prio: Int = 0


    func encode(with aCoder: NSCoder) {
        var tmp: String = ""
        for e in surName {
            tmp += e.0
        }
        aCoder.encode(tmp, forKey: PropertyKey.surNameKey)
        aCoder.encode(surName1, forKey: PropertyKey.surName1Key)
        tmp = ""
        for e in givenName {
            tmp += e.0
        }
        aCoder.encode(tmp, forKey: PropertyKey.givenNameKey)
        aCoder.encode(givenName1, forKey: PropertyKey.givenName1Key)
        aCoder.encode(saju, forKey: PropertyKey.sajuKey)
        aCoder.encode(dob, forKey: PropertyKey.dobKey)
        aCoder.encode(ilganGangYag.0, forKey: PropertyKey.ilganKey)
        aCoder.encode(ilganGangYag.1, forKey: PropertyKey.gangYagKey)
        aCoder.encode(ilganGangYag.2, forKey: PropertyKey.antiIlganKey)
        aCoder.encode(ilganGangYag.3, forKey: PropertyKey.antiGangYagKey)
        aCoder.encode(hy, forKey: PropertyKey.hyKey)
    }
    
    required convenience init?(coder aDecoder: NSCoder) {
        let sn = aDecoder.decodeObject(forKey: PropertyKey.surNameKey) as! String
        let sn1 = aDecoder.decodeObject(forKey: PropertyKey.surName1Key) as! String
        var snh: [Hanja] = [Hanja]()
        for i in 0...(sn1.count - 1) {
            let index = sn.index(sn.startIndex, offsetBy: i)
            let index1 = sn1.index(sn1.startIndex, offsetBy: i)
            snh.append(getHanjaData(String(sn1[index1]), hanja: String(sn[index])))
        }

        let gn = aDecoder.decodeObject(forKey: PropertyKey.givenNameKey) as! String
        let gn1 = aDecoder.decodeObject(forKey: PropertyKey.givenName1Key) as! String
        var gnh: [Hanja] = [Hanja]()
        for i in 0...(gn1.count - 1) {
            let index = gn.index(gn.startIndex, offsetBy: i)
            let index1 = gn1.index(gn1.startIndex, offsetBy: i)
            gnh.append(getHanjaData(String(gn1[index1]), hanja: String(gn[index])))
        }
        let sj = aDecoder.decodeObject(forKey: PropertyKey.sajuKey) as! String
        let d = aDecoder.decodeObject(forKey: PropertyKey.dobKey) as! String
        let il = aDecoder.decodeInteger(forKey: PropertyKey.ilganKey)
        let gy = aDecoder.decodeDouble(forKey: PropertyKey.gangYagKey)
        let antiIl = aDecoder.decodeInteger(forKey: PropertyKey.antiIlganKey)
        let antiGy = aDecoder.decodeDouble(forKey: PropertyKey.antiGangYagKey)

        let h = aDecoder.decodeObject(forKey: PropertyKey.hyKey) as! [Int]
        
        self.init(surName1: sn1, surName:snh, givenName1: gn1, givenName: gnh,
                  saju:sj, dob:d, ilgan: il, gangYag:gy, antiIlgan:antiIl, antiGangYag: antiGy, hy: h)
    
    }
    
    init?(surName1: String, surName: [Hanja], givenName1: String, givenName:[Hanja],
          saju: String, dob: String, ilgan: Int, gangYag: Double, antiIlgan: Int, antiGangYag: Double,
          hy: [Int]) {
        // Initialize stored properties.
        self.surName1 = surName1
        self.surName = surName
        self.givenName1 = givenName1
        self.givenName = givenName
        self.saju = saju
        self.dob = dob
        self.ilganGangYag = (ilgan, gangYag, antiIlgan, antiGangYag)
        self.hy = hy
        
        super.init()
        
        // Initialization should fail if there is no name or if the rating is negative.
        if surName1.count < 1 || givenName1.count  < 1 {
            return nil
        }
    }

    init (name:[Hanja], num: Int) {
        surName = [Hanja]()
        for i in 0..<num {
            surName.append(name[i])
        }
        givenName = [Hanja]()
        for i in num..<name.count {
            givenName.append(name[i])
        }
        saju = ""
        dob = ""
        surName1 = ""
        givenName1 = ""
        ilganGangYag = (0,0, 0, 0)
        hy = [Int]()
    }
    
    func desc() -> String {
        var r: String = ""
        for e in surName {
            r += e.0
        }
        for e in givenName {
            r += e.0
        }
        r += " ("
        for i  in 0...(givenName.count - 1) {
            r += givenName[i].1
            // r += "(" + String(givenName[i].2) + "획)"
            if (i != givenName.count - 1) {
                r += ", "
            }
        }
        r += ")"
        
        return r
    }
    
    func getSaju() -> String {
        var r: String = "사주: "
        r += saju
        return r
    }
    
    func getDob() -> String {
        var str = self.dob.components(separatedBy: " ")
        return "생년월일: " + str[2] + "년" + str[1] + "월" + str[0] + "일 " + str[3] + ":" + str[4]
    }
    
    func getJaWonOHang() -> String {
        var r: String = "이름 글자의 자원오행이 "
        
        for i  in 0...(givenName.count - 1) {
            r += " " + ohangHanja[givenName[i].3]!
        }
        
        r += " 으로"
        return r
    }
    
    func getUmYang() -> String {
        var r: String = "성과 이름이 각각 "
        
        var s = 0
        for i in 0...(surName.count - 1) {
            s += surName[i].2
        }
        r += String(s) + "획 "
        
        for i  in 0...(givenName.count - 1) {
            r += String(givenName[i].2) + "획 "
        }
        
        return r + "으로"
    }

    
    func getIlganGangYag() -> String {
        var r: String = "사주의 기준 오행은 "
        r += ohangHanja[self.ilganGangYag.0]!
        r += " 입니다" // + String(self.ilganGangYag.1)
//        r += " 극: "
//        r += ohangHanja[self.ilganGangYag.2]!
//        r += " " + String(self.ilganGangYag.3)
        return r
    }
    
    func getHeeYong() -> String {
        var r: String = "사주에 부족한 오행은 "
        
        for e in hy {
            r += ohangHanja[e]!
            r += " "
        }
        r += "입니다"
        return r
    }

    func isBarumInHeeYong() -> Bool {
        
        for i in 0...self.givenName1.count - 1 {
            let index = self.givenName1.index(self.givenName1.startIndex, offsetBy: i)
            let i = getBarumOhangIndex(String(self.givenName1[index]))
            if hy.contains(i) {
                return true
            }
        }

        return false
    }
    
    func getHelpOhang() -> String {
        var r: String = "도움: "
        
        for e in helpohang[ilganGangYag.0]! {
            r += ohangHanja[e]!
        }
        return r
    }
    
    func getBarumOhang() -> String {
        var r: String = "참고로 이름 글자의 발음오행은 "
        for i in 0...self.givenName1.count - 1 {
            let index = self.givenName1.index(self.givenName1.startIndex, offsetBy: i)
            r += ohangHanja[getBarumOhangIndex(String(self.givenName1[index]))]!
            r += " "
        }
        
        return r
    }

    // is it ok to save all? optimal case would be to save only last element
    func save() {
        for e in savedElements {
            for i in 0..<e.givenName.count {
                if e.givenName[i] == self.givenName[i] {
                    if i == (e.givenName.count - 1) {
                        // already have it.
                        return
                    }
                }
                else {
                    break;
                }
                
            }
        }
        savedElements.append(self)
        saveElem()
    }

    // save and load
    static let DocumentsDirectory = FileManager().urls(for: .documentDirectory, in: .userDomainMask).first!
    
    static let ArchiveURL = DocumentsDirectory.appendingPathComponent("data")
}

// saved elements
var savedElements: [Elem] = [Elem]()


func saveElem() {
    let isSuccessfulSave = NSKeyedArchiver.archiveRootObject(savedElements, toFile: Elem.ArchiveURL.path)
    if !isSuccessfulSave {
        print("Failed to save elements...")
    }
}

func clearElem() {
    savedElements = [Elem]()
    let isSuccessfulSave = NSKeyedArchiver.archiveRootObject(savedElements, toFile: Elem.ArchiveURL.path)
    if !isSuccessfulSave {
        print("Failed to save elements...")
    }
}


func loadElem() -> [Elem]? {
    return NSKeyedUnarchiver.unarchiveObject(withFile: Elem.ArchiveURL.path) as? [Elem]
}

class MasterViewController: UITableViewController {
    
    var objects = [AnyObject]()
    var numSelected: Int = 0

    var day: Int = 0
    var month: Int = 0
    var year: Int = 0
    var hour: Int = 0
    var minute: Int = 0
    var hy: [Int] = []
    var dob : String = ""
    var surName: String = ""
    var givenName: String = ""
    var prio_set:[[Int:Int]] = [[Int:Int]]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func search(_ surName: String, surNameH: String, givenName: String, selectedDate: String) {
        var gname: [Hanja] = [Hanja]()
        self.objects = [AnyObject]()
        self.numSelected = 0
      
      //  for var i = 0; i < givenName.characters.count; ++i {
      //      let index = givenName.startIndex.advancedBy(i)
      //      var hanja : [Hanja] = getHanjaDataFromHangul(String(givenName[index]))
      //      gname.append(hanja[0])
      //  }
        
        
        // set date and time of birth
        self.dob = selectedDate
        self.surName = surName
        self.givenName = givenName
        var str = selectedDate.components(separatedBy: " ")
        
        self.day = Int(str[0])!
        self.month = Int(str[1])!
        self.year = Int(str[2])!
        self.hour = Int(str[3])!
        self.minute = Int(str[4])!
        self.hy = getHeeYong(self.year, month: self.month, day: self.day, hour: self.hour, minute: self.minute)

        prio_set = [[Int:Int]]()
        for _ in 1...givenName.count {
            self.prio_set.append([:])
        }
        
        
        let index = givenName.index(givenName.startIndex, offsetBy: 0)
        gname = getHanjaDataFromHangul(String(givenName[index]))
        
        var i: Int = 1
        for g in gname {
            var name: [Hanja] = [Hanja]()
            name += getLastNameHanjaData(surName, hanja: surNameH)
            name.append(g)
            var x: [Int] = [Int]()
            x.append(i)
            findAndInsert(name, givenName: givenName, idx: 1, prio: x)
            i += 1
        }

        objects.sort(by: {$0.prio < $1.prio})
    }
    
    func findAndInsert(_ name: [Hanja], givenName: String, idx : Int, prio : [Int]) {
        
        if (idx == givenName.count) {
            insertNewObject(name, prio: prio)
            return
        }
        
        var gname: [Hanja] = [Hanja]()
        let index = givenName.index(givenName.startIndex, offsetBy: idx)
        gname = getHanjaDataFromHangul(String(givenName[index]))
        
        var i: Int = 1
        for g in gname {
            var n = name
            n.append(g)
            var x: [Int] = prio
            x.append(i)
            findAndInsert(n, givenName: givenName, idx: idx + 1, prio: x)
            i += 1
        }

    }
    
    func insertNewObject(_ name: [Hanja], prio: [Int]) {
        if name.count < 2 {
            return
        }
        
        // filter out all even number or all odd number hanja
        var k = name[0].2 % 2
        if self.surName.count == 2 {
            k = (name[0].2 + name[1].2) % 2
        }

        var count = 1
        var i = 0
        for n in name {
            i += 1
            // skip surname
            if i <= self.surName.count {
                continue
            }
            
            if ((n.2 % 2) == k) {
                count += 1
            }
        }
        if count == name.count - self.surName.count + 1 {
            // instead of just return, we may add some big number to get the priority lower.
            return
        }
        
        //filter out by jawon ohang
        
        for i in self.surName.count ... name.count - 1 {
            if self.hy.contains(name[i].3) == false {
                return
            }
        }
        
        // calculate priority. hanja is assumed be sorted from higher proi to lower.
        var priority: Int = 0
        for i in 0..<prio.count {
            if prio_set[i][prio[i]] != nil {
            } else {
                let size = prio_set[i].count + 1
                prio_set[i][prio[i]] = size
            }
            priority += prio_set[i][prio[i]]!
        }
        
        // add name
        let elem = Elem(name: name, num:self.surName.count)
        elem.prio = priority
        elem.saju = getSaju(self.year, month:self.month, day:self.day, hour:self.hour, minute:self.minute)
        elem.dob =  self.dob
        elem.surName1 = surName
        elem.givenName1 = givenName
        elem.ilganGangYag = getIlganGangYag(self.year, month:self.month, day:self.day, hour:self.hour, minute:self.minute)
        elem.hy = self.hy
        
        objects.insert(elem, at: numSelected)
        numSelected += 1
//        let indexPath = NSIndexPath(forRow: 0, inSection: 0)
//        self.tableView.insertRowsAtIndexPaths([indexPath], withRowAnimation: .Automatic)
    }
    
    // MARK: - Table View
    
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return objects.count
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "Cell", for: indexPath)
        
        let object = objects[(indexPath as NSIndexPath).row] as! Elem
        cell.textLabel!.text = object.desc()
        return cell
    }
    
    override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        // Return false if you do not want the specified item to be editable.
        return true
    }
    
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            objects.remove(at: (indexPath as NSIndexPath).row)
            tableView.deleteRows(at: [indexPath], with: .fade)
        } else if editingStyle == .insert {
            // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
        }
    }
    
    // MARK: - Segues
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "showDetail" {
            if let indexPath = self.tableView.indexPathForSelectedRow {
                let obj = objects[(indexPath as NSIndexPath).row] as! Elem
                let controller = segue.destination as! DetailViewController
                controller.detailItem = obj
            }
        }
    }
    
    @IBAction func goHome(_ sender: UIBarItem)
    {
        navigationController?.popToRootViewController(animated: true)
    }

}

