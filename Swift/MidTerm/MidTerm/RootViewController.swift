//
//  RootViewController.swift
//  MidTerm
//
//  Created by Skala,Cody on 11/3/15.
//  Copyright © 2015 Skala,Cody. All rights reserved.
//

import UIKit

class RootViewController: UIViewController, UIPageViewControllerDelegate {

    var pageViewController: UIPageViewController?


    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        // Configure the page view controller and add it as a child view controller.
        self.pageViewController = UIPageViewController(transitionStyle: .PageCurl, navigationOrientation: .Horizontal, options: nil)
        self.pageViewController?.delegate = self

        //Check to see if self.storyboard exists and abort with an error if it doesn't
        guard let ss = self.storyboard else{
            fatalError("Could not load self.storyboard in function \(__FUNCTION__) on line \(__LINE__)")
        }
        //Check to see if self.modelController.viewControllerAtIndex exists and abort with an error if it doesn't
        guard let modelController = self.modelController.viewControllerAtIndex(0, storyboard: ss) else{
            fatalError("Could not load self.modelViewController.viewControllerAtIndex in function \(__FUNCTION__) on line \(__LINE__)")
        }
        //This determines the default view that will load
        let startingViewController: DataViewController = modelController
        let viewControllers = [startingViewController]
        self.pageViewController?.setViewControllers(viewControllers, direction: .Forward, animated: false, completion: {done in })

        //The following allows the Model to communicate with the Controller of the MVC
        self.pageViewController?.dataSource = self.modelController

        //Check to see if self.pageViewController exists and abort with an error if it doesn't
        guard let spVC = self.pageViewController else{
            fatalError("Could not load self.pageViewController in function \(__FUNCTION__) on line \(__LINE__)")
        }
        //Removing the following will break the dual view on the bigger width devices like the iPad 2 when rotated on its side
        self.addChildViewController(spVC)
        self.view.addSubview(spVC.view)

        // Set the page view controller's bounds using an inset rect so that self's view is visible around the edges of the pages.
        //This section didn't seem to change anything so the code has been commented out.
        /*var pageViewRect = self.view.bounds
        if UIDevice.currentDevice().userInterfaceIdiom == .Pad {
            pageViewRect = CGRectInset(pageViewRect, 40.0, 40.0)
        }
        self.pageViewController?.view.frame = pageViewRect

        self.pageViewController?.didMoveToParentViewController(self)*/

        // Add the page view controller's gesture recognizers to the book view controller's view so that the gestures are started more easily.
        //Not really necessary so commented out as well
        self.view.gestureRecognizers = self.pageViewController?.gestureRecognizers
    }
    
    //Don't really need this function
    /*
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }*/

    //The modelController is used to appropriately assign a ModelController() for the first time
    var modelController: ModelController {
        // Return the model controller object, creating it if necessary.
        // In more complex implementations, the model controller may be passed to the view controller.
        if _modelController == nil {
            _modelController = ModelController()
        }
        
        //Check to see if _modelController exists and abort with an error if it doesn't
        guard let mC = _modelController else{
            fatalError("Could not load _modelController in function \(__FUNCTION__) on line \(__LINE__)")
        }
        return mC
    }

    //Was able to make this field lazy without errors. Save memory, save lives
    lazy var _modelController: ModelController? = nil

    // MARK: - UIPageViewController delegate methods

    //This function will determine if the current view can support showing two pages of the book or not
    func pageViewController(pageViewController: UIPageViewController, spineLocationForInterfaceOrientation orientation: UIInterfaceOrientation) -> UIPageViewControllerSpineLocation {
        if (orientation == .Portrait) || (orientation == .PortraitUpsideDown) || (UIDevice.currentDevice().userInterfaceIdiom == .Phone) {
            // In portrait orientation or on iPhone: Set the spine position to "min" and the page view controller's view controllers array to contain just one view controller. Setting the spine position to 'UIPageViewControllerSpineLocationMid' in landscape orientation sets the doubleSided property to true, so set it to false here.
            
            //Check to see if self.pageViewController.viewControllers exists and abort with an error if it doesn't
            guard let currentViewController = self.pageViewController?.viewControllers?[0] else{
                fatalError("Could not make currentViewController in function \(__FUNCTION__) on line \(__LINE__)")
            }
            let viewControllers = [currentViewController]
            self.pageViewController?.setViewControllers(viewControllers, direction: .Forward, animated: true, completion: {done in })

            //If we only see one view, we don't want anything printed on the back of it because when the page is turned, it's never seen
            self.pageViewController?.doubleSided = false
            //Returns the left side of the sceen so pages flip as if it is only on the right hand side of a book
            return .Min
        }

        // In landscape orientation: Set set the spine location to "mid" and the page view controller's view controllers array to contain two view controllers. If the current page is even, set it to contain the current and next view controllers; if it is odd, set the array to contain the previous and current view controllers.
        
        //Check to see if self.pageViewController.viewControllers exists and abort with an error if it doesn't
        guard let currentViewController = self.pageViewController?.viewControllers?[0] as? DataViewController else{
            fatalError("Could not make currentViewController as? DataViewController in function \(__FUNCTION__) on line \(__LINE__)")
        }
        var viewControllers: [UIViewController]

        let indexOfCurrentViewController = self.modelController.indexOfViewController(currentViewController)
        
        if (indexOfCurrentViewController == 0) || (indexOfCurrentViewController % 2 == 0) {
            //Check to see if self.pageViewController exists and abort with an error if it doesn't
            guard let spVC = self.pageViewController else{
                fatalError("Could not load self.pageViewController in function \(__FUNCTION__) on line \(__LINE__)")
            }
            let nextViewController = self.modelController.pageViewController(spVC, viewControllerAfterViewController: currentViewController)
            //Check to see if nextViewController exists and abort with an error if it doesn't
            guard let nVC = nextViewController else{
                fatalError("Could not load nextViewController in function \(__FUNCTION__) on line \(__LINE__)")
            }
            viewControllers = [currentViewController, nVC]
        } else {
            //Check to see if self.pageViewController exists and abort with an error if it doesn't
            guard let spVC = self.pageViewController else{
                fatalError("Could not load self.pageViewController in function \(__FUNCTION__) on line \(__LINE__)")
            }
            let previousViewController = self.modelController.pageViewController(spVC, viewControllerBeforeViewController: currentViewController)
            //Check to see if previousViewController exists and abort with an error if it doesn't
            guard let pVC = previousViewController else{
                fatalError("Could not load previousViewController in function \(__FUNCTION__) on line \(__LINE__)")
            }
            viewControllers = [pVC, currentViewController]
        }
        //There really should be another check here for if the current page is the last page to prevent a crash for odd numbered arrays on double spine view
        
        //This needs to be here or we crash when rotating the device
        self.pageViewController?.setViewControllers(viewControllers, direction: .Forward, animated: true, completion: {done in })
        //Returns the middle of the screen (width) as if this is a real book
        return .Mid
    }


}

