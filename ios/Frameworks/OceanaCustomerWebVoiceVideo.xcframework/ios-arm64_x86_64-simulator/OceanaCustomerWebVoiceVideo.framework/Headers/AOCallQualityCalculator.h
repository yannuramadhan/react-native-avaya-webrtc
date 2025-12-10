//
//  AOCallQualityCalculator.h
//  OceanaCustomerWebVoiceVideo
//
//  Created by Gslab Pune on 20/01/21.
//  Copyright © 2021 Avaya. All rights reserved.
//
#import "AOCallQuality.h"
#import "AOAudioDetails.h"
#import "AOVideoDetails.h"

@interface AOCallQualityCalculator : NSObject
@property (nonatomic, assign) NSInteger QUALITY_MONITOR_INTERVAL_MILISECONDS; //This is directly in seconds;
@property (nonatomic, assign) NSInteger previousMOS;

+(AOCallQuality)getMOSFromTheVideoCallStats:(AOVideoDetails *)videoDetails
                              audioDetails:(AOAudioDetails *)audioDetails;

+(AOCallQuality)getMOSFromTheAudioCallStats:(AOAudioDetails *)audioDetails;

+(AOCallQuality)calculateMos:(NSUInteger)roundTripTimeMillis
averageJitterReceivedMillis:(NSUInteger)averageJitterReceivedMillis
averageJitterTransmittedMillis:(NSUInteger)averageJitterTransmittedMillis
      currentPacketLossRate:(NSUInteger)currentPacketLossRate;

+ (AOCallQuality)convertToCallQuality:(double)mos;
@end
