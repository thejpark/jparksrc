//
//  HeavyViewController.m
//  sleep1
//
//  Created by Park Jung Gyu on 15/03/14.
//  Copyright (c) 2014 pyfamily. All rights reserved.
//

#import "HeavyViewController.h"

@interface HeavyViewController ()

@end

@implementation HeavyViewController


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
    //    return (toInterfaceOrientation == UIInterfaceOrientationPortrait) ||
    //    UIInterfaceOrientationIsLandscape(toInterfaceOrientation);
    return (toInterfaceOrientation == UIInterfaceOrientationPortrait);
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        // get the tab bar item
        UITabBarItem *tbi = [self tabBarItem];
        
        // give it a label
        [tbi setTitle:@"test"];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
