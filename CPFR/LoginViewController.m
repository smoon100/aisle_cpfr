//
//  LoginViewController.m
//  four
//
//  Created by SEOHWAN.MOON on 1/15/14.
//  Copyright (c) 2014 moon. All rights reserved.
//
// NSUSERDefault Values : StoreNumber, IsLoggedIn

#define kBgQueue dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0 )
#define TAG_DEVICE_ALERT 1
#define TAG_UPDATE_ALERT 2
#define TAG_LOGIN_ALERT 3
#define TAG_STORENUM_ALERT 4
#define TAG_SERVER_CONN_ALERT 5


#import "LoginViewController.h"



@interface LoginViewController ()

@end

@implementation LoginViewController



// scroll view
-(void)viewDidLayoutSubviews{
    [super viewDidLayoutSubviews];
    [scrollView layoutIfNeeded];
    scrollView.contentSize= ContentView.bounds.size;
    [scrollView setContentSize:(CGSizeMake(320, 900))];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    serverIp = [prefs valueForKey:@"ServerIP"];
    programId = [prefs integerForKey:@"ProgramID"];
    
    //init page
    [self initPage];
    // login btn custom
    [self customizeBtn];
    // input disabled
    txtViewLogin.userInteractionEnabled = NO;
    
    txtUserName.delegate = self;
    txtPassword.delegate = self;
    
    
    
}

-(void)textFieldDidBeginEditing:(UITextField *)textField{
    CGPoint scrollPoint = CGPointMake(0, textField.frame.origin.y/2);
    [scrollView setContentOffset:scrollPoint animated:YES];
}

-(void)textFieldDidEndEditing:(UITextField *)textField{
    //CGPoint scrollPoint = CGPointMake(0, textField.frame.origin.y);
    [scrollView setContentOffset:CGPointZero animated:YES];
}


-(void)initPage{
    // (1)get store number by AP ip address
    NSString *urlForStoreNumber = [NSString stringWithFormat:@"http://%@/AISLEMASTER/json/reply_store_num.jsp?", serverIp] ;
    
    [self jsonFromUrl:(NSString *) urlForStoreNumber];
    
    // (2)update current device app version and get device info
    //NSString *uuid =  [[[UIDevice currentDevice] identifierForVendor] UUIDString];
    NSString *uuid =  [[[UIDevice currentDevice] identifierForVendor] UUIDString];
    NSString *appVer = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    
    // (3)device register & version upgrade check
    
    
    NSString *urlForDeviceCheck = [NSString stringWithFormat:@"http://%@/AISLEMASTER/json/reply_device_cpfr.jsp?", serverIp] ;
    
    urlForDeviceCheck = [urlForDeviceCheck stringByAppendingString:@"UDUD="];
    urlForDeviceCheck = [urlForDeviceCheck stringByAppendingString:uuid];
    
    urlForDeviceCheck = [urlForDeviceCheck stringByAppendingString:@"&AppVersion="];
    urlForDeviceCheck = [urlForDeviceCheck stringByAppendingString:appVer];
    
    urlForDeviceCheck = [urlForDeviceCheck stringByAppendingString:@"&ProgramId="];
    urlForDeviceCheck = [urlForDeviceCheck stringByAppendingString:[@(programId) stringValue]];
    
    //NSLog(urlForDeviceCheck);
    [self jsonFromUrl:(NSString *) urlForDeviceCheck];
    
    // (4)update login button ( login <-> logoiut)
    [self updateLoginView];
}


// read JSON data from given URL and call "fetchedData" and passing data as NSData.
-(void)jsonFromUrl:(NSString *) urlAddress{
    // tesing read product info from DB
    NSString *urlAsString = urlAddress;
    
    NSURL *rtnJsonURL = [NSURL URLWithString: (NSString *)urlAsString];
    
    //dispatch_async(kBgQueue, ^{
    NSData *data = [NSData dataWithContentsOfURL:rtnJsonURL];
    
    [self performSelectorOnMainThread: @selector(fetchedData:) withObject:data waitUntilDone:YES];
    
    // });
}


// json data has its type and result ( device, product, login ), so it will run by the type
// device type : 1.checkDeviceRegistered, 2.checkLatestVersion,
- (NSArray *) fetchedData:(NSData *) responseData {
    // [displayStatus setText:@"fetched Data"];
    NSError* error;
    
    if (responseData == nil) {
        UIAlertView *alert_store_number = [[UIAlertView alloc] initWithTitle:@"Info Message" message:@"Server is not responding" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
        alert_store_number.tag = TAG_SERVER_CONN_ALERT;
        [alert_store_number show];
        return nil;
    }
    
    NSDictionary* json = [NSJSONSerialization JSONObjectWithData:responseData options:kNilOptions error:&error];
    
    NSString* type = [json objectForKey:@"Type"];
    NSArray* result = [json objectForKey:@"Result"];
    
    //NSLog(@"Type: %@", type);
    NSArray *urlTypes = @[@"StoreNumber", @"Device", @"Login"];
    NSInteger int_type = [urlTypes indexOfObject:type];
    
    BOOL isDeviceRegistered = FALSE;
    switch (int_type) { // reply type
        case 0: // store number save
            if( [result isEqual: @"NotFound"]){
                UIAlertView *alert_store_number = [[UIAlertView alloc] initWithTitle:@"INFO MESSAGE" message:@"Your Store's IP Address is found  in our DB!" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
                alert_store_number.tag = TAG_STORENUM_ALERT;
                [alert_store_number show];
                // SETTING FOR MACBOOK IN HQ
                NSString *store_number = @"55";
                NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
                [prefs setValue:store_number forKey:@"StoreNumber"];
                [prefs synchronize];
                // END OF SETTING FOR MACBOOK IN HQ
                
            }else{
                NSLog(@"store found");
                NSDictionary *result_dic = [result objectAtIndex:0];
                NSString *store_number = [result_dic objectForKey:@"STORENUM"];
                NSString *label_lang = [result_dic objectForKey:@"LABEL_LANG"];
                
                NSLog(@"LABEL_LANG_NUM: %@", label_lang);
                // save store number into NSUSERDefault
                NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
                // saving an NSString
                [prefs setValue:store_number forKey:@"StoreNumber"];
                [prefs synchronize];
                //NSLog(@"init: Store Number saved");
            }
            
            break;
        case 1: // Device
            //(1) func to update cur version and check if the device is registered, otherwise show error msg.
            
            NSLog(@"result: %@", result);
            isDeviceRegistered = [self checkDeviceRegistered:(NSArray *)result];
            if( isDeviceRegistered){
                NSLog(@" Device is Registered");
                //(2) if registered, then check latest app version
                NSDictionary *result_dic = [result objectAtIndex:0];
                //NSLog(result_dic);
                NSString *app_version = [result_dic objectForKey:@"APP_VER"];
                NSString *latest_app_version = [result_dic objectForKey:@"LATEST_APP_VER"];
                
                float num_app_version = [app_version floatValue];
                float num_latest_app_version = [latest_app_version floatValue];
                
                if( num_app_version < num_latest_app_version){
                    NSLog(@"Device will update!");
                    UIAlertView *alert_app_update = [[UIAlertView alloc] initWithTitle:@"INFO MESSAGE" message:@"You should update the app version!" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
                    alert_app_update.tag = TAG_UPDATE_ALERT;
                    [alert_app_update show];
                    
                }else{
                    NSLog(@"Device do not need to update!");
                }
                
            }else{
                //show error msg like you need to register the device first.
                UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Wait" message:@"Your device should be registered. Please contact Aisle Master Administrator!" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
                alert.tag = TAG_DEVICE_ALERT;
                [alert show];
            }
            
            break;
            
        case 2: // login
            if( [result  isEqual: @"Not Found"]){ // json should return
                [txtViewLogin setText:@"Not Found! Please try it again!"];
            }else{
                // get the result info
                NSDictionary *detail = [result objectAtIndex:0];
                //NSLog(detail);
                // get item info from json
                NSString* userID = [detail objectForKey:@"USERID"];
                // NSString* storeno = [detail objectForKey:@"STORENO"];
                NSLog(userID);
                // NSLog(storeno);
                
                [txtViewLogin setText:@""];
                NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
                // saving an NSString
                [prefs setBool:true forKey:@"IsLoggedIn"];
                
                UIAlertView *alert_login_result = [[UIAlertView alloc] initWithTitle:@"INFO MESSAGE" message:@"You are logged in" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
                alert_login_result.tag = TAG_LOGIN_ALERT;
                [alert_login_result show];
            }
            
            break;
    }
    return result;
}



-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    switch (alertView.tag) {
        case TAG_DEVICE_ALERT:
            NSLog(@"alert device");
            //exit(0);
            break;
            
        case TAG_UPDATE_ALERT:
            NSLog(@"alert update");
            if(buttonIndex == 0){
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"https://appdeploy.hmart.com:8181/installCPFRApp.html"]];
            }
            break;
        case TAG_LOGIN_ALERT:
            if(buttonIndex == 0){
                [self performSegueWithIdentifier:@"segue.login.after" sender:self];
            }
            break;
            
        case TAG_STORENUM_ALERT:
            NSLog(@"alert store number");
            // exit(0);
            break;
        case TAG_SERVER_CONN_ALERT:
            // exit(0);
            break;
            
        default:
            break;
    }
    // NSLog(@"button index: %i", (int)buttonIndex);
}



-(BOOL)checkDeviceRegistered:(NSArray *) jsonResult{
    // get the result's first elem.
    if( [jsonResult  isEqual: @"NotFound"]){
        return 0;
    }else{
        return 1;
    }
}


- (IBAction)loginClicked:(id)sender {
    
    NSLog(@"Login clicked");
    
    // [self performSelectorOnMainThread:@selector(startSpinner) withObject:nil waitUntilDone:YES];
    
    NSString *username = txtUserName.text;
    username = [username stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    username = [username stringByReplacingOccurrencesOfString:@" " withString:@"%20"];
    NSString *password = txtPassword.text;
    if( [username  isEqual: @"admin"] && [password  isEqual: @"0214"]){
        NSLog(@"admin logined");
        [self performSegueWithIdentifier:@"segue.adminSetup" sender:self];
    }else{
        // device info
        NSString *urlForLogin = [NSString stringWithFormat:@"http://192.168.1.175:8080/BIEARWeb/AisleMasterLogIn.jsp?"] ;
        //NSString *urlForLogin = liveServerIp
        
        urlForLogin = [urlForLogin stringByAppendingString:@"userid="];
        urlForLogin = [urlForLogin stringByAppendingString:username];
        
        urlForLogin = [urlForLogin stringByAppendingString:@"&pwd="];
        urlForLogin = [urlForLogin stringByAppendingString:password];
        
        NSLog(urlForLogin);
        [self jsonFromUrl:(NSString *) urlForLogin];
    }
    
    
}

// receiving verification btn
/*
 - (IBAction)goRVClicked:(id)sender {
 [self performSegueWithIdentifier:@"segue.after.login.alert" sender:self];
 }*/

/*
 - (IBAction)enterClicked:(id)sender {
 NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
 [prefs setBool:TRUE forKey:@"IsLoggedIn"];
 
 [prefs synchronize];
 
 [self performSegueWithIdentifier:@"segue.login.after" sender:self];
 }*/

-(void)updateLoginView{
    
    [btnLogin setTitle:@"LOGIN" forState:UIControlStateNormal];
    // lblId.hidden = NO;
    // lblPassword.hidden = NO;
    txtUserName.hidden = NO;
    txtPassword.hidden = NO;
    txtUserName.text = @"";
    txtPassword.text = @"";
    //  btnGoRVPage.hidden = YES;
    
    [self.navigationController setNavigationBarHidden:YES];
    self.navigationItem.hidesBackButton = YES;
    // self.hidesBottomBarWhenPushed = YES;
    
}



-(void)startSpinner {
    self.spinner = [[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    CGRect mainBounds = [self.view bounds];
    [self.spinner setCenter:CGPointMake((mainBounds.size.width / 2), (mainBounds.size.height / 2))];
    [self.view addSubview:self.spinner];
    [self.spinner startAnimating];
}

-(void)stopSpinner {
    [self.spinner stopAnimating];
}


-(void) backgroundClicked:(id)sender{
    [txtUserName resignFirstResponder];
    [txtPassword resignFirstResponder];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



-(void)customizeBtn{
    UIImage *buttonImage = [[UIImage imageNamed:@"greyButton.png"]
                            resizableImageWithCapInsets:UIEdgeInsetsMake(18, 18, 18, 18)];
    UIImage *buttonImageHighlight = [[UIImage imageNamed:@"greyButtonHighlight.png"]
                                     resizableImageWithCapInsets:UIEdgeInsetsMake(18, 18, 18, 18)];
    // Set the background for any states you plan to use
    [btnLogin setBackgroundImage:buttonImage forState:UIControlStateNormal]
    ;
    [btnLogin setBackgroundImage:buttonImageHighlight forState:UIControlStateHighlighted];
}
@end
