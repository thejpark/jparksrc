//
//  helpView.m
//  sleep1
//
//  Created by Park Jung Gyu on 10/03/14.
//  Copyright (c) 2014 pyfamily. All rights reserved.
//

#import "helpViewController.h"

@implementation helpViewController

-(id)initWithNibName:(NSString *)nibName bundle:(NSBundle *) bundle
{
    // call super class
    self = [super initWithNibName:nil
                           bundle:nil];
    if (self) {
        // get the tab bar item
//        UITabBarItem *tbi = [self tabBarItem];
//        
//        // give it an image
//        UIImage *i = [UIImage imageNamed:@"Time.png"];
//        [tbi setImage:i];
    }
    
    return self;
}

//// Do we need this? As this does not make any difference
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
    //    return (toInterfaceOrientation == UIInterfaceOrientationPortrait) ||
    //    UIInterfaceOrientationIsLandscape(toInterfaceOrientation);
    return (toInterfaceOrientation == UIInterfaceOrientationPortrait);
}


@end
