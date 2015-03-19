//
//  AppDelegate.h
//  four
//
//  Created by SEOHWAN.MOON on 1/15/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LoginViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>{
    //AisleMaster JSP
    NSString *testServerIp;
    NSString *liveServerIp;
    
    //CPFR JSP
    NSString *testCPFRServerIp;
    
    //Program ID
    int programId;
    
    NSString *languageDesc;
    NSTimer *idleTimer;
}

@property (strong, nonatomic) UIWindow *window;

@end
