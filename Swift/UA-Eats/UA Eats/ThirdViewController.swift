//
//  ThirdViewController.swift
//  UA Eats
//
//  Created by Cameron Reilly on 11/5/15.
//  Copyright © 2015 Cameron Reilly. All rights reserved.
//

import UIKit
import MapKit
import CoreLocation

// class ThirdViewController: UIViewController, MKMapViewDelegate, CLLocationManagerDelegate {
class ThirdViewController: UIViewController, CLLocationManagerDelegate {
//    class ThirdViewController: UIViewController, CLLocationManagerDelegate {


    @IBOutlet weak var mapView: MKMapView!
    
    var data: Dictionary<String, Dictionary<String, String>>?
    var destination: Locations!

    let locationManager = CLLocationManager()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
      
        mapView.delegate = self
        
        // Do any additional setup after loading the view.
        self.locationManager.delegate = self
        self.locationManager.desiredAccuracy = kCLLocationAccuracyBest
        self.locationManager.requestWhenInUseAuthorization()
        self.locationManager.startUpdatingLocation()
        self.mapView.showsUserLocation = true
        if destination == nil {
            data = {
                guard let path = NSBundle.mainBundle().pathForResource("swipes", ofType: "plist") else {
                    fatalError("Invalid path for plist")
                }
                return NSDictionary(contentsOfFile: path) as? Dictionary<String, Dictionary <String, String>>
                }()
            for (name,info) in data! {
                print("Name: \(name)")
                let location = Locations(title: info["name"]!,
                    address: info["address"]!,
                    paytype: "Swipes",
                    coordinate: CLLocationCoordinate2D(latitude: Double(info["coodinateX"]!)!, longitude: Double(info["coodinateY"]!)!))
                    mapView.addAnnotation(location)
            }
            print("Dining $$$")
            data = {
                guard let path = NSBundle.mainBundle().pathForResource("dining", ofType: "plist") else {
                    fatalError("Invalid path for plist")
                }
                return NSDictionary(contentsOfFile: path) as? Dictionary<String, Dictionary <String, String>>
                }()
            for (name,info) in data! {
                print("Name: \(name)")
                let location = Locations(title: info["name"]!,
                    address: info["address"]!,
                    paytype: "Dining $$$",
                    coordinate: CLLocationCoordinate2D(latitude: Double(info["coodinateX"]!)!, longitude: Double(info["coodinateY"]!)!))
                print("AddAnnotation")
                mapView.addAnnotation(location)
                mapView.tintColor = UIColor.redColor()
            }
        }
        else {
            mapView.addAnnotation(destination)
            mapView.tintColor = UIColor.redColor()
           
        }
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func locationManager(manager: CLLocationManager, didUpdateLocations locations: [CLLocation])
    {
        if destination == nil {
            let location = locations.last
            let center = CLLocationCoordinate2D(latitude: location!.coordinate.latitude, longitude: location!.coordinate.longitude)
            let region = MKCoordinateRegion(center: center, span: MKCoordinateSpan(latitudeDelta: 0.01, longitudeDelta: 0.01))
            self.mapView.setRegion(region, animated: true)
            self.locationManager.stopUpdatingLocation()
        }
        else {
            // let location = locations.last
            let center = destination.coordinate
            let region = MKCoordinateRegion(center: center, span: MKCoordinateSpan(latitudeDelta: 0.01, longitudeDelta: 0.01))
            self.mapView.setRegion(region, animated: true)
            self.locationManager.stopUpdatingLocation()
           
        }
    }
    
    func locationManager(manager: CLLocationManager, didFailWithError error: NSError)
    {
        print("Did not allow... Errors: " + error.localizedDescription)
        if destination == nil {
            let center = CLLocationCoordinate2D(latitude: 41.0752, longitude: -81.5115)
            let region = MKCoordinateRegion(center: center, span: MKCoordinateSpan(latitudeDelta: 0.01, longitudeDelta: 0.01))
            self.mapView.setRegion(region, animated: true)
        }
        else {
            let center = destination.coordinate
            let region = MKCoordinateRegion(center: center, span: MKCoordinateSpan(latitudeDelta: 0.01, longitudeDelta: 0.01))
            self.mapView.setRegion(region, animated: true)
            
        }
    }
}
