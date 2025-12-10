/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * User configuration information for the messaging service.
 * This class provides configuration and preference data for the messaging service features.
 */
@interface CSMessagingConfiguration : NSObject

/**
 * The initial time interval between a connection failure and a reconnect attempt.
 *
 * If connection attempts continue to fail the reconnect interval will be progressively extended
 * using a backoff algorithm based on this initial reconnect interval.  The default is 2 seconds.
 *
 * Set to zero to disable automatic reconnection attempts.
 * Values < 0 or > 65535 are ignored.
 */
@property (nonatomic) NSTimeInterval initialReconnectInterval;

/**
 * The maximum time interval between a connection failure and a reconnect attempt.
 * The default is 1800 seconds.
 * Values < 0 or > 65535 are ignored.
 */
@property (nonatomic) NSTimeInterval maxReconnectInterval;

/**
 * A Boolean value indicating whether message delivery and read updates should be tracked or not.
 * By default, delivery/read states are not monitored.
 */
@property (nonatomic, getter=isMessageDeliveryReadStateMonitoringEnabled) BOOL messageDeliveryReadStateMonitoringEnabled;

/**
 * A Boolean value indicating whether the application wants to report
 * 'message read' indication to other conversation participants, i.e. let 
 * other conversation participants know when I mark a message as read.
 * By default, message read reports are enabled.
 */
@property (nonatomic, getter=isMessageReadReportingEnabled) BOOL messageReadReportingEnabled;


@end
