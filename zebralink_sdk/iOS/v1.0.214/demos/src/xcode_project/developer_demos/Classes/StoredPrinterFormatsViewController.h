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

@interface StoredPrinterFormatsViewController : UITableViewController {
	NSArray *printerFormats;
	NSArray *variables;
	NSString *ipDnsName;
	NSInteger port;
	UIActivityIndicatorView *loadingSpinner;
}

@property (nonatomic, retain) NSArray *printerFormats;
@property (nonatomic, retain) NSArray *variables;
@property (nonatomic, retain) NSString *ipDnsName;
@property (nonatomic, assign) NSInteger port;
@property (nonatomic, retain) UIActivityIndicatorView *loadingSpinner;

-(id)initWithFormats:(NSArray*)formats withIpDnsName:(NSString *)anIpDnsName andPort:(NSInteger)aPort;

@end
