/* Copyright Avaya Inc. */

#import "AOSessionEnum.h"
#import "AOVideoDevice.h"
#import "AOConnectionListener.h"
#import "AOVideoDetails.h"
#import "AOAudioDetails.h"
#import <AvayaClientServicesLite/AvayaClientServicesLite.h>
#import "AOCallQuality.h"
#import "AOAbstractInteraction.h"
/**
 * @file AOVideoInteraction.h
 * @brief Defines the AOVideoInteraction class.
 */

/**
 * Describes methods that are implemented by the delegate of AOVideoInteractionDelegate.
 */
@protocol AOVideoInteractionDelegate <NSObject>

/**
 * Sent when the outgoing interaction is requesting a session from the Avaya Mobile Communications snap-in.
 */
- (void)interactionInitiating;

/**
 * Sent when the outgoing interaction begins alerting at the remote end.
 *
 * In SIP this corresponds to the interaction receiving a 180 or 183 response from the network. It
 * should be noted that this method may be sent multiple times during initiating an interaction
 * as a result of changes to early media availability and/or redirections. Application
 * developers should not make assumptions about exact ordering of provisional responses, as the
 * sequence depends on different call routing features/topologies.
 */
- (void)interactionRemoteAlerting;

/**
 * Sent when the outgoing interaction has been established.
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
 * Sent when the interaction's video is muted or unmuted.
 *
 * @param isMuted The new video mute state.
 */
- (void)interactionVideoMuteStatusChanged:(BOOL)isMuted;

/**
 * Sent when the interaction's video is enabled or disabled.
 *
 * @param isEnabled The new video state.
 */
- (void)interactionVideoEnabledStatusChanged:(BOOL)isEnabled;

/**
 * Sent when the interaction has finished discarding.
 */
- (void)discardComplete;

/**
 * Sent when the interaction has held.
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
/**
    * Called when a interaction's video mute state changes
    * @param state true when video has been muted, false when video is active
    */
- (void)onInteractionVideoMuteStatusChanged:(BOOL) state;

/**
 * Called when a interaction's video is disabled in case of bandwidth going below the threshold level.
 * This event will only be triggered when disableVideoInLowBandwidth() has been set to true with {@link AOCallQuality} threshold value in {@link VideoInteraction} object.
 *  @param quality Current {@link AOCallQuality} value
 */
- (void)onInteractionVideoDisabledBelowThreshold:(AOCallQuality)quality;

/**
 * Called when a interaction's video can be enabled in case the bandwidth is equivalent or above the threshold value when disableVideoInLowBandwidth() has been set to true with {@link AOCallQuality} threshold value in {@link VideoInteraction} object.
 * @param quality Current {@link AOCallQuality} value
 */
- (void)onInteractionVideoCanBeEnabledThresholdCrossed:(AOCallQuality)quality;


@end

@interface AOVideoInteraction : AOAbstractInteraction

/**
 * Set the authorization token. The authorization token identifies the customer within Avaya Aura Web Gateway. This identity is used for the lifetime of the current interaction in Oceana.
 */
@property (nonatomic) NSString* authorizationToken;

/**
 * Returns a VideoDevice instance that provides media control services.
 */
@property (nonatomic, readonly) AOVideoDevice* videoDevice;

/**
 * Initiate a video interaction.
 */
- (void) start;

/**
 * The delegate responsible for handling video interaction-related events.
 */
@property (nonatomic, assign) id<AOVideoInteractionDelegate> delegate;

/**
 * The delegate responsible for handling connection listener events.
 */
@property (nonatomic, weak) id<AOConnectionListenerDelegate> connectionListenerDelegate;

/**
 * A Boolean value indicating whether audio has been explicitly muted for this interaction.
 */
@property (nonatomic, readonly, getter=isAudioMuted) BOOL audioMuted;

/**
 * A Boolean value indicating whether video has been explicitly muted for this interaction.
 */
@property (nonatomic, readonly, getter=isVideoMuted) BOOL videoMuted;

/**
 * A Boolean value indicating whether video has been explicity enabled for this interaction.
 */
@property (nonatomic, readonly, getter=isVideoEnabled) BOOL videoEnabled;

/**
* A Boolean value indicating whether call has been explicitly held for this interaction.
*/
@property (nonatomic, readonly, getter=isHeld) BOOL held;

/**
 * End the active video interaction.
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
 * Mutes or unmutes the interaction's video.
 *
 * @param mute The new video mute state.
 */
- (void)muteVideo:(BOOL)mute;

/**
 * Hold active call
 */
- (void)holdWithCompletionHandler:(void (^)(NSError *))handler;

/**
 * Unhold active call
 */
- (void)unholdWithCompletionHandler:(void (^)(NSError *))handler;

/**
 * Enables or disables the interaction's video.
 *
 * @param enable The new video state.
 */
- (void) enableVideo:(BOOL)enable;

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
 * Returns the current interaction state.
 */
- (AOInteractionState)getInteractionState;

/**
 * The remote address for this interaction.
 *
 * For SIP this is the unescaped URI of the remote end of the interaction.
 */
@property (nonatomic, strong) NSString *destinationAddress;

/**
 * Reads list of AOVideoDetails objects representing details of all video streams in the interaction.
 *
 * @param handler A block to be called to with video details in AOVideoDetails.
 */
- (void)readVideoDetailsWithCompletionHandler:(void (^)(AOVideoDetails *videoDetails))handler;

/**
 * Reads detailed information about the audio channel associated with the call.
 *
 * If the audio channel has ended the audio details contain the information received from the
 * channel just before it was ended.
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
