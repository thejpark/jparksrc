//
//  MasterViewController.swift
//  singleview
//
//  Created by Park Jung Gyu on 15/10/2015.
//  Copyright © 2015 pyfamily. All rights reserved.
//

import UIKit

class Elem {
    var surName : Hanja
    var givenName : [Hanja]
    var saju: String = ""
    init (name:[Hanja]) {
        surName = name[0]
        givenName = [Hanja]()
        for i in 1...(name.count - 1) {
            givenName.append(name[i])
        }
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
            if (i != givenName.count - 1) {
                r += ", "
            }
        }
        r += ")"
        
        return r
    }
}

class MasterViewController: UITableViewController {
    
    var objects = [AnyObject]()

    var day: Int = 0
    var month: Int = 0
    var year: Int = 0
    var hour: Int = 0
    var minute: Int = 0
    var hy: [Int] = []
    var numSelected: Int = 0
    
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

