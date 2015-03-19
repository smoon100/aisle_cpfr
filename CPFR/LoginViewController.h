//
//  LoginViewController.h
//  four
//
//  Created by SEOHWAN.MOON on 1/15/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface LoginViewController : UIViewController<UITextFieldDelegate>{
    
    IBOutlet UIScrollView *scrollView;
    
    IBOutlet UIView *ContentView;
    
    IBOutlet UITextField *txtPassword;
    IBOutlet UITextField *txtUserName;
    IBOutlet UIButton *btnLogin;
   
    IBOutlet UITextView *txtViewLogin;
   
    NSString *languageDesc;
    NSString *serverIp;    
    int programId;
}

@property (nonatomic, retain) UIActivityIndicatorView  *spinner;

-(void)startSpinner;
-(void)stopSpinner;

- (IBAction)backgroundClicked:(id)sender;
- (IBAction)loginClicked:(id)sender;
//- (IBAction)goRVClicked:(id)sender;


//- (IBAction)enterClicked:(id)sender;

@end
