//
//  DataViewController.swift
//  MidTerm
//
//  Created by Skala,Cody on 11/3/15.
//  Copyright © 2015 Skala,Cody. All rights reserved.
//

import UIKit

class DataViewController: UIViewController {

    //Referencing outlet to the label at the top of the page
    @IBOutlet weak var dataLabel: UILabel?
    var dataObject: String = ""


    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        //The dataLabel is set to "" initially but will be changed
        self.dataLabel?.text = dataObject
    }


}

