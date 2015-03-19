//
//  CommonViewController.m
//  AisleMaster
//
//  Created by SEOHWAN.MOON on 2/21/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import "CommonViewController.h"
#import <AudioToolbox/AudioToolbox.h>
//import for zebra printer
#import "PrinterStatus.h"
#import "ZebraPrinterFactory.h"
#import "TcpPrinterConnection.h"

#define PRINTER_NOT_FOUND_ALERT 3

@interface CommonViewController ()

@end

@implementation CommonViewController

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
	// Do any additional setup after loading the view.
}



-(NSString*)getBrBarcode:(NSString*)barcode type:(int)type{
    
    NSString *br_barcode=@"";
    
    switch(type){
        case 1:{//@"UPC-A":
            
            // Type-2
            int first_digit = (int)([barcode characterAtIndex:0] - '0');
            if(first_digit == 2){
                NSString *PLU_num = [barcode substringToIndex:6];
                br_barcode = [NSString stringWithFormat:@"%@00000",PLU_num];
                break;
            }
            
            br_barcode = [barcode substringToIndex:barcode.length-1];
            break;
        }
        case 7: // Code 128
            br_barcode = [barcode substringToIndex:barcode.length];
            break;
            
        case 13: {// EAN 8 => br add 3 0s => 000 + num + check digit
            NSString *numbers = [barcode substringToIndex:7];
            br_barcode = [NSString stringWithFormat:@"0000%@", numbers];
            break;
        }
        case 14: {// EAN 13
            br_barcode = [barcode substringToIndex:barcode.length-1];
            break;
        }
        case 41:{// UPC-E
            if(barcode.length == 7){
                br_barcode = [self ConvertUPCE2A:barcode];                
            }
            break;

        }
    }
    
    return br_barcode;
}

-(NSString*)ConvertUPCE2A:(NSString*)barcode{
    NSLog(@"UPC-E");
    barcode = [barcode substringToIndex:6];
    int sixth_digit = (int)([barcode characterAtIndex:5] - '0');
    
    NSString *final_num = @"";
    NSString *manufactur_num = @"";
    NSString *itme_num =  @"";
    switch (sixth_digit) {
        case 0:
            
            manufactur_num = [NSString stringWithFormat:@"%c%c%c00",[barcode characterAtIndex:0], [barcode characterAtIndex:1], [barcode characterAtIndex:5]];
            itme_num = [NSString stringWithFormat:@"00%c%c%c",[barcode characterAtIndex:2], [barcode characterAtIndex:3], [barcode characterAtIndex:4]];
            
            break;
            
        case 1:
            manufactur_num = [NSString stringWithFormat:@"%c%c%c00",[barcode characterAtIndex:0], [barcode characterAtIndex:1], [barcode characterAtIndex:5]];
            itme_num = [NSString stringWithFormat:@"00%c%c%c",[barcode characterAtIndex:2], [barcode characterAtIndex:3], [barcode characterAtIndex:4]];
            break;
            
        case 2:
            manufactur_num = [NSString stringWithFormat:@"%c%c%c00",[barcode characterAtIndex:0], [barcode characterAtIndex:1], [barcode characterAtIndex:5]];
            itme_num = [NSString stringWithFormat:@"00%c%c%c",[barcode characterAtIndex:2], [barcode characterAtIndex:3], [barcode characterAtIndex:4]];
            break;
            
        case 3:
            manufactur_num = [NSString stringWithFormat:@"%c%c%c00",[barcode characterAtIndex:0], [barcode characterAtIndex:1], [barcode characterAtIndex:2]];
            itme_num = [NSString stringWithFormat:@"000%c%c", [barcode characterAtIndex:3], [barcode characterAtIndex:4]];
            break;
            
        case 4:
            manufactur_num = [NSString stringWithFormat:@"%c%c%c%c0",[barcode characterAtIndex:0], [barcode characterAtIndex:1], [barcode characterAtIndex:2], [barcode characterAtIndex:3]];
            itme_num = [NSString stringWithFormat:@"0000%c", [barcode characterAtIndex:4]];
            break;
            
        default:
            manufactur_num = [NSString stringWithFormat:@"%c%c%c%c%c",[barcode characterAtIndex:0], [barcode characterAtIndex:1], [barcode characterAtIndex:2], [barcode characterAtIndex:3], [barcode characterAtIndex:4]];
            itme_num = [NSString stringWithFormat:@"0000%c", [barcode characterAtIndex:5]];
            break;
    }
    
    final_num = [NSString stringWithFormat:@"0%@%@", manufactur_num, itme_num];
    
    return final_num;
}

-(BOOL)validateCurrency:(NSString *)price{
    NSError *error = NULL;
    NSRegularExpression *regex = [NSRegularExpression
                                  //regularExpressionWithPattern:@"^[$][0-9]+([.][0-9]{2})?$"
                                  regularExpressionWithPattern:@"^[0-9]+[.][0-9]{2}?$"
                                  options:NSRegularExpressionCaseInsensitive
                                  error:&error];
    if ([regex numberOfMatchesInString:price options:0 range:NSMakeRange(0, price.length)]) {
        return true;
    }
    return false;
}

-(void)commonPrintLabel:(NSString *)printerIP withUpcType:(NSString *)upc_type withLang:(NSString *)label_lang withDetail:(NSDictionary *)detail withQty:(int)reg_price_qty{
    
    NSLog(@"start of common funct.");
    
    NSError *error = nil;
    
    // get item info from json
    NSString* upc_code = [detail objectForKey:@"UPC"];
    NSString* aisle_no = [detail objectForKey:@"AisleNo"];
    NSString* eng_desc = [detail objectForKey:@"EngDesc"];
    NSString* kor_desc = [detail objectForKey:@"KorDesc"];
    NSString* retail_price = [detail objectForKey:@"RetailPrice"];
    NSString* shelf_no = [detail objectForKey:@"ShelfNo"];
    NSString* unit_measure = [detail objectForKey:@"UnitMeasure"];
    NSString* unit_price = [detail objectForKey:@"UnitPrice"];
    //NSString* unit_size = [detail objectForKey:@"UnitSize"];
    NSString* product_size = [detail objectForKey:@"ProductSize"];
    NSString* is_tax = [detail objectForKey:@"IsTax"];
    NSString* disp_crv = [detail objectForKey:@"IsCRV"];
    NSString* pack_qty = [detail objectForKey:@"PackQty"];
    NSString* vd_item_code = [detail objectForKey:@"VendorItemCode"];
    NSString* vd_code = [detail objectForKey:@"VendorCode"];
   // NSString* spaceAddedText = [self stringByAddingSpace:(pack_qty) spaceCount:5 atIndex:5];
    NSString* extra = [NSString stringWithFormat :@"%@          %@         %@", pack_qty, vd_code, vd_item_code];
    //NSString* extra = [NSString stringWithFormat :@"%@     %@", vd_code, pack_qty];
    //NSString* extra = [NSString stringWithFormat :@"%@ %@ %@", pack_qty, vd_code, vd_item_code];
    
    //######### SCAN COMMON SECTION###########
    NSLog(@"Starting");
    zebraPrinterConnection = [[TcpPrinterConnection alloc] initWithAddress:printerIP andWithPort:6101];
    BOOL success = [zebraPrinterConnection open];
    //NSLog(@"PRINTER IS-CONNECTED?: %i",success);
    printer = [ZebraPrinterFactory getInstance:zebraPrinterConnection error:&error];
    
    
    NSString *itemKrnDesc = kor_desc;//  @"해오름 숙성 소면 3LB";#PARAM#
    NSString *multi_lang_desc = @"";
    NSLog(@"Lang Setting: %@", label_lang);
    NSString *lang_prefix = @"";
    if ([label_lang isEqualToString:@"KOREAN"]) {
        NSUInteger encoding = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingEUC_KR);
        const char * eucKRString = [itemKrnDesc cStringUsingEncoding:encoding];
        multi_lang_desc = [NSString stringWithFormat:@"%s", eucKRString];
        lang_prefix = @"";
        
    }else if( [label_lang isEqualToString:@"CHINESE"]){
        multi_lang_desc = [NSString stringWithCString:[itemKrnDesc UTF8String]];
        lang_prefix = @"CHINESE_";
        
    }else if( [label_lang isEqualToString:@"SPANISH"]){
        //
        lang_prefix = @"SPANISH_";
    }else if( [label_lang isEqualToString:@"JAPANESE"]){
        //
        lang_prefix = @"JAPANESE_";
    }
    
    
    NSString *zpl_format_name = @"";
    if( [upc_type isEqualToString:@"UPC-A"]){
        zpl_format_name = [NSString stringWithFormat :@"E:%@FORMAT.ZPL", lang_prefix];
    }else{
        zpl_format_name = [NSString stringWithFormat :@"E:%@FORMAT_E13.ZPL", lang_prefix];
    }
    
    NSLog(@"selected Lang: %@", multi_lang_desc);
    
    // 6/13/2014
    // price for 2/$5.00
    NSString *printed_retail_price = [NSString stringWithFormat:@"$%@", retail_price];
    if( reg_price_qty > 1){
        printed_retail_price = [NSString stringWithFormat:@"%i/$%@", reg_price_qty, retail_price];
    }
    
    // check price length and space padding
    NSInteger price_length = [printed_retail_price length];
    //NSLog(@"price length: %i",price_length);
    
    NSString *space_paddings = @"";
    for(int i=0; i < (10-price_length); i++){
        //space_paddings
        space_paddings = [space_paddings stringByAppendingString:@" "];
    }
    printed_retail_price = [space_paddings stringByAppendingString:printed_retail_price];
    
    if([is_tax isEqual:@"true"]){
        is_tax = @"+ TAX";
    }else{
        is_tax = @"";
    }
    
    NSLog(@"IS TAX: %@", is_tax);
    NSLog(@"IS CRV: %@", disp_crv);
    
    NSString *printed_unit_price = [NSString stringWithFormat:@"$%@", unit_price];
    NSString *cur_date = @"";//[self formatDate:[NSDate date]];
    
    // FORMAT.ZPL has two fields - the first is number 12, the second is number 11
    NSMutableDictionary *vars = [[NSMutableDictionary alloc] init];
    //unit price
    [vars setObject:printed_unit_price forKey:[NSNumber numberWithInt:11]];
    [vars setObject:unit_measure forKey:[NSNumber numberWithInt:12]];
    [vars setObject:eng_desc forKey:[NSNumber numberWithInt:13]];
    [vars setObject:printed_retail_price forKey:[NSNumber numberWithInt:14]];//retail
    //[vars setObject:[NSString stringWithFormat:@"%s", eucKRString] forKey:[NSNumber numberWithInt:15]];
    [vars setObject:multi_lang_desc forKey:[NSNumber numberWithInt:15]];
    [vars setObject:product_size forKey:[NSNumber numberWithInt:16]];//product size
    [vars setObject:aisle_no forKey:[NSNumber numberWithInt:17]];//Aisle
    [vars setObject:shelf_no forKey:[NSNumber numberWithInt:18]];//Shelf
    [vars setObject:cur_date forKey:[NSNumber numberWithInt:19]];
    [vars setObject:upc_code  forKey:[NSNumber numberWithInt:7]];
    [vars setObject:upc_code forKey:[NSNumber numberWithInt:8]];
    
    [vars setObject:is_tax forKey:[NSNumber numberWithInt:9]];
    [vars setObject:disp_crv forKey:[NSNumber numberWithInt:10]];
    
    //extra
    //[vars setObject:vd_item_code forKey:[NSNumber numberWithInt:21]];
    [vars setObject:extra forKey:[NSNumber numberWithInt:20]];
    //disp_crv
    
    success = success && [[printer getFormatUtil] printStoredFormat:zpl_format_name withDictionary:vars error:&error];
    
    if (error != nil || printer == nil || success == NO) {
        UIAlertView *errorAlert = [[UIAlertView alloc] initWithTitle:@"Error" message:[error localizedDescription] delegate:self cancelButtonTitle:@"Ok" otherButtonTitles:@"FIND  PRINTER", nil];
        errorAlert.tag = PRINTER_NOT_FOUND_ALERT;
        [errorAlert show];
        
    }
    
    [zebraPrinterConnection close];
    
    NSLog(@"end of printing..");
    NSLog(@"end of common funct.");
}


-(void)buttonSound{
    AudioServicesPlaySystemSound(1306); // Tock.caf
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


-(NSString*)stringByAddingSpace:(NSString*)stringToAddSpace spaceCount:(NSInteger)spaceCount atIndex:(NSInteger)index{
    NSString *result = [NSString stringWithFormat:@"%@%@",[@" " stringByPaddingToLength:spaceCount withString:@" " startingAtIndex:0],stringToAddSpace];
    return result;
}

@end
