/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSMessagingLimits.h"
#import "CSCapability.h"
#import "CSVisualVoiceMailMessageEnums.h"
#import "CSVisualVoiceMailCompletionHandler.h"
#import "CSCancellableDataRetrieval.h"

@protocol CSVisualVoiceMailMessageDelegate;

/**
 * Interface for all Visual Voicemail Message related tasks and properties.
 */
@interface CSVisualVoiceMailMessage : NSObject

/**
 * The delegate responsible for handling message-related events.
 */
@property (nonatomic, weak) id<CSVisualVoiceMailMessageDelegate> delegate;


/**
 * The identity of the party that left the voice message.
 */
@property (nonatomic, readonly) NSString *callerAddress;

/**
 * The name of the party that left the voice message.
 */
@property (nonatomic, readonly) NSString *callerName;

/**
 * The subject of the voice message.
 */
@property (nonatomic, readonly) NSString *subject;

/**
 * The received date/time of the voice message.
 */
@property (nonatomic, readonly) NSDate *receivedDate;

/**
 * The flag indicating whether or not the message is read.
 */
@property (nonatomic, readonly) BOOL isRead;

/**
 * The size of attached audio voicemail file.
 */
@property (nonatomic, readonly) UInt64 size;

/**
 * The duration of attached audio voicemail file.
 */
@property (nonatomic, readonly) NSUInteger duration;

/**
 * The location of attached audio voicemail file.
 */
@property (nonatomic, readonly) NSString *location;

/**
 * The status of attached audio voicemail file.
 */
@property (nonatomic, readonly) CSVisualVoiceMailMessageStatus audioFileStatus;

/**
 * Capabilities
 */

/**
 * A ::CSCapability object that indicates if the visual voicemail can be marked as read.
 * @return Capability object describing whether the visual voicemail can be marked as read.
 */
@property (nonatomic, readonly) CSCapability *markMessageAsReadCapability;

/**
 * A ::CSCapability object that indicates if the visual voicemail can be marked as unread.
 * @return Capability object describing whether the visual voicemail can be marked as unread.
 */
@property (nonatomic, readonly) CSCapability *markMessageAsUnreadCapability;

/**
 * A ::CSCapability object that indicates if the audio voicemail file can be downloaded.
 * @return Capability object describing whether the audio voicemail file can be downloaded.
 */
@property (nonatomic, readonly) CSCapability *downloadCapability;

/**
 * A ::CSCapability object that indicates if the audio voicemail file can be consumed.
 * @return Capability object describing whether the audio voicemail file can be consumed.
 */
@property (nonatomic, readonly) CSCapability *consumeCapability;

/**
 * Marks the visual voicemail message as read.
 */
- (void)markAsRead;

/**
 * Marks the visual voicemail message as read.
 */
- (void)markAsUnread;

/**
 * Start the download of the audio voicemail file asynchronously.
 * @param downloadFilePath The path to download audio voicemail file.
 * @param handler The application/client context associated with this operation.
 *
 * @return Data retrieval cancel object.
 */
- (CSCancellableDataRetrieval *)download:(NSString*) downloadFilePath completionHandler:(CSVisualVoiceMailCompletionHandler) handler;

/**
 * Returns the location of audio file for consumption and changes
 * audio file status to eCONSUMED.
 * @return URI of attachment or empty string if location is not available.
 */
- (NSString*)consume;

- (BOOL)isEqual:(id)object;

@end

/**
 * Delegate that can be used to retrieve status updates for a message. Delegate can be
 * registered to retrieve status updates on the messages’ various attributes.
 */
@protocol CSVisualVoiceMailMessageDelegate <NSObject>

/**
 * Called to report that the "is read" status of the visual voice mail message has changed.
 *
 * @param visualVoiceMailMessage The {@link CSVisualVoiceMailMessage} for which the "is read" status has changed.
 * @param isRead The new value of the visual voice mail read state.
 *
 * @see ::CSVisualVoiceMailMessage::isRead
 */
- (void)visualVoiceMailMessage:(CSVisualVoiceMailMessage *)visualVoiceMailMessage didChangeIsReadStatus:(BOOL)isRead;

/**
 * Called to report that the status of the message has changed.
 *
 * @param visualVoiceMailMessage The {@link CSVisualVoiceMailMessage} for which the status has changed.
 * @param status The new value of the visual voice mail message status.
 *
 * @see ::CSVisualVoiceMailMessage::audioFileStatus
 */
- (void)visualVoiceMailMessage:(CSVisualVoiceMailMessage *)visualVoiceMailMessage didChangeFileStatus:(CSVisualVoiceMailMessageStatus)status;

/**
 * Called to report that the location of the message has changed.
 *
 * @param visualVoiceMailMessage The {@link CSVisualVoiceMailMessage} for which the location  has changed.
 * @param location The new value of the visual voice mail location.
 *
 * @see ::CSVisualVoiceMailMessage::location
 */
- (void)visualVoiceMailMessage:(CSVisualVoiceMailMessage *)visualVoiceMailMessage didChangeLocation:(NSString*)location;


/**
 * Called to report that one or more of the capabilities of the message has changed.
 * The application should query each of the capabilities and enable/disable elements of the
 * user interface based on the new capability settings. Capabilities can change as a result
 * of local or remote actions.
 *
 * @param visualVoiceMailMessage The {@link CSVisualVoiceMailMessage} that the callback is associated with.
 *
 * @see ::CSCapability
 * @see ::CSVisualVoiceMailMessage::markMessageAsReadCapability
 * @see ::CSVisualVoiceMailMessage::markMessageAsUnreadCapability
 * @see ::CSVisualVoiceMailMessage::downloadCapability
 * @see ::CSVisualVoiceMailMessage::consumeCapability
 */
- (void)visualVoiceMailMessageDidChangeCapabilities:(CSVisualVoiceMailMessage *)visualVoiceMailMessage ;

@end
