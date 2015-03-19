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
#import "ZebraPrinterConnection.h"



@interface StoredFormatViewController : UIViewController {
	UIActivityIndicatorView *loadingSpinner;
	id<ZebraPrinter,NSObject> printer;
	id<ZebraPrinterConnection, NSObject> printerConnection;
	UITextField *ipDnsTextField;
	UITextField *portTextField;
	UIButton *getFormatsButton;
	NSString *ipDnsName;
	NSInteger port;
	NSArray *fileNames;
}

@property (nonatomic,retain) IBOutlet UITextField *ipDnsTextField;
@property (nonatomic,retain) IBOutlet UITextField *portTextField;
@property (nonatomic,retain) IBOutlet UIButton *getFormatsButton;
@property (nonatomic, retain) UIActivityIndicatorView *loadingSpinner;
@property (nonatomic, retain) id<ZebraPrinterConnection, NSObject> printerConnection;
@property (nonatomic, retain) id<ZebraPrinter,NSObject> printer;
@property (nonatomic, retain) NSString *ipDnsName;
@property (nonatomic, assign) NSInteger port;
@property (nonatomic, retain) NSArray *fileNames;

-(IBAction)buttonPressed:(id)sender;
-(IBAction)textFieldDoneEditing : (id)sender;
-(IBAction)backgroundTap : (id)sender;

@end
