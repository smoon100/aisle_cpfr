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

#import "RootViewController.h"
#import "ConnectivityDemoController.h"
#import "DiscoveryViewController.h"
#import "ImagePrintDemoViewController.h"
#import "StatusViewController.h"
#import "StoredFormatViewController.h"
#import "ListFormatsDemoViewController.h"
#import "SignatureCaptureDemoViewController.h"
#import "MagCardDemoViewController.h"
#import "SmartCardDemoViewController.h"
#import "SendFileDemoViewController.h"

@implementation RootViewController

@synthesize listData;

- (void)viewDidLoad {
    
	
	NSArray *listItems = [[NSArray alloc]initWithObjects:@"Connectivity", @"Discovery", @"Image Print", @"List Formats", @"Mag Card", @"Printer Status", @"Smart Card", @"Signature Capture", @"Send File", @"Stored Format",nil];

	self.listData = listItems;
	[listItems release];
	[super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload {
	self.listData = nil;
	[super viewDidUnload];
}


#pragma mark Table view methods

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.listData count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
    
	NSUInteger row = [indexPath row];
	cell.textLabel.text = [listData objectAtIndex:row];
	cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {

	NSUInteger row = [indexPath row];
	UIViewController *anotherViewController = nil;
	switch (row) {
		case 0:
			anotherViewController = [[ConnectivityDemoController alloc] initWithNibName:@"ConnectivityView" bundle:nil];
			break;
		case 1:
			anotherViewController = [[DiscoveryViewController alloc] initWithNibName:@"DiscoveryView" bundle:nil];
			break;
		case 2:
			anotherViewController = [[ImagePrintDemoViewController alloc] initWithNibName:@"ImagePrintView" bundle:nil];
			break;
		case 3:
			anotherViewController = [[ListFormatsDemoViewController alloc] initWithNibName:@"ListFormatsDemoView" bundle:nil];
			break;
		case 4:
			anotherViewController = [[MagCardDemoViewController alloc] initWithNibName:@"MagCardView" bundle:nil];
			break;
		case 5:
			anotherViewController = [[StatusViewController alloc] initWithNibName:@"StatusView" bundle:nil];
			break;
        case 6:
            anotherViewController = [[SmartCardDemoViewController alloc] initWithNibName:@"SmartCardView" bundle:nil];
            break;
		case 7:
			anotherViewController = [[SignatureCaptureDemoViewController alloc] initWithNibName:@"SignatureView" bundle:nil];
			break;
        case 8:
            anotherViewController = [[SendFileDemoViewController alloc] initWithNibName:@"SendFileView" bundle:nil];
            break;
		case 9:
			anotherViewController = [[StoredFormatViewController alloc] initWithNibName:@"StoredFormatView" bundle:nil];
			break;
		default:
			break;
	}
	if (anotherViewController != nil) {
		[self.navigationController pushViewController:anotherViewController animated:YES];
		[anotherViewController release];
	}
}

- (void)dealloc {
	[listData release];
    [super dealloc];
}


@end

