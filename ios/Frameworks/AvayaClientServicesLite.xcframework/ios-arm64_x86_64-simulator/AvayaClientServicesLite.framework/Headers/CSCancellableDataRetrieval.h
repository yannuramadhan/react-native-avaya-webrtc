/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Represents cancel of asynchronous data retrieval for the current operation.
 */
@interface CSCancellableDataRetrieval : NSObject

/**
 * Stop background task
 */
- (void)cancel;

@end
