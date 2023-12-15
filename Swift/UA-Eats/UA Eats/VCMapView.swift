//
//  VCMapView.swift
//  UA Eats
//
//  Created by Klenotic, Andrew on 12/10/15.
//  Copyright © 2015 Cameron Reilly. All rights reserved.
//

import Foundation
import MapKit

extension ThirdViewController: MKMapViewDelegate {
    
    // 1
    func mapView(mapView: MKMapView,
        viewForAnnotation annotation: MKAnnotation) -> MKAnnotationView? {
            print("mapView")
            if let annotation = annotation as? Locations {
                let identifier = "pin"
                var view: MKPinAnnotationView
                if let dequeuedView = mapView.dequeueReusableAnnotationViewWithIdentifier(identifier)
                    as? MKPinAnnotationView { // 2
                        dequeuedView.annotation = annotation
                        view = dequeuedView
                } else {
                    // 3
                    view = MKPinAnnotationView(annotation: annotation, reuseIdentifier: identifier)
                    view.canShowCallout = true
                    view.calloutOffset = CGPoint(x: -5, y: 5)
                    //view.rightCalloutAccessoryView = UIButton(type: .DetailDisclosure) as UIView
                }
                
                view.pinTintColor = annotation.pinColor()
                
                return view
            }
            return nil
    }
    
    //func mapView(mapView: MKMapView, annotationView view: MKAnnotationView, calloutAccessoryControlTapped control: UIControl) {
    //  let location = view.annotation as! Locations
    //  let launchOptions = [MKLaunchOptionsDirectionsModeKey: MKLaunchOptionsDirectionsModeDriving]
    //  location.mapItem().openInMapsWithLaunchOptions(launchOptions)
    //}
    
}
