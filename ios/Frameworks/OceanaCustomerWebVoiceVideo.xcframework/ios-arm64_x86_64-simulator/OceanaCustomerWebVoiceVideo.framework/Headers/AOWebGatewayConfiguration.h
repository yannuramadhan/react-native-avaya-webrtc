/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * @file AOWebGatewayConfiguration.h
 * @brief Declares the AOWebGatewayConfiguration class.
 */
@interface AOWebGatewayConfiguration : NSObject

/**
 * The address (FQDN) used to contact the Avaya Aura Web Gateway server.
 */
@property (nonatomic) NSString* webGatewayAddress;

/**
 * The port number used to contact the Avaya Aura Web Gateway server.
 */
@property (nonatomic) NSString* port;

/**
 * If true, connect to the Avaya Aura Web Gateway server using HTTPS. If false, uses HTTP.
 */
@property (nonatomic) BOOL isSecure;

/**
 * Optional.  This allows the Avaya Aura Web Gateway REST url to be customised in the format :
 * http(s)://restFQDN:port/{webGatewayUrlPath}
 * If not set the url defaults to csa/resources/tenants/default.
 */
@property (nonatomic) NSString* webGatewayUrlPath;

@end
