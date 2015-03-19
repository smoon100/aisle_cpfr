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

#import "DiscoveredPrintersViewController.h"
#import "DiscoveredPrinter.h"

@implementation DiscoveredPrintersViewController

@synthesize listData;

-(DiscoveredPrintersViewController*)initWithPrinters:(NSArray*)printers {
  
    DiscoveredPrintersViewController *discoveredPrinterView;
    discoveredPrinterView = [self.storyboard instantiateViewControllerWithIdentifier:@"story_discovered_printer"];
    
	self.title = [NSString stringWithFormat:@"%lu FOUND",(unsigned long)[printers count]];
	NSMutableArray *objs = [[NSMutableArray alloc]init];
	for(DiscoveredPrinter *d in printers) {
		[objs addObject:d.address];
	}
	[objs addObject:@""];
	self.listData = objs;
	
	return self;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.listData count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
	NSUInteger row = [indexPath row];
	cell.textLabel.text = [self.listData objectAtIndex:row];
    return cell;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	
	NSUInteger row = [indexPath row];
	//UIViewController *anotherViewController;
	//NSLog(@"row:%i", row);
    NSLog(@"row title:%@", [self.listData objectAtIndex:row]);
    NSString *selected_printer_ip = [self.listData objectAtIndex:row];
    [NSThread detachNewThreadSelector:@selector(saveDefaultPrinterIP:) toTarget:self withObject:selected_printer_ip];
    
	[self.tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (void)saveDefaultPrinterIP:(NSString *)printerIP{
    //NSLog(@"printer ip is selected");
   // NSUserDefaults *default = [NSUserDefaults standardDefault];
     NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    // saving an NSString
    [prefs setObject:printerIP forKey:@"DefaultPrinterIP"];
    [prefs synchronize];
   // NSString *myString = [prefs stringForKey:@"DefaultPrinterIP"];
    //NSLog(@"saved IP:%@", myString);
    
    UIAlertView *alert_store_number = [[UIAlertView alloc] initWithTitle:@"Info Message" message:@"Default printer is saved!" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alert_store_number show];
    
}



- (void)viewDidLoad
{
    NSLog(@"discovered printer view is open");
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

@end