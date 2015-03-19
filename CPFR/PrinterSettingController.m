//
//  PrinterSettingController.m
//  four
//
//  Created by SEOHWAN.MOON on 1/20/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import "PrinterSettingController.h"
#import "LoginViewController.h"


@interface PrinterSettingController ()

@end

@implementation PrinterSettingController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}
- (void)viewDidAppear:(BOOL)animated{
    [self showDefaultPrinter];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSLog(@"printer setting view is open");
    
    [self showDefaultPrinter];
    //self.txtCurPrinter.userInteractionEnabled = NO;
	// Do any additional setup after loading the view.
  
    [self customizeBtn];
    [self createLogoutBtn];
}

-(void)showDefaultPrinter{
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    NSString *printerIP = [prefs stringForKey:@"DefaultPrinterIP"];
    self.txtCurPrinter.text = printerIP;
}

-(void)customizeBtn{
    UIImage *buttonImage = [[UIImage imageNamed:@"greyButton.png"]
                            resizableImageWithCapInsets:UIEdgeInsetsMake(18, 18, 18, 18)];
    UIImage *buttonImageHighlight = [[UIImage imageNamed:@"greyButtonHighlight.png"]
                                     resizableImageWithCapInsets:UIEdgeInsetsMake(18, 18, 18, 18)];
    // Set the background for any states you plan to use
    [btnEditDefault setBackgroundImage:buttonImage forState:UIControlStateNormal]
    ;
    [btnEditDefault setBackgroundImage:buttonImageHighlight forState:UIControlStateHighlighted];
    //
    [btnSavePrinter setBackgroundImage:buttonImage forState:UIControlStateNormal]
    ;
    [btnSavePrinter setBackgroundImage:buttonImageHighlight forState:UIControlStateHighlighted];
}



-(void)createLogoutBtn{
    UIButton *btnLogout = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 60, 40)];
    
    //[btnLogin setTitle:@"LOGOUT" forState:UIControlStateNormal];
    [btnLogout setImage:[UIImage imageNamed:@"logout-button.png"] forState:UIControlStateNormal];
    [btnLogout setTitle:@"logout" forState:UIControlStateNormal];
    [btnLogout addTarget:self action:@selector(logoutClicked) forControlEvents:UIControlEventTouchUpInside];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:btnLogout];
}

-(void)logoutClicked{
    NSLog(@"logout clicked");
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    BOOL isLoggedIn = [prefs boolForKey:@"IsLoggedIn"];
    // NSLog(@"login?:%d", isLoggedIn);
    if( isLoggedIn ){
        NSLog(@"LogOut clicked");
        [prefs setBool:FALSE forKey:@"IsLoggedIn"];
        [prefs setValue:@"" forKey:@"REALNAME"];
        [prefs setValue:@"" forKey:@"UID"];
        
        [prefs synchronize];
    }
    //[self performSegueWithIdentifier:@"segue.receiving.logout" sender:self];
    LoginViewController *loginViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"LoginViewPage"];
    [self.navigationController pushViewController:loginViewController animated:YES];
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)saveBtnClicked:(id)sender {
    NSString *printer_to_save = self.txtCurPrinter.text;
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    [prefs setValue:printer_to_save forKey:@"DefaultPrinterIP"];
    [prefs synchronize];
    
    UIAlertView *alert_result = [[UIAlertView alloc] initWithTitle:@"INFO MESSAGE" message:@"Default Printer is saved!" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
  
    [alert_result show];
}
/*
-(void) backgroundClicked:(id)sender{
    [self.txtCurPrinter resignFirstResponder];
}*/
- (IBAction)backgroundClicked:(id)sender {
    [self.txtCurPrinter resignFirstResponder];
}
@end
