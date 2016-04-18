//
//  MasterViewController.swift
//  singleview
//
//  Created by Park Jung Gyu on 15/10/2015.
//  Copyright © 2015 pyfamily. All rights reserved.
//

import UIKit


class Elem: NSObject, NSCoding {
    var surName : Hanja
    var surName1: String // hangul
    var givenName : [Hanja]
    var givenName1: String // hangul
    var saju: String
    var dob: String
    var ilganGangYag: (Int, Double)
    var hy: [Int]

    struct PropertyKey {
        static let surNameKey = "surName"
        static let surName1Key = "surName1"
        static let givenNameKey = "givenName"
        static let givenName1Key = "givenName1"
        static let sajuKey = "saju"
        static let dobKey = "dob"
        static let ilganKey = "ilgan"
        static let gangYagKey = "gangYag"
        static let hyKey = "hy"
    }
    
    func encodeWithCoder(aCoder: NSCoder) {
        aCoder.encodeObject(surName.0, forKey: PropertyKey.surNameKey)
        aCoder.encodeObject(surName1, forKey: PropertyKey.surName1Key)
        var tmp: String = ""
        for e in givenName {
            tmp += e.0
        }
        aCoder.encodeObject(tmp, forKey: PropertyKey.givenNameKey)
        aCoder.encodeObject(givenName1, forKey: PropertyKey.givenName1Key)
        aCoder.encodeObject(saju, forKey: PropertyKey.sajuKey)
        aCoder.encodeObject(dob, forKey: PropertyKey.dobKey)
        aCoder.encodeObject(ilganGangYag.0, forKey: PropertyKey.ilganKey)
        aCoder.encodeObject(ilganGangYag.1, forKey: PropertyKey.gangYagKey)
        aCoder.encodeObject(hy, forKey: PropertyKey.hyKey)
    }
    
    required convenience init?(coder aDecoder: NSCoder) {
        let sn = aDecoder.decodeObjectForKey(PropertyKey.surNameKey) as! String
        let sn1 = aDecoder.decodeObjectForKey(PropertyKey.surName1Key) as! String
        let snh = getHanjaData(sn1, hanja: sn)
        let gn = aDecoder.decodeObjectForKey(PropertyKey.givenNameKey) as! String
        let gn1 = aDecoder.decodeObjectForKey(PropertyKey.givenName1Key) as! String
        var gnh: [Hanja] = [Hanja]()
        for i in 0...(gn1.characters.count - 1) {
            let index = gn.startIndex.advancedBy(i)
            let index1 = gn1.startIndex.advancedBy(i)
            gnh.append(getHanjaData(String(gn1[index1]), hanja: String(gn[index])))
        }
        let sj = aDecoder.decodeObjectForKey(PropertyKey.sajuKey) as! String
        let d = aDecoder.decodeObjectForKey(PropertyKey.dobKey) as! String
        let il = aDecoder.decodeObjectForKey(PropertyKey.ilganKey) as! Int
        let gy = aDecoder.decodeObjectForKey(PropertyKey.gangYagKey) as! Double
        let h = aDecoder.decodeObjectForKey(PropertyKey.hyKey) as! [Int]
        
     
        self.init(surName1: sn1, surName:snh, givenName1: gn1, givenName: gnh,
                  saju:sj, dob:d, ilgan: il, gangYag:gy, hy: h)
    
    }
    
    init?(surName1: String, surName: Hanja, givenName1: String, givenName:[Hanja],
          saju: String, dob: String, ilgan: Int, gangYag: Double, hy: [Int]) {
        // Initialize stored properties.
        self.surName1 = surName1
        self.surName = surName
        self.givenName1 = givenName1
        self.givenName = givenName
        self.saju = saju
        self.dob = dob
        self.ilganGangYag = (ilgan, gangYag)
        self.hy = hy
        
        super.init()
        
        // Initialization should fail if there is no name or if the rating is negative.
        if surName1.characters.count < 1 || givenName1.characters.count  < 1 {
            return nil
        }
    }

    init (name:[Hanja]) {
        surName = name[0]
        givenName = [Hanja]()
        for i in 1...(name.count - 1) {
            givenName.append(name[i])
        }
        saju = ""
        dob = ""
        surName1 = ""
        givenName1 = ""
        ilganGangYag = (0,0)
        hy = [Int]()
    }
    
    func desc() -> String {
        var r: String
        r = surName.0
        for e in givenName {
            r += e.0
        }
        r += " ("
        for i  in 0...(givenName.count - 1) {
            r += givenName[i].1
            r += "(" + String(givenName[i].2) + "획)"
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
        var str = self.dob.componentsSeparatedByString(" ")
        return "생년월일: " + str[2] + "년" + str[1] + "월" + str[0] + "일 " + str[3] + ":" + str[4]
    }
    
    func getJaWonOHang() -> String {
        var r: String = "자원오행: "
        r += ohangHanja[surName.3]!
        
        for i  in 0...(givenName.count - 1) {
            r += " " + ohangHanja[givenName[i].3]!
        }
        
        return r
    }
    
    func getIlganGangYag() -> String {
        var r: String = "일간: "
        r += gan[self.ilganGangYag.0]
        r += " " + String(self.ilganGangYag.1)
        return r
    }
    
    func getHeeYong() -> String {
        var r: String = "희용: "
        
        for e in hy {
            r += ohangHanja[e]!
        }
        return r
    }

    func getHelpOhang() -> String {
        var r: String = "도움: "
        
        for e in helpohang[ilganGangYag.0]! {
            r += ohangHanja[e]!
        }
        return r
    }

    // is it ok to save all? optimal case would be to save only last element
    func save() {
        savedElements.append(self)
        saveElem()
    }

    // save and load
    static let DocumentsDirectory = NSFileManager().URLsForDirectory(.DocumentDirectory, inDomains: .UserDomainMask).first!
    
    static let ArchiveURL = DocumentsDirectory.URLByAppendingPathComponent("data")
}

// saved elements
var savedElements: [Elem] = [Elem]()


func saveElem() {
    let isSuccessfulSave = NSKeyedArchiver.archiveRootObject(savedElements, toFile: Elem.ArchiveURL.path!)
    if !isSuccessfulSave {
        print("Failed to save elements...")
    }
}


func loadElem() -> [Elem]? {
    return NSKeyedUnarchiver.unarchiveObjectWithFile(Elem.ArchiveURL.path!) as? [Elem]
}

class MasterViewController: UITableViewController {
    
    var objects = [AnyObject]()

    var day: Int = 0
    var month: Int = 0
    var year: Int = 0
    var hour: Int = 0
    var minute: Int = 0
    var hy: [Int] = []
    var dob : String = ""
    var numSelected: Int = 0
    var surName: String = ""
    var givenName: String = ""
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func search(surName: String, surNameH: String, givenName: String, selectedDate: String) {
        var gname: [Hanja] = [Hanja]()
      
      //  for var i = 0; i < givenName.characters.count; ++i {
      //      let index = givenName.startIndex.advancedBy(i)
      //      var hanja : [Hanja] = getHanjaDataFromHangul(String(givenName[index]))
      //      gname.append(hanja[0])
      //  }

        // set date and time of birth
        self.dob = selectedDate
        self.surName = surName
        self.givenName = givenName
        var str = selectedDate.componentsSeparatedByString(" ")
        
        self.day = Int(str[0])!
        self.month = Int(str[1])!
        self.year = Int(str[2])!
        self.hour = Int(str[3])!
        self.minute = Int(str[4])!
        self.hy = getHeeYong(self.year, month: self.month, day: self.day, hour: self.hour, minute: self.minute)

        let index = givenName.startIndex.advancedBy(0)
        gname = getHanjaDataFromHangul(String(givenName[index]))
        
        for g in gname {
            var name: [Hanja] = [Hanja]()
            name.append(getHanjaData(surName, hanja: surNameH))
            name.append(g)
            findAndInsert(name, givenName: givenName, idx: 1)
        }
        
    }
    
    func findAndInsert(name: [Hanja], givenName: String, idx : Int) {
        
        if (idx == givenName.characters.count) {
            insertNewObject(name)
            return
        }
        
        var gname: [Hanja] = [Hanja]()
        let index = givenName.startIndex.advancedBy(idx)
        gname = getHanjaDataFromHangul(String(givenName[index]))
        
        for g in gname {
            var n = name
            n.append(g)
            findAndInsert(n, givenName: givenName, idx: idx + 1)
        }

    }
    
    func insertNewObject(name: [Hanja]) {
        // at most one given name
        if name.count < 2 {
            return
        }
        
        // filter out all even number or all odd number hanja
        let k = name[0].2 % 2
        var count = 0
        for n in name {
            if ((n.2 % 2) == k) {
                count += 1
            }
        }
        if count == name.count {
            return
        }
        
        //filter out by jawon ohang
        
        for i in 1 ... name.count - 1 {
            if self.hy.contains(name[i].3) == false {
                return
            }
        }
        
        // add name
        let elem = Elem(name: name)
        elem.saju = getSaju(self.year, month:self.month, day:self.day, hour:self.hour, minute:self.minute)
        elem.dob = self.dob
        elem.surName1 = surName
        elem.givenName1 = givenName
        elem.ilganGangYag = getIlganGangYag(self.year, month:self.month, day:self.day, hour:self.hour, minute:self.minute)
        elem.hy = self.hy
        
        objects.insert(elem, atIndex: numSelected)
        numSelected += 1
        let indexPath = NSIndexPath(forRow: 0, inSection: 0)
        self.tableView.insertRowsAtIndexPaths([indexPath], withRowAnimation: .Automatic)
    }
    
    // MARK: - Table View
    
    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1
    }
    
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return objects.count
    }
    
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("Cell", forIndexPath: indexPath)
        
        let object = objects[indexPath.row] as! Elem
        cell.textLabel!.text = object.desc()
        return cell
    }
    
    override func tableView(tableView: UITableView, canEditRowAtIndexPath indexPath: NSIndexPath) -> Bool {
        // Return false if you do not want the specified item to be editable.
        return true
    }
    
    override func tableView(tableView: UITableView, commitEditingStyle editingStyle: UITableViewCellEditingStyle, forRowAtIndexPath indexPath: NSIndexPath) {
        if editingStyle == .Delete {
            objects.removeAtIndex(indexPath.row)
            tableView.deleteRowsAtIndexPaths([indexPath], withRowAnimation: .Fade)
        } else if editingStyle == .Insert {
            // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
        }
    }
    
    // MARK: - Segues
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "showDetail" {
            if let indexPath = self.tableView.indexPathForSelectedRow {
                let obj = objects[indexPath.row] as! Elem
                let controller = segue.destinationViewController as! DetailViewController
                controller.detailItem = obj
            }
        }
    }
}

