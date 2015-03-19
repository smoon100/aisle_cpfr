//
//  UdidViewController.m
//  AisleMaster
//
//  Created by SEOHWAN.MOON on 2/10/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import "UdidViewController.h"

#define kBgQueue dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0 )

@interface UdidViewController ()

@end

@implementation UdidViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSString *uuid =  [[[UIDevice currentDevice] identifierForVendor] UUIDString];
    NSString *appVer = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    txtUdid.text = uuid;
    txtAppVersion.text = appVer;
	// Do any additional setup after loading the view.
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    serverIp = [prefs valueForKey:@"ServerIP"];
    programId = [prefs integerForKey:@"ProgramID"];
    
    // (1)get store list
    NSString *urlForStoreList = [NSString stringWithFormat:@"http://%@/AISLEMASTER/json/reply_store_list.jsp", serverIp];
    [self jsonFromUrl:(NSString *) urlForStoreList];
    
    // Department / Vedor  picker
    store_picker = [[UIPickerView alloc]initWithFrame:CGRectMake(0, 43, 320, 480)];
    store_picker.delegate = self;
    store_picker.dataSource = self;
    
    [store_picker setShowsSelectionIndicator:YES];
    txtStoreName.inputView = store_picker;
 
    //
    txtUdid.userInteractionEnabled = NO;
    txtAppVersion.userInteractionEnabled = NO;
}



-(void)jsonFromUrl:(NSString *) urlAddress {
    // tesing read product info from DB
    NSString *urlAsString = urlAddress;
    NSLog(@"url copy: %@", urlAddress);
    //NSString *methodName = @"fetchedData";
    //SEL curMethod = @selector(fetchedData:);
    
    NSURL *jsonInfoURL = [NSURL URLWithString: (NSString *)urlAsString];
   // NSLog(jsonInfoURL);
    // Department
    
    //dispatch_async(kBgQueue, ^{
        NSData *data = [NSData dataWithContentsOfURL:jsonInfoURL];
       // NSLog(data);
        [self performSelectorOnMainThread: @selector(fetchedDataForStoreList:) withObject:data waitUntilDone:YES];
   // });
    
}



- (void) fetchedDataForStoreList:(NSData *) responseData {
    // [displayStatus setText:@"fetched Data"];
    NSError* error;
    if (responseData == nil) {
        NSLog(@"no reponse1");
        list_stores =  @[ @"Server Error" ];
    }else{
        id json = [NSJSONSerialization JSONObjectWithData:responseData options:kNilOptions error:&error];
        NSArray *keys = [json valueForKeyPath:@"KEY"];
        NSArray *values = [json valueForKeyPath:@"VALUE"];
        
        NSDictionary *storetList = [NSDictionary dictionaryWithObjects:values forKeys:keys];
       // NSLog(storetList);
        dic_stores = storetList;
        list_stores = values;
        NSLog(@"%@", dic_stores);
    }
}


-(NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView{
    return 1;
}

-(NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component{
    if([pickerView isEqual: store_picker]){
        return [list_stores count];
    }else{
        return 0;
    }
    
}

-(NSString*)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component{
    
    if([pickerView isEqual: store_picker]){
        return [list_stores objectAtIndex:row];
    }else{
        return nil;
    }
    
}

-(void) pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component{
    if (row != 0) {
        
        if([pickerView isEqual: store_picker]){
            txtStoreName.text = [list_stores objectAtIndex:row];
        }
        
    }
}

-(void) backgroundClicked:(id)sender{
    
    [txtStoreName resignFirstResponder];
    
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)registerBtnClicked:(id)sender {
    
    
    
   // NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    //dic_departments
    NSString *deviceId = txtUdid.text;
  
    
    NSString *appVersion = txtAppVersion.text;
    
    NSString *storeName = txtStoreName.text;
    NSArray *temp = [dic_stores allKeysForObject:storeName];
    NSString *store_no = [temp lastObject];
    if( [storeName isEqualToString:@"Little Ferry"]){
        store_no = @"46";
    }
    //NSString *store_no = [prefs stringForKey:@"StoreNumber"];
    
    
    
    NSString *urlAsString = [NSString stringWithFormat:@"http://%@/AISLEMASTER/json/device_register_post.jsp?", serverIp];
    urlAsString = [urlAsString stringByAppendingString:@"MacAddress="];
    urlAsString = [urlAsString stringByAppendingString:deviceId];
    
    urlAsString = [urlAsString stringByAppendingString:@"&AppVersion="];
    urlAsString = [urlAsString stringByAppendingString:appVersion];
    
    urlAsString = [urlAsString stringByAppendingString:@"&StoreNo="];
    urlAsString = [urlAsString stringByAppendingString:store_no];
    
    urlAsString = [urlAsString stringByAppendingString:@"&ProgramId="];
    urlAsString = [urlAsString stringByAppendingString:[@(programId) stringValue]];
    
    urlAsString = [urlAsString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
    NSLog(@"string %@", urlAsString);
    NSString *urlForAddReceiving = urlAsString;
    [self jsonFromUrl:(NSString *) urlForAddReceiving :1];
    
}



-(void)jsonFromUrl:(NSString *) urlAddress :(NSInteger) type{
    // tesing read product info from DB
    NSString *urlAsString = urlAddress;
    NSLog(@"url copy: %@", urlAddress);
    //NSString *methodName = @"fetchedData";
    //SEL curMethod = @selector(fetchedData:);
    
    NSURL *jsonInfoURL = [NSURL URLWithString: (NSString *)urlAsString];
    switch (type) {
        
        case 1:{ // Receiving
            dispatch_async(kBgQueue, ^{
                NSData *data = [NSData dataWithContentsOfURL:jsonInfoURL];
                [self performSelectorOnMainThread: @selector(fetchedData:) withObject:data waitUntilDone:YES];
            });
            break;
        }
            
    }
}


- (void) fetchedData:(NSData *) responseData {
    // [displayStatus setText:@"fetched Data"];
    NSLog(@" %@", responseData );
    if (responseData == nil) {
        
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
            msg_result = @"The Device is registered!";
            // call clear input fields function
           // [self initAllInputs];
        }else{
            NSString* err_message = [json objectForKey:@"Message"];
            msg_result = err_message;
        }
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Confirm Message" message:msg_result delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
        
        [alert show];
    }
}




@end
