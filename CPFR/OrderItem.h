//
//  OrderItem.h
//  CPFR
//
//  Created by SEOHWAN.MOON on 3/12/15.
//  Copyright (c) 2015 moon. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface OrderItem : NSObject{
    @public NSString *num;
    @public NSString *upc;
    @public NSString *description;
   // NSDictionary *dictionary;
}
-(id)initWithDictionary:(NSDictionary *)dictionary;
@end
