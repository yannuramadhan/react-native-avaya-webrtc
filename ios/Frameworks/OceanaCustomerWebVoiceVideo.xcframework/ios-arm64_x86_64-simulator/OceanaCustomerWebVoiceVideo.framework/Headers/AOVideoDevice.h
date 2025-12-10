/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 * @file AOVideoDevice.h
 * @brief Defines the AOVideoDevice class.
 */

/**
 * List of available cameras on a mobile device.
 */
typedef NS_ENUM(NSInteger, AOCameraType) {
    AOCameraTypeFront,
    AOCameraTypeBack
};

/**
 * Video resolutions.
 */
typedef NS_ENUM(NSUInteger, AOVideoResolution) { //Depricated
    AOVideoResolution_176x144 = 0,
    AOVideoResolution_320x180, // 180p
    AOVideoResolution_352x288,
    AOVideoResolution_480x272,
    AOVideoResolution_640x360, // 360p
    AOVideoResolution_640x480,
    AOVideoResolution_848x480,
    AOVideoResolution_960x540,
    AOVideoResolution_1280x720,
    AOVideoResolution_1920x1080
};

// Requested Capture Resolutions
//    Max - highest capture resolution supported by device
//    Min - lowest capture resolution supported by device
//    Specific resolution - upper bound for capture resolution. Maybe limited by hardware support

typedef NS_ENUM(NSUInteger, AOVideoCapturePreference) {
    AOVideoCapturePreference_Max = 0,
    AOVideoCapturePreference_1080p,
    AOVideoCapturePreference_720p,
    AOVideoCapturePreference_540p,
    AOVideoCapturePreference_360p,
    AOVideoCapturePreference_270p,
    AOVideoCapturePreference_Min
};

// Requested Capture Orientations

typedef NS_ENUM(NSInteger, AOVideoCaptureOrientation)
{
    AOVideoCaptureOrientation_LandscapeOnly = 0,
    AOVideoCaptureOrientation_LandscapeOrPortrait
};

@interface AOVideoDevice : NSObject

/**
 * Select which camera type to be used for the video interaction.
 */
- (void) selectCamera: (AOCameraType) cameraType;

/**
 * Switch from the front to the rear camera or vice-versa.
 */
-(void) switchCamera;

/**
 * Set the camera capture resolution for the interaction.
 */
-(void) setCameraCaptureResolution: (AOVideoResolution) resolution; // __deprecated_msg("Refer to setVideoCaptureResolutionWithCaptureOrientation:orientationPreference:");

/**
 * Returns a list of Video Resolutions that are supported by the device.
 */
+(NSMutableArray*) getSupportedCameraCaptureResolutions; //Depricated

/**
 * Get current camera capture resolution.
 */
- (AOVideoResolution)getCameraCaptureResolution; //Depricated

/**
 * Set the VideoSurface to be used to render the remote video stream.
 */
-(void) setRemoteView:(UIView*) remote;

/**
 * Set the VideoSurface to be used to render the local video stream.
 */
-(void) setLocalView:(UIView*) local;

/**
* Returns a list of Video Resolutions that are supported by the device.
*/
+(NSMutableArray*) getSupportedCameraCaptureResolutionPrefes;

/**
* Set the camera capture resolution with Orientation.
*/
- (void) setVideoCaptureResolutionWithCaptureOrientation : (AOVideoCapturePreference) resolutionPreference  orientationPreference : (AOVideoCaptureOrientation) orientationPreference;

/**
* Get the camera capture resolution.
*/

-(AOVideoCapturePreference) getVideoCapturePreference;

/**
* Get the camera capture Orientation.
*/

- (AOVideoCaptureOrientation) getVideoCaptureOrientation;

@end
