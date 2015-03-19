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

#import "SendFileDemoViewController.h"
#import "TcpPrinterConnection.h"
#import "ZebraPrinterFactory.h"

@implementation SendFileDemoViewController

@synthesize loadingSpinner;
@synthesize ipDnsTextField;
@synthesize portTextField;
@synthesize sendFileButton;
@synthesize ipDnsName;
@synthesize port;

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

- (void)viewDidLoad {
	self.title = @"Send File";
	[self setUserDefaults];
    [super viewDidLoad];
}

-(void)showErrorDialog :(NSString*)errorMessage {
	[self.loadingSpinner stopAnimating];
	UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Error" message:errorMessage delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
	[alert release];
}

-(void)showSuccessDialog {
	[self.loadingSpinner stopAnimating];
	UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Success" message:@"File sent to printer" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
	[alert release];
}


-(id<ZebraPrinterConnection, NSObject>) connectToPrinter:(NSError **)error {
	id<ZebraPrinterConnection, NSObject> printerConnection = [[[TcpPrinterConnection alloc]initWithAddress:self.ipDnsName andWithPort:self.port] autorelease];
	
	[printerConnection open];
	
	return printerConnection;
}

-(void) sendFileToPrinter {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	NSError *error = nil;
	id<ZebraPrinterConnection, NSObject> printerConnection = [self connectToPrinter:&error];
	if (printerConnection != nil) {
		id<ZebraPrinter, NSObject> printer = [ZebraPrinterFactory getInstance:printerConnection error:&error];
		if (printer != nil) {
			id<FileUtil, NSObject> fileUtil = [printer getFileUtil];
			
			NSString *fileName = ([printer getPrinterControlLanguage] == PRINTER_LANGUAGE_ZPL) ? @"test_zpl.zpl" : @"test_cpcl.lbl";
			NSString *filePath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fileName];
			
			if ([fileUtil sendFileContents:filePath error:&error] == NO) {
				[self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:[error localizedDescription] waitUntilDone:YES];
			} else {
				[self performSelectorOnMainThread:@selector(showSuccessDialog) withObject:nil waitUntilDone:YES];
			}
		} else {
			[self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:[error localizedDescription] waitUntilDone:YES];
		}
		[printerConnection close];
	} else {
		[self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:[error localizedDescription] waitUntilDone:YES];
	}
	
	[pool release];
}

-(IBAction)buttonPressed:(id)sender {
	[ipDnsTextField resignFirstResponder];
	[portTextField resignFirstResponder];
		
	[self saveUserDefaults: [ipDnsTextField text] portNumAsNsString: [portTextField text]];
		
	self.ipDnsName = [ipDnsTextField text];
	self.port = [[portTextField text] intValue];
		
	[self popupSpinner];
	[NSThread detachNewThreadSelector:@selector(sendFileToPrinter) toTarget:self withObject:nil];
}

-(IBAction)textFieldDoneEditing : (id)sender {
	[sender resignFirstResponder];
}

-(IBAction)backgroundTap : (id)sender {
	[self.ipDnsTextField resignFirstResponder];
	[self.portTextField	resignFirstResponder];
}

-(void)dealloc {
	[loadingSpinner release];
	[ipDnsTextField release];
	[portTextField release];
	[sendFileButton release];
	[ipDnsName release];
	[super dealloc];
}

@end

