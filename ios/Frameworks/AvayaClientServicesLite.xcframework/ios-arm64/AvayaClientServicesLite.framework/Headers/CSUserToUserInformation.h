/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * User-to-User Information (UUI), known as call control UUI data, is
 * a small piece of data inserted by an application initiating the call
 * and utilized by the application receiving the call.
 * The syntax and semantics for the UUI data used by a specific application
 * are defined by a UUI package.
 */
@interface CSUserToUserInformation : NSObject

/**
 * Represents a unique  identifier for every call in a call center customer
 * environment for unifrom data-tracking for all call-related data in a call center,
 * regardless of the system.
 */
@property (nonatomic, readonly) NSString* ucid;

/**
 * Represents Adjunct Switch Applications Interface (ASAI) User Data.
 * ASAI UUI information is required to provide screen-pop type functionality
 * by using the UUI to perform data base searches.
 */
@property (nonatomic, readonly) NSString* asai;

/**
 * Represents VDN call duration.
 */
@property (nonatomic, readonly) NSString* inVdnTime;

/**
 * Represents a Vector Directory Number name.
 * Agent needs to know from which VDN call is arrived in order to be prepared.
 * For example, the agent may servicing incoming calls about sales and
 * technical support questions that are represented by two separate VDNs.
 * When the incoming call is presented to the agent, the agent will better be prepared to talk
 * about a particular topic based on the VDN information associated with the call.
 */
@property (nonatomic, readonly) NSString *vdnName;

/**
 * Represents full UUI if it is not encoded according to Avaya specs for UUI transport.
 * Otherwise it is empty.
 * @see isParsedSuccessfully
 */
@property (nonatomic, readonly) NSString* fullUserToUserInformation;
/**
 * Represents the caller entered information during IVR phase of the call.
 */
@property (nonatomic, readonly) NSString* collectedDigits;

/**
 * Indiciates whether the UUI is parsed successfully according to Avaya specs for UUI transport.
 */
@property (nonatomic, readonly, getter=isParsedSuccessfully) BOOL parsedSuccessfully;

@end
