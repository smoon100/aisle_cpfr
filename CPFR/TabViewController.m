//
//  TabViewController.m
//  AisleMaster
//
//  Created by SEOHWAN.MOON on 2/28/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import "TabViewController.h"

@interface TabViewController ()

@end

@implementation TabViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    NSLog(@"tab view opend");
    
    
    //UITabBarController *tabBarController = (UITabBarController *)self.window.rootViewController;
    UITabBar *tabBar = self.tabBar;
    
    UITabBarItem *tabBarItem1 = [tabBar.items objectAtIndex:0];
    UITabBarItem *tabBarItem2 = [tabBar.items objectAtIndex:1];
    //UITabBarItem *tabBarItem3 = [tabBar.items objectAtIndex:1];
   // UITabBarItem *tabBarItem4 = [tabBar.items objectAtIndex:3];
    
    tabBarItem1.title = @"ORDER";
    //tabBarItem2.title = @"SCAN&PRINT";
    tabBarItem2.title = @"CONNET";
    //tabBarItem4.title = @"MORE";
    
    [tabBarItem1 setImage:[[UIImage imageNamed:@"caravan.png"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]];
    
    //[tabBarItem2 setImage:[[UIImage imageNamed:@"torch-light.png"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]];
    
    [tabBarItem2 setImage:[[UIImage imageNamed:@"printer.png"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]];
    
   // [tabBarItem4 setImage:[[UIImage imageNamed:@"monitor.png"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]];
    
    //tabBar.selectedItem = tabBarItem2;
    [self setSelectedIndex:0];
    NSLog(@"ok");
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
