//
//  AOCallQualityNotification.h
//  OceanaCustomerWebVoiceVideo
//
//  Created by Gslab Pune on 21/01/21.
//  Copyright © 2021 Avaya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AOCallQuality.h"
#import "AOCallQualityNotificationEvent.h"

@interface AOCallQualityNotification : NSObject
@property (nonatomic, assign) AOCallQualityNotificationEvent notificationEvent;
@property (nonatomic, assign) AOCallQuality qualityValue;
-(AOCallQualityNotification *)initCallQualityNotification:(AOCallQualityNotificationEvent)event quality:(AOCallQuality)quality;
-(AOCallQualityNotificationEvent)getEvent;
-(AOCallQuality)getQuality;
@end

