//
/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSServerInfo.h"
#import "CSCredentialProvider.h"

/**
 * Configuration information for Avaya Messaging provider.
 */
@interface CSAvayaMessagingConfiguration : NSObject

/**
 * A Boolean value indicating whether Avaya Messaging provider is enabled.
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * Avaya Messaging server to connect to.
 */
@property (nonatomic, strong) CSServerInfo *server;

/**
 * The credential provider
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

@end
