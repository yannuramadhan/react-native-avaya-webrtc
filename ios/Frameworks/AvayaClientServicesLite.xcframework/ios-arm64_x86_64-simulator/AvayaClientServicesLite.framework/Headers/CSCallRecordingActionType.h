/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Call recording action types
 */
typedef NS_ENUM(NSUInteger, CSCallRecordingActionType) {	
	/**
	 * The action to start call recording
	 */
	CSCallRecordingActionTypeStart,
	
	/**
	 * The action to stop call recording
	 */
	CSCallRecordingActionTypeStop,
	
	/**
	 * The action to pause call recording
	 */
	CSCallRecordingActionTypePause,
	
	/**
	 * The action to resume call recording
	 */
	CSCallRecordingActionTypeResume
};
