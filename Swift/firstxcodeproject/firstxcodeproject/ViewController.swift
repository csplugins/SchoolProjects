//
//  ViewController.swift
//  firstxcodeproject
//
//  Created by Skala,Cody on 10/9/15.
//  Copyright © 2015 Skala,Cody. All rights reserved.
//

import UIKit

class ViewController: UIViewController , UITextFieldDelegate{

    @IBOutlet weak var animal1: UITextField!
    @IBOutlet weak var animal2: UITextField!
    @IBOutlet weak var animal3: UITextField!
    @IBOutlet weak var animal4: UITextField!
    @IBOutlet weak var animal5: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        animal1.delegate = self
        animal2.delegate = self
        animal3.delegate = self
        animal4.delegate = self
        animal5.delegate = self
        
        // load the dictionary
        loadData()
    }
    
    func loadData() {
        let paths = NSSearchPathForDirectoriesInDomains(.DocumentDirectory, .UserDomainMask, true) as NSArray
        let documentsDirectory = paths[0] as! String
        let path = documentsDirectory+"/rdata.plist"
        let fileManager = NSFileManager.defaultManager()
        //check if file exists
        if(!fileManager.fileExistsAtPath(path)) {
            // If it doesn't, copy it from the default file in the Bundle
            if let bundlePath = NSBundle.mainBundle().pathForResource("AnimalList", ofType: "plist") {
                let animalDictionary = NSMutableDictionary(contentsOfFile: bundlePath)
                print("Bundle GameData.plist file is --> \(animalDictionary?.description)")
                do{
                    try fileManager.copyItemAtPath(bundlePath, toPath: path)
                }
                catch{
                    print("Could not copy the bundled path")
                }
                print("Copied successfully")
            } else {
                print("AnimalList.plist not found. Please, make sure it is part of the bundle.")
            }
        } else {
            print("rdata.plist already exits at path.")
            // use this to delete file from documents directory
            /*do{
                try fileManager.removeItemAtPath(path)
            }
            catch{
                print("Removed")
            }*/
        }
        let rdataDictionary = NSMutableDictionary(contentsOfFile: path)
        print("Loaded rdata.plist file is --> \(rdataDictionary?.description)")
        let myDict = NSDictionary(contentsOfFile: path)
        if let dict = myDict {
            //loading values
            var s = dict.valueForKey("animal1") as! String
            animal1.text = s
            s = dict.valueForKey("animal2") as! String
            animal2.text = s
            s = dict.valueForKey("animal3") as! String
            animal3.text = s
            s = dict.valueForKey("animal4") as! String
            animal4.text = s
            s = dict.valueForKey("animal5") as! String
            animal5.text = s
        } else {
            print("WARNING: Couldn't create dictionary from rdata.plist! Default values will be used!")
            guard let path = NSBundle.mainBundle().pathForResource("AnimalList", ofType: "plist") else {
                print("Invalid path for plist")
                return
            }
            var data = NSDictionary(contentsOfFile: path) as? Dictionary<String, String>
            var s = data?["animal1"]
            animal1.text = s
            s = data?["animal2"]
            animal2.text = s
            s = data?["animal3"]
            animal3.text = s
            s = data?["animal4"]
            animal4.text = s
            s = data?["animal5"]
            animal5.text = s
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        let documentDir = NSSearchPathForDirectoriesInDomains(.DocumentDirectory, .UserDomainMask, true)[0] as String
        let url = NSURL(string: documentDir)
        guard let docURL = url?.URLByAppendingPathComponent("rdata.plist")else{ return false }
        if let docURLPath = docURL.path{
            var rdata = NSDictionary(contentsOfFile: docURLPath) as? Dictionary <String, String>
            var temp = animal1.text
            rdata?["animal1"] = temp
            temp = animal2.text
            rdata?["animal2"] = temp
            temp = animal3.text
            rdata?["animal3"] = temp
            temp = animal4.text
            rdata?["animal4"] = temp
            temp = animal5.text
            rdata?["animal5"] = temp
            if (rdata! as NSDictionary).writeToFile(docURLPath, atomically: true){
                print("Write success")
            }
        }
        return true
    }

}