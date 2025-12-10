/* Copyright Avaya Inc. */

/**
 * @file AOService.h
 * @brief Defines the AOService class.
 */

@interface AOService : NSObject

/**
 * Set the Service attributes.
 */
@property (nonatomic) NSMutableDictionary* attributes;

/**
 * Set the Service priority.
 */
@property (nonatomic) NSString* priority;

/**
 * Set the Service rank.
 */
@property (nonatomic) NSString* rank;

/**
 * Set the Service resource count.
 */
@property (nonatomic) NSString* resourceCount;

/**
 * Set the Service min proficiency.
 */
@property (nonatomic) NSString* minProficiency;

/**
 * Set the Service max proficiency.
 */
@property (nonatomic) NSString* maxProficiency;

@end
