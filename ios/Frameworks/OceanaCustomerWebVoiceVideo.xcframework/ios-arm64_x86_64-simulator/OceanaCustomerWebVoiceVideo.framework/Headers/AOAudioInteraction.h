/* Copyright Avaya Inc. */

#import "AOSessionEnum.h"
#import "AOConnectionListener.h"
#import "AOAudioDetails.h"
#import "AOAbstractInteraction.h"
#import <AvayaClientServicesLite/AvayaClientServicesLite.h>
#import "AOCallQuality.h"
/**
 * @file AOAudioInteraction.h
 * @brief Defines the AOAudioInteraction class.
 */

/**
 * Describes methods that are implemented by the delegate of AOAudioInteractionDelegate.
 */
@protocol AOAudioInteractionDelegate <NSObject>

/**
 * Sent when the interaction is reqesting a session from the Avaya Mobile Communications snap-in.
 *
 */
- (void)interactionInitiating;

/**
 * Sent when the interaction begins alerting at the remote end.
 *
 * In SIP this corresponds to the interaction receiving a 180 or 183 response from the network. It
 * should be noted that this method may be sent multiple times during initiating an interaction
 * as a result of changes to early media availability and/or redirections. Application
 * developers should not make assumptions about exact ordering of provisional responses, as the
 * sequence depends on different call routing features/topologies.
 */
- (void)interactionRemoteAlerting;

/**
 * Sent when the interaction has been established.
 */
- (void)interactionActive;

/**
 * Sent when the interaction has ended.
 */
- (void)interactionEnded;

/**
 * Sent when the interaction has failed.
 *
 * @param error An error object describing the failure.
 */
- (void)interactionFailed:(NSError*)error;

/**
 * Sent when the interaction's audio is muted or unmuted.
 *
 * @param isMuted The new audio mute state.
 */
- (void)interactionAudioMuteStatusChanged:(BOOL)isMuted;

/**
 * Sent when the interaction has finished discarding.
 */
- (void)discardComplete;

/**
 * Sent when the interaction is on hold
 */
- (void)holdComplete;

/**
 * Sent when the interaction has unheld.
 */
- (void)unholdComplete;

/**
 * Sent when the interaction is on remotely hold
 */
- (void)remoteHoldComplete;

/**
 * Sent when the interaction has remotely unheld.
 */
- (void)remoteUnholdComplete;

/**
 * Called when a interaction's quality state changes
 * @param quality {@link AOCallQuality} representing quality of the call
 */
- (void)onInteractionQualityChanged:(AOCallQuality) quality;


@end

@interface AOAudioInteraction : AOAbstractInteraction

/**
 * Set the authorization token. The authorization token identifies the customer within Avaya Aura Web Gateway. This identity is used for the lifetime of the current interaction in Oceana.
 */
@property (nonatomic) NSString* authorizationToken;

/**
 *  Initiate an audio interaction.
 */
- (void) start;

/**
 * The delegate responsible for handling audio interaction-related events.
 */
@property (nonatomic, assign) id<AOAudioInteractionDelegate> delegate;

/**
 * The delegate responsible for handling connection listener events.
 */
@property (nonatomic, weak) id<AOConnectionListenerDelegate> connectionListenerDelegate;

/**
 * A Boolean value indicating whether audio has been explicitly muted for this interaction.
 */
@property (nonatomic, readonly, getter=isAudioMuted) BOOL audioMuted;

/**
* A Boolean value indicating whether call has been explicitly held for this interaction.
*/
@property (nonatomic, readonly, getter=isHeld) BOOL held;

/**
 * End the active audio interaction.
 */
- (void)end;

/**
 * Shutdown the SDK after the interaction has ended.
 */
- (void) discard;

/**
 * Mutes or unmutes the interaction's audio.
 *
 * @param mute The new audio mute state.
 */
- (void)muteAudio:(BOOL)mute;

/**
 * Hold active call
 */
- (void)holdWithCompletionHandler:(void (^)(NSError *))handler;

/**
 * Unhold active call
 */
- (void)unholdWithCompletionHandler:(void (^)(NSError *))handler;

/**
 * Gets time elapsed of the current interaction.
 */
- (long)getInteractionTimeElapsed;

/**
 * Sends the specified DTMF tone.
 *
 * @param tone The tone to transmit.
 */
- (void)sendDTMF:(AODTMFTone)tone;

/**
 * Returns the current interaction state
 */
- (AOInteractionState)getInteractionState;

/**
 * The remote address for this interaction.
 * For SIP this is the unescaped URI of the remote end of the interaction.
 */
@property (nonatomic, strong) NSString *destinationAddress;

/**
 * Reads detailed information about the audio channel associated with the call.
 *
 * If the audio channel has ended the audio details contain the information received from the
 * channel just before it was ended.
 *
 * @param handler A block to be called to with audio details in AOAudioDetails.
 */
- (void)readAudioDetailsWithCompletionHandler:(void (^)(AOAudioDetails *audioDetails))handler;

/**
* Reads Call Type information  associated with the call.
* @param handler A block to be called to with Call Type in NSString.
*/
- (void)readCallTypeWithCompletionHandler:(void (^)(NSString *csCallTypeString))handler;

#ifdef DEBUG_1
// To change the AudioCodec at runtime for Dev
@property (nonatomic, assign) CSAudioCodec useThisCodec;
#endif

/**
* Set the platform types for the client configurations (Elite and Oceana)
* @param type an AOPlatformType to be passed to set the platform.
*/
- (void) setPlatformType : (AOPlatformType) type;

@end
