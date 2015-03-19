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

#import "MulticastViewController.h"
#import "NetworkDiscoverer.h"
#import "DiscoveredPrintersViewController.h"

@implementation MulticastViewController

- (void)viewDidLoad {
	self.title = @"Multicast";
	[super viewDidLoad];
}

-(void)buttonPressed:(id)sender {
	[self.discoveryParamTextField resignFirstResponder];
	[self startSpinner];
	[NSThread detachNewThreadSelector:@selector(doDiscovery:) toTarget:self withObject:self.discoveryParamTextField.text];
}

- (void) doDiscovery :(NSInteger*)numHops {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	NSError *error = nil;
	NSNumberFormatter *formatter = [[[NSNumberFormatter alloc]init] autorelease];
	[formatter setNumberStyle:kCFNumberFormatterDecimalStyle];
	NSNumber *hops  = [formatter numberFromString:self.discoveryParamTextField.text];
	NSArray *printers;
	if(hops == nil){
		[self stopSpinner];
		[self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:@"Invalid hop count" waitUntilDone:YES];
	} else {
		printers = [NetworkDiscoverer multicastWithHops:[hops integerValue] error:&error];
		[self stopSpinner];		
		if(printers != nil) {
			UIViewController *anotherViewController= [[DiscoveredPrintersViewController alloc] initWithPrinters:printers];
			[self.navigationController pushViewController:anotherViewController animated:YES];
			[anotherViewController release];
		} else {
			[self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:[error localizedDescription] waitUntilDone:YES];
		}
		
	}
	[self setButtonState:YES];
	[pool release];
}

@end

