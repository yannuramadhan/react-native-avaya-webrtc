/* Copyright Avaya Inc. */

 #import <Foundation/Foundation.h>

/**
 *  Indicates the IP address type preference to use when negotiating media streams when the client connects to dual stack server from a dual
 *  stack client network.
 */
typedef NS_ENUM(NSInteger, CSMediaAddressMode) {
	/**
	 * Only use local IPv4 address during media information exchange.
	 * This option is used in an IPv4 only network environment, where the
	 * local client has an IPv4 network address.
	 * Setting this mode in an IPv6  only environment is a configuration
	 * error, however the call is allowed to proceed with an IPv6 media
	 * address.
	 */
	CSMediaAddressModeIPv4 = 0,
	/**
	 * Only use local IPv6 address during media information exchange.
	 * This option is used in an IPv6 only network environment, where the
	 * local client has an IPv6 network addresses.
	 * Setting this mode in an IPv4 only environment is a configuration
	 * error, however the call is allowed to proceed with an IPv4 media
	 * address.
	 */
	CSMediaAddressModeIPv6,
	/**
	 * Prefer local IPv4 address over local IPv6 address when both
	 * are available to the local endpoint.
	 * This option is used in a dual IPv4 and IPv6 network environment, where the
	 * local client has both IPv4 and IPv6 address.
	 * Both IPv4 and IPv6 local addresses are provided during media
	 * exchange, and the IPv4 local address is preferred over the IPv6 address.
	 */
	CSMediaAddressModeIPv4Then6,
	/**
	 * Prefer local IPv6 address over local IPv4 address when both
	 * are available to the local endpoint.
	 * This option is used in a dual IPv4 and IPv6 network environment, where the
	 * local client has both IPv4 and IPv6 addresses.
	 * Both IPv4 and IPv6 local addresses are provided during media
	 * exchange, and the IPv6 local address is preferred over the IPv4 address.
	 */
	CSMediaAddressModeIPv6Then4
};
