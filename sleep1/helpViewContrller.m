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
        UITabBarItem *tbi = [self tabBarItem];
        
        // give it an image
        UIImage *img = [UIImage imageNamed:@"icon.png"];
        [tbi setImage:img];
        
        
    }
    
    return self;
}

@end
