//
//  CSVideoCapturerIOS.h
//  rvMedia
//
//  Created by David McGarry on 3/11/11.
//  Copyright 2011 RADVISION Inc. All rights reserved.
//

#import "CSVideoCommon.h"

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

extern NSString *const CSVideoCapturerErrorDomain;

typedef NS_ENUM(NSInteger, CSVideoCapturerErrorCode)
{
	CSVideoCapturerErrorCode_RuntimeError = 1,
	CSVideoCapturerErrorCode_DeviceNotFound,
	CSVideoCapturerErrorCode_DeviceInUse,
	CSVideoCapturerErrorCode_UnknownError,
	CSVideoCapturerErrorCode_UnsupportedInput,
	CSVideoCapturerErrorCode_UnsupportedOutput,
	CSVideoCapturerErrorCode_UnsupportedSessionPreset,
	CSVideoCapturerErrorCode_ApplicationIsNotAuthorizedToUseDevice,
};

typedef NS_ENUM(NSUInteger, CSVideoCapturerParams)
{
	CSVideoCapturerParams_640x480_480x640 = 0,
	CSVideoCapturerParams_640x480_640x360,
	CSVideoCapturerParams_640x480_624x352,
	CSVideoCapturerParams_640x480_480x272,
	CSVideoCapturerParams_480x360_480x272,
	CSVideoCapturerParams_352x288_320x192,
	CSVideoCapturerParams_352x288_320x180,
	CSVideoCapturerParams_LandscapeOnly_480x272,
	CSVideoCapturerParams_LandscapeOnly_960x540,
	CSVideoCapturerParams_LandscapeOnly_960x540_Wide,
	CSVideoCapturerParams_LandscapeOnly_1280x720,
	CSVideoCapturerParams_LandscapeOnly_1920x1080,
	CSVideoCapturerParams_LandscapePortrait_480x272,
	CSVideoCapturerParams_LandscapePortrait_960x540,
	CSVideoCapturerParams_LandscapePortrait_1280x720,
	CSVideoCapturerParams_LandscapePortrait_1920x1080,
	CSVideoCapturerParams_MaxIndex,
}; // __deprecated_enum_msg("Refer to CSVideoCapturePreference and CSVideoCaptureOrientation");

// Requested Capture Resolutions
//    Max - highest capture resolution supported by device
//    Min - lowest capture resolution supported by device
//    Specific resolution - upper bound for capture resolution. Maybe limited by hardware support
typedef NS_ENUM(NSInteger, CSVideoCapturePreference)
{
	CSVideoCapturePreference_Max = 0,
	CSVideoCapturePreference_1080p,
	CSVideoCapturePreference_720p,
	CSVideoCapturePreference_540p,
	CSVideoCapturePreference_360p,
	CSVideoCapturePreference_270p,
	CSVideoCapturePreference_Min
};

typedef NS_ENUM(NSInteger, CSVideoCaptureOrientation)
{
	CSVideoCaptureOrientation_LandscapeOnly = 0,
	CSVideoCaptureOrientation_LandscapeOrPortrait
};

typedef NS_ENUM(NSInteger, CSVideoCameraPosition)
{
	CSVideoCameraPositionUnspecified = AVCaptureDevicePositionUnspecified,
	CSVideoCameraPositionBack		 = AVCaptureDevicePositionBack,
	CSVideoCameraPositionFront		 = AVCaptureDevicePositionFront,
};

typedef NS_ENUM(NSInteger, CSVideoCapturerInterruptionReason)
{
	CSVideoCapturerInterruptionReason_Unspecified				= 0,
	CSVideoCapturerInterruptionReason_InUseByAnotherClient		= AVCaptureSessionInterruptionReasonVideoDeviceInUseByAnotherClient,
	CSVideoCapturerInterruptionReason_NotAvailableInBackground	= AVCaptureSessionInterruptionReasonVideoDeviceNotAvailableInBackground,
	CSVideoCapturerInterruptionReason_NotAvailableWithMultipleForegroundApps = AVCaptureSessionInterruptionReasonVideoDeviceNotAvailableWithMultipleForegroundApps,
};


@protocol CSVideoCapturerDelegate <NSObject>

- (void) videoCapturerRuntimeError:(NSError *)error;

@optional

- (void) videoCapturerWasInterruptedWithReason:(CSVideoCapturerInterruptionReason)reason;
- (void) videoCapturerWasInterrupted;
- (void) videoCapturerInterruptionEnded;

@end


@interface CSVideoCapturerIOS : NSObject <CSVideoSource>

@property (atomic, strong) id<CSVideoSink> videoSink;
@property (atomic, strong) id<CSVideoSink> localVideoSink;
@property (nonatomic, weak) id<CSVideoCapturerDelegate> delegate;
@property (nonatomic, assign) CSVideoCapturerParams params; // __deprecated_msg("Refer to setVideoCapturePreference:withOrientation:");
@property (nonatomic, assign) BOOL blurBars;

@property (readonly) CSVideoCapturePreference videoCapturePreference;
@property (readonly) CSVideoCaptureOrientation videoCaptureOrientation;

- (void) setVideoCapturePreference:(CSVideoCapturePreference)preference
                   withOrientation:(CSVideoCaptureOrientation)orientation;
                   
- (void) setFrameRate:(int32_t)framesPerSecond;

- (BOOL) hasVideoCameraAtPosition:(CSVideoCameraPosition)position;

- (void) useVideoCameraAtPosition:(CSVideoCameraPosition)position
					   completion:(void (^)(NSError *error))completion;

@end
