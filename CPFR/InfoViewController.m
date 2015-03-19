//
//  InfoViewController.m
//  AisleMaster
//
//  Created by SEOHWAN.MOON on 7/3/14.
//  Copyright (c) 2014 moon. All rights reserved.
//

#import "InfoViewController.h"

@interface InfoViewController ()

@end

@implementation InfoViewController

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
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    NSString *serverIp = [prefs valueForKey:@"ServerIP"];
    NSString *storeno = [prefs stringForKey:@"StoreNumber"];
    NSString *lang_desc = [prefs stringForKey:@"LANGUAGE"];
    //lang_int = [prefs stringForKey:@"LANGUAGE_INT"];
    
    self.txtServerIp.text = serverIp;
    self.txt2ndLanguage.text = lang_desc;
    self.txtStoreNum.text = storeno;
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
