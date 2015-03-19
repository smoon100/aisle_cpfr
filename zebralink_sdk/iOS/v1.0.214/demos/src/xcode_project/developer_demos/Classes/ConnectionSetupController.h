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


@interface ConnectionSetupController : UIViewController {
	UILabel *statusLabel;
	UITextField *ipDnsTextField;
	UITextField *portTextField;
	UIButton *testButton;
	id delegate;
}

@property (nonatomic,retain) IBOutlet UILabel *statusLabel;
@property (nonatomic,retain) IBOutlet UITextField *ipDnsTextField;
@property (nonatomic,retain) IBOutlet UITextField *portTextField;
@property (nonatomic,retain) IBOutlet UIButton *testButton;
@property (nonatomic,assign) IBOutlet id delegate;


-(IBAction)buttonPressed:(id)sender;
-(IBAction)textFieldDoneEditing : (id)sender;
-(IBAction)backgroundTap : (id)sender;
-(void)setStatus: (NSString*)status withColor :(UIColor*)color;
-(void) setButtonState : (BOOL)state;
-(void)setButtonText:(NSString*) text;

-(id)initWithDelegate:(id)del andButtonName:(NSString*)buttonText;
@end
