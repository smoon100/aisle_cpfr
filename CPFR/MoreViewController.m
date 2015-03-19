//
//  MoreViewController.m
//  AisleMaster
//
//  Created by SEOHWAN.MOON on 2/7/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import "MoreViewController.h"
#import "LoginViewController.h"

@interface MoreViewController ()

@end

@implementation MoreViewController


- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
   // NSMutableArray *objs = [[NSMutableArray alloc]init];
    
   // NSString *uuid =  [[[UIDevice currentDevice] //[objs addObject:@[@"Web View", @"Batch Scan"]];
    //[objs addObject:@"View Device Number"];
	self.listData = @[ @"GBK GROCERY ORDER"];//@"WEB CPFR (COMMING SOON)"
    
    [self createLogoutBtn];
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	
	NSUInteger row = [indexPath row];
	//UIViewController *anotherViewController;
	//NSLog(@"row:%i", row);
    //[NSThread detachNewThreadSelector:@selector(doLocalBroadcast) toTarget:self withObject:nil];
	switch (row) {
            /*
        case 0:
            [self performSegueWithIdentifier:@"segue.webView" sender:self.view];
            break;
            */
        case 0:{
            [self performSegueWithIdentifier:@"segue.gbk.grocery.order" sender:self.view];
            break;
        }
            
            
        default:
            break;
    }
    
	[self.tableView deselectRowAtIndexPath:indexPath animated:YES];
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.listData count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
	NSUInteger row = [indexPath row];
	cell.textLabel.text = [self.listData objectAtIndex:row];
    
    // add image
    UIImage *image = [UIImage imageNamed:@"30-key.png"];
    cell.imageView.image = image;
    
    return cell;
}




-(void)createLogoutBtn{
    UIButton *btnLogout = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 60, 40)];
    
    //[btnLogin setTitle:@"LOGOUT" forState:UIControlStateNormal];
    [btnLogout setImage:[UIImage imageNamed:@"logout-button.png"] forState:UIControlStateNormal];
    [btnLogout setTitle:@"logout" forState:UIControlStateNormal];
    [btnLogout addTarget:self action:@selector(logoutClicked) forControlEvents:UIControlEventTouchUpInside];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:btnLogout];
}

-(void)logoutClicked{
    NSLog(@"logout clicked");
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    BOOL isLoggedIn = [prefs boolForKey:@"IsLoggedIn"];
    // NSLog(@"login?:%d", isLoggedIn);
    if( isLoggedIn ){
        NSLog(@"LogOut clicked");
        [prefs setBool:FALSE forKey:@"IsLoggedIn"];
        [prefs setValue:@"" forKey:@"REALNAME"];
        [prefs setValue:@"" forKey:@"UID"];
        
        [prefs synchronize];
    }
    //[self performSegueWithIdentifier:@"segue.receiving.logout" sender:self];
    LoginViewController *loginViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"LoginViewPage"];
    [self.navigationController pushViewController:loginViewController animated:YES];
}



- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a story board-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}

 */

@end
