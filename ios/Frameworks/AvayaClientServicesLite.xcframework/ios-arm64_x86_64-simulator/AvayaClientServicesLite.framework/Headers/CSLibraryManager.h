/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSLibraryDocument.h"

/**
 * Library sharing is not supported in Client SDK
 *
 * Library document types.
 */
typedef NS_ENUM(NSUInteger, CSLibraryDocumentType) {
	CSLibraryDocumentPresentation,
	CSLibraryDocumentOtherDocument,
	CSLibraryDocumentPicture
};

/**
 * **Unsupported:**
 * The library sharing feature is currently not supported in Client SDK.
 *
 * Class that represents library management functions such as add, edit, remove documents
 * from the network document library.
 * ---
 * **Unsupported:**
 * This class and all of its supporting classes are for internal Avaya use only and should not be
 * used by third party applications at this time. This is an incubating feature that is currently
 * under development and the classes and methods associated with this feature are subject to change
 * at any time. Use of this feature will not be supported by Avaya until such time that it is
 * officially released.
 */
@interface CSLibraryManager : NSObject

/**
 * Not supported in Client SDK
 *
 * A list of documents in library
 */
@property (nonatomic, readonly) NSArray *libraryContent;

/**
 * Not supported in Client SDK
 */
- (void)deleteDocument:(CSLibraryDocument *)document;

/**
 * Not supported in Client SDK
 */
- (void)renameDocument:(CSLibraryDocument *)document toName:(NSString *)newName;

/**
 * Not supported in Client SDK
 */
- (void)uploadDocumentWithName:(NSString *)name type:(CSLibraryDocumentType)type filePath:(NSString *)filePath;

@end
