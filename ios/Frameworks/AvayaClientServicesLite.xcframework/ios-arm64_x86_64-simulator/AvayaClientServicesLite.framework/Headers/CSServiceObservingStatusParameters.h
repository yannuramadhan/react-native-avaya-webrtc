/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSServiceObservingType.h"
#import "CSServiceObservingMode.h"
#import "CSButtonLampState.h"

/**
 * This class represents the details about the service observing status parameters.
 * @see CSCallFeatureService::serviceObservingStatusParameters
 */
@interface CSServiceObservingStatusParameters : NSObject

/**
 * Represents the information about the extension of the endpoint used by the observer.
 */
@property (nonatomic, readonly) NSString *nativeExtension;

/**
 * Represents the information about the extension being observed.
 */
@property (nonatomic, readonly) NSString *serviceObservingExtension;

/**
 * Represents service observing type.
 * ( Basic | No-Talk | Next-Cal | By-Location )
 */
@property (nonatomic, readonly) CSServiceObservingType serviceObservingType;

/**
 * Indicates whether the observer will join the call in "listen-only" or "listen-talk" mode
 * in "listen-only" or "listen-talk" mode.
 */
@property (nonatomic, readonly) CSServiceObservingMode serviceObservingMode;

/**
 * When there is no error response code present, this field
 * provides a text string that the endpoint renders on the
 * display when responding to a feature operation. i.e.
 * "VDN xxx-xxxx SO" indicates that VDN (vector directory number)
 * xxx-xxxx is being service observed.
 */
@property (nonatomic, readonly) NSString *displayText;

/**
 * The location number associated with the observed VDN.
 */
@property (nonatomic, readonly) NSInteger serviceObservingLocation;

/**
 * Indicates whether coaching option for service observing is enabled
 *
 * @return True if coaching option available. False otherwise.
 */
 @property (nonatomic, readonly, getter=IsCoachingOptionEnabled) BOOL coachingOptionEnabled;

/**
 * Indicates whether listen only option for service observing is enabled
 *
 * @return True if ListenOnly option available. False otherwise.
 */
 @property (nonatomic, readonly, getter=IsListenOnlyOptionEnabled) BOOL listenOnlyOptionEnabled;

@end

