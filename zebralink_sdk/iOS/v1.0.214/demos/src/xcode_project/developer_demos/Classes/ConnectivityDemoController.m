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

#import "ConnectivityDemoController.h"
#import "ZebraPrinterConnection.h"
#import	"TcpPrinterConnection.h"
#import "ZebraPrinter.h"
#import "ZebraPrinterFactory.h"

@implementation ConnectivityDemoController

@synthesize performingDemo;
@synthesize connectivityViewController;

- (void)viewDidLoad {
	self.title = @"Connectivity";
	self.connectivityViewController = [[[ConnectionSetupController alloc] initWithDelegate:self andButtonName:@"Test"] autorelease];	
	self.performingDemo = NO;
	[self.view addSubview:self.connectivityViewController.view];
    [super viewDidLoad];
}

-(void) viewWillDisappear:(BOOL)animated{
	if (self.performingDemo) {
		[NSThread sleepForTimeInterval:5];
	}
}

-(NSString*) getLanguageName :(PrinterLanguage)language {
	if(language == PRINTER_LANGUAGE_ZPL){
		return @"ZPL";
	} else {
		return @"CPCL";
	}
}

-(BOOL)printTestLabel:(PrinterLanguage) language onConnection:(id<ZebraPrinterConnection, NSObject>)connection withError:(NSError**)error {
	NSString *testLabel;
	if (language == PRINTER_LANGUAGE_ZPL) {
		testLabel = @"^XA^FO17,16^GB379,371,8^FS^FT65,255^A0N,135,134^FDTEST^FS^XZ";
		NSData *data = [NSData dataWithBytes:[testLabel UTF8String] length:[testLabel length]];
		[connection write:data error:error];
	} else if (language == PRINTER_LANGUAGE_CPCL) {
		testLabel = @"! 0 200 200 406 1\r\nON-FEED IGNORE\r\nBOX 20 20 380 380 8\r\nT 0 6 137 177 TEST\r\nPRINT\r\n";
		NSData *data = [NSData dataWithBytes:[testLabel UTF8String] length:[testLabel length]];
		[connection write:data error:error];
	}
	if(*error == nil){
		return YES;
	} else {
		return NO;
	}
}

-(void)connectTo:(NSString*) ipDnsName andPortNum:(NSString*)portNumAsNsString {
	NSArray *connectionInfo = [NSArray arrayWithObjects:ipDnsName, portNumAsNsString, nil];
	[NSThread detachNewThreadSelector:@selector(performConnectionDemo:) toTarget:self withObject:connectionInfo];
}

- (void) performConnectionDemo : (NSArray*)connectionInfo {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	if([connectionInfo count] >= 2){
		self.performingDemo = YES;
		[self.connectivityViewController setButtonState:NO];
		NSString *ipDnsName = [connectionInfo objectAtIndex:0];
		NSString *portNumAsText = [connectionInfo objectAtIndex:1];
		NSInteger portNum = [portNumAsText intValue];
		
		[self.connectivityViewController setStatus:@"Connecting..." withColor:[UIColor yellowColor]];
		
		
		id<ZebraPrinterConnection, NSObject> connection = [[TcpPrinterConnection alloc] initWithAddress:ipDnsName andWithPort:portNum];
		
		BOOL didOpen = [connection open];
		if(didOpen == YES) {	
			[self.connectivityViewController setStatus:@"Connected..." withColor:[UIColor greenColor]];
			
			[self.connectivityViewController setStatus:@"Determining Printer Language..." withColor:[UIColor yellowColor]];	
			
			NSError *error = nil;
			id<ZebraPrinter,NSObject> printer = [ZebraPrinterFactory getInstance:connection error:&error];
			
			if(printer != nil) {
				PrinterLanguage language = [printer getPrinterControlLanguage];			
				[self.connectivityViewController setStatus:[NSString stringWithFormat:@"Printer Language %@",[self getLanguageName:language]] withColor:[UIColor cyanColor]];
				
				[self.connectivityViewController setStatus:@"Sending Data" withColor:[UIColor cyanColor]];
				
				BOOL sentOK = [self printTestLabel:language onConnection:connection withError:&error];
				if (sentOK == YES) {
					[self.connectivityViewController setStatus:@"Test Label Sent" withColor:[UIColor greenColor]];
				} else {
					[self.connectivityViewController setStatus:@"Test Label Failed to Print" withColor:[UIColor redColor]];
				}
			} else {
				[self.connectivityViewController setStatus:@"Could not Detect Language" withColor:[UIColor redColor]];
			}
		} else {
			[self.connectivityViewController setStatus:@"Could not connect to printer" withColor:[UIColor redColor]];
		}
		
		[self.connectivityViewController setStatus:@"Disconnecting..." withColor:[UIColor redColor]];
		
		[connection close];
		[connection release];
		self.performingDemo = NO;
	} 
	
	[self.connectivityViewController setStatus:@"Not Connected" withColor:[UIColor redColor]];
	
	[self.connectivityViewController setButtonState:YES];
	[pool release];
}

-(void)dealloc {
	[connectivityViewController release];
	[super dealloc];
}

@end
