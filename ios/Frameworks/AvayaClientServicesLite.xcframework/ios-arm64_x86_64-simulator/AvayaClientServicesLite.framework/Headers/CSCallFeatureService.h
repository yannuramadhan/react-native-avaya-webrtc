/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSAutodial.h"
#import "CSBusyIndicator.h"
#import "CSCapability.h"

#if !TARGET_OS_IPHONE
#import "CSCrisisAlert.h"
#endif

#import "CSEnhancedCallForwardingStatus.h"
#import "CSFeatureInvocationParameters.h"
#import "CSFeatureParameters.h"
#import "CSFeatureStatusParameters.h"
#import "CSFeatureType.h"
#import "CSServiceObservingMode.h"
#import "CSServiceObservingStatusParameters.h"
#import "CSServiceObservingType.h"
#import "CSTeamButton.h"
#import "CSButtonLampState.h"
#import "CSCallRecordingActionType.h"

@protocol CSCallFeatureServiceDelegate;
@class CSCallPickupAlertStatus;
@class CSCall;

/**
 * The CSCallFeatureService object is accessible from the CSUser object, 
 * providing access to additional business communication features.
 * The CSCallFeatureService object provides a set of APIs that allow
 * application developers to implement advanced SIP telephony features.
 *
 * In general, administered features can be invoked depending upon the 
 * current state of the system.
 *
 * The client application is notified about status updates on features 
 * reported by the call feature service through handlers that the 
 * application has registered on the CSCallFeatureService object. 
 * These updates may be the result of local operations on the 
 * CSCallFeatureService object as well as remote changes initiated by either 
 * the service/server or other end users.
 */
@interface CSCallFeatureService : NSObject

/**
 * The delegate responsible for handling call feature events.
 */
@property (nonatomic, weak) id<CSCallFeatureServiceDelegate> delegate;

/**
 * A Boolean value indicating whether the Call Feature Service is available.
 *
 * @return YES if the Call Feature Service is available, NO otherwise.
 */
@property (nonatomic, readonly) BOOL isServiceAvailable;

/**
 * Gets all the calls features available to the user.
 *
 * @return An NSArray of CSFeatureStatusParameters objects describing the
 *         available features.
 */
- (NSArray *)availableFeatures;

/**
 * Gets all the busy indicators available to the user.
 *
 * @return An NSArray of CSBusyIndicator objects.
 *
 */
- (NSArray *)availableBusyIndicators;

/**
 * Gets all the autodials available to the user.
 *
 * @return An NSArray of CSAutodial objects.
 *
 */
- (NSArray *)availableAutodials;

/**
 * Gets a list of configured hunt-group-busy-position feature buttons for the user.
 *
 * @return An NSArray of CSFeatureStatusParameters objects describing the 
 *          available hunt-group-busy-position features.
 *
 */
- (NSArray<CSFeatureStatusParameters *> *)availableHuntGroupBusyPositionFeatures;

/**
 * Sends out a request in the network to update a configured Autodial button
 *
 * @param updatedAutodial User modified autodial button
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)updateAutodial:(CSAutodial *)updatedAutodial completionHandler:(void (^)(NSError *error))handler;

/**
 * Returns a Boolean value indicating whether the specified feature is available.
 *
 * @param featureType The feature to query.
 */
- (BOOL)isFeatureAvailable:(CSFeatureType)featureType;

/**
 * Returns a capability object indicating whether the specified feature is
 * available.
 *
 * @param featureType The feature to query.
 */
- (CSCapability *)capabilityForFeature:(CSFeatureType)featureType;

/**
* Returns feature status parameters for a specified extension and feature type.
* If feature type is not configured for specified extension, this API will return
* empty object of type FeatureStatusParameters with CSFeatureStatusUndefined status in it.
* Other status are CSFeatureStatusOn/CSFeatureStatusOff/CSFeatureStatusAlerting.
*
* @param featureType The feature to query.
* @param ownerExtension Extension number
*
* This method is deprecated please use \a featureStatusParametersForFeature: .
*/
-(CSFeatureStatusParameters *)featureStatusParametersForType:(CSFeatureType)featureType withExtension:(NSString*)ownerExtension DEPRECATED_MSG_ATTRIBUTE("Use featureStatusParametersForFeature: instead");

/**
 * Returns feature status parameters for a specified CSFeatureParameters object.
 * If feature type is not configured for specified extension, this API will return
 * empty object of type FeatureStatusParameters with CSFeatureStatusUndefined status in it.
 * Other status are CSFeatureStatusOn/CSFeatureStatusOff/CSFeatureStatusAlerting.
 *
 * @param featureParams The CSFeatureParameters object to query feature status.
 */
-(CSFeatureStatusParameters *)featureStatusParametersForFeature:(CSFeatureParameters *)featureParams;

/**
 * Invokes a feature that takes no parameters.
 *
 * @param featureType The feature to invoke.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)invokeFeature:(CSFeatureType)featureType completionHandler:(void (^)(NSError *error))handler;

/**
 * Invokes a feature.
 *
 * @code
 * Feature                                  Parameters
 * ---------------------------------------------------------------------------------
 * CSFeatureTypeSendAllCalls                [action] [owner-extension]
 * CSFeatureTypeForwardAllCalls             [action] [destination] [owner-extension]
 * CSFeatureTypeForwardBusyNoAnswerCalls    [action] [destination] [owner-extension]
 * CSFeatureTypeExclusion                   [action]
 * CSFeatureTypeEC500                       [action]
 * CSFeatureTypeExtendCall
 * CSFeatureTypeCallPark
 * CSFeatureTypeCallUnpark                  [extension]
 * CSFeatureTypeAutoCallback                [action]
 * CSFeatureTypeWhisperPage                 [extension]
 * CSFeatureTypeGroupCallPickup
 * CSFeatureTypeExtendedGroupCallPickup     [pickup-number]
 * CSFeatureTypeCallingPartyNumberBlock     [destination]
 * CSFeatureTypeCallingPartyNumberUnblock   [destination]
 * CSFeatureTypeOneTouchRecording           [action] [extension]
 * CSFeatureTypeDirectedCallPickup          [extension]
 * CSFeatureTypePriorityCall                [destination]
 * CSFeatureTypeHuntGroupBusyPosition       [action] [hunt-group number]
 * CSFeatureTypeMaliciousCallTrace
 * CSFeatureTypeNoHoldConference            [destination]
 * CSFeatureTypeLimitCalls                [action]
 * @endcode
 *
 * @param featureType The feature to invoke.
 * @param featureParameters The parameters supporting this feature invocation.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)invokeFeature:(CSFeatureType)featureType parameters:(CSFeatureInvocationParameters *)featureParameters completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the send all calls feature is
 * available for the user's local extension.
 */
@property (readonly) CSCapability *sendAllCallsCapability;

/**
 * A capability object indicating whether the send all calls feature is
 * available for the specified extention.
 *
 * @param extension The extension for which to query the availability of the
 *        feature.
 */
- (CSCapability *)sendAllCallsCapabilityForExtension:(NSString *)extension;

/**
 * A Boolean value indicating whether the send all calls feature is enabled for
 * the user's local extension.
 */
@property (readonly, getter=isSendAllCallsEnabled) BOOL sendAllCallsEnabled;

/**
 * Returns a Boolean value indicating whether the send all calls feature is
 * enabled for the specified extension.
 *
 * @param extension The extension for which to query the status of the feature.
 */
- (BOOL)isSendAllCallsEnabledForExtension:(NSString *)extension;

/**
 * Enables or disables sending all calls to coverage.
 *
 * @param enabled If @c YES send all calls is enabled. If @c NO send all calls
 *        is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setSendAllCallsEnabled:(BOOL)enabled completionHandler:(void (^)(NSError *error))handler;

/**
 * Enables or disables sending all calls to coverage for another extension.
 *
 * @param enabled If @c YES send all calls is enabled. If @c NO send all calls
 *        is disabled.
 * @param extension The extension to enable or disable send all calls for.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setSendAllCallsEnabled:(BOOL)enabled forExtension:(NSString *)extension completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the call forwarding feature is
 * available for the user's local extension.
 */
@property (readonly) CSCapability *callForwardingCapability;

/**
 * A Boolean value indicating whether the call forwarding feature is enabled for
 * the user's local extension.
 */
@property (readonly, getter=isCallForwardingEnabled) BOOL callForwardingEnabled;

/**
 * The call forwarding destination for the user's local extension, if any.
 */
@property (readonly) NSString *callForwardingDestination;

/**
 * A Boolean value indicating whether the internal twinning feature is enabled.
 */
@property (readonly, getter=isInternalTwinningEnabled) BOOL internalTwinningEnabled;

/**
 * A capability object indicating whether the call forwarding feature is
 * available for the specified extension.
 *
 * @param extension The extension for which to query the availability of the
 *        feature.
 */
- (CSCapability *)callForwardingCapabilityForExtension:(NSString *)extension;

/**
 * Returns a Boolean value indicating whether the call forwarding feature is
 * enabled for the specified extension.
 *
 * @param extension The extension for which to query the status of the feature.
 */
- (BOOL)isCallForwardingEnabledForExtension:(NSString *)extension;

/**
 * Returns the call forwarding destination for the specified extension, if any.
 *
 * @param extension The extension for which to query the forwarding destination.
 */
- (NSString *)callForwardingDestinationForExtension:(NSString *)extension;

/**
 * Enables or disables forwarding of all calls to the specified destination.
 *
 * @param enabled If @c YES forwarding is enabled. If @c NO forwarding is
 *        disabled.
 * @param destination The destination number to forward calls to.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setCallForwardingEnabled:(BOOL)enabled destination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * Enables or disables forwarding of all calls to the specified destination for
 * another extension.
 *
 * @param enabled If @c YES forwarding is enabled. If @c NO forwarding is
 *        disabled.
 * @param extension The extension to enable or disable forwarding for.
 * @param destination The destination number to forward calls to.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setCallForwardingEnabled:(BOOL)enabled forExtension:(NSString *)extension destination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the call forwarding busy-no-answer
 * feature is available for the user's local extension.
 */
@property (readonly) CSCapability *callForwardingBusyNoAnswerCapability;

/**
 * A Boolean value indicating whether the call forwarding busy-no-answer feature
 * is enabled for the user's local extension.
 */
@property (readonly, getter=isCallForwardingBusyNoAnswerEnabled) BOOL callForwardingBusyNoAnswerEnabled;

/**
 * The call forwarding busy-no-answer destination for the user's local
 * extension, if any.
 */
@property (readonly) NSString *callForwardingBusyNoAnswerDestination;

/**
 * A capability object indicating whether the call forwarding busy-no-answer
 * feature is available for the specified extension.
 *
 * @param extension The extension for which to query the availability of the
 *        feature.
 */
- (CSCapability *)callForwardingBusyNoAnswerCapabilityForExtension:(NSString *)extension;

/**
 * Returns a Boolean value indicating whether the call forwarding busy-no-answer
 * feature is enabled for the specified extension.
 *
 * @param extension The extension for which to query the status of the feature.
 */
- (BOOL)isCallForwardingBusyNoAnswerEnabledForExtension:(NSString *)extension;

/**
 * Returns the call forwarding busy-no-answer destination for the specified
 * extension, if any.
 *
 * @param extension The extension for which to query the forwarding destination.
 */
- (NSString *)callForwardingBusyNoAnswerDestinationForExtension:(NSString *)extension;

/**
 * Enables or disables forwarding of calls that receive a busy signal or are not
 * answered to the specified destination.
 *
 * @param enabled If @c YES forwarding is enabled. If @c NO forwarding is
 *        disabled.
 * @param destination The destination number to forward calls to.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setCallForwardingBusyNoAnswerEnabled:(BOOL)enabled destination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * Enables or disables forwarding of calls that receive a busy signal or are not
 * answered to the specified destination for another extension.
 *
 * @param enabled If @c YES forwarding is enabled. If @c NO forwarding is
 *        disabled.
 * @param extension The extension to update call forwarding settings for.
 * @param destination The destination number to forward calls to.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setCallForwardingBusyNoAnswerEnabled:(BOOL)enabled forExtension:(NSString *)extension destination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the Enhanced Call Forwarding feature
 * is available for the user's local extension.
 */
@property (readonly) CSCapability *enhancedCallForwardingCapability;

/**
 * A capability object indicating whether the Enhanced Call Forwarding feature
 * is available for the specified extension.
 *
 * @param extension The extension for which to query the availability of the
 *        feature.
 */
- (CSCapability *)enhancedCallForwardingCapabilityForExtension:(NSString *)extension;

/**
 * The Enhanced Call Forwarding status for the user's local extension, if any.
 */
@property (nonatomic, readonly) CSEnhancedCallForwardingStatus *enhancedCallForwardingStatus;

/**
 * Returns the Enhanced Call Forwarding status for the specified extension.
 *
 * @return A CSEnhancedCallForwardingStatus object describing the busy, no
 *         reply, and unconditional call forwarding settings.
 */
- (CSEnhancedCallForwardingStatus *)enhancedCallForwardingStatusForExtension:(NSString *)extension;

/**
 * Sets the Enhanced Call Forwarding status for the user's local extension.
 *
 * @param enhancedCallForwardingStatus The new enhanced call forwarding status,
 *        specifying the busy, no reply, and unconditional call forwarding
 *        settings.
 *        For IP Office, the same destination number should be provided
 *        for call forward busy and no reply.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setEnhancedCallForwardingStatus:(CSEnhancedCallForwardingStatus *)enhancedCallForwardingStatus completionHandler:(void (^)(NSError *error))handler;

/**
 * Sets the Enhanced Call Forwarding status for another extension.
 *
 * @param enhancedCallForwardingStatus The new enhanced call forwarding status,
 *        specifying the busy, no reply, and unconditional call forwarding
 *        settings.
 *        For IP Office, the same destination number should be provided
 *        for call forward busy and no reply.
 * @param extension The extension to update call forwarding settings for.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setEnhancedCallForwardingStatus:(CSEnhancedCallForwardingStatus *)enhancedCallForwardingStatus forExtension:(NSString *)extension completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the Limit Number of Concurrent Calls feature is available.
 */
@property (readonly) CSCapability *limitCallsCapability;

/**
 * Enables or disables Limit Number of Concurrent Calls feature.
 *
 * Limit Number of Concurrent Calls feature: Users can use this to limit the number of concurrent calls at
 * a station to one call, where normally multiple call appearances can terminate at the station.
 *
 * @param enabled If @c YES Limit Number of Concurrent Calls is enabled. If @c NO Limit Number of Concurrent Calls is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)limitCalls:(BOOL)enabled completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the exclusion feature is available.
 */
@property (readonly) CSCapability *exclusionCapability;

/**
 * Enables or disables exclusion for the active call.
 *
 * Exclusion prevents any other users from bridging onto the call, and drops any
 * other users who are already bridged onto the call.
 *
 * @param enabled If @c YES exclusion is enabled. If @c NO exclusion is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setExclusionEnabled:(BOOL)enabled completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the EC500 feature is available.
 */
@property (readonly) CSCapability *EC500Capability;

/**
 * A Boolean value indicating whether the EC500 feature is enabled.
 */
@property (readonly, getter=isEC500Enabled) BOOL EC500Enabled;

/**
 * Enables or disables EC500.
 *
 * @param enabled If @c YES EC500 is enabled. If @c NO EC500 is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setEC500Enabled:(BOOL)enabled completionHandler:(void (^)(NSError *error))handler;

/**
 * Enables EC500 with the mobile phone number provided or disables EC500.
 * Use this method only if EC500 destination is editable,
 * otherwise use CSCallFeatureService::setEC500Enabled:completionHandler: method.
 * @see CSFeatureStatusParameters::isDestinationExtensionEditable
 *
 * @param enabled If @c YES EC500 is enabled. If @c NO EC500 is disabled.
 * @param number A mobile phone number.
 *               The destination can be any external number the user is able to dial normally.
 *               It should include any prefix if necessary. The number is not relevant if enabled=false.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setEC500Enabled:(BOOL)enabled withDestinationNumber:(NSString *)number  completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the extend call feature is available.
 */
@property (readonly) CSCapability *extendCallCapability;

/**
 * Extends the active call to the off-pbx destinations configured for the user's
 * extension, namely EC500.
 *
 * An invocation of @c extendCallWithCompletionHandler: is not considered
 * successful until the call has been answered on one of the user's off-pbx
 * destinations. Until this occurs @c cancelExtendCallWithCompletionHandler: may
 * be used to cancel the pending extension of the active call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 *
 * @see cancelExtendCallWithCompletionHandler:
 */
- (void)extendCallWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Cancels a pending extension of the active call to the off-pbx destinations
 * configured for the user's extension.
 *
 * An invocation of @c extendCallWithCompletionHandler: is not considered
 * successful until the call has been answered on one of the user's off-pbx
 * destinations. Until this occurs @c cancelExtendCallWithCompletionHandler: may
 * be used to cancel the pending extension of the active call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 *
 * @see extendCallWithCompletionHandler:
 */
- (void)cancelExtendCallWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the call park feature is available.
 */
@property (readonly) CSCapability *parkCallCapability;

/**
 * Parks the active call.
 *
 * A parked call may later be unparked from another extension.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)parkCallWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the call unpark feature is available.
 */
@property (readonly) CSCapability *unparkCallCapability;

/**
 * Unparks a call previously parked at the user's extension.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)unparkCallWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Unparks a call previously parked at the specified extension.
 *
 * @param extension The extension from which to retrieve the parked call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)unparkCallAtExtension:(NSString *)extension completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the auto callback feature is
 * available.
 */
@property (readonly) CSCapability *autoCallbackCapability;

/**
 * A Boolean value indicating whether the auto callback feature is enabled.
 */
@property (readonly, getter=isAutoCallbackEnabled) BOOL autoCallbackEnabled;

/**
 * A Boolean value indicating whether auto callback feature is enabled for the specified destination.
 * Use this method only if AutoCallback destination is editable,
 * otherwise use CSCallFeatureService::autoCallbackEnabled property.
 * @see CSFeatureStatusParameters::isDestinationExtensionEditable
 *
 * @param destination The destination to query auto-callback enablement for.
 */
-(BOOL)isAutoCallbackEnabledForDestination:(NSString *)destination;

/**
 * The list of outstanding automatic callback destinations in case
 * autoCallbackDestination capability is enabled, empty list otherwise.
 */
@property (nonatomic, readonly) NSArray *autoCallbackList;

/**
 * Enables an automatic callback for the last call if it received a busy signal
 * or was unanswered.
 *
 * When the station becomes able to receive a call the user who invoked this
 * feature will be called back automatically.
 *
 * @param enabled If @c YES automatic callback is enabled. If @c NO automatic
 *        callback is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setAutoCallbackEnabled:(BOOL)enabled completionHandler:(void (^)(NSError *error))handler;

/**
 * Enables or disables automatic callback for the specified destination.
 * When the destination user becomes able to receive a call the user who invoked this
 * feature will be called back automatically.
 * Use this method only if autoCallback destination is editable,
 * otherwise use CSCallFeatureService::setAutoCallbackEnabled:completionHandler: method.
 * @see CSFeatureStatusParameters::isDestinationExtensionEditable
 *
 * @param enabled If @c YES automatic callback is enabled. If @c NO automatic callback is disabled.
 * @param destination The destination to enable auto-callback for.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setAutoCallbackEnabled:(BOOL)enabled forDestination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the whisper page feature is available.
 */
@property (readonly) CSCapability *whisperPageCapability;

/**
 * Starts a whisper page to another user that is on an active call.
 *
 * @param extension The extension to start a whisper page to.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)whisperPageToExtension:(NSString *)extension completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the directed call pickup feature is
 * available.
 */
@property (readonly) CSCapability *pickupCallAtExtensionCapability;

/**
 * Picks up a call ringing at the specified extension (directed call pickup).
 *
 * @param extension The extension to pick up the call from.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)pickupCallAtExtension:(NSString *)extension completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the group call pickup feature is
 * available.
 */
@property (readonly) CSCapability *pickupGroupCallCapability;

/**
 * Picks up a call for the user's pickup group (group call pickup).
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)pickupGroupCallWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the extended group call pickup feature
 * is available.
 */
@property (readonly) CSCapability *pickupCallForGroupCapability;

/**
 * Picks up a call for the specified pickup group (extended group call pickup).
 *
 * @param groupNumber The group number to pick up the call from.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)pickupCallForGroup:(NSInteger)groupNumber completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the block calling party number feature
 * is available.
 */
@property (readonly) CSCapability *blockCallingPartyNumberCapability;

/**
 * Starts a call to the specified destination with the user's calling party
 * number information blocked if the call is made over a trunk.
 *
 * @param destination The destination to call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)blockCallingPartyNumberToDestination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the unblock calling party number
 * feature is available.
 */
@property (readonly) CSCapability *unblockCallingPartyNumberCapability;

/**
 * Starts a call to the specified destination with the user's calling party
 * number information unblocked if it would normally be blocked.
 *
 * @param destination The destination to call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)unblockCallingPartyNumberToDestination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the priority call feature is
 * available.
 */
@property (readonly) CSCapability *priorityCallCapability;

/**
 * List of team buttons assigned to the station.
 * This list represents those addresses/endpoints/users participated in this leg of the call and does not
 * represent the union of all users who participated in this call. The local user may
 * have conversed with those remoteParticipants listed in callEvents records.
 *
 * @see CSCallFeatureService::didChangeTeamButtons:
 */
@property (nonatomic, readonly) NSArray<CSTeamButton *> *teamButtons;

/**
 * Starts a priority call to the specified destination.
 *
 * Priority calls have distinct alerting and typically do not go to coverage.
 *
 * @param destination The destination to call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)startPriorityCallToDestination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * Completes call preemption after user acknowledges the continuous preemption tone.
 *
 * Call preemption occurs when a precedence call is sent to a preemptable endpoint
 * that is busy with a call of lower precedence and has no idle appearances.
 * This causes the lower precedence call to be preempted, regardless of whether
 * the lower precedence call and the new higher precedence call are of the same media type.
 * When preemption occurs, the active busy user receive a continuous preemption tone until user
 * acknowledges the preemption by invoking complete preemption method and the other party receives
 * a preemption tone for a minimum of 3 seconds.
 * After acknowledging the preemption, the extension to which the precedence call is directed will
 * be provided with precedence ringing and the calling party will receive an audible ring-back
 * precedence tone.
 *
 * Application must start playing preemption tone upon receipt of event ::CSCallDelegate::call:didPreempt:isPreemptionCompletionRequiredByClient:
 * and stop preemption tone before calling completeCallPreemption when user acknowledges the preemption.
 * However when other end receives preemption application must stop tone after 3 seconds and
 * ::CSCallDelegate::call:didPreempt:isPreemptionCompletionRequiredByClient: is NOT needed since there is no precedence call is directed at this
 * end, other end is free and ready to receive any other new call while tone is being played.
 *
 * @param preemptedCall call which was preempted and received didPreempt event.
 * @param handler A completion handler that receives the result of
 *                          the operation.
 *
 * @see ::CSCallDelegate::call:didPreempt:isPreemptionCompletionRequiredByClient:
 */

- (void)completePreemptionForCall:(CSCall*)preemptedCall completionHandler:(void (^)(NSError *error))handler;

/**
 * Enables or Disables Hunt Group Busy Position feature for a specified hunt group number.
 * When enabled, user will not receive any calls targeted for that hunt group.
 * In order to receive calls on the hunt group, feature needs to be disabled again.
 *
 * @param enabled If @c YES hunt group busy position is enabled. 
 *                If @c NO hunt group busy position is disabled.
 * @param huntGroupNumber The hunt group number for which feature is enabled or disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setHuntGroupBusyPositionEnabled:(BOOL)enabled forHuntGroup:(NSInteger)huntGroupNumber completionHandler:(void (^)(NSError *error))handler;

/**
 * Updates the feature with personalized label given by user.
 *
 * @param featureLabel The personalized label to be set.
 * @param featureParams The CSFeatureParameters object providing details about feature to update.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setPersonalizedLabel:(NSString *)featureLabel forFeature:(CSFeatureParameters *)featureParams completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the hunt-group-busy-position feature is
 * available for the specified hunt group number.
 *
 * @param huntGroupNumber The hunt group number for which to query the availability of the
 *        feature.
 */
- (CSCapability *)huntGroupBusyPositionCapabilityForHuntGroupNumber:(NSInteger)huntGroupNumber;

#if !TARGET_OS_IPHONE
/**
 * Returns crisis alert details.
 *
 * If there is an active crisis alert, then
 * the {@link CSCrisisAlert} object contains crisis alert
 * status as ON with details of the user who initiated the alert
 * like user location, time of alert raised, etc.
 *
 * If there isn't any active crisis alert, the feature status
 * will be OFF.
 *
 * If the Crisis Alert feature button is not configured by the admin,
 * then nil will be returned.
 *
 * There can be only one active alert on the attendant's console
 * at any given device at a time.
 * Subsequent alerts raised by users will be queued on the server.
 * When the attendant clears the active alert, the next queued alert
 * will be presented to the watcher.
 *
 * @see CSCallFeatureServiceDelegate::callFeatureService:didChangeCrisisAlertStatus:
 */
@property (nonatomic, readonly) CSCrisisAlert *crisisAlert;

/**
 * Clears crisis alert for the watcher.
 *
 * Multiple users may place emergency call. As a result, the system can have
 * multiple crisis alerts raised. The first crisis alert is presented to all
 * the watchers (attendants), remaining alerts are queued on the server.
 *
 * If the admin has configured the system in Single User Response mode, then
 * clearing the alert on one of the watchers will clear the alert from all
 * watchers.
 *
 * The next queued alert will be presented to all the watchers.
 *
 * If the admin has configured the system in Every User Response mode then if
 * one of the watchers clears the alert, the next alert from the server will
 * be presented only to that user. Other watchers will still have the same crisis
 * alert active on their devices.
 *
 * In order to receive the next queued crisis alert every watcher has to clear
 * active crisis alert on his device.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful then this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)clearCrisisAlertWithCompletionHandler:(void (^)(NSError *error))handler;
#endif


/**
 * A capability object indicating whether Malicious Call Trace feature is available for incoming active call.
 */
@property (readonly) CSCapability *maliciousCallTraceCapability;

/**
 * A Boolean value indicating whether Malicious Call Trace feature is activated.
 */
@property (readonly, getter=isMaliciousCallTraceActive) BOOL maliciousCallTraceActive;

/**
 * Activate Malicious Call Trace feature for incoming active call.
 * When malicious call trace controller (human) presses "mct-contr" button, callback
 * didChangeMaliciousCallTraceStatus(true) is invoked. When the controller deactivates a malicious call trace,
 * callback didChangeMaliciousCallTraceStatus(false) is invoked.
 * Feature is deactivated by pressing the feature deactivation code by same client, which pressed "mct-contr" button.
 * "mct-contr" button is implemented in CM for h.323 only.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)activateMaliciousCallTraceWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether No Hold Conference feature is available for active call.
 */
@property (readonly) CSCapability *noHoldConferenceCapability;

/**
 * A capability object indicating whether No Hold Conference feature can be canceled.
 */
@property (readonly) CSCapability *noHoldConferenceCancelCapability;

/**
 * The destination extension for No Hold Conference feature button.
 */
@property (readonly)NSString *noHoldConferenceDestination;

/**
 * Start No Hold Conference for active call, or add new participant to existing conference.
 *
 * No Hold Conference feature button allows a user to set up a conference call without interrupting the
 * current conversation. The called party is automatically added to the conference as soon as they answer.
 * Successful completionHandler is invoked after invited party answered, or the feature was canceled.
 * Current active call will be transformed into the conference.
 * The number dialed by the user is sent as a message and not as tone so that the digits are not heard by
 * any party on the call. So No Hold Conference button should be used if it's important that no tones are
 * heard by participants, and/or remote user should not be held. In other cases AddParticipantFromCall/AddParticipant
 * methods of Conference interface should be used.
 * No Hold Conference is Avaya Communication Manager feature, which is not available in other environments.
 *
 * @param destination Network address of the person who is being added to the conference call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)makeNoHoldConferenceWithDestination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * Cancels the No Hold Conference invocation.
 * The feature can be canceled after invocation of No Hold Conference and during the time it's ringing on the
 * party that is to be added to the No Hold Conference.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)cancelNoHoldConferenceWithCompletionHandler:(void(^)(NSError *error))handler;

/**
 * Returns service observing feature status parameters.
 *
 * If service observing feature is enabled then
 * the {@link CSServiceObservingStatusParameters} object contains details
 * of service observing feature.
 *
 * @see CSServiceObservingStatusParameters
 */
@property (nonatomic, readonly) CSServiceObservingStatusParameters *serviceObservingStatusParameters;

/**
 * Returns an indication as to whether the service observing is available.
 *
 * @return CSCapability object describing whether the service observing is available.
 */
@property (nonatomic,readonly) CSCapability *serviceObservingCapability;

/**
 * Starts service observing.
 *
 * @param entity The extension of the endpoint currently observed.
 * @param type The Service Observing type.
 * @param location The location number associated with the observed VDN. The valid range is 0-2000.
 * 		  The value 0 means that the service observing type is not "By Location"
 * @param handler An Object that wants to learn about the result of start service
 * 		  observing operation i.e., whether it was successful.
 *
 * @see CSServiceObservingType
 */
-(void)startServiceObserving:(NSString *)entity withType:(CSServiceObservingType)type withLocation:(NSInteger)location completionHandler:(void (^)(NSError *error)) handler;

/**
 * Change the mode of service observing session
 *
 * @param mode The Service Observing mode.
 * @param handler An Object that wants to learn about the result of change service
 *		  observing mode operation i.e., whether it was successful.
 *
 * @see CSServiceObservingMode
 */
-(void)changeServiceObservingMode:(CSServiceObservingMode)mode completionHandler:(void (^)(NSError *error)) handler;

/**
 * Stops coaching session.
 *
 * @param handler An Object that wants to learn about the result of stop coaching
 * 		  session operation i.e., whether it was successful.
 */
 -(void)stopCoachingSession:(void (^)(NSError *error)) handler;

/**
 * Stops service observing.
 *
 * @param handler An Object that wants to learn about the result of stop service
 * 		  observing operation i.e., whether it was successful.
 */
-(void)stopServiceObserving:(void (^)(NSError *error)) handler;

/**
 * Returns a capability object indicating whether a particular call recording action is allowed
 *
 * @param type The call recording action type.
 * @return CSCapability object describing whether the recording action is allowed.
 *
 * @see CSCallRecordingActionType
 */
- (CSCapability *)callRecordingCapabilityForActionType:(CSCallRecordingActionType)type;

/**
 * Perform call recording operation with specific action type
 *
 * @param type The call recording action type.
 * @param handler An Object that wants to learn about the result of call recording
 * 		  operation i.e., whether it was successful.
 *
 * @see CSCallRecordingActionType
 */
- (void)performCallRecordingWithActionType:(CSCallRecordingActionType)type completionHandler:(void (^)(NSError *error)) handler;

/**
 * Call Handover to move a call to user's simultaneous/twin clients
 *
 * @param handler An Object that wants to learn about the result of call handover
 * 		  operation i.e., whether it was successful.
 */
- (void)moveCall:(void (^)(NSError *error)) handler;

/**
 * Call Handover to retrieve a call from user's simultaneous/twin clients
 *
 * @param handler An Object that wants to learn about the result of call handover
 * 		  operation i.e., whether it was successful.
 */
- (void)retrieveCall:(void (^)(NSError *error)) handler;

@end

@protocol CSCallFeatureServiceDelegate <NSObject>
@optional

/**
 * Sent to indicate that call feature service is available.
 *
 * @param callFeatureService The call feature service instance sending the message.
 */
- (void)callFeatureServiceDidBecomeAvailable:(CSCallFeatureService *)callFeatureService;

/**
 * Sent to indicate that call feature service is unavailable.
 *
 * @param callFeatureService The call feature service instance sending the message.
 */
- (void)callFeatureServiceDidBecomeUnavailable:(CSCallFeatureService *)callFeatureService;

/**
 * Sent when the capability of a feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param featureType The feature for which capability has changed.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeFeatureCapability:(CSFeatureType)featureType;

/**
 * Sent when the status of a feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param featureStatus The updated feature status information.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeFeatureStatus:(CSFeatureStatusParameters *)featureStatus;

/**
 * Sent when the list of available features has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 */
-(void)callFeatureServiceDidChangeAvailableFeatures:(CSCallFeatureService *)callFeatureService;

/**
 * Sent when the status of the send all calls feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param enabled The new state of the feature.
 * @param extension The extension for which the feature has been enabled or
 *        disabled. The value is nil if the feature has been enabled or disabled
 *        for the user's local extension.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeSendAllCallsStatus:(BOOL)enabled forExtension:(NSString *)extension;

/**
 * Sent when the status of the call forwarding feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param enabled The new state of the feature.
 * @param extension The extension for which the feature has been enabled or
 *        disabled. The value is nil if the feature has been enabled or disabled
 *        for the user's local extension.
 * @param destination The new forwarding destination.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeCallForwardingStatus:(BOOL)enabled forExtension:(NSString *)extension destination:(NSString *)destination;

/**
 * Sent when the status of the call forwarding busy-no-answer feature has
 * changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param enabled The new state of the feature.
 * @param extension The extension for which the feature has been enabled or
 *        disabled. The value is nil if the feature has been enabled or disabled
 *        for the user's local extension.
 * @param destination The new forwarding destination.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeCallForwardingBusyNoAnswerStatus:(BOOL)enabled forExtension:(NSString *)extension destination:(NSString *)destination;

/**
 * Sent when the status of the Enhanced Call Forwarding feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param featureStatus The updated feature status information.
 * @param extension The extension for which the feature has been enabled or
 *        disabled. The value is nil if the feature has been enabled or disabled
 *        for the user's local extension.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeEnhancedCallForwardingStatus:(CSEnhancedCallForwardingStatus *)featureStatus forExtension:(NSString *)extension;

/**
 * Sent when the status of the EC500 feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param enabled The new state of the feature.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeEC500Status:(BOOL)enabled;

/**
 * Sent when the status of the auto callback feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param enabled The new state of the feature.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeAutoCallbackStatus:(BOOL)enabled;

/**
 * Occurs when the list of outstanding automatic callback extensions is changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param list The new list of outstanding automatic callback extensions.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeAutoCallbackList:(NSArray<NSString *> *)list;

/**
 * Sent when the status of the busy indicator object has changed.
 *
 * @param callFeatureService The call feature service instance that the
 *        callback is associated with.
 * @param busyIndicator The changed busy indicator object.
 */

- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeBusyIndicator:(CSBusyIndicator *)busyIndicator;

/**
 * Sent when the status of the call pickup feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param callPickupFeatureStatus The call pickup feature alert status
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeCallPickupAlertStatus:(CSCallPickupAlertStatus *)callPickupFeatureStatus;

/**
 * Occurs when the available team buttons list are updated.
 *
 * @see CSCallFeatureService::teamButtons
 */
- (void)didChangeTeamButtons:(CSCallFeatureService *)callFeatureService;

/**
 * Occurs if the Team Button busy status is changed when the monitored station
 * either dials or has an active call.
 * A Team Button is considered Idle if all call appearances on the monitored  station
 * are either in the Idle or Ringing states. If there are bridged call appearances on
 * the monitored station, the states "Alerting" and "In-Use" are interpreted by the CM
 * as equivalent to Idle.
 * @param callFeatureService The call feature service instance reporting the callback.
 * @param teamButton The team button with busy status updated.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeBusyStatusForTeamButton:(CSTeamButton *)teamButton;

/**
 * Occurs when the monitored station of Team Button has an incoming ringing call.
 * The Team Button notification alert status depends on {@link CSTeamButton::pickupRingType}.
 *
 * {@link CSTeamButtonIncomingCall} started ringing at the monitored station is provided.
 * {@link CSTeamButtonIncomingCall::pickupWithCompletionHandler:} functionality is available.
 * @param callFeatureService The call feature service instance reporting the callback.
 * @param teamButton The team button that has alerting calls.
 * @param call The team button call that started alerting.
 * @see CSTeamButton::pickupCapability
 * @see CSTeamButton::speedDialCapability
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didAddIncomingCall:(CSTeamButtonIncomingCall *)call forTeamButton:(CSTeamButton *)teamButton;

/**
 * Occurs when the incoming call to monitored station stops ringing.
 *
 * {@link CSTeamButtonIncomingCall} stopped ringing at the monitored station is provided.
 * {@link CSTeamButtonIncomingCall::pickupWithCompletionHandler:} functionality is available.
 * @param callFeatureService The call feature service instance reporting the callback.
 * @param teamButton The team button that has alerting calls.
 * @param call The team button call that stopped alerting.
 * @see CSTeamButton::pickupCapability
 * @see CSTeamButton::speedDialCapability
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didRemoveIncomingCall:(CSTeamButtonIncomingCall *)call forTeamButton:(CSTeamButton *)teamButton;

/**
 * Occurs when the forwarding status of Team Button monitored station is changed.
 * @see CSTeamButton::forwardingEnabled
 * @see CSTeamButton::forwardingDestination
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeForwardingStatusForTeamButton:(CSTeamButton *)teamButton;

#if !TARGET_OS_IPHONE
/**
 * Occurs when the status of the crisis alert feature has changed.
 * The status can also be retrieved using {@link CSCallFeatureService::crisisAlert} method.
 *
 * When any user places an emergency call then the system raises
 * the crisis alert which is presented to the watchers (attendants).
 *
 * If a user is not logged in while an active alert is raised in the system,
 * the alert will be presented to the user upon login.
 *
 * If multiple users are watchers for the crisis alert, all the
 * watchers will be presented with crisis alert.
 *
 * There can be only one active alert on the watcher's console.
 * Subsequent alerts will be queued on the server. When the attendant clears
 * the active alert, next queued alert will be presented.
 *
 * @see CSCrisisAlert
 * @see CSCallFeatureService::clearCrisisAlertWithCompletionHandler:
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeCrisisAlertStatus:(CSCrisisAlert *)crisisAlert;
#endif

/**
 * Occurs when the Malicious Call Trace status is changed (active/not active).
 * Feature status is changed to active when Malicious Call Trace controller took control over a malicious call trace.
 * Feature status is changed to not active when Malicious Call Trace controller deactivated a malicious call trace.
 * @param callFeatureService The call feature service instance sending the message.
 * @param active The new status of the feature (active/not active).
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeMaliciousCallTraceStatus:(BOOL)active;

/**
 * Reports service observing got enabled.
 *
 * @param callFeatureService instance of call feature service callback is associated with
 * @param type The Service Observing type
 * @param entity The observed entity
 * @param buttonLamp The Service Observing button lamp type
 *
 * @see CSCallFeatureService::startServiceObservingwithTypewithLocationcompletionHandler:
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didEnableServiceObservingType:(CSServiceObservingType)type forEntity:(NSString *)entity withButtonLamp:(CSButtonLampState)buttonLamp;

/**
 * Reports service observing got disabled.
 *
 * @param callFeatureService instance of call feature service callback is associated with
 *
 * @see CSCallFeatureService::stopServiceObserving:
 */
- (void)callFeatureServiceDidDisableServiceObserving:(CSCallFeatureService *)callFeatureService;

/**
 * Reports service observing feature status changed.
 *
 * @param callFeatureService instance of call feature service callback is associated with
 * @param serviceObservingStatusParameters service observing status parameters
 *
 * @see CSServiceObservingStatusParameters
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeServiceObservingStatus:(CSServiceObservingStatusParameters *)serviceObservingStatusParameters;

/**
 * Reports an error received for service observing session.
 *
 * Client SDK raises this event if it receives an error from the server during the service observing session.
 * e.g. supervisor is trying to start a service observing session by providing an invalid agent id.
 * e.g. observed user has activated the exclusion during the service observing call.
 *
 * @param callFeatureService instance of call feature service callback is associated with
 * @param errorCode An error object describing the service observing error
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didReceivedServiceObservingError:(NSError *)errorCode;

@end
