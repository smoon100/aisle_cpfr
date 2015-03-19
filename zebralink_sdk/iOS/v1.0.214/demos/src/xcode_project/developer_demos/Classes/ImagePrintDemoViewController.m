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

#import "ImagePrintDemoViewController.h"
#import "PrintPreviewController.h"
#import "ZebraPrinterConnection.h"
#import "TcpPrinterConnection.h"
#import "GraphicsUtil.h"
#import "ZebraPrinter.h"
#import "ZebraPrinterFactory.h"

@implementation ImagePrintDemoViewController

@synthesize pathOnPrinterTextField;
@synthesize printOrStoreToggle;
@synthesize isStoreSelected;
@synthesize ipDnsTextField;
@synthesize portTextField;
@synthesize ipDnsName;
@synthesize port;
@synthesize pathOnPrinterText;
@synthesize loadingSpinner;

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

-(void)showErrorDialog :(NSString*)errorMessage {
	[self.loadingSpinner stopAnimating];
	UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Error" message:errorMessage delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
	[alert release];
}

- (void)viewDidLoad {
	self.title = @"Image Print";
	self.isStoreSelected = NO;
	[self.pathOnPrinterTextField setHidden:YES];
	[self setUserDefaults];
    [super viewDidLoad];
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

-(IBAction)printOrStoreToggleValueChanged : (id)sender {
	UISegmentedControl *control = sender;
	if (control.selectedSegmentIndex == 0) {
		[self.pathOnPrinterTextField setHidden:YES];
		self.isStoreSelected = NO;
	} else {
		[self.pathOnPrinterTextField setHidden:NO];
		self.isStoreSelected = YES;
	}
}


-(void)showError:(NSString *)errorString {
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:errorString delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
	[alert release];
}

-(void)showSuccessDialog:(NSString *)successMessage {
	[self.loadingSpinner stopAnimating];
	UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Success" message:successMessage delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
	[alert release];
}

-(IBAction)cameraButtonPressed : (id)sender {
	if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera] == YES) {
		UIImagePickerController *imagePickerController = [[[UIImagePickerController alloc]init]autorelease];
		imagePickerController.delegate = self;
		imagePickerController.sourceType = UIImagePickerControllerSourceTypeCamera;
		
		[self presentModalViewController:imagePickerController animated:YES];
	} else {
		[self showError:@"This device does not have a camera"];
	}
}

-(IBAction)photoAlbumButtonPressed : (id)sender {
	UIImagePickerController *imagePickerController = [[[UIImagePickerController alloc]init]autorelease];
	imagePickerController.delegate = self;
    imagePickerController.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
	
	[self presentModalViewController:imagePickerController animated:YES];
}

-(id<ZebraPrinterConnection, NSObject>) connectToPrinter:(NSError **)error {
	id<ZebraPrinterConnection, NSObject> printerConnection = [[[TcpPrinterConnection alloc]initWithAddress:self.ipDnsName andWithPort:self.port] autorelease];
	
	[printerConnection open];
	
	return printerConnection;
}

-(void) sendImageToPrinter:(UIImage *)image {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	NSError *error = nil;
	id<ZebraPrinterConnection, NSObject> printerConnection = [self connectToPrinter:&error];
	if (printerConnection != nil) {
		id<ZebraPrinter, NSObject> printer = [ZebraPrinterFactory getInstance:printerConnection error:&error];
		if (printer != nil) {
			id<GraphicsUtil, NSObject> graphicsUtil = [printer getGraphicsUtil];
			
			BOOL success = NO;
			if (self.isStoreSelected) {
				success = [graphicsUtil storeImage:self.pathOnPrinterText withImage:[image CGImage] withWidth:550 andWithHeight:412 error:&error];
			} else {
				success = [graphicsUtil printImage:[image CGImage] atX:0 atY:0 withWidth:550 withHeight:412 andIsInsideFormat:NO error:&error];
			}
						   
			if (success == NO) {
			   [self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:[error localizedDescription] waitUntilDone:YES];
			} else {
				NSString *successMessage = (self.isStoreSelected == NO) ? @"Image sent to printer" : [NSString stringWithFormat:@"Stored image %@ to printer", self.pathOnPrinterText];
				[self performSelectorOnMainThread:@selector(showSuccessDialog:) withObject:successMessage waitUntilDone:YES];
			}
		} else {
			[self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:[error localizedDescription] waitUntilDone:YES];
		}
		[printerConnection close];
	} else {
		[self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:[error localizedDescription] waitUntilDone:YES];
	}
	
	[image release];
	
	[pool release];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info {	
	UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];
	[image retain];

	[self dismissModalViewControllerAnimated:YES];
	
	[self saveUserDefaults: [ipDnsTextField text] portNumAsNsString: [portTextField text]];
	
	self.ipDnsName = self.ipDnsTextField.text;
	self.port = [self.portTextField.text intValue];
	self.pathOnPrinterText = self.pathOnPrinterTextField.text;
	
	[self popupSpinner];
	[NSThread detachNewThreadSelector:@selector(sendImageToPrinter:) toTarget:self withObject:image];
}

-(IBAction)pdfButtonPressed : (id)sender {
	[self saveUserDefaults: [ipDnsTextField text] portNumAsNsString: [portTextField text]];
	
	self.ipDnsName = self.ipDnsTextField.text;
	self.port = [self.portTextField.text intValue];
	self.pathOnPrinterText = self.pathOnPrinterTextField.text;
	
	PrintPreviewController *controller = [[[PrintPreviewController alloc] initWithPath:@"PDFDemo2.pdf" 
																	  withStoreSelected:self.isStoreSelected
																		 withIpDnsName:self.ipDnsTextField.text
																			  withPort:[self.portTextField.text intValue]
																	  andPathOnPrinter:self.pathOnPrinterTextField.text] autorelease];
	[self.navigationController pushViewController:controller animated:YES];
}

-(IBAction)textFieldDoneEditing : (id)sender {
	[sender resignFirstResponder];
}

-(IBAction)backgroundTap : (id)sender {
	[self.ipDnsTextField resignFirstResponder];
	[self.portTextField	resignFirstResponder];
	[self.pathOnPrinterTextField resignFirstResponder];
}

-(void)dealloc {
	[pathOnPrinterTextField release];
	[printOrStoreToggle release];
	[ipDnsTextField release];
	[portTextField release];
	[ipDnsName release];
	[pathOnPrinterText release];
	[loadingSpinner release];
	[super dealloc];
}

@end
