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

#import "StatusViewController.h"
#import "ZebraPrinterConnection.h"
#import	"TcpPrinterConnection.h"
#import "ZebraPrinter.h"
#import "ZebraPrinterFactory.h"
#import "PrinterStatus.h"
#import "PrinterStatusMessages.h"

@implementation StatusViewController

@synthesize statusLabel;
@synthesize ipDnsTextField;
@synthesize portTextField;
@synthesize testButton;
@synthesize printerStatusText;

- (void) setUserDefaults {
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	[self.ipDnsTextField setText:[defaults objectForKey:@"ipDnsName"]];
	[self.portTextField setText:[defaults objectForKey:@"portNum"]];
	
}

- (void) saveUserDefaults: (NSString *) ipDnsName portNumAsNsString: (NSString *) portNumAsNsString  {
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	[defaults setObject:ipDnsName forKey:@"ipDnsName"];
	[defaults setObject:portNumAsNsString forKey:@"portNum"];
	
}
+(BOOL) deviceOrientationIsLandscape {
	UIInterfaceOrientation actualDeviceOrientation = [UIApplication sharedApplication].statusBarOrientation;	
	return (actualDeviceOrientation == UIDeviceOrientationLandscapeLeft || actualDeviceOrientation == UIDeviceOrientationLandscapeRight);
}

- (void) viewWillAppear:(BOOL)animated {	
	[super viewWillAppear:(BOOL)animated];
	[self.printerStatusText setText:@""];
	self.printerStatusText.layer.borderWidth = 3;
	self.printerStatusText.layer.borderColor = [[UIColor grayColor] CGColor];
	self.printerStatusText.layer.cornerRadius = 8;
	if ([StatusViewController deviceOrientationIsLandscape]) {
		[self.printerStatusText setFrame:CGRectMake(109,180,280,70)];
		[self.printerStatusText flashScrollIndicators];
	} else {
		[self.printerStatusText setFrame:CGRectMake(20,185,280,202)];
	}
	[self setUserDefaults];
	
}

-(void)viewDidAppear:(BOOL)animated {
	self.title = @"Printer Status";
	[self.printerStatusText flashScrollIndicators];
	[super viewDidAppear:animated];
}

-(NSString*) getLanguageName :(PrinterLanguage)language {
	if(language == PRINTER_LANGUAGE_ZPL){
		return @"ZPL";
	} else {
		return @"CPCL";
	}
}

-(void) setButtonState : (BOOL)state {
	[self performSelectorOnMainThread:@selector(setTestButtonStateSelector:) withObject:[NSNumber numberWithBool:state] waitUntilDone:NO];
}

- (void) setTestButtonStateSelector : (NSNumber*)state {
	[self.testButton setEnabled:[state boolValue]];
}

-(void)setStatus: (NSString*)status withColor :(UIColor*)color {
	NSArray *statusInfo = [NSArray arrayWithObjects:status, color, nil];
	[self performSelectorOnMainThread:@selector(changeStatusLabel:) withObject:statusInfo waitUntilDone:NO];
	[NSThread sleepForTimeInterval:1];
}

-(IBAction)buttonPressed:(id)sender {
	NSString *ipDnsName = [self.ipDnsTextField text];
	NSString *portNumAsNsString = [self.portTextField text];
	
	NSArray *connectionInfo = [NSArray arrayWithObjects:ipDnsName, portNumAsNsString, nil];
	[self saveUserDefaults: ipDnsName portNumAsNsString: portNumAsNsString];
	[NSThread detachNewThreadSelector:@selector(performConnectionDemo:) toTarget:self withObject:connectionInfo];
}

-(void)updatePrinterStatusText: (NSString*)status {
	[self performSelectorOnMainThread:@selector(updatePrinterStatusTextOnGuiThread:) withObject:status waitUntilDone:NO];
	[NSThread sleepForTimeInterval:1];
}

- (void) performConnectionDemo : (NSArray*)connectionInfo {
	[self setButtonState:NO];
	NSString *ipDnsName = [connectionInfo objectAtIndex:0];
	NSString *portNumAsText = [connectionInfo objectAtIndex:1];
	NSInteger portNum = [portNumAsText intValue];
	
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	[self setStatus:@"Connecting..." withColor:[UIColor yellowColor]];
	
	id<ZebraPrinterConnection, NSObject> connection = [[TcpPrinterConnection alloc] initWithAddress:ipDnsName andWithPort:portNum];
	
	BOOL didOpen = [connection open];
	if(didOpen == YES) {	
		[self setStatus:@"Connected..." withColor:[UIColor greenColor]];
		
		[self setStatus:@"Determining Printer Language..." withColor:[UIColor yellowColor]];	
		
		NSError *error = nil;
		id<ZebraPrinter,NSObject> printer = [ZebraPrinterFactory getInstance:connection error:&error];
		
		if(printer != nil) {
			PrinterLanguage language = [printer getPrinterControlLanguage];			
			
			[self setStatus:[NSString stringWithFormat:@"Printer Language %@",[self getLanguageName:language]] withColor:[UIColor cyanColor]];
			
			[self setStatus:@"Retreiving Status" withColor:[UIColor cyanColor]];
			
			PrinterStatus *status = [printer getCurrentStatus:&error];
			if (status == nil) {
				[self setStatus:@"Error retreiving status" withColor:[UIColor redColor]];
			} else {
				NSMutableString *statusMessages = [NSMutableString stringWithFormat:@"Ready to Print: %@\r\n", (status.isReadyToPrint ? @"TRUE" : @"FALSE")];
				
				[statusMessages appendFormat:@"Labels in Batch: %d\r\n", status.labelsRemainingInBatch];
				[statusMessages appendFormat:@"Labels in Buffer: %d\r\n\r\n", status.numberOfFormatsInReceiveBuffer];
				
				PrinterStatusMessages *printerStatusMessages = [[[PrinterStatusMessages alloc] initWithPrinterStatus:status] autorelease];
				NSArray *printerStatusMessagesArray = [printerStatusMessages getStatusMessage]; 
													   
				for(int i = 0; i < [printerStatusMessagesArray count]; i++) {
					[statusMessages appendFormat:@"%@\r\n", [printerStatusMessagesArray objectAtIndex:i]];
				}
				
				[self updatePrinterStatusText:statusMessages];
			}
		} else {
			[self setStatus:@"Could not Detect Language" withColor:[UIColor redColor]];
		}
	} else {
		[self setStatus:@"Could not connect to printer" withColor:[UIColor redColor]];
	}
	
	[self setStatus:@"Disconnecting..." withColor:[UIColor redColor]];
	
	[connection close];
	[connection release];
	
	[self setStatus:@"Not Connected" withColor:[UIColor redColor]];
	
	[self setButtonState:YES];
	[pool release];
}

-(void)updatePrinterStatusTextOnGuiThread: (NSString*)status {
	[self.printerStatusText setText:status];
	[self.printerStatusText flashScrollIndicators];
}

-(void)changeStatusLabel: (NSArray*)statusInfo {
	NSString *statusText = [statusInfo objectAtIndex:0];
	UIColor *statusColor = [statusInfo objectAtIndex:1];
	
	NSString *tmpStatus = [NSString stringWithFormat:@"Status : %@", statusText];
	[self.statusLabel setText:tmpStatus];
	[self.statusLabel setBackgroundColor:statusColor];
}

-(IBAction)textFieldDoneEditing : (id)sender {
	[sender resignFirstResponder];
}

-(IBAction)backgroundTap : (id)sender {
	[self.ipDnsTextField resignFirstResponder];
	[self.portTextField	resignFirstResponder];
}

- (void)viewDidUnload{
	self.ipDnsTextField =nil;
	self.portTextField = nil;
	[super viewDidUnload];
}

- (void)dealloc {
	[statusLabel release];
	[ipDnsTextField release];
	[portTextField release];
	[testButton release];
    [printerStatusText release];
	[super dealloc];
}

@end
