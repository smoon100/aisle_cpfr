//
//  NewItemViewController.h
//  AisleMaster
//
//  Created by SEOHWAN.MOON on 2/27/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LineaSDK.h"
#import "CommonViewController.h"
#import "TcpPrinterConnection.h"
#import "ZebraPrinterFactory.h"


@interface NewItemViewController : UIViewController<LineaDelegate, UIPickerViewDataSource, UIPickerViewDelegate>{
    Linea *linea;
    
    NSString *serverIp;
    NSString *storeno;
    NSString *lang_int;
    NSString *dept_permit;
    BOOL can_price_change;
    NSString *isTaxA;
    NSString *isTaxB;
    NSString *isTaxC;
    NSString *isTaxD;
    NSString *isFoodStamp;
    NSString *isWeightReq;
    
    IBOutlet UILabel *lblGreeting;
    IBOutlet UIButton *btnScannerStatus;
    
    IBOutlet UIScrollView *scrollView;
    IBOutlet UIView *contentView;
    
    //unit-code dropbox
    UIPickerView *unitcode_picker;
    NSDictionary *dic_unitcodes;
    NSArray *list_unitcodes;
    //
    NSDictionary *dic_departments;
    NSArray *list_departments;
    NSArray *list_vendors;
    NSArray *list_vendor_codes;
    
    UIPickerView *dept_picker;
    UIPickerView *vendor_picker;
    //other pickerview
    NSDictionary *dic_taxtypes;
    NSArray *list_taxtypes;
    UIPickerView *tax_picker;
    
    NSDictionary *dic_fdstamps;
    NSArray *list_foodstamps;
    UIPickerView *fdstamp_picker;
    
    NSDictionary *dic_agerst;
    NSArray *list_agerst;
    UIPickerView *agerst_picker;
    
    NSDictionary *detail;
}


@property (nonatomic, strong) CommonViewController *commonViewController;
@property (strong, nonatomic) IBOutlet UIButton *btnSearch;
@property (strong, nonatomic) IBOutlet UITextField *txtOrderNo;

@property (strong, nonatomic) IBOutlet UITextField *txtItemNo;
@property (strong, nonatomic) IBOutlet UITextField *txtDesc;

@property (strong, nonatomic) IBOutlet UITextField *txtPalletQty;
@property (strong, nonatomic) IBOutlet UITextField *txtPackQty;

@property (strong, nonatomic) IBOutlet UITextField *txtUnitSize;
@property (strong, nonatomic) IBOutlet UITextField *txtUnitCode;

@property (strong, nonatomic) IBOutlet UITextField *txtSRP;
@property (strong, nonatomic) IBOutlet UITextField *txtPrice;

@property (strong, nonatomic) IBOutlet UITextField *txt2W;
@property (strong, nonatomic) IBOutlet UITextField *txt1W;
@property (strong, nonatomic) IBOutlet UITextField *txtOrderQty;

@property (strong, nonatomic) IBOutlet UITextField *txtOnHand;
@property (strong, nonatomic) IBOutlet UITextField *txtFdaHold;

@property (strong, nonatomic) IBOutlet UIButton *btnSaveItem;


- (IBAction)backgroundClicked:(id)sender;
- (IBAction)saveBtnClicked:(id)sender;
- (IBAction)searchBtnClicked:(id)sender;

@end
