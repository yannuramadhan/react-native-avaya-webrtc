//
/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSServerInfo.h"
#import "CSCredentialProvider.h"

/**
 * The Personal Profile Manager configuration class that contains the configuration data specific for this User.
 * In some deployments, the PPM server address may be different from the initial SIP proxy server address.
 */
@interface CSPPMConfiguration : NSObject

/**
 * A Boolean value indicating whether the PPM provider is enabled.
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * A Boolean value indicating whether PPM contacts are enabled.
 */
@property (nonatomic) BOOL contactsEnabled;

/**
 * A Boolean value indicating whether 24x7 Call Journaling are enabled.
 */
@property (nonatomic) BOOL callJournalingEnabled;

/**
 * The PPM server to connect with
 */
@property (nonatomic, strong) CSServerInfo *server;

/**
 * The credential provider
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

/**
 * A Boolean value indicating whether functionality of PPM (Personal Profile manager) persistent data is enabled.
 * When this setting is enabled, PPM (Personal Profile manager) data is not re-queried after network recovery,
 * when the client wakes up after being in sleep mode (specific for MAC client),
 * when client fails over to secondary when primary server goes down and vice versa,
 * when client goes in background and comes to foreground when user selects the or phone is locked and unlocked(specific for iOS client).
 * Existing PPM cached data will be used. Client needs to logout/login or restart to get updated data.
 * The PPM cached data consists of UC and Agent features, button locations and button customization.
 * This feature is useful to reduce network traffic in large scale environments.
 */
@property (nonatomic) BOOL ppmPersistentDataEnabled;

/**
 * How long to wait for a server response on PPM Configuration Request (in milliseconds)
 * The default value is 10000.
 * Affected PPM Requests:
 *  CPPMGetAllEndpointConfigurationCommand,
 *  CPPMGetHomeCapabilitiesCommand,
 *  CPPMGetDeviceDataCommand
 */
@property (nonatomic) NSUInteger ppmConfigRequestTimeout;


@end
