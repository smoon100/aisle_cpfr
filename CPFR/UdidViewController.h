//
//  UdidViewController.h
//  AisleMaster
//
//  Created by SEOHWAN.MOON on 2/10/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UdidViewController : UIViewController<UIPickerViewDataSource, UIPickerViewDelegate, UITextFieldDelegate>{
    NSString *serverIp;
    int programId;
    
    IBOutlet UITextField *txtUdid;
    
    IBOutlet UITextField *txtAppVersion;
    
    IBOutlet UITextField *txtStoreName;
    
    NSDictionary *dic_stores;
    NSArray *list_stores;
    
    UIPickerView *store_picker;
}



- (IBAction)registerBtnClicked:(id)sender;
- (IBAction)backgroundClicked:(id)sender;

@end
