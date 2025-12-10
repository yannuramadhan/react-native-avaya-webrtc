/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Enumeration representing visual voice mail message statuses.
 */
typedef NS_ENUM(NSUInteger, CSVisualVoiceMailMessageStatus) {
	CSVisualVoiceMailMessageStatusReadyToDownload,
	CSVisualVoiceMailMessageStatusDownloading,
	CSVisualVoiceMailMessageStatusReadyToConsume,
	CSVisualVoiceMailMessageStatusConsumed,
};
