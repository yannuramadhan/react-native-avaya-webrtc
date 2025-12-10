/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCallDenialPolicy.h"
#import "CSConnectionPolicy.h"
#import "CSCredentialProvider.h"
#import "CSSIPAgentConfiguration.h"
#import "CSSIPClientConfiguration.h"
#import "CSMediaTransportPreference.h"
#import "CSMediaAddressMode.h"
#import "CSOutboundSubscriptionConfiguration.h"

/**
 * The mobility mode for a user.
 */
typedef NS_ENUM(uint32_t, CSSIPMobilityMode) {
	/**
	 * No mobility information is available.
	 */
	CSSIPMobilityModeUnspecified = 0,

	/**
	 * The user is at a fixed location.
	 */
	CSSIPMobilityModeFixed,

	/**
	 * The user is on a mobile device.
	 */
	CSSIPMobilityModeMobile
};

/**
 *  Indicates the SIP session manager address type preference when the client connects to dual stack server from a dual stack client network.
 */
typedef NS_ENUM(NSInteger, CSSignalingAddressMode) {
	/**
	 * Prefer IPv4 SM address
	 */
	CSSignalingAddressModeIPv4 = 0,

	/**
	 * Prefer IPv6 SM address
	 */
	CSSignalingAddressModeIPv6
};

/**
 * Configuration information for a @c CSSIPSignalingEngine.
 */
@interface CSSIPUserConfiguration : NSObject

/**
 * A Boolean value indicating whether the SIP provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * The connection policy defining the signaling servers to communicate with.
 */
@property (nonatomic, strong) CSConnectionPolicy *connectionPolicy;

/**
 * The user ID.
 */
@property (nonatomic, copy) NSString *userId;

/**
 * The SIP domain for the user.
 */
@property (nonatomic, copy) NSString *domain;

/**
 * The credential provider to be used for SIP authentication.
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

/**
 * The display name used to identify the endpoint the user is on.
 *
 * In SIP this is inserted in the display name portion of SIP Contact header. For example, the display name
 * may be set to "Alice's Flare on iPad". This label is used to identify an endpoint from a list of endpoints
 * that can be registered on behalf of the user (e.g., when SM's parallel forking group feature is enabled).
 */
@property (nonatomic, copy) NSString *displayName;

/**
 * The language string to use in Accept-Language header.
 */
@property (nonatomic, copy) NSString *language;

/**
 * The mobility mode for the user.
 */
@property (nonatomic) CSSIPMobilityMode mobilityMode;

/**
 * The alternate network type for a dual-mode client.
 *
 * Generally set to "mobile" for dual-mode clients.
 */
@property (nonatomic, copy) NSString *alternateNetwork;

/**
 * The address-of-record for the user in the alternate network.
 *
 * For a dual-mode client, this specifies the user's cell number.
 */
@property (nonatomic, copy) NSString *alternateAddressOfRecord;

/**
 * List of enabled ciphersuites for SRTP
 */

@property (nonatomic, strong)NSArray* mediaEncryptionCipherList;

/**
 * A Boolean value indicating whether encryption is enabled for SRTCP.
 */
@property (nonatomic) BOOL SRTCPEnabled;

/**
 * Controls whether the SIP endpoint uses sips (secure SIP) URI scheme for all SIP requests it initiates towards the network,
 * including secure media calls.
 *
 * If enabled, SIP endpoint registers a SIPS Contact address with the SIP registrar, and uses SRTP
 * crypto suites as controlled by {@link #mediaEncryptionCipherList}.
 *
 * If disabled, SIP endpoint registers a SIP Contact address with the SIP registrar, and uses SRTP
 * crypto suites as controlled by {@link #mediaEncryptionCipherList}.
 *
 */
@property (nonatomic) BOOL useSIPSURIOverTLS;

/**
 * Controls whether the local MAC address information is provided in the "+av.mac-address" field
 * of the SIP registration contact address or not. By default, this property is set to false, 
 * indicating that no local MAC address information is provided in the SIP registration message.
 * When this property is set to true and the local operating system allows reading of the MAC address 
 * based on the local IP address used for connection to the SIP server, then the local MAC address 
 * is provided in the "+av.mac-address" field. 
 * The MAC address provided in the "+av.mac-address" field is used by Avaya development partners
 * to determine the location of the machine for E.911 calling.
 */
@property (nonatomic) BOOL MACAddressInfoInSIPRegistrationEnabled;

/**
 * Configuration information for SIP Client data.
 */
@property (nonatomic, strong) CSSIPClientConfiguration *SIPClientConfiguration;

/**
 * Configuration information for SIP Agent Feature service.
 */
@property (nonatomic, strong) CSSIPAgentConfiguration *SIPAgentConfiguration;

/**
 * Configuration information for Outbound Subscription data.
 */
@property (nonatomic, strong) CSOutboundSubscriptionConfiguration *outboundSubscriptionConfiguration;

/**
 * VoIP Calling preference of user.
 */
@property (nonatomic) CSMediaTransportPreference voipCallingPreference;

/**
 * Indicates the SIP session manager address type preference when the client connects to dual stack server from a dual stack client network
 */
@property (nonatomic) CSSignalingAddressMode signalingAddressMode;

/**
 * Indicates the IP address type preference to use when negotiating media streams when the client connects to dual stack server from a dual
 * stack client network.
 */
@property (nonatomic) CSMediaAddressMode mediaAddressMode;

/**
 * A Boolean value indicating if transfer to voicemail feature is enabled.
 */
@property (nonatomic, getter=isTransferToVoicemailEnabled) BOOL transferToVoicemailEnabled;

/**
 * A Boolean value indicating that the user doesn't wish to receive incoming calls through VoIP service.
 */
@property (nonatomic, getter=isIncomingVoipCallsBarred) BOOL incomingVoipCallsBarred;

/**
 * It accelerates dialing by eliminating the need to wait for
 * the INTER_DIGIT_TIMEOUT timer to expire.
 * The value can contain 0 to 1023 characters; the default value is null ("").
 * See the telephone Administrator's Guide for format and setting alternatives.
 * example: "[23]xxxx|91xxxxxxxxxx|9[2-9]xxxxxxxxx"
 */
@property (nonatomic, copy) NSString *dialPlan;

/**
 * The emergency phone numbers
 *
 * Used in the Non-Aura environment.
 * In a Aura environment, the identification of emergency numbers occurs automatically.
 */
@property (nonatomic, strong) NSSet *emergencyNumbers;

#if !TARGET_OS_IPHONE
/**
* Controls whether the SIP endpoint registers in desk phone mode on startup.
*
* If set to true, SIP endpoint registers with the lowest q-value i.e. 0.
* If set to false, SIP endpoint registers with the highest q-value i.e. 1.
* By default, the property is set to false.
*
* @note If this property is set to true then it is expected that application should call
* {@link CSSharedControlService::activateSharedControlWithControllableEndpoint:completionHandler: activateSharedControlWithControllableEndpoint:completionHandler} method
* after registration is successful and controllable endpoints are available.
*
*/
@property (nonatomic) BOOL enableDeskphoneModeOnStartup;

/**
 * Controls whether the SIP endpoint sends Alternate-CLI header in other phone mode to other phone number. By default, this property is false.
 * If enabled, the SIP endpoint sets the Alternate-CLI header to the remote caller information and sends Alternate-CLI header to other phone number.
 * If disabled, the SIP endpoint  doesn't send Alternate-CLI header to other phone number.
 */
@property (nonatomic) BOOL enableAlternateCLI;

/**
 * When Send All Calls feature is enabled, there continues to be an incoming call notification that arrives at the client application, 
 * and will be forwarded to the Telecommuter device and cancelled when the Aura coverage timer fires. 
 * To avoid the unnecessary signalling, the property may be set to disable.
 */
@property (nonatomic) BOOL initiateTCCallWhenForwardingEnabled;

#endif

/**
 * Specifies the call denial policy.
 * If a user denies a call using {@link CSCall::denyWithCompletionHandler:} method then
 * the denial reason will be determined based on CallDenialPolicy policy.
 * By default, the property is set to Busy.
 */
@property (nonatomic) CSCallDenialPolicy callDenialPolicy;

/**
 * The maximum number of servers a user can simultaneously register to.
 *
 * The recommended range is from 1 to 5.
 * If the property is not set, Client SDK will continue to simultaneously register to a maximum of three servers, as provided by PPM.
 */
@property (nonatomic) NSUInteger maxSimultaneousRegistrations;

/**
 * Time period for waiting for completion of initial INVITE transaction with other phone call leg.
 * If no early or final media response is received from remote party within this time period,
 * then the other phone call leg transaction will be completed with a dummy media response.
 * Dummy media will be updated to real remote media info upon media response from remote party.
 *
 * Valid values are within 0 to 30 seconds range. Default value is 30.
 * If set to 0, it means there is no wait for completion of the initial INVITE transaction with the telecommuter call leg.
 * If set to more than 30 or less than 0, this variable will be set to the default value of 30.
 */
@property (nonatomic) NSUInteger otherPhoneModeRemoteMediaResponseTimeout;

/**
 * Controls whether the Client SDK shall automatically invoke line reservation feature prior to placing an outgoing call.
 * The default value is false, which means automatic line reservation is disabled.
 */
@property (nonatomic) BOOL automaticLineReservationEnabled;

@end
