//
//  OrderListTableViewController.h
//  CPFR
//
//  Created by SEOHWAN.MOON on 3/11/15.
//  Copyright (c) 2015 moon. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AFNetworking.h"
#import "OrderItem.h"

@interface OrderListTableViewController : UITableViewController{
    NSInteger _currentPage;
    NSInteger _totalPages;
    NSInteger _itemNum;
}
@property (nonatomic, retain)NSArray *listData;

@end
