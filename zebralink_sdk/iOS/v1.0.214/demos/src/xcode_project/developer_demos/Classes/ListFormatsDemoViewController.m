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

#import "ListFormatsDemoViewController.h"
#import "ListFormatsViewController.h"
#import "ZSDKDeveloperDemosAppDelegate.h"
#import "ZebraPrinterConnection.h"
#import "TcpPrinterConnection.h"
#import "ZebraPrinterFactory.h"
#import "FileUtil.h"

@implementation ListFormatsDemoViewController

@synthesize connectionInfo;
@synthesize loadingSpinner;
@synthesize printer;
@synthesize connectivityViewController;

static NSString* kDNSNAMEKEY = @"dnsname";
static NSString* kPORTKEY = @"port";
static NSString* kFILENAMESKEY = @"filename";
static NSString* kERRORKEY = @"error";

- (void)viewDidLoad {
	self.title = @"List Formats";
	self.connectivityViewController = [[[ConnectionSetupController alloc] initWithDelegate:self andButtonName:@"List Formats"] autorelease];	
	[self.view addSubview:self.connectivityViewController.view];
    [super viewDidLoad];
}

-(NSString*) getLanguageName :(PrinterLanguage)language {
	if(language == PRINTER_LANGUAGE_ZPL){
		return @"ZPL";
	} else {
		return @"CPCL";
	}
}

-(void)showErrorDialog :(NSString*)errorMessage {
	UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Error" message:errorMessage delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
	[alert release];
}

- (void) getListOfFormatsFromPrinter: (NSMutableDictionary *) aConnectionInfo {
	
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	NSString *ipDnsName = [aConnectionInfo objectForKey:kDNSNAMEKEY];
	NSString *portNumAsText = [aConnectionInfo objectForKey:kPORTKEY];
	NSInteger port = [portNumAsText intValue];
	
	id<ZebraPrinterConnection, NSObject> printerConnection = [[TcpPrinterConnection alloc]initWithAddress:ipDnsName andWithPort:port];
	
	BOOL openedOk = NO;
	self.printer = nil;
	[self.connectivityViewController setStatus:@"Connecting..." withColor:[UIColor yellowColor]];

	if( ![printerConnection isConnected] ) {
		openedOk = [printerConnection open];
		[self.connectivityViewController setStatus:@"Connected..." withColor:[UIColor greenColor]];
	}
	if (openedOk == YES) {
		NSError *error = nil;
		
		self.printer = [ZebraPrinterFactory getInstance:printerConnection error:&error];
		if (self.printer != nil) {
			[self.connectivityViewController setStatus:@"Determining Printer Language..." withColor:[UIColor yellowColor]];	
			PrinterLanguage lang = [self.printer getPrinterControlLanguage];
			
			[self.connectivityViewController setStatus:[NSString stringWithFormat:@"Printer Language %@", [self getLanguageName:lang]] withColor:[UIColor cyanColor]];

			[self.connectivityViewController setStatus:@"Connected" withColor:[UIColor greenColor]];

			NSArray *extensions = (PRINTER_LANGUAGE_ZPL == lang) ? [NSArray arrayWithObject:@"ZPL"] : [NSArray arrayWithObjects:@"FMT",@"LBL",nil];
			id<FileUtil,NSObject> fileUtil = [self.printer getFileUtil];
			NSArray *fileNames = [fileUtil retrieveFileNamesWithExtensions:extensions error:&error];

			[aConnectionInfo setObject:fileNames forKey:kFILENAMESKEY];
			
		} else {
			[self.connectivityViewController setStatus:@"Could not Detect Language" withColor:[UIColor redColor]];
			[aConnectionInfo setObject:[error localizedDescription] forKey:kERRORKEY];
		}
        [printerConnection close];
	} else {
		[self.connectivityViewController setStatus:@"Could not connect to printer" withColor:[UIColor redColor]];
		[aConnectionInfo setObject:@"Connection Failed" forKey:kERRORKEY];
	}
	
    [printerConnection release];
	[self performSelectorOnMainThread:@selector(threadFinished) withObject:nil waitUntilDone:YES];
	[pool release];
}

-(void)threadFinished {
	[self.loadingSpinner stopAnimating];
	
	NSString *errorString = [self.connectionInfo objectForKey:kERRORKEY];
	if (errorString == nil) {
		NSArray *fileNames = [self.connectionInfo objectForKey:kFILENAMESKEY];
		ListFormatsViewController *controller = [[ListFormatsViewController alloc]initWithFormats:fileNames andPrinter:self.printer];
		[self.navigationController pushViewController:controller animated:YES];
		[controller release];
	} else {
		[self showErrorDialog:errorString];
	}
}


-(void) popupSpinner{
	self.loadingSpinner = [[[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray] autorelease];
	[self.view addSubview:self.loadingSpinner];
	self.loadingSpinner.center = self.view.center;
	self.loadingSpinner.autoresizingMask = UIViewAutoresizingFlexibleBottomMargin | 
	UIViewAutoresizingFlexibleTopMargin | 
	UIViewAutoresizingFlexibleRightMargin | 
	UIViewAutoresizingFlexibleLeftMargin;
	[self.loadingSpinner startAnimating];
}


-(void)connectTo:(NSString*) ipDnsName andPortNum:(NSString*)portNum {
	[self popupSpinner];
	self.connectionInfo = [NSMutableDictionary dictionaryWithObjectsAndKeys:ipDnsName, kDNSNAMEKEY, portNum, kPORTKEY, nil];
	[NSThread detachNewThreadSelector:@selector(getListOfFormatsFromPrinter:) toTarget:self withObject:self.connectionInfo];	
}

- (void)dealloc {
	[connectivityViewController release];
	[loadingSpinner release];
    [printer release];
    [connectionInfo release];
    [super dealloc];
}


@end
