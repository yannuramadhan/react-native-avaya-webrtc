//
//  CSExportService.h
//
#import <Foundation/Foundation.h>
#import "CSCapability.h"
#import "CSConference.h"
#import "CSMessagingConversation.h"

/**
 *	status for Export progress
 */
typedef NS_ENUM(NSUInteger, CSExportStatus) {
	CSExportStarted,
	CSExportSucceeded,
	CSExportSucceededWithAttachmentFailure,
	CSExportNotSupported,
	CSExportFailed,
	CSExportMessageDownloadInProgress,
	CSExportMessageDownloadCompleted,
	CSExportMessageDownloadFailed,
	CSExportAttachmentDownloadInProgress,
	CSExportAttachmentDownloadCompleted,
	CSExportAttachmentDownloadFailed,
	CSExportFileWritingInProgress,
	CSExportFileWritingCompleted,
	CSExportFileWritingFailed,
	CSExportCancelInProgress,
	CSExportCancelSucceeded,
	CSExportCancelFailed
};


/**
 * Strings constants  as keys for identifying localized strings
 */
typedef NSString* CSExportLocalizedStringKey;

/**
 * Key representing a string for participant joined the messaging conversation.
 * e.g., @"%@ joined conversation on %@"
 * Client SDK replaces first %@ with the participant's name who joined the conversation
 * and last %@ with time stamp when participant joined the conversation.
*/
static CSExportLocalizedStringKey const CSExportJoinConversation  = @"CSExportJoinConversation";
/**
 * Key representing a string for participant left the messaging conversation.
 * e.g., @"%@ left conversation on %@"
 * Client SDK replaces %@ with the participant's name who left the conversation
 * and last %@ with time stamp when participant left the conversation.
*/
static CSExportLocalizedStringKey const CSLeftConversation = @"CSLeftConversation";
/**
 * Key representing a string for participant removed from the messaging conversation.
 * e.g., @"%@ has been removed from the conversation by %@ on %@"
 * Client SDK replaces first %@ with the removed participant's name, second %@ with the participant's name who removed the other participant
 * and last %@ with time stamp when participant is removed from the conversation.
*/
static CSExportLocalizedStringKey const CSRemovedFromConversation = @"CSRemovedFromConversation";
/**
 * Key representing a string for subject changed of the messaging conversation.
 * e.g., @"set the subject to: "
*/
static CSExportLocalizedStringKey const CSSubjectChanged = @"CSSubjectChanged";
/**
 * Key representing a string for attachment downloaded.
 * e.g., @"Attachment: "
*/
static CSExportLocalizedStringKey const CSAttachmentDownloaded = @"CSAttachmentDownloaded";
/**
 * Key representing a string for attachment download failed.
 * e.g., @"Failed to download attachment: "
*/
static CSExportLocalizedStringKey const CSAttachementFailed = @"CSAttachementFailed";
/**
 * Key representing a conversation title string in the header section.
 * e.g., @"Avaya Workplace Conversation Transcript"
*/
static CSExportLocalizedStringKey const CSHeaderConversationTitle = @"CSHeaderConversationTitle";
/**
 * Key representing a conference title string in the header section.
 * e.g., @"Avaya Workplace Conference Public Chat Transcript"
*/
static CSExportLocalizedStringKey const CSHeaderConferenceTitle = @"CSHeaderConferenceTitle";
/**
 * Key representing a string for conversation label in the header section.
 * e.g., @"Conversation: "
*/
static CSExportLocalizedStringKey const CSHeaderConversation = @"CSHeaderConversation";
/**
 * Key representing a string for conference label in the header section.
 * e.g., @"Meeting: "
*/
static CSExportLocalizedStringKey const CSHeaderConference = @"CSHeaderConference";
/**
 * Key representing a string for participants label in the header section.
 * e.g., @"Participants (%d):  %@"
 * Client SDK replaces %d with number of participants and %@ with the list of participants.
*/
static CSExportLocalizedStringKey const CSHeaderParticipants = @"CSHeaderParticipants";
/**
 * Key representing a string for exported at label in the header section.
 * e.g., @"Exported at %@"
 * Client SDK replaces %@ with time stamp when export operation is completed.
*/
static CSExportLocalizedStringKey const CSHeaderExportedAt = @"CSHeaderExportedAt";
/**
 * Key representing a string for exported by label in the header section.
 * e.g., @"Exported by %@"
 * Client SDK replaces %@ with the participant's name who started the export operation.
*/
static CSExportLocalizedStringKey const CSHeaderExportedBy = @"CSHeaderExportedBy";
/**
 * Key representing a string for attachments folder name to download attachments.
 * e.g., @"attachments"
*/
static CSExportLocalizedStringKey const CSAttachmentFolder = @"CSAttachmentFolder";


@protocol CSExportServiceDelegate;

/**
 * The CSExportService object is accessible from the CSUser object,
 * providing the ability to export messages for Conference Chat and Messaging conversation.
 * The CSExportService exposes a set of APIs that allow application developers to
 * download conference chat and messaging conversations for archival on the local file system or
 * other storage location depending on the client application's implementation.
 *
 * The availability of this service depends on a configuration setting controlled by the system administrator.
 *
 * The client application is notified about the status of export service
 * through handlers that the application has registered on the CSExportService object.
 * These updates may be the result of operations on the CSExportService object.
 *
 * It is the duty of the application to archive this file along with attachment folder for the user.
 */

@interface CSExportService : NSObject

/**
 * The delegate responsible for handling Export service related events such as export in progress, done, failed.
 */
@property (nonatomic, weak) id<CSExportServiceDelegate> delegate;

/**
 * Returns CSCapability object describing the Conferenec Chat export availability.
 * @return {@link CSCapability} object describing the Conference Chat export availability.
 */
@property (readonly) CSCapability *conferenceChatExportCapability;

/**
 * Returns CSCapability object describing the Messaging Conversation export availability.
 * @return {@link CSCapability} object describing the Messaging Conversation export availability.
 */
@property (readonly) CSCapability *messagingConversationExportCapability;

/**
 * Sets the text alignment to be used in the exported HTML file.
 * Pass True to set the alignment as right-to-left. Typically set for languages like Hebrew.
 * The default text alignment for the exported file will be left-to-right.
 *
 * @param enabled True if the exported HTML is to be right-to-left aligned.
 */
- (void)setRightToLeftAlignment:(BOOL)enabled;

/**
 * Sets the localized strings to be used in the exported HTML file.
 * The dictionary consists of  {@link CSExportLocalizedStringKey} key and its respective string as value.
 *
 * @param localizedStrings the dictionary containing localized strings.
 */
- (void)setLocalizedStrings:(NSDictionary<CSExportLocalizedStringKey, NSString *> *)localizedStrings;

/**
 * Exports the messages from the given conference chat.
 * Only public conference chat will be exported.
 *
 * @param conference the conference object from which the public chat is to be exported.
 * @param directoryPath path to export the messages.
 * @param fileName name of the HTML file where messages are exported.
 * @param completionHandler The completion handler for this operation.
 * @see -[conferenceChatExportCapability]
 * @see -[cancelChatExport]
 */
- (void)exportChat:(CSConference *)conference directoryPath:(NSString *)directoryPath fileName:(NSString *)fileName completionHandler:(void (^)(NSError *error))completionHandler;

/**
 * Cancel the chat export.
 *
 * @param conference the conference object whose public chat export is to be cancelled.
 * @param completionHandler the completion handler for this operation.
 * @see -[conferenceChatExportCapability]
 * @see -[exportChat]
 */
- (void)cancelChatExport:(CSConference *)conference completionHandler:(void (^)(NSError *error))completionHandler;

/**
 * Exports the messages and attachments from the given Messaging Conversation.
 * All messages and attachments in the conversation are downloaded from server and placed in the specified directory.
 * The messages are written to the specified HTML file and attachments are written into a subfolder named "attachments".
 *
 * @param conversation the messaging conversation object to export messages.
 * @param directoryPath path to export the messages and attachments
 * @param fileName name of HTML file where messages are exported.
 * @param completionHandler The completion handler for this operation.
 * @see -[messagingConversationExportCapability]
 * @see -[cancelMessagingConversationExport]
 */
- (void)exportMessagingConversation:(CSMessagingConversation *)conversation directoryPath:(NSString *)directoryPath fileName:(NSString *)fileName completionHandler:(void (^)(NSError *error))completionHandler;

/**
 * Cancel the messaging conversation export.
 *
 * @param conversation the messaging conversation object to cancel exporting messages.
 * @param completionHandler the completion handler for this operation.
 * @see -[messagingConversationExportCapability]
 * @see -[exportMessagingConversation]
 */
- (void)cancelMessagingConversationExport:(CSMessagingConversation *)conversation completionHandler:(void (^)(NSError *error))completionHandler;

@end

/**
 * Describes methods that are implemented by the delegate of a @c CSExportService.
 */
@protocol CSExportServiceDelegate <NSObject>

/**
 * Called when export status on Conference Chat has changed.
 *
 * @param conference the Conference object whose public chat export status has changed.
 * @param exportStatus the current status of Export.
 */
- (void)didChangeStatusForChatExport:(CSConference *)conference status:(CSExportStatus)exportStatus;

/**
 * Called when export status on Messaging Conversation has changed.
 *
 * @param conversation the Messaging Conversation whose export status has changed.
 * @param exportStatus the current status of Export.
 */
- (void)didChangeStatusForMessagingConversationExport:(CSMessagingConversation *)conversation status:(CSExportStatus)exportStatus;

@end

