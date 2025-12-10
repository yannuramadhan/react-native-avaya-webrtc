/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

/**
 * **Unsupported:**
 * The library sharing feature is currently not supported in Client SDK.
 *
 * Class that represents information about a document stored at a conferencing server library.
 * ---
 * **Unsupported:**
 * This class and all of its supporting classes are for internal Avaya use only and should not be
 * used by third party applications at this time. This is an incubating feature that is currently
 * under development and the classes and methods associated with this feature are subject to change
 * at any time. Use of this feature will not be supported by Avaya until such time that it is
 * officially released.
 */
@interface CSLibraryDocument : NSObject

/**
 * Not supported in Client SDK
 */
@property (nonatomic, readonly) NSString *documentId;

/**
 * Not supported in Client SDK
 *
 * Document title.
 */
@property (nonatomic, readonly) NSString *title;

/**
 * Not supported in Client SDK
 *
 * Document path on the library server.
 */
@property (nonatomic, readonly) NSString *url;

/**
 * Not supported in Client SDK
 *
 * Document creation date. Provided in string form by the network library server.
 */
@property (nonatomic, readonly) NSString *creationDate;

/**
 * Not supported in Client SDK
 *
 * Number of pages in the document.
 */
@property (nonatomic, readonly) NSUInteger pagesCount;

/**
 * Not supported in Client SDK
 *
 * Size of the document page in pixels.
 */
@property (nonatomic, readonly) CGSize contentSize;

/**
 * Not supported in Client SDK 
 *
 * Location of the icon file on the network library.
 */
@property (nonatomic, readonly) NSString *iconFile;

@end
