//
//  NewItemViewController.m
//  AisleMaster
//
//  Created by SEOHWAN.MOON on 2/27/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import "NewItemViewController.h"

#define kBgQueue dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0 )
#define UnitCodeList 1;

@interface NewItemViewController ()

@end

@implementation NewItemViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)viewDidLayoutSubviews{
    [super viewDidLayoutSubviews];
    [scrollView layoutIfNeeded];
    scrollView.contentSize= contentView.bounds.size;
}

- (void)viewDidAppear:(BOOL)animated{
    //[self initAllInputs]; // clear all inputs
    linea =[Linea sharedDevice];
    [linea addDelegate:self];
    [linea connect];
    //NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
   }

-(void)viewWillDisappear:(BOOL)animated{
    
    linea =[Linea sharedDevice];
    [linea removeDelegate:self];
    [linea disconnect];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    serverIp = [prefs valueForKey:@"ServerIP"];
    storeno = [prefs stringForKey:@"StoreNumber"];
    //lang_int = [prefs stringForKey:@"LANGUAGE_INT"];
    //dept_permit = [prefs stringForKey:@"DEPT_PERMIT"];
    //can_price_change = [prefs boolForKey:@"CAN_PRICE_CHANGE"];
    
    linea =[Linea sharedDevice];
    //[linea disconnect];
    [linea addDelegate:self];
    [linea connect];
    
    [self createDataForOtherList];
    [self customizeBtn];
    [self initAllInputs];
   
    

   


    /*
    NSString *barcode = @"76189865100";
    self.txtUpcCode.text = barcode;
    NSString *urlForProduct = [NSString stringWithFormat: @"http://%@/AISLEMASTER/json/reply_product.jsp?UPCCode=%@&storeno=%@&lang=%@", serverIp, barcode, storeno, lang_int];
    
    // NSLog(@"url: %@", urlForProduct);
    [self jsonFromUrl:(NSString *) urlForProduct :5];
    */
    
    //[self createToolbar];
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFastForward target:self action:@selector(print_Message)];
    //self.navigationItem.rightBarButtonItem.title = @"List";
    
    //self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"purchase_order-26.png"]]];
    //[self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:@"uberbar.png"] forBarMetrics:UIBarMetricsDefault];
    /*
    UIImage *image = [[UIImage imageNamed:@"show_property-25.png"] imageWithAlignmentRectInsets:UIEdgeInsetsMake(0, 0, 10, 10)];
   
    self.navigationItem.rightBarButtonItem  = [[UIBarButtonItem alloc] initWithImage:image style:UIBarButtonItemStylePlain target:self action:@selector(print_Message)];*/
}

-(void)print_Message {
    NSLog(@"Eh up, someone just pressed the button!");
    [self performSegueWithIdentifier:@"segue.gbk.grocery.order.list" sender:self.view];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}




// Barcode type: UPC-A(1)( type 2, , EAN 8(13), EAN 13(14), Code 128(7)
-(void)barcodeData:(NSString *)barcode type:(int)type {
    
    
    if ([barcode isEqualToString:self.txtItemNo.text]) {
        int cur_order_qty = [self.txtOrderQty.text intValue];
        self.txtOrderQty.text = [NSString stringWithFormat:@"%d",cur_order_qty + 1] ;
    }else{
        self.txtOrderQty.text = [NSString stringWithFormat:@"%d", 1] ;
        // load data
    }
    
    self.txtItemNo.text = barcode;
    /*
    NSString *urlForProduct = [NSString stringWithFormat: @"http://%@/AISLEMASTER/json/reply_product.jsp?UPCCode=%@&storeno=%@&lang=%@", serverIp, barcode, storeno, lang_int];
    
    // NSLog(@"url: %@", urlForProduct);
    [self jsonFromUrl:(NSString *) urlForProduct :5];*/
}


-(void)barcodeSearchData:(NSString *)barcode{
    //self.commonViewController = [[CommonViewController alloc]init];
    //barcode = [self.commonViewController getBrBarcode:barcode type:type];
   // self.txtUpcCode.text = barcode;
    NSString *urlForProduct = [NSString stringWithFormat: @"http://%@/AISLEMASTER/json/reply_product.jsp?UPCCode=%@&storeno=%@&lang=%@", serverIp, barcode, storeno, lang_int];
    
    // NSLog(@"url: %@", urlForProduct);
    [self jsonFromUrl:(NSString *) urlForProduct :5];
}


- (IBAction)saveBtnClicked:(id)sender {
    NSLog(@"save btn clicked");
}

- (IBAction)searchBtnClicked:(id)sender {
    
    NSString *upc_code = self.txtItemNo.text;
    [self barcodeSearchData:upc_code];
    
}




-(BOOL)validateInputs{
       return true;
}


-(void)jsonFromUrl:(NSString *) urlAddress :(NSInteger) type{
    // tesing read product info from DB
    NSString *urlAsString = urlAddress;
    NSLog(@"url copy: %@", urlAddress);
    //NSString *methodName = @"fetchedData";
    //SEL curMethod = @selector(fetchedData:);
    
    NSURL *jsonInfoURL = [NSURL URLWithString: (NSString *)urlAsString];
    switch (type) {
        case 5:{ // load product info
            dispatch_async(kBgQueue, ^{
                NSData *data = [NSData dataWithContentsOfURL:jsonInfoURL];
                [self performSelectorOnMainThread: @selector(fetchedDataForProductInfo:) withObject:data waitUntilDone:YES];
            });
            break;
        }
    }
    
}










- (void) fetchedData:(NSData *) responseData {
    // [displayStatus setText:@"fetched Data"];
    if (responseData == nil) {
        NSLog(@"no reponse3");
        UIAlertView *alert_srv_response = [[UIAlertView alloc] initWithTitle:@"Info Message" message:@"Server is not responding!" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
        //alert_login_result.tag = TAG_LOGIN_ALERT;
        [alert_srv_response show];
    }else{
        
        NSError* error;
        NSDictionary* json = [NSJSONSerialization JSONObjectWithData:responseData options:kNilOptions error:&error];
        NSLog(@"json:%@", error);
        NSArray* result = [json objectForKey:@"Result"];
        NSString *msg_result =@"";
        if( [result isEqual: @"Success"]){
            msg_result = @"The Item is successfully added!";
            // call clear input fields function
            [self initAllInputs];
        }else{
            NSString* err_message = [json objectForKey:@"Message"];
            if( [err_message isEqual:@""]){
                err_message = @"Fail! Contact to Mobile CPFR Developer";
            }
            msg_result = err_message;
        }
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Confirm Message" message:msg_result delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
        //alert.tag = UPDATE_PRODCUT_ALERT;
        [alert show];
    }
    

    
    
    /* NSLog(@"where: product info");
     if ([result isEqual:@"NotFound"]) {
     //[self initAllInputs];
     UIAlertView *alert_producut = [[UIAlertView alloc] initWithTitle:@"INFO MESSAGE" message:@"Product is not found! If the item is not new item but the msg is repeated, move to another tab and come back!" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
     //alert_producut.tag = PRODUCT_NOT_FOUND_ALERT;
     [alert_producut show];
     }else{
     }

     */
}


- (void) fetchedDataForProductInfo:(NSData *) responseData {
    // [displayStatus setText:@"fetched Data"];
    if (responseData == nil) {
        NSLog(@"no reponse3");
        UIAlertView *alert_srv_response = [[UIAlertView alloc] initWithTitle:@"Info Message" message:@"Server is not responding!" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
        //alert_login_result.tag = TAG_LOGIN_ALERT;
        [alert_srv_response show];
    }else{
        
        NSError* error;
        NSDictionary* json = [NSJSONSerialization JSONObjectWithData:responseData options:kNilOptions error:&error];
        NSLog(@"json:%@", error);
        NSArray* result = [json objectForKey:@"Result"];
        NSLog(@"result: %@", result);
        NSString *msg_result =@"";
        if( [result isEqual: @"NotFound"]){
            msg_result = @"The Item is not found!";
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Confirm Message" message:msg_result delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
            [alert show];
            //[self initAllInputs];
        }else{
            //msg_result = @"The Item is already existed!";
            detail = [result objectAtIndex:0];
            
            // get item info from json
            self.txtDesc.text = [detail objectForKey:@"EngDesc"];
                       self.txtUnitSize.text = [detail objectForKey:@"UnitSize"];
            self.txtUnitCode.text = [detail objectForKey:@"UnitCode"];
            
        
            

        }
        
        CGPoint scrollPoint = CGPointMake(0, contentView.frame.origin.y-65);
        [scrollView setContentOffset:scrollPoint animated:YES];
        
        
    }
}



- (void)initAllInputs{
    self.txtOrderQty.text = @"0";
    
    [self.txtItemNo resignFirstResponder];
    [self.txtOrderQty resignFirstResponder];
    
    self.txtOrderNo.userInteractionEnabled = NO;
    self.txtFdaHold.userInteractionEnabled = NO;
    self.txtPalletQty.userInteractionEnabled =NO;
    self.txtPackQty.userInteractionEnabled =NO;
    self.txtUnitCode.userInteractionEnabled =NO;
    self.txtUnitSize.userInteractionEnabled =NO;
    self.txtSRP.userInteractionEnabled =NO;
    self.txt2W.userInteractionEnabled =NO;
    self.txt1W.userInteractionEnabled =NO;
    self.txtOnHand.userInteractionEnabled =NO;
    self.txtPrice.userInteractionEnabled =NO;
    self.txtDesc.userInteractionEnabled =NO;
   
    //set textfield border color blue
   
    self.txtItemNo.layer.cornerRadius = 8.0f;
    self.txtItemNo.layer.borderWidth = 1;
    self.txtItemNo.layer.borderColor = [[UIColor colorWithRed:0.0 green:122.0/255.0 blue:1.0 alpha:1.0] CGColor];
    
    self.txtOrderQty.layer.cornerRadius = 8.0f;
    self.txtOrderQty.layer.borderWidth = 1;
    self.txtOrderQty.layer.borderColor = [[UIColor colorWithRed:0.0 green:122.0/255.0 blue:1.0 alpha:1.0] CGColor];
    
    self.txtUnitSize.layer.cornerRadius = 8.0f;
    self.txtUnitSize.layer.borderWidth =1;
    self.txtUnitSize.layer.borderColor = [[UIColor colorWithRed:0.905 green:0.0 blue:0.552 alpha:1.0] CGColor];
    
    self.txtUnitCode.layer.cornerRadius = 8.0f;
    self.txtUnitCode.layer.borderWidth =1;
    self.txtUnitCode.layer.borderColor = [[UIColor colorWithRed:0.905 green:0.0 blue:0.552 alpha:1.0] CGColor];
    
    self.txtSRP.layer.cornerRadius = 8.0f;
    self.txtSRP.layer.borderWidth =1;
    self.txtSRP.layer.borderColor = [[UIColor colorWithRed:0.905 green:0.0 blue:0.552 alpha:1.0] CGColor];
}

- (void) createDataForOtherList{
    list_taxtypes = @[@"TAX TYPE", @"NONE", @"TAX-A", @"TAX-B", @"TAX-C", @"TAX-D"];
    list_foodstamps = @[@"FOOD STAMP", @"TRUE", @"FALSE"];
    dic_fdstamps = @{@"TRUE" : [NSNumber numberWithInt:1], @"FALSE" : [NSNumber numberWithInt:0]};
    list_agerst = @[@"AGE RESTRICTION", @"NONE", @"ALCOHOL", @"TOBOCCO"];
    dic_agerst = @{@"NONE" : [NSNumber numberWithInt:0], @"ALCOHOL" : [NSNumber numberWithInt:1], @"TOBOCCO" : [NSNumber numberWithInt:2]};
}


-(void)customizeBtn{
    UIImage *buttonImage = [[UIImage imageNamed:@"greyButton.png"]
                            resizableImageWithCapInsets:UIEdgeInsetsMake(18, 18, 18, 18)];
    UIImage *buttonImageHighlight = [[UIImage imageNamed:@"greyButtonHighlight.png"]
                                     resizableImageWithCapInsets:UIEdgeInsetsMake(18, 18, 18, 18)];
    // Set the background for any states you plan to use
    [self.btnSaveItem setBackgroundImage:buttonImage forState:UIControlStateNormal];
    [self.btnSaveItem setBackgroundImage:buttonImageHighlight forState:UIControlStateHighlighted];
    [self.btnSearch setBackgroundImage:buttonImage forState:UIControlStateNormal];
    [self.btnSearch setBackgroundImage:buttonImageHighlight forState:UIControlStateHighlighted];

}


// check the Linea scanner conneciton, but this func. not used yet.
-(void)connectionState:(int)state {
    /*
     NSString *msg_result = [ NSString stringWithFormat:@"State: %i", state];
     UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"INFO MESSAGE" message:msg_result delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
     [alert show];
     */
    switch (state) {
        case CONN_DISCONNECTED:{
            //btnScannerStatus
            UIImage *buttonImage = [[UIImage imageNamed:@"orangeButton.png"]
                                    resizableImageWithCapInsets:UIEdgeInsetsMake(18, 18, 18, 18)];
            // Set the background for any states you plan to use
            [btnScannerStatus setBackgroundImage:buttonImage forState:UIControlStateNormal];
            break;
        }
            
        case CONN_CONNECTING:
            break;
        case CONN_CONNECTED:{
            //btnScannerStatus
            UIImage *buttonImage = [[UIImage imageNamed:@"greenButton.png"]
                                    resizableImageWithCapInsets:UIEdgeInsetsMake(18, 18, 18, 18)];
            // Set the background for any states you plan to use
            [btnScannerStatus setBackgroundImage:buttonImage forState:UIControlStateNormal];
            
            break;
        }
    }
}









-(void) backgroundClicked:(id)sender{
    [self.txtItemNo resignFirstResponder];
    [self.txtOrderQty resignFirstResponder];
}






-(NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView{
    return 1;
}

-(NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component{
    if([pickerView isEqual: unitcode_picker]){
       // NSLog(@"is Equal to unitcode_picker 1");
        return [list_unitcodes count];
    }else if( [pickerView isEqual:dept_picker]){
        return [list_departments count];
    }else if( [pickerView isEqual:vendor_picker]){
        return [list_vendors count];
    }else if( [pickerView isEqual:tax_picker]){
        return [list_taxtypes count];
    }else if( [pickerView isEqual:fdstamp_picker]){
        return [list_foodstamps count];
    }else if( [pickerView isEqual:agerst_picker]){
        return [list_agerst count];
    }else{
        return 0;
    }
    
}

-(NSString*)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component{
    
    if([pickerView isEqual: unitcode_picker]){
       // NSLog(@"is Equal to list_unitcodes 2");
        return [list_unitcodes objectAtIndex:row];
    }else if( [pickerView isEqual:dept_picker]){
        return [list_departments objectAtIndex:row];
    }else if( [pickerView isEqual:vendor_picker]){
        return [list_vendors objectAtIndex:row];
    }else if( [pickerView isEqual:tax_picker]){
        return [list_taxtypes objectAtIndex:row];
    }else if( [pickerView isEqual:fdstamp_picker]){
        return [list_foodstamps objectAtIndex:row];
    }else if( [pickerView isEqual:agerst_picker]){
        return [list_agerst objectAtIndex:row];
    }else{
        return nil;
    }
    
}

-(void) pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component{
    if (row != 0) {
        
        
    }
}

@end
