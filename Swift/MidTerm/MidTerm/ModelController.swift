//
//  ModelController.swift
//  MidTerm
//
//  Created by Skala,Cody on 11/3/15.
//  Copyright © 2015 Skala,Cody. All rights reserved.
//

import UIKit

/*
 A controller object that manages a simple model -- a collection of month names.
 
 The controller serves as the data source for the page view controller; it therefore implements pageViewController:viewControllerBeforeViewController: and pageViewController:viewControllerAfterViewController:.
 It also implements a custom method, viewControllerAtIndex: which is useful in the implementation of the data source methods, and in the initial configuration of the application.
 
 There is no need to actually create view controllers for each page in advance -- indeed doing so incurs unnecessary overhead. Given the data model, these methods create, configure, and return a new view controller on demand.
 */


class ModelController: NSObject, UIPageViewControllerDataSource {

    var pageData: [String] = []


    override init() {
        super.init()
        // Create the data model.
        //Interestingly, if there is an odd number of items, and you have two pages of the book displaying, the app will crash when you try to flip to the last page
        let catNames: [String] = ["Pete", "Buster", "Mikky", "Feline", "Tyger", "Princess", "Tommy", "Harry"]
        pageData = catNames
    }

    func viewControllerAtIndex(index: Int, storyboard: UIStoryboard) -> DataViewController? {
        // Return the data view controller for the given index.
        if (self.pageData.count == 0) || (index >= self.pageData.count) {
            return nil
        }

        // Create a new view controller and pass suitable data.
        guard let dataViewController = storyboard.instantiateViewControllerWithIdentifier("DataViewController") as? DataViewController else{
            fatalError("Could not instantiate the view controller With Identifier for the storyboard as? DataViewController in function \(__FUNCTION__) on line \(__LINE__)")
        }
        //Allow the data to be shown on the page. Removing this will not show a page label and not allow you to flip pages. App crashed without it when trying to rotate
        dataViewController.dataObject = self.pageData[index]
        return dataViewController
    }

    func indexOfViewController(viewController: DataViewController) -> Int {
        // Return the index of the given data view controller.
        // For simplicity, this implementation uses a static array of model objects and the view controller stores the model object; you can therefore use the model object to identify the index.
        return pageData.indexOf(viewController.dataObject) ?? NSNotFound
    }

    // MARK: - Page View Controller Data Source

    //Used for looking at the previous page. This is useful to keep things in order and ensure we don't fip to an out of bounds page
    func pageViewController(pageViewController: UIPageViewController, viewControllerBeforeViewController viewController: UIViewController) -> UIViewController? {
        guard let vC = viewController as? DataViewController else{
            fatalError("Could not cast viewController as? DataViewController in function \(__FUNCTION__) on line \(__LINE__)")
        }
        var index = self.indexOfViewController(vC)
        if (index == 0) || (index == NSNotFound) {
            return nil
        }
        
        //Change the page count to keep flipping between pages in bound and display the proper next item in the array
        index--
        guard let vCS = viewController.storyboard else{
            fatalError("Could not find viewController.storyboard in function \(__FUNCTION__) on line \(__LINE__)")
        }
        return self.viewControllerAtIndex(index, storyboard: vCS)
    }

    //Used for looking at the next page. This is also useful to keep things in order and ensure we don't fip to an out of bounds page
    func pageViewController(pageViewController: UIPageViewController, viewControllerAfterViewController viewController: UIViewController) -> UIViewController? {
        guard let vC = viewController as? DataViewController else{
            fatalError("Could not cast viewController as? DataViewController in function \(__FUNCTION__) on line \(__LINE__)")
        }
        var index = self.indexOfViewController(vC)
        if index == NSNotFound {
            return nil
        }
        
        //Change the page count to keep flipping between pages in bound and display the proper next item in the array
        index++
        if index == self.pageData.count {
            return nil
        }
        guard let vCS = viewController.storyboard else{
            fatalError("Could not find viewController.storyboard in function \(__FUNCTION__) on line \(__LINE__)")
        }
        return self.viewControllerAtIndex(index, storyboard: vCS)
    }

}

