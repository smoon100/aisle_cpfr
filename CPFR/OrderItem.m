//
//  OrderItem.m
//  CPFR
//
//  Created by SEOHWAN.MOON on 3/12/15.
//  Copyright (c) 2015 moon. All rights reserved.
//

#import "OrderItem.h"

@implementation OrderItem

- (id)initWithDictionary:(NSDictionary *)dictionary {
    self = [super init];
    if (self) {
        //self.beerId = [[dictionary objectForKey:@"id"] intValue];
        self->upc = [dictionary objectForKey:@"UPC"];
        self->description = [dictionary objectForKey:@"DESCRIPTION"];
        self->num = [dictionary objectForKey:@"NUMBER"];
    }
    
    return self;
}

- (BOOL)isEqual:(id)object {
    if (![object isKindOfClass:[OrderItem class]]) {
        return NO;
    }
    
    OrderItem *other = (OrderItem *)object;
    return other->upc == self->upc;
}

@end
