/********************************************** 
 * CONFIDENTIAL AND PROPRIETARY 
 *
 * The source code and other information contained herein is the confidential and the exclusive property of
 * ZIH Corp. and is subject to the terms and conditions in your end user license agreement.
 * This source code, and any other information contained herein, shall not be copied, reproduced, published, 
 * displayed or distributed, in whole or in part, in any medium, by any means, for any purpose except as
 * expressly permitted under such license agreement.
 * 
 * Copyright ZIH Corp. 2010
 *
 * ALL RIGHTS RESERVED 
 ***********************************************/

#import <UIKit/UIKit.h>
#import "ZebraPrinter.h"

@interface ImagePrintDemoViewController : UIViewController<UIImagePickerControllerDelegate, UINavigationControllerDelegate> {
	UITextField *pathOnPrinterTextField;
	UISegmentedControl *printOrStoreToggle;
	UITextField *ipDnsTextField;
	UITextField *portTextField;
	NSString *ipDnsName;
	NSInteger port;
	NSString *pathOnPrinterText;
	BOOL isStoreSelected;
	UIActivityIndicatorView *loadingSpinner;
}

@property (nonatomic, retain) IBOutlet UITextField *pathOnPrinterTextField;
@property (nonatomic, retain) IBOutlet UISegmentedControl *printOrStoreToggle;
@property (nonatomic, assign) BOOL isStoreSelected;
@property (nonatomic, retain) IBOutlet UITextField *ipDnsTextField;
@property (nonatomic, retain) IBOutlet UITextField *portTextField;
@property (nonatomic, retain) NSString *ipDnsName;
@property (nonatomic, assign) NSInteger port;
@property (nonatomic, retain) NSString *pathOnPrinterText;
@property (nonatomic, retain) UIActivityIndicatorView *loadingSpinner;


-(IBAction)textFieldDoneEditing : (id)sender;
-(IBAction)backgroundTap : (id)sender;
-(IBAction)printOrStoreToggleValueChanged : (id)sender;
-(IBAction)pdfButtonPressed : (id)sender;
-(IBAction)cameraButtonPressed : (id)sender;
-(IBAction)photoAlbumButtonPressed : (id)sender;
@end
