/* Copyright Avaya Inc. */

/**
 * @file AOConnectionListener.h
 * @brief Defines the AOConnectionListener class.
 */

/**
 * Describes methods that are implemented by the delegate of AOConnectionListener.
 */
@protocol AOConnectionListenerDelegate <NSObject>

/**
 * Sent when the signalling path for an interaction is attempting to reconnect after an outage.
 * Expect limited call capabilities and the media path to remain active.
 */
- (void) interactionServiceConnecting;

/**
 * Sent when the signalling path for an interaction is available.
 */
- (void) interactionServiceConnected;

/**
 * Sent when the signalling path for an interaction has failed or is unavailable.
 *
 * @param error. An error object describing the failure.
 */
- (void) interactionServiceDisconnectedWithError:(NSError *)error;

@end
