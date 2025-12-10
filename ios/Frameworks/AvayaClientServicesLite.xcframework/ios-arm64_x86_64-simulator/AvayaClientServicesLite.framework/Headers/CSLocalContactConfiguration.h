/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * For iOS there is no need to have the configuration information. So just enable this service by default.
 */
@interface CSLocalContactConfiguration : NSObject

/**
 * A Boolean value indicating whether the Local device provider is enabled.
 *
 */
@property (nonatomic) BOOL enabled;

/**
 * The minimum number of digits to be used for local contact matching. The default value is 10.
 * If the number of digits in the received phone number is less than or equal to the configured value,
 * then only a contact with a phone number that exactly matches the received phone number will be matched.
 * Otherwise, contact matching will be based on the right-most 'N' digits of contact's phone number where 'N' is the configured value.
 */
@property (nonatomic, readwrite) NSUInteger contactMatchingMinDigits;

@end
