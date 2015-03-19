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

#import "ConnectionSetupController.h"

@implementation ConnectionSetupController
@synthesize statusLabel;
@synthesize ipDnsTextField;
@synthesize portTextField;
@synthesize testButton;
@synthesize delegate;

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

-(id)initWithDelegate:(id)del andButtonName:(NSString*)buttonText {
	[self initWithNibName:@"ConnectionSetupView" bundle:nil];
	self.delegate = del;
	[self.view setAutoresizingMask:UIViewAutoresizingFlexibleWidth];
	[testButton setTitle:buttonText forState:UIControlStateNormal];
	
	[self setUserDefaults];

	return self;
}

-(void)connectTo:(NSString*) ipDnsName andPortNum:(NSString*)portNumAsNsString {
	NSAssert(NO, @"please implement -(void)connectTo:(NSString*) ipDnsName andPortNum:(NSString*)portNumAsNsString"); 
}

-(IBAction)buttonPressed:(id)sender {
	if(self.delegate != nil){
		[ipDnsTextField resignFirstResponder];
		[portTextField resignFirstResponder];
		NSString *ipDnsName = [ipDnsTextField text];
		NSString *portNumAsNsString = [portTextField text];
		[self saveUserDefaults: ipDnsName portNumAsNsString: portNumAsNsString];

		[self.delegate connectTo:ipDnsName andPortNum:portNumAsNsString];
	}
}

-(void) setButtonState : (BOOL)state {
	[self performSelectorOnMainThread:@selector(setTestButtonStateSelector:) withObject:[NSNumber numberWithBool:state] waitUntilDone:NO];
}

- (void) setTestButtonStateSelector : (NSNumber*)state {
	[testButton setEnabled:[state boolValue]];
}

-(void)setStatus: (NSString*)status withColor :(UIColor*)color {
	NSArray *statusInfo = [NSArray arrayWithObjects:status, color, nil];
	[self performSelectorOnMainThread:@selector(changeStatusLabel:) withObject:statusInfo waitUntilDone:NO];
	[NSThread sleepForTimeInterval:1];
}

-(void)changeStatusLabel: (NSArray*)statusInfo {
	NSString *statusText = [statusInfo objectAtIndex:0];
	UIColor *statusColor = [statusInfo objectAtIndex:1];
	
	NSString *tmpStatus = [NSString stringWithFormat:@"Status : %@", statusText];
	[statusLabel setText:tmpStatus];
	[statusLabel setBackgroundColor:statusColor];
}

-(IBAction)textFieldDoneEditing : (id)sender {
	[sender resignFirstResponder];
}

-(IBAction)backgroundTap : (id)sender {
	[ipDnsTextField resignFirstResponder];
	[portTextField	resignFirstResponder];
}

- (void)viewDidUnload{
	self.ipDnsTextField =nil;
	self.portTextField = nil;
	[super viewDidUnload];
}

-(void)setButtonText:(NSString*) text {
	self.testButton.titleLabel.text =text;
}

- (void)dealloc {
	[statusLabel release];
	[ipDnsTextField release];
	[portTextField release];
	[testButton release];
	[super dealloc];
}

@end
