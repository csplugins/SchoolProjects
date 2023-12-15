//
//  Locations.swift
//  UA Eats
//
//  Created by Klenotic,Andrew on 12/9/15.
//  Copyright © 2015 Cameron Reilly. All rights reserved.
//

import Foundation
import MapKit

class Locations: NSObject, MKAnnotation {
    var title: String?
    let address: String
    let paytype: String
    let coordinate: CLLocationCoordinate2D
    
    init(title: String, address: String, paytype: String, coordinate: CLLocationCoordinate2D) {
        self.title = title
        self.address = address
        self.paytype = paytype
        self.coordinate = coordinate
        
        super.init()
    }
    
    var subtitle: String? {
        return "Takes: " + paytype + ", Address: " + address
    }
    func pinColor() -> UIColor  {
        print("PinColor")
        switch paytype {
        case "Dining $$$":
            return UIColor.blueColor()
        case "Swipes":
            return UIColor.yellowColor()
        default:
            return UIColor.greenColor()
        }
    }

}