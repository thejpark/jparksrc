//
//  sleepViewController.m
//  sleep1
//
//  Created by Park Jung Gyu on 17/02/14.
//  Copyright (c) 2014 pyfamily. All rights reserved.
//

#import "sleepViewController.h"

@implementation sleepViewController

@synthesize player;

- (IBAction)showCurrentT:(id)sender
{
    NSDate *now = [NSDate date];
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setTimeStyle:NSDateFormatterMediumStyle];
    [tLabel setText:[formatter stringFromDate:now]];
    
    if (player.playing == YES)
		[self pausePlaybackForPlayer: player];
	else
		[self startPlaybackForPlayer: player];
}

- (void)viewDidLoad
{
    // probably this is the best place to define file url and create audio player, as this method is called
    // after Nib is loaded. initWithNibName:bundle can be called before nib is loaded.
	// Load the the sample file, use mono or stero sample
	NSURL *fileURL = [[NSURL alloc] initFileURLWithPath: [[NSBundle mainBundle] pathForResource:@"kmkim" ofType:@"mp3"]];
    
    player = [[AVAudioPlayer alloc] initWithContentsOfURL:fileURL error:nil];
    
	if (self.player != nil) {
		player.numberOfLoops = 1;
		player.delegate = self;
	}
	
	[[AVAudioSession sharedInstance] setDelegate: self];
	
    NSError *setCategoryError = nil;
	
    [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayback error: &setCategoryError];
	if (setCategoryError) NSLog(@"Error setting category! %d", setCategoryError.code);
    
	fileURL = nil;
}


-(void)pausePlaybackForPlayer:(AVAudioPlayer*)p
{
	[p pause];
    //	[self updateViewForPlayerState:p];
    NSLog(@"Pause play");
}

-(void)startPlaybackForPlayer:(AVAudioPlayer*)p
{
	if ([p play])
	{
        //		[self updateViewForPlayerState:p];
	}
	else
		NSLog(@"Could not play %@\n", p.url);
}



@end
