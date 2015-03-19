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

#import "VariablesViewController.h"
#import "VariableFieldEditViewController.h"
#import "ZSDKDeveloperDemosAppDelegate.h"
#import "FieldDescriptionData.h"
#import "ZebraPrinterConnection.h"
#import "ZebraPrinterFactory.h"
#import "TcpPrinterConnection.h"

@implementation VariablesViewController
@synthesize printQuantity;
@synthesize printButton;
@synthesize variableFieldsView;
@synthesize dataFields;
@synthesize dataValues;
@synthesize formatPath;
@synthesize ipDnsName;
@synthesize port;

-(id)initWithFields:(NSArray*) fields withFormatPath:(NSString*)aformatPath withIpDnsName:(NSString*)anIpDnsName andPort:(NSInteger)aPort {
	self =[super initWithNibName:@"VariablesView" bundle:nil];
    self.formatPath = aformatPath;
    self.dataFields = fields;
	self.ipDnsName = anIpDnsName;
	self.port = aPort;
    
    self.dataValues = [NSMutableDictionary dictionaryWithCapacity:[fields count]];
    NSEnumerator *enumerator = [self.dataFields objectEnumerator];
    FieldDescriptionData *descriptor = nil;
    while (descriptor = [enumerator nextObject]) {
        [self.dataValues setObject:@"" forKey:descriptor.fieldNumber]; 
	}
	return self; 
}

-(id<ZebraPrinterConnection, NSObject>) connectToPrinter:(NSError **)error {
	id<ZebraPrinterConnection, NSObject> printerConnection = [[[TcpPrinterConnection alloc]initWithAddress:self.ipDnsName andWithPort:self.port] autorelease];
	
	[printerConnection open];
	
	return printerConnection;
}

-(void) printFormatOnSeperateThread {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	NSError *error = nil;
	id<ZebraPrinterConnection, NSObject> printerConnection = [self connectToPrinter:&error];
	if (printerConnection != nil) {
		id<ZebraPrinter, NSObject> printer = [ZebraPrinterFactory getInstance:printerConnection error:&error];
		if (printer != nil) {
			id<FormatUtil, NSObject> formatUtil = [printer getFormatUtil];
			
			for (int i = 0; i < [self.printQuantity.text intValue]; i++) {
				[formatUtil printStoredFormat:self.formatPath withDictionary:self.dataValues error:nil];
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
	[NSThread detachNewThreadSelector:@selector(printFormatOnSeperateThread) toTarget:self withObject:nil];
}

- (void) doAnimation: (NSNotification *) aNotification moveUp:(BOOL)moveUp {
    NSDictionary* userInfo = [aNotification userInfo];
    NSTimeInterval animationDuration;
    UIViewAnimationCurve animationCurve;

    [[userInfo objectForKey:UIKeyboardAnimationCurveUserInfoKey] getValue:&animationCurve];
    [[userInfo objectForKey:UIKeyboardAnimationDurationUserInfoKey] getValue:&animationDuration];
	
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:animationDuration];
    [UIView setAnimationCurve:animationCurve];
	
    CGRect rect = self.view.frame;
    NSInteger keyboardFrameHeight = rect.size.height / 2;
	rect.origin.y += (moveUp ? 1.0f :-1.0f) * (keyboardFrameHeight-45);
	self.view.frame = rect;
	
	[UIView commitAnimations];

}

- (void) returnMainViewToInitialposition:(NSNotification*)aNotification {
	[self.variableFieldsView setHidden:NO];	
    [self doAnimation: aNotification moveUp:YES];
}

- (void) liftMainViewWhenKeybordAppears:(NSNotification*)aNotification {
	[self.variableFieldsView setHidden:YES];
    [self doAnimation: aNotification moveUp:NO];
}

-(IBAction)backgroundTap : (id)sender {
	[self.printQuantity resignFirstResponder];
}

- (void)viewDidLoad {
	self.title = @"Variables";
    [super viewDidLoad];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(liftMainViewWhenKeybordAppears:) name:UIKeyboardWillShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(returnMainViewToInitialposition:) name:UIKeyboardWillHideNotification object:nil];

}

- (void) viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.dataFields count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
	
	FieldDescriptionData *fieldNameAndData = [self.dataFields objectAtIndex:indexPath.row];
	
	NSString *fieldName = fieldNameAndData.fieldName;
	NSString *value = [self.dataValues objectForKey:fieldNameAndData.fieldNumber];
	cell.textLabel.text = fieldName ? [NSString stringWithFormat:@"%@ : %@",fieldName, value] : [NSString stringWithFormat:@"Field %@ : %@",fieldNameAndData.fieldNumber, value];
	
	cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    return cell;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	FieldDescriptionData *fieldNameAndData = [self.dataFields objectAtIndex:indexPath.row];
	NSString *value = nil;
	value = [self.dataValues objectForKey:fieldNameAndData.fieldNumber];
	
	VariableFieldEditViewController *controller = [[VariableFieldEditViewController alloc] initWithFieldDescriptionData:fieldNameAndData andValue:value andWithVariableModifier:self];
	[self.navigationController pushViewController:controller animated:YES];
	[controller release];	
	
}

-(void) setVariableValue:(NSString*)value forFieldNumber:(NSNumber*)key {
	[self.dataValues setObject:value forKey:key];
	[self.variableFieldsView reloadData];
}

- (void)dealloc {
	[formatPath release];
	[dataFields release];
	[dataValues release];
    [printQuantity release];
    [printButton release];
    [variableFieldsView release];
	[ipDnsName release];
    [super dealloc];
}

@end

