/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSHTTPClientConfiguration.h"
#import "CSMediaTransportPreference.h"
#import "CSMediaAddressMode.h"

/**
 * Configuration information for a HttpSignalingEngine
 */
@interface CSHTTPUserConfiguration : NSObject

/**
 * A Boolean value indicating whether the HTTP provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * List of enabled ciphersuites for SRTP
 */

@property (nonatomic, strong)NSArray* mediaEncryptionCipherList;

/**
 * A Boolean value indicating whether encryption is enabled for SRTCP.
 */
@property (nonatomic) BOOL SRTCPEnabled;

/**
 * Configuration information for HTTP Client data.
 */
@property (nonatomic, strong) CSHTTPClientConfiguration *HTTPClientConfiguration;

/**
 * A Boolean value indicating whether the Media Tunneling is allowed by the configuration.
 * If media tunneling is allowed, Client SDK will try to tunnel audio/video data on ports 443/8443
 * upon failure of audio/video data connections on standard ports.
 */
@property(nonatomic, getter = isMediaTunnelingEnabled) BOOL mediaTunnelingEnabled;

/**
 * A Boolean value indicating whether the Media Tunneling is enforced by the configuration.
 * Should be used only for testing purposes.
 */
@property(nonatomic, getter = isMediaTunnelingEnforced) BOOL mediaTunnelingEnforced;

/**
 * VoIP Calling preference of user.
 */
@property (nonatomic) CSMediaTransportPreference voipCallingPreference;

/**
 * Indicates the IP address type preference to use while transporting media for HTTP calls from a dual stack client network.
 * Currently IPv4 and IPv6 are the valid options supported by Client SDK.
 * IPv4Then6 and IPv6Then4 are internally treated as IPv4 and IPv6 respectively for HTTP calls.
 */
@property (nonatomic) CSMediaAddressMode mediaAddressMode;

@end
