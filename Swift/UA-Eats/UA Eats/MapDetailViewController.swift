//
//  MapDetailViewController.swift
//  UA Eats
//
//  Created by Klenotic,Andrew on 12/16/15.
//  Copyright © 2015 Cameron Reilly. All rights reserved.
//

import UIKit
import MapKit
import CoreLocation


class MapDetailViewController: UIViewController, MKMapViewDelegate, CLLocationManagerDelegate {
    
    
//    @IBOutlet weak var mapView: MKMapView!

    @IBOutlet weak var mapDetailView: MKMapView!
    
    var data: Dictionary<String, Dictionary<String, String>>?
    
    let locationManager = CLLocationManager()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        mapDetailView.delegate = self
        
        // Do any additional setup after loading the view.
        self.locationManager.delegate = self
        self.locationManager.desiredAccuracy = kCLLocationAccuracyBest
        self.locationManager.requestWhenInUseAuthorization()
        self.locationManager.startUpdatingLocation()
        self.mapDetailView.showsUserLocation = true
        print("Swipes")
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
            mapDetailView.addAnnotation(location)
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
            mapDetailView.addAnnotation(location)
            mapDetailView.tintColor = UIColor.redColor()
        }
        
        
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func locationManager(manager: CLLocationManager, didUpdateLocations locations: [CLLocation])
    {
        let location = locations.last
        
        let center = CLLocationCoordinate2D(latitude: location!.coordinate.latitude, longitude: location!.coordinate.longitude)
        
        let region = MKCoordinateRegion(center: center, span: MKCoordinateSpan(latitudeDelta: 0.01, longitudeDelta: 0.01))
        
        self.mapDetailView.setRegion(region, animated: true)
        
        self.locationManager.stopUpdatingLocation()
    }
    
    func locationManager(manager: CLLocationManager, didFailWithError error: NSError)
    {
        print("Did not allow... Errors: " + error.localizedDescription)
        let center = CLLocationCoordinate2D(latitude: 41.0752, longitude: -81.5115)
        
        let region = MKCoordinateRegion(center: center, span: MKCoordinateSpan(latitudeDelta: 0.01, longitudeDelta: 0.01))
        
        self.mapDetailView.setRegion(region, animated: true)
    }
}
