/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * @file AOConfiguration.h.
 * @brief Declares the AOConfiguration class.
 */
@interface AOConfiguration : NSObject

/**
 * The FQDN used to contact the Breeze cluster hosting AvayaMobileCommunications.
 */
@property (nonatomic) NSString* restUrl;

/**
 * The port number used to contact Breeze cluster hosting AvayaMobileCommunications.
 */
@property (nonatomic) NSString* port;

/**
 * If true, connect to the AvayaMobileCommunications Breeze cluster using HTTPS. If false, uses HTTP.
 */
@property (nonatomic) BOOL isSecure;

/**
 * Optional.  This allows the AvayaMobileCommunications REST url to be customised in the format :
 * http(s)://restUrl:port/{urlPath}
 * If not set the url defaults to http(s)://restFQDN:port/services/AvayaMobileCommunications/sessions.
 */
@property (nonatomic) NSString* urlPath;

@end
