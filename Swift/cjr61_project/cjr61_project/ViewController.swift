//
//  ViewController.swift
//  cjr61_project
//
//  Created by Cameron Reilly on 10/14/15.
//  Copyright © 2015 Cameron Reilly. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITextFieldDelegate {

    @IBOutlet weak var god: UITextField!
    @IBOutlet weak var pantheon: UITextField!
    @IBOutlet weak var godClass: UITextField!
    @IBOutlet weak var range: UITextField!
    @IBOutlet weak var godTitle: UITextField!
    
    var data: Dictionary<String, Dictionary<String, String>>?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        god.delegate = self
        
         data = {
            guard let path = NSBundle.mainBundle().pathForResource("data", ofType: "plist") else {
                print("Invalid path for plist")
                return nil
            }
            
            return NSDictionary(contentsOfFile: path) as? Dictionary<String, Dictionary <String, String>>
            }()
    
        print(data?["God"]!["Kali"])
        print(data?["Description"]!["Kali"])
        
    }
    
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        let godName = god.text
        print(godName)
        
        godTitle.text = data?["Description"]![god.text!]
        pantheon.text = data?["Pantheon"]![god.text!]
        godClass.text = data?["Class"]![god.text!]
        range.text = data?["AttackRange"]![god.text!]
        
        self.view.endEditing(true)
        
        return true
    }
    
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

