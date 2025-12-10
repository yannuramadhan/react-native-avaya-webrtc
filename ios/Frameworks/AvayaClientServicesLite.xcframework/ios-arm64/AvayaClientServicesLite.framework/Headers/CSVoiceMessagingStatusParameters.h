/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@interface CSVoiceMessagingStatusParameters : NSObject

/**
 * Indicates if there is a new voice mail message pending.
 */
@property (nonatomic, readonly, getter=isMessageWaiting) BOOL messageWaiting;

/**
 * The voicemail account URI for which the voicemail status is indicated
 */
@property (nonatomic, readonly) NSString *messageAccount;


- (instancetype)initWithVoiceMessagingStatus:(BOOL)messageWaiting;

- (instancetype)initWithVoiceMessagingStatus:(BOOL)messageWaiting andMessageAccount:(NSString*)messageAccount;

@end
