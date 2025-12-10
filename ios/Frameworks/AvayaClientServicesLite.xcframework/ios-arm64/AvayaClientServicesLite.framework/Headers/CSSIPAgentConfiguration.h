/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSCredentialProvider.h"

/**
 * Configuration information for SIP Agent Feature provider.
 */
@interface CSSIPAgentConfiguration : NSObject

/**
 * A Boolean value indicating whether the SIP Agent Feature provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * The credential provider
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

@end
