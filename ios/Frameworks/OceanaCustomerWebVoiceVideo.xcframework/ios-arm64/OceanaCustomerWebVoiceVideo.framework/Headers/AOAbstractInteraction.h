//
//  AOAbstractInteraction.h
//  OceanaCustomerWebVoiceVideo
//
//  Created by Gslab Pune on 21/01/21.
//  Copyright © 2021 Avaya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AOCallQuality.h"
#import "AOAudioDetails.h"
#import "AOCallQualityNotification.h"

NS_ASSUME_NONNULL_BEGIN

@interface AOAbstractInteraction : NSObject
{
    NSDate* poorQualityStartTime;
    NSInteger previousMOSValue;
//    BOOL disableVideoInLowBandwidth;
//    AOCallQuality qualityThreshold;
//    NSInteger maxPoorQualityTimeAllowedMillis;
//    BOOL bVideoDisabledEventSent;
    NSTimer* timerCallQuality;
}
- (id)init;
//- (void)resetCallQualityParams;
- (void)startCallQualityTimer;
- (void)stopCallQualityTimer;
- (void)readAudioDetailsWithCompletionHandler:(void (^)(AOAudioDetails *audioDetails))handler;
- (void)sendCallQualityEvent:(AOCallQualityNotification*) notification;
@end

NS_ASSUME_NONNULL_END
