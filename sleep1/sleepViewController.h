//
//  sleepViewController.h
//  sleep1
//
//  Created by Park Jung Gyu on 17/02/14.
//  Copyright (c) 2014 pyfamily. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
// #import <AudioToolbox/AudioToolbox.h>

@interface sleepViewController : UIViewController <UIPickerViewDelegate, AVAudioPlayerDelegate>
{
    __weak IBOutlet UILabel *tLabel;
}

@property (nonatomic)	AVAudioPlayer	*player;

- (IBAction)showCurrentT:(id)sender;
- (IBAction)itemAction:(id)sender;
@end
