/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "AOConfiguration.h"
#import "AOWebGatewayConfiguration.h"

/**
 * @file AOClientConfiguration.h.
 * @brief @brief Declares the AOClientConfiguration class.
 */
@interface AOClientConfiguration : NSObject

/**
 * A configuration object, indicating the Oceana server to communicate with.
 */
@property (nonatomic) AOConfiguration* configuration;

/**
 * A configuration object, indicating the signalling gateway to communicate with.
 */
@property (nonatomic) AOWebGatewayConfiguration* webGatewayConfiguration;

@end
