/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSServerInfo.h"
#import "CSCredentialProvider.h"

/**
 * Configuration information for IP Office.
 */
@interface CSIPOfficeConfiguration : NSObject

/**
 * A Boolean value indicating whether the IP Office provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * A Boolean value indicating whether to enable One-X Portal messaging service for IP Office 
 *
 */
@property (nonatomic, getter=isMessagingEnabled) BOOL messagingEnabled;

/**
 * A Boolean value indicating whether the IP Office contacts provider is enabled.
 *
 */
@property (nonatomic) BOOL contactsEnabled;

/**
 * A Boolean value indicating whether the IP Office presence provider is enabled.
 *
 */
@property (nonatomic) BOOL presenceEnabled;

/**
 * A Boolean value indicating whether the IP Office Centralized Call Log is enabled.
 */
@property (nonatomic) BOOL callLogEnabled;

/**
 * A Boolean value indicating whether the IP Office Conference controls are enabled.
 */
@property (nonatomic) BOOL conferenceControlsEnabled;

/**
 * A Boolean value indicating whether the IP Office call recording is enabled.
 */
@property (nonatomic) BOOL callRecordingEnabled;

/**
 * A Boolean value indicating whether the IP Office call handover is enabled.
 */
@property (nonatomic) BOOL callHandoverEnabled;

/**
 * The signaling server to connect with
 */
@property (nonatomic, strong) CSServerInfo *server;

/**
 * The credential provider
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

/**
 * Messaging credential provider. The messaging service and server are not coupled to SIP service.
 */
@property (nonatomic, weak) id <CSCredentialProvider> messagingCredentialProvider;

/**
 * The URL of the primary messaging server
 */
@property (nonatomic, copy) NSURL *primaryMessagingServerUrl;

/**
 * The URL of the secondary messaging server
 */
@property (nonatomic, copy) NSURL *secondaryMessagingServerUrl;

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

#if TARGET_OS_IPHONE
/**
 * A Boolean value indicating whether Push Notifications are enabled.
 */
@property (nonatomic, getter=isMessagingPushNotificationEnabled) BOOL messagingPushNotificationEnabled;

/**
 * A unique app-device token assigned by Apple to an
 * application instance running in a specific iOS device.
 * This is used by the OneXPortal server when
 * sending messaging events towards the push notification client.
*/
@property (nonatomic, copy) NSData *messagingRemoteNotificationDeviceToken;

/**
 * A Boolean value indicating whether incoming push notification events should
 * be sent through Apple's development push notification network
 * (api.development.push.apple.com) or the production push notification network
 * (api.push.apple.com). The Boolean flag is set to YES  if the application is built
 * using a development provisioning profile. By default, the property is
 * set to NO, and Apple's production network is used to route push notification
 * messages.
 */
@property (nonatomic, getter=isUseDevelopmentPushNotificationNetwork) BOOL useDevelopmentPushNotificationNetwork;

#endif //TARGET_OS_IPHONE

/**
 * A Boolean value indicating whether the IP Office MonApps service is enabled.
 * MonApps are miscellaneous PBX features which are not call features but are still useful for a user
 * application to be able to monitor. Current support is for the monitoring of button MonApp only.
 */
@property (nonatomic, getter=isMonAppsEnabled) BOOL monAppsEnabled;

#if TARGET_OS_OSX
/**
 * A Boolean value indicating whether the IP Office other phone mode is enabled.
 */
@property (nonatomic, getter=IsOtherPhoneModeEnabled) BOOL otherPhoneModeEnabled;

#endif //TARGET_OS_OSX

@end
