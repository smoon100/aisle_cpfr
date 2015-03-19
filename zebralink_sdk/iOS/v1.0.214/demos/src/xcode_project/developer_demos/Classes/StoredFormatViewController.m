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

#import "StoredFormatViewController.h"
#import "ZSDKDeveloperDemosAppDelegate.h"
#import "StoredPrinterFormatsViewController.h"
#import "TcpPrinterConnection.h"
#import "ZebraPrinterFactory.h"
#import "FileUtil.h"

@implementation StoredFormatViewController

@synthesize loadingSpinner;
@synthesize printerConnection;
@synthesize printer;
@synthesize ipDnsTextField;
@synthesize portTextField;
@synthesize getFormatsButton;
@synthesize ipDnsName;
@synthesize port;
@synthesize fileNames;

- (void) setUserDefaults {
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	[self.ipDnsTextField setText:[defaults objectForKey:@"ipDnsName"]];
	[self.portTextField setText:[defaults objectForKey:@"portNum"]];
	
}

- (void) saveUserDefaults: (NSString *) anIpDnsName portNumAsNsString: (NSString *) portNumAsNsString  {
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	[defaults setObject:anIpDnsName forKey:@"ipDnsName"];
	[defaults setObject:portNumAsNsString forKey:@"portNum"];
	
}

- (void)viewDidLoad {
	self.title = @"Stored Format";
	[self setUserDefaults];
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
	[self.loadingSpinner stopAnimating];
	
	UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Error" message:errorMessage delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
	[alert release];
}

- (void) getListOfFormatsFromPrinter {
	
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	self.printerConnection = [[[TcpPrinterConnection alloc]initWithAddress:self.ipDnsName andWithPort:self.port] autorelease];
	
	BOOL openedOk = NO;
	self.printer = nil;	
	
	if( ![self.printerConnection isConnected] ) {
		openedOk = [self.printerConnection open];
	}
	if (openedOk == YES) {
		NSError *error = nil;
		
		self.printer = [ZebraPrinterFactory getInstance:self.printerConnection error:&error];
		if (self.printer != nil) {
			PrinterLanguage lang = [self.printer getPrinterControlLanguage];
			
			NSArray *extensions = (PRINTER_LANGUAGE_ZPL == lang) ? [NSArray arrayWithObject:@"ZPL"] : [NSArray arrayWithObjects:@"FMT",@"LBL",nil];
			id<FileUtil,NSObject> fileUtil = [self.printer getFileUtil];
			self.fileNames = [fileUtil retrieveFileNamesWithExtensions:extensions error:&error];
			
			[self performSelectorOnMainThread:@selector(pushFilesViewController) withObject:nil waitUntilDone:YES];
			
		} else {
			[self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:[error localizedDescription] waitUntilDone:YES];
		}
	} else {
		[self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:@"Connection Failed" waitUntilDone:YES];
	}
	
	[pool release];
}

-(IBAction)textFieldDoneEditing : (id)sender {
	[sender resignFirstResponder];
}

-(IBAction)backgroundTap : (id)sender {
	[ipDnsTextField resignFirstResponder];
	[portTextField	resignFirstResponder];
}



-(void)pushFilesViewController {
	[self.loadingSpinner stopAnimating];

	StoredPrinterFormatsViewController *controller = [[StoredPrinterFormatsViewController alloc]initWithFormats:self.fileNames withIpDnsName:self.ipDnsName andPort:self.port];
	[self.navigationController pushViewController:controller animated:YES];
	[controller release];
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

-(IBAction)buttonPressed:(id)sender {
	[self popupSpinner];
	[ipDnsTextField resignFirstResponder];
	[portTextField resignFirstResponder];
	
	[self saveUserDefaults: [ipDnsTextField text] portNumAsNsString: [portTextField text]];
	
	self.ipDnsName = [ipDnsTextField text];
	self.port = [[portTextField text] intValue];
	
	[NSThread detachNewThreadSelector:@selector(getListOfFormatsFromPrinter) toTarget:self withObject:nil];
}

-(void)dealloc {
	[printerConnection close];
	[printerConnection release];
	[loadingSpinner release];
    [printer release];
	[ipDnsTextField release];
	[portTextField release];
	[getFormatsButton release];
	[ipDnsName release];
	[fileNames release];
	[super dealloc];
}

@end
