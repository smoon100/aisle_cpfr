//
//  OrderListTableViewController.m
//  CPFR
//
//  Created by SEOHWAN.MOON on 3/11/15.
//  Copyright (c) 2015 moon. All rights reserved.
//

#import "OrderListTableViewController.h"
#import "AFNetworking.h"
#import "OrderItem.h"

const int kLoadingCellTag = 1273;

@interface OrderListTableViewController ()
@property (nonatomic, retain) NSMutableArray *orderItems;
- (void)fetchOrderItems;
@end

@implementation OrderListTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(print_Message)];
   
    self.orderItems = [NSMutableArray array];
    _currentPage = 0;
    _itemNum = 1;
    /*
    self.listData = @[ @"Item1", @"Item2", @"Item3", @"Item4",@"Item1", @"Item2", @"Item3", @"Item4",@"Item1", @"Item2", @"Item3", @"Item4",@"Item1", @"Item2", @"Item3", @"Item4",@"Item1", @"Item2", @"Item3", @"Item4",@"Item1", @"Item2", @"Item3", @"Item4",@"Item1", @"Item2", @"Item3", @"Item4",@"Item1", @"Item2", @"Item3", @"Item4",@"Item1", @"Item2", @"Item3", @"Item4"];
    */
    self.tableView.pagingEnabled = YES;
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

-(void)print_Message {
    UIAlertView *alert_srv_response = [[UIAlertView alloc] initWithTitle:@"Info Message" message:@"Are you sure you complete this order?" delegate:self cancelButtonTitle:@"NO" otherButtonTitles:@"YES", nil];
    //alert_login_result.tag = TAG_LOGIN_ALERT;
    [alert_srv_response show];
    
    NSLog(@"Eh up, someone just pressed the button!");
   // [self performSegueWithIdentifier:@"segue.gbk.grocery.order.list" sender:self.view];
}


- (void) alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if( 0 == buttonIndex ){ //cancel button
        [alertView dismissWithClickedButtonIndex:buttonIndex animated:YES];
    } else if ( 1 == buttonIndex ){
        [alertView dismissWithClickedButtonIndex:buttonIndex animated:YES];
        UIAlertView * secondAlertView = [[UIAlertView alloc] initWithTitle:@"Info Message"
                                                                   message:@"The Order is successfully saved!"
                                                                  delegate:nil
                                                         cancelButtonTitle:@"OK"
                                                         otherButtonTitles:nil];
        [secondAlertView show];
    }
}



- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (_currentPage == 0) {
            NSLog(@"cur page is 1");
        return 1;
    }
    
    if (_currentPage < _totalPages) {
        return self.orderItems.count + 1;
    }
    return self.orderItems.count;
}


- (UITableViewCell *)orderItemCellForIndexPath:(NSIndexPath *)indexPath {
    NSLog(@"call func.  orderItemCellForIndexPath");
    static NSString *cellIdentifier = @"cell";
    UITableViewCell *cell = [self.tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle
                                       reuseIdentifier:cellIdentifier];
    }
    OrderItem *item = [self.orderItems objectAtIndex:indexPath.row];
    //NSLog(@"item upc: %@", item->upc);
    cell.textLabel.text = [NSString stringWithFormat:@" %@, %@", item->num, item->upc];//(@"%@",item->upc) ;
    
    //Beer *beer = [self.beers objectAtIndex:indexPath.row];
    //cell.textLabel.text = beer.name;
    cell.detailTextLabel.text = item->description;
    
    return cell;

}


- (UITableViewCell *)loadingCell {
    NSLog(@"LOADING...");
    UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                                    reuseIdentifier:nil] ;
    
    UIActivityIndicatorView *activityIndicator = [[UIActivityIndicatorView alloc]
                                                  initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    activityIndicator.center = cell.center;
    [cell addSubview:activityIndicator];
    
    [activityIndicator startAnimating];
    
    cell.tag = kLoadingCellTag;
    
    return cell;
    

}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    NSLog(@"cur indexPath.row count: %i", indexPath.row);
    NSLog(@"cur order item count: %i", self.orderItems.count);
    if (indexPath.row < self.orderItems.count) {
        NSLog(@"less than current page count");
        return [self orderItemCellForIndexPath:indexPath];
    } else {
        NSLog(@"greater than current page count");
        return [self loadingCell];
    }

}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (cell.tag == kLoadingCellTag) {
        _currentPage++;
        [self fetchOrderItems];
    }
}


- (void)fetchOrderItems {
    NSString *urlString = [NSString stringWithFormat:@"http://192.168.1.205:8080/PasingViewJson/PagingJson.jsp?Page=%d", _currentPage];
    NSURL *url = [NSURL URLWithString:urlString];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    
    
    
    AFHTTPRequestOperation *operation = [[AFHTTPRequestOperation alloc] initWithRequest:request];
    operation.responseSerializer = [AFJSONResponseSerializer serializer];
    operation.responseSerializer.acceptableContentTypes = [NSSet setWithObject:@"text/html"];
    [operation setCompletionBlockWithSuccess:^(AFHTTPRequestOperation *operation, id responseObject) {
        NSLog(@"responseObject %@", responseObject);
        
        _totalPages = [[responseObject objectForKey:@"totalCount"] intValue];
        NSLog(@"total pages %i", _totalPages);
        for (id orderItemDictionary in [responseObject objectForKey:@"Result"]) {
            OrderItem *orderItem = [[OrderItem alloc] initWithDictionary:orderItemDictionary];
            if (![self.orderItems containsObject:orderItem]) {
                [self.orderItems addObject:orderItem];
                NSLog(@"cur orderItem %@", orderItem->upc);
            }
            
        }
        //NSLog(@"self.orderItems %@", self.orderItems);
        [self.tableView reloadData];
        
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        NSLog(@"Error: %@", [error localizedDescription]);
        [[[UIAlertView alloc] initWithTitle:@"Error fetching order items!"
                                     message:@"Please try again later"
                                    delegate:nil
                           cancelButtonTitle:@"OK"
                           otherButtonTitles:nil]  show];
    }];
    
    [operation start];
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}











/*
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:<#@"reuseIdentifier"#> forIndexPath:indexPath];
    
    // Configure the cell...
    
    return cell;
}
*/

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
