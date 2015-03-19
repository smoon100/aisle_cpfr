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

#import "StoredPrinterFormatsViewController.h"
#import "ZSDKDeveloperDemosAppDelegate.h"
#import "VariablesViewController.h"
#import "FieldDescriptionData.h"
#import "ZebraPrinterConnection.h"
#import "ZebraPrinterFactory.h"
#import "TcpPrinterConnection.h"


@implementation StoredPrinterFormatsViewController

@synthesize printerFormats;
@synthesize variables;
@synthesize ipDnsName;
@synthesize port;
@synthesize loadingSpinner;

-(void)showErrorDialog :(NSString*)errorMessage {
	[self.loadingSpinner stopAnimating];
	UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Error" message:errorMessage delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	[alert show];
	[alert release];
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

-(id)initWithFormats:(NSArray*)formats withIpDnsName:(NSString *)anIpDnsName andPort:(NSInteger)aPort {
    self = [super initWithNibName:@"StoredPrinterFormatsView" bundle:nil];
    self.printerFormats = formats;
	self.ipDnsName = anIpDnsName;
	self.port = aPort;
	return self;
}
- (void)viewDidLoad {
	self.title = @"Formats";
    [super viewDidLoad];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.printerFormats count];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
    
	cell.imageView.image = [UIImage imageNamed:@"rw420.jpg"];
	cell.textLabel.text = [self.printerFormats objectAtIndex:indexPath.row];
	cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;

    return cell;
}


-(id<ZebraPrinterConnection, NSObject>) connectToPrinter:(NSError **)error {
	id<ZebraPrinterConnection, NSObject> printerConnection = [[[TcpPrinterConnection alloc]initWithAddress:self.ipDnsName andWithPort:self.port] autorelease];
	
	[printerConnection open];
	
	return printerConnection;
}

-(void) getVariablesFromFormatOnSeperateThread:(NSString *)formatPath {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	NSError *error = nil;
	id<ZebraPrinterConnection, NSObject> printerConnection = [self connectToPrinter:&error];
	if (printerConnection != nil) {
		id<ZebraPrinter, NSObject> printer = [ZebraPrinterFactory getInstance:printerConnection error:&error];
		if (printer != nil) {
			id<FormatUtil, NSObject> formatUtil = [printer getFormatUtil];
			
			NSData *formatContents = [formatUtil retrieveFormatFromPrinterWithPath:formatPath error:&error];
			if (formatContents == nil) {
				[self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:[error localizedDescription] waitUntilDone:YES];
			} else {
				NSString *contentsAsString = [[[NSString alloc]initWithData:formatContents encoding:NSUTF8StringEncoding]autorelease];
				
				self.variables = [formatUtil getVariableFieldsWithFormatContents:contentsAsString error:&error];
				if (self.variables == nil) {
					[self performSelectorOnMainThread:@selector(showErrorDialog:) withObject:[error localizedDescription] waitUntilDone:YES];
				} else {
					[self performSelectorOnMainThread:@selector(pushVariableFieldEditController:) withObject:formatPath waitUntilDone:YES];
				}
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

-(void)pushVariableFieldEditController:(NSString *)formatPath {
	[self.loadingSpinner stopAnimating];
	VariablesViewController *controller = [[VariablesViewController alloc]initWithFields:self.variables withFormatPath:formatPath withIpDnsName:self.ipDnsName andPort:self.port];
	[self.navigationController pushViewController:controller animated:YES];
	[controller release];	
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	NSString *formatPath = [self.printerFormats objectAtIndex:indexPath.row];
	[self popupSpinner];
	[NSThread detachNewThreadSelector:@selector(getVariablesFromFormatOnSeperateThread:) toTarget:self withObject:formatPath];
}

- (void)dealloc {
	[printerFormats release];
	[variables release];
	[ipDnsName release];
	[loadingSpinner release];
    [super dealloc];
}


@end

