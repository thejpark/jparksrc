//
//  SavedViewTableController.swift
//  BabyName
//
//  Created by Park Jung Gyu on 18/04/2016.
//  Copyright © 2016 pyfamily. All rights reserved.
//

import UIKit


class SavedViewTableController: UITableViewController {
    
    var objects = [AnyObject]()
    
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
    
    func LoadTable() {
        var i:Int = 0
        for e in savedElements {
            objects.insert(e, at: i)
            i += 1
        }
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
        cell.textLabel!.font = UIFont(name: "Avenir", size:20);
        return cell
    }
    
    override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        // Return false if you do not want the specified item to be editable.
        return true
    }
    
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            objects.remove(at: (indexPath as NSIndexPath).row)
            savedElements.remove(at: (indexPath as NSIndexPath).row)
            saveElem()
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
                let controller = segue.destination as! SavedDetailViewController
                controller.detailItem = obj
            }
        }
    }
}
