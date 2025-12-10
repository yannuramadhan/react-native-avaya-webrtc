/* Copyright Avaya Inc. */

#import "AOWork.h"
#import "AOClientConfiguration.h"

/**
 * @file AOOceanaCustomerWebVoiceVideo.h
 * @brief Declares the AOOceanaCustomerWebVoiceVideo class.
 */
@interface AOOceanaCustomerWebVoiceVideo : NSObject

/**
 * Initializes the OceanaCustomerWebVoiceVideo SDK
 *
 * @param clientConfiguration The AOClientConfiguration to initialize the SDK.
 */
-(instancetype)initWithClientConfiguration:(AOClientConfiguration*)clientConfiguration;
-(instancetype)initWithIsSecure:(BOOL)isSecure andPort:(NSString*)port andRestFQDN:(NSString*)restFQDN;

/**
 * Returns the OceanaCustomerWebVoiceVideo SDK version number.
 */
@property (nonatomic, readonly) NSString* versionNumber;

/**
 * Create a Work instance, used to create interactions.
 */
@property (nonatomic, readonly) AOWork* createWork;

@end
