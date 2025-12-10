/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@class CSVisualVoiceMailMessage;

/**
 * Type of block used to report status of background task.
 */

typedef void (^CSVisualVoiceMailCompletionHandler)(NSError *error);
typedef void (^CSVisualVoiceMailMessageCompletionHandler)(CSVisualVoiceMailMessage *message, NSError *error);
