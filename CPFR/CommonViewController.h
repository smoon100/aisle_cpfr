//
//  CommonViewController.h
//  AisleMaster
//
//  Created by SEOHWAN.MOON on 2/21/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TcpPrinterConnection.h"
#import "ZebraPrinterFactory.h"

@interface CommonViewController : UIViewController{
    //zebra printer
    TcpPrinterConnection *zebraPrinterConnection;
    id<ZebraPrinter, NSObject> printer;
}
-(NSString*)getBrBarcode:(NSString *)barcode type:(int)type;
-(BOOL)validateCurrency:(NSString *)price; // RecevingController
-(void)commonPrintLabel:(NSString *)printerIP withUpcType:(NSString *)upc_type withLang:(NSString *)label_lang withDetail:(NSDictionary *)detail withQty:(int)reg_price_qty;

@end
