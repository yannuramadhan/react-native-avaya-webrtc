/* Copyright Avaya Inc. */

 #import <Foundation/Foundation.h>

/**
 * Enumeration that describes call denial policy.
 */
typedef NS_ENUM(NSInteger, CSCallDenialPolicy) {
	/**
	 * If the call denial policy is disabled then the call denial capability will not be allowed.
	 */
	CSCallDenialPolicyDisabled = 0,
	/**
	 * If the user denies an incoming call without specifying a reason
	 * then the call will be denied with reason as busy in response.
	 */
	CSCallDenialPolicyBusy,
	/**
	 * If the user denies an incoming call without specifying a reason
	 * then the call will be denied with reason as decline in response.
	 */
	CSCallDenialPolicyDecline
};
