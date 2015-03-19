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

@interface PrintPreviewController : UIViewController<UIWebViewDelegate> {
	UIWebView *webView;
	NSString *path;
	BOOL storeSelected;
	NSString *pathOnPrinter;
	UIActivityIndicatorView *loadingSpinner;
	NSString *ipDnsName;
	NSInteger port;
}

@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, copy) NSString *path;
@property (nonatomic, copy) NSString *pathOnPrinter;
@property (nonatomic, assign) BOOL storeSelected;
@property (nonatomic, retain) UIActivityIndicatorView *loadingSpinner;
@property (nonatomic, retain) NSString *ipDnsName;
@property (nonatomic, assign) NSInteger port;

-(id)initWithPath:(NSString*)aPath withStoreSelected:(BOOL)isStoreSelected withIpDnsName:(NSString *)anIpDnsName withPort:(NSInteger)aPort andPathOnPrinter:(NSString*)aPathOnPrinter;
-(IBAction)print:(id)sender;

@end
