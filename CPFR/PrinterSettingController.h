//
//  PrinterSettingController.h
//  four
//
//  Created by SEOHWAN.MOON on 1/20/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import <UIKit/UIKit.h>



@interface PrinterSettingController : UIViewController{
    
    IBOutlet UIButton *btnEditDefault;
    
    IBOutlet UIButton *btnSavePrinter;
}
@property (strong, nonatomic) IBOutlet UITextField *txtCurPrinter;
- (IBAction)saveBtnClicked:(id)sender;
//- (IBAction)backgroundClicked:(id)sender;
- (IBAction)backgroundClicked:(id)sender;

@end
