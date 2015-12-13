//
//  OpenCVWrapper.h
//  ledmessage
//
//  Created by Park Jung Gyu on 13/12/2015.
//  Copyright © 2015 pyfamily. All rights reserved.
//

#ifndef OpenCVWrapper_h
#define OpenCVWrapper_h

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

//#include <opencv2/videoio/cap_ios.h>

//using namespace cv;

@interface OpenCVWrapper : NSObject

- (void)videoInit;
- (void)startVideo;

//@property (nonatomic, retain) CvVideoCamera* videoCamera;

@end



#endif /* OpenCVWrapper_h */
