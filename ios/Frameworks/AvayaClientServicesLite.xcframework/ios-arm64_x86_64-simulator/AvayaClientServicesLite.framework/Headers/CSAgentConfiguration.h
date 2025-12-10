/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * User configuration information for the Agent service.
 * This class provides configuration and preference data for the Agent service features.
 */
@interface CSAgentConfiguration : NSObject

/**
 * The the flag indicating whether the agent should be automatically logged in upon Agent service start.
 * The AutoLogin preference is set to false by default.
 */
@property (nonatomic, getter=isAutoLoginOnStart) BOOL autoLoginOnStart;

/**
 * The the flag indicating whether the agent should be automatically logged out as part of graceful service shutdown.
 * The AutoLogout preference is set to true by default.
 */
@property (nonatomic, getter=isAutoLogoutOnStop) BOOL autoLogoutOnStop;

/**
 * The logout reason code for automatic agent logout.
 * The reason code is set to 0 by default.
 */
@property (nonatomic) NSInteger autoLogoutReasonCode;

@end
