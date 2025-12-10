/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSVisualVoiceMailMessage.h"
#import "CSVisualVoiceMailCompletionHandler.h"
#import "CSCapability.h"
#import "CSDataRetrievalWatcher.h"

@protocol CSVisualVoiceMailServiceDelegate;

/**
* Service interface for visual voicemail, providing visual voicemail service
* retrieve and delete voice messages, mark messages as read and unread.
*/
@interface CSVisualVoiceMailService : NSObject

/**
* The delegate responsible for visual voicemail events.
*/
@property (nonatomic, weak) id<CSVisualVoiceMailServiceDelegate> delegate;

/**
* Returns an indication of whether the visual voicemail messages can be retrieved.
* @return Capability object describing whether the visual voicemail messages can be retrieved.
*/
@property (nonatomic, readonly) CSCapability *retrieveMessagesCapability;

/**
* Returns an indication of whether the visual voicemail messages can be deleted.
* @return Capability object describing whether the visual voicemail messages can be deleted.
*/
@property (nonatomic, readonly) CSCapability *deleteMessagesCapability;

/**
* Returns whether the user has unread voice messages.
* @return  True if user has unread voice messages.
*/
@property (nonatomic, readonly) BOOL hasUnreadMessages;

/**
* Get number of unread voice messages.
* @return The unread message count.
*/
@property (nonatomic, readonly) NSUInteger unreadMessageCount;

/**
* Report the service availability status.
*/
@property (nonatomic, readonly) BOOL serviceAvailable;

/**
* Retrieve visual voicemail messages for the user.
* @param watcher Watcher.
*/
- (void)retrieveAllMessages:(CSDataRetrievalWatcher *)watcher;

/**
 * Delete visual voicemail message.
 * @param visualVoiceMailMessage The {@link CSVisualVoiceMailMessage}  for this operation.
 * @param handler {@link CSMessagingCompletionHandler} for this operation
*/
- (void)deleteMessage:(CSVisualVoiceMailMessage *)visualVoiceMailMessage completionHandler:(CSVisualVoiceMailCompletionHandler)handler;
@end

@protocol CSVisualVoiceMailServiceDelegate <NSObject>

/**
 * Report that the visual voice mail service has successfully started or restored.
 *
 * @param visualVoiceMailService The {@link CSVisualVoiceMailService} object that the callback is associated with.
 * @see -[visualVoiceMailServiceUnavailable]
 * @see -[CSVisualVoiceMailService serviceAvailable]
 */
- (void)visualVoiceMailServiceAvailable:(CSVisualVoiceMailService *)visualVoiceMailService;

/**
 * Report that the visual voice mail service has been successfully closed or its
 * work was interrupted, for example by a network or server problem.
 *
 * @param visualVoiceMailService the {@link CSVisualVoiceMailService} object that the callback is associated with.
 * @see -[visualVoiceMailServiceAvailable]
 * @see -[CSVisualVoiceMailService serviceAvailable]
 */
- (void)visualVoiceMailServiceUnavailable:(CSVisualVoiceMailService *)visualVoiceMailService;

/**
 * Report that visual voice mail service capabilities have changed.
 *
 * @param visualVoiceMailService The {@link CSVisualVoiceMailService} object that the callback is associated with.
 * @see -[CSVisualVoiceMailService retrieveMessagesCapability]
 * @see -[CSVisualVoiceMailService deleteMessagesCapability]
 */
- (void)visualVoiceMailServiceDidChangeCapabilities:(CSVisualVoiceMailService *)visualVoiceMailService;

/**
 * Called to report that a unreadMessageCount has changed.
 *
 * @param visualVoiceMailService The {@link CSVisualVoiceMailService} object that the callback is associated with.
 * @param unreadMessageCount The number of unread messages.
 *
 * @see ::CSVisualVoiceMailService::unreadMessageCount
 */
- (void)visualVoiceMailService:(CSVisualVoiceMailService *)visualVoiceMailService didChangeUnreadMessageCount:(NSUInteger)unreadMessageCount;

@end
