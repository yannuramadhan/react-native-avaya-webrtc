//
//  CustomLog.h
//  OceanaCustomerWebVoiceVideo
//
//  Created by Mohan on 17/01/20.
//  Copyright © 2020 Avaya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AvayaClientServicesLite/CSClient.h>
NS_ASSUME_NONNULL_BEGIN


@protocol CustomLogDelegate <NSObject>

/**
* Sent when the CustomLog Logs a message
*
*/

- (void)didAddLogToFile :(CSLogLevel)level withTag:(NSString * _Nullable)tag message:(NSString * _Nonnull)message ;

@end

@interface CustomLog : NSObject
+ (instancetype)sharedInstance;
@property (nonatomic, weak) id<CustomLogDelegate> customLogDelegate;
-(void) addLogToFile :(CSLogLevel)level withTag:(NSString * _Nullable)tag message:(NSString * _Nonnull)message ;
@end

NS_ASSUME_NONNULL_END
