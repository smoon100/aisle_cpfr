//
//  AppDelegate.m
//  four
//
//  Created by SEOHWAN.MOON on 1/15/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import "AppDelegate.h"
#import <ifaddrs.h>
#import <arpa/inet.h>

#define kMaxIdleTimeSeconds 900.0

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // saving an NSString
    testServerIp = @"192.168.1.198:8088";
    liveServerIp = @"192.168.200.109:8088";
    
    testCPFRServerIp = @"192.168.1.175:8080";
    
    programId = 2;
    
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    
    [prefs setValue:testServerIp forKey:@"ServerIP"]; // -(1) TEST SERVER
    //[prefs setValue:liveServerIp forKey:@"ServerIP"];  // -(2) LIVE SERVER
    
    [prefs setInteger:programId forKey:@"ProgramID"];
    
    
    // SET LANGUAGE FOR LABEL DESCRIPTION
    //languageDesc = @"KOREAN";
    //languageDesc = @"CHINESE";
    //[prefs setValue:languageDesc forKey:@"LANGUAGE"];
    //[prefs synchronize];
   
    
    
    
    BOOL is_right_store = FALSE;
    is_right_store = [self checkIsDeviceInStore];
    if(is_right_store){
        return YES;
    }else{
        return FALSE;
    }
}


							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
   // [[UIApplication sharedApplication] setIdleTimerDisabled:NO];
    //[self resetIdleTimer];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}



-(BOOL)checkIsDeviceInStore{
   // NSString *cur_device_ip = [self getIPAddress];
   // NSLog(cur_device_ip);
    //request JSON data ( true or false )
    return FALSE;
}

// Get IP Address
- (NSString *)getIPAddress {
    NSString *address = @"error";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if([[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"]) {
                    // Get NSString from C String
                    address = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr)];
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    // Free memory
    freeifaddrs(interfaces);
    //NSLog(address);
    return address;
}



/************   AUTO LOGOUT   ***************/

- (void)resetIdleTimer {
    //NSLog(@"resetIdleTimer");
    if (!idleTimer) {
        idleTimer = [NSTimer scheduledTimerWithTimeInterval:kMaxIdleTimeSeconds
                                                      target:self
                                                    selector:@selector(idleTimerExceeded)
                                                    userInfo:nil
                                                     repeats:NO];
    }
    else {
        if (fabs([idleTimer.fireDate timeIntervalSinceNow]) < kMaxIdleTimeSeconds-1.0) {
            [idleTimer setFireDate:[NSDate dateWithTimeIntervalSinceNow:kMaxIdleTimeSeconds]];
        }
    }
}

- (void)idleTimerExceeded {
    idleTimer = nil;
   // [self startScreenSaverOrSomethingInteresting];
    NSLog(@"Timer logtout");
    
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    BOOL isLoggedIn = [prefs boolForKey:@"IsLoggedIn"];
    // NSLog(@"login?:%d", isLoggedIn);
    if( isLoggedIn ){
       // NSLog(@"LogOut clicked");
        [prefs setBool:FALSE forKey:@"IsLoggedIn"];
        [prefs setValue:@"" forKey:@"REALNAME"];
        [prefs setValue:@"" forKey:@"UID"];
        
        [prefs synchronize];
    }
    
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    LoginViewController *loginViewController = [storyboard instantiateViewControllerWithIdentifier:@"LoginViewPage"];
    [(UINavigationController *)self.window.rootViewController pushViewController:loginViewController animated:YES];
    //[self resetIdleTimer];
}

- (UIResponder *)nextResponder {
    [self resetIdleTimer];
    return [super nextResponder];
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    [self resetIdleTimer];
}


/************   END OF AUTO LOGOUT   ***************/

@end
