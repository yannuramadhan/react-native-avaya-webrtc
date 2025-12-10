/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSServerInfo.h"
#import "CSCredentialProvider.h"
#import "CSAuthenticationMethod.h"

/**
 * Configuration information for ACS.
 */
@interface CSACSConfiguration : NSObject

/**
 * A Boolean value indicating whether the ACS provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * The signaling server to connect with
 */
@property (nonatomic, strong) CSServerInfo *server;

/**
 * The credential provider
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

#ifdef CS_SUPPORTS_MULTIPLE_AUTHENTICATION_METHODS
/**
 * Set priorities of authentication methods to be used for provider.
 */
@property (nonatomic, copy) NSArray *authenticationMethodPreferences;

#endif // CS_SUPPORTS_MULTIPLE_AUTHENTICATION_METHODS

/**
 * The URL of the server to connect with.
 * CSServerInfo will be ignored if this URL is specified.
 */
@property (nonatomic, copy) NSURL *serverURL;

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

@end
