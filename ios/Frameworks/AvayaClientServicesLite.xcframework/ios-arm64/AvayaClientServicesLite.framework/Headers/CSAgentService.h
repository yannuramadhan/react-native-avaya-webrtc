/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSAgentFeature.h"
#import "CSCapability.h"
#import "CSAgentInformation.h"
#import "CSQueueStatistics.h"
#import "CSAgentState.h"
#import "CSAgentFeatureType.h"
#import "CSAgentSkill.h"
#import "CSButtonLampState.h"

@protocol CSAgentStateDelegate;
@protocol CSAgentServiceStatusDelegate;
@class CSCall;

/**
 * The AgentService object is accessible from the User object,
 * providing access to a set of APIs that allow
 * application developers to implement SIP contact center agent features.
 *
 * The client application is notified about status updates on agent features
 * reported by the agent service through handlers that the
 * application has registered on the AgentService object.
 * These updates may be the result of local operations on the
 * AgentService object as well as remote changes initiated by either
 * the service/server or other end users.
 */
@interface CSAgentService : NSObject

/**
 * The delegate responsible for agent service state events.
 */
@property (nonatomic, weak) id<CSAgentStateDelegate> stateDelegate;

/**
 * The delegate responsible for agent service status events.
 */
@property (nonatomic, weak) id<CSAgentServiceStatusDelegate> statusDelegate;

/**
 * Returns list of available agent features or feature buttons administered on
 * signalling server for the registered SIP user.
 *
 * @return An array of AgentFeatures or null otherwise.
 */
@property (nonatomic, readonly) NSArray *availableAgentFeatures;

/**
 * Returns current agent information. Whenever agent work mode or configuration
 * is changed new AgentInformation object is available through
 * AgentServiceListener::onAgentInformationUpdated(AgentService, User, AgentInformation)
 * method.
 *
 * @return An AgentInformation object which provides current agent state, work mode and
 * configuration information.
 *
 * @see CSAgentState
 * @see CSAgentWorkMode
 * @throws IllegalStateException if this method is called before the agent logged in.
 */
@property (nonatomic, readonly) CSAgentInformation *agentInformation;

/**
 * Returns current agent state. The agent state change is reported via
 * AgentServiceListener#onAgentStateChanged(AgentService, User, AgentState)
 * method.
 *
 * @return An AgentState enumeration which represents agent availability.
 * @throws IllegalStateException if this method is called before the agent logged in.
 */
@property (nonatomic, readonly) CSAgentState agentState;

/**
 * Returns list of administered auxiliary work mode reason codes available for an agent to change
 * in to auxiliary work mode.
 * Note: Application developers can also use availableAgentFeatures
 * property to get full list of features available for an application.
 
 * @see CSAgentService::availableAgentFeatures
 * @return An array of auxiliary work mode reason codes as an Integers or null otherwise.
 */
@property (nonatomic, readonly) NSArray *allowedAuxiliaryWorkModeReasonCode;

/**
 * Gets an agent current work mode.
 *
 * @return An AgentWorkMode enumeration which represents agent current work mode.
 */
@property (nonatomic, readonly) CSAgentWorkMode agentWorkMode;

/**
 * Indicates whether agent service is available or not.
 *
 * @return True if agent service available. False otherwise.
 */
@property (nonatomic, readonly, getter=isAgentServiceAvailable) BOOL agentServiceAvailable;

/**
 * Returns whether the agent feature indicated by featureType is available for the application.
 *
 * @param featureType Type of agent feature.
 * @return A boolean value indicating whether the agent feature indicated by featureType is
 * available for the application.
 */
- (BOOL)isAgentFeatureAvailable: (CSAgentFeatureType) featureType;

/**
 * Updates agent feature with a personalized label given by user.
 *
 * @param label        The personalized label to be set.
 * @param agentFeature The agent feature.
 * @param handler      An object that wants to learn about result of logout operation i.e., whether it was successful.
 */
-(void)setLabel:(NSString *)label forAgentFeature:(CSAgentFeature *)agentFeature completionHandler:(void (^)(NSError *error))handler;

/**
 * Starts agent login process with the communications servers. Feedback is provided via the
 * AgentServiceCompletionHandler object.
 *
 * @param handler An object that wants to learn about result of login operation i.e., whether
 *                it was successful.
 */
- (void)loginWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Stops agent services including logout with reason code from the signalling servers.
 * Use '0' as default reason code if reason code is not available. Feedback is provided via
 * the AgentServiceCompletionHandler object.<br>
 * With reason codes, staffed agents can enter a numeric 1-digit or 2-digit code that describes
 * the reason for logging out of the system. Reason codes give call center managers information
 * about how agents spend time.
 *
 * @param reasonCode Reason code for agent logout. Minimum value - 0, Maximum value - 9,
 *                   Default value - 0. Reason code policy is administered on signalling server.
 *                   The provisioning of these reason codes are not passed down to the clients.
 *                   The agents are told by their supervisor what these codes are, and the agents
 *                   are used to enter these integer numbers.
 * @param handler    An object that wants to learn about result of logout operation i.e., whether
 *                   it was successful.
 */
-(void)logoutWithReasonCode:(NSInteger) reasonCode completionHandler:(void (^)(NSError *error)) handler;

/**
 * Current logout reason code for automatic agent logout.
 * The property is initialized with the value from AgentConfiguration and can be used for updating
 * logout reason code after startup.
 */
@property (nonatomic, getter=getAutoLogoutReasonCode, setter=setAutoLogoutReasonCode:) NSInteger autoLogoutReasonCode;

/**
 * Returns an indication as to whether the agent work mode indicated by workModeType is
 * allowed for use.
 *
 * @see CSAgentWorkMode
 * @param workMode Type of agent work mode.
 * @return A boolean value indication whether the agent work mode is allowed for use.
 */
-(BOOL)isAgentWorkModeAllowed:(CSAgentWorkMode) workMode;

/**
 * Sets agent work mode. Result is notified by callbacks defined in
 * AgentServiceCompletionHandler object. The updated work mode is notified by
 * AgentServiceListener#onAgentWorkModeChanged(AgentService, User, AgentWorkMode)
 * callback.
 *
 * @see CSAgentWorkMode
 * @param newAgentWorkMode New work mode for agent
 * @param reasonCode       The reason code in case of changing to auxiliary work mode, for other
 *                         modes use '0' as default code.
 * @param handler          An Object that wants to learn about result of setting work
 *                         mode operation i.e., whether it was successful.
 */
-(void)setAgentWorkMode:(CSAgentWorkMode) newAgentWorkMode withReasonCode: (NSInteger) reasonCode  completionHandler:(void (^)(NSError *error)) handler;

/**
 * Returns a queue statistics collection that is available to an agent, this information
 * can be used by an agent to monitor skill based queue statistics using method -[CSAgentService startMonitoringForQueueStatistics:]
 * Note: Application developers can also use AgentService#getAvailableAgentFeatures()
 * method to get full list of features available for an application.
 *
 * @return An array of CSQueueStatistics objects or null otherwise.
 */
@property (nonatomic,readonly) NSArray *queueStatisticsList;

/**
 * Returns an indication whether queue statistics monitor feature is available for particular skill or not.
 *
 * @param skillId The hunt group/skill number associated with the button.
 * @return Capability object describing whether the queue status statistics feature is available.
 */
-(CSCapability *) queueStatisticsMonitoringCapabilityForSkillId:(NSInteger) skillId;

/**
 * Starts queue statistics monitoring. It provides information about particular skill or queue
 * for the agent as administered on signalling server.
 *
 * For example: Queue statistics provides various queue statistics parameters like the number of 
 * calls in a queue, the time the oldest call has been in queue as well as alerts when 
 * particular thresholds are met or exceeded.
 * Note: Though agent login is not required to invoke monitor operation but sip user login is
 * required.
 *
 * @param queueStatistics The QueueStatistics information object for which to start monitor operation.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nill. If an error occurred it
 *        contains an object describing the error.
 */
-(void)startMonitoringForQueueStatistics:(CSQueueStatistics *) queueStatistics completionHandler:(void (^)(NSError *error)) handler;

/**
 * Stops queue statistics monitoring operation.
 *
 * @param queueStatistics The QueueStatistics information object for which to start monitor operation.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nill. If an error occurred it
 *        contains an object describing the error.
 */
-(void)stopMonitoringForForQueueStatistics:(CSQueueStatistics *) queueStatistics completionHandler:(void (^)(NSError *error)) handler;

/**
 * Sets refresh interval for queue statistics.
 * 
 * @param refreshInterval The refresh interval in seconds. Minimum value: 0 (i.e. no refresh), maximum value: 3600 (i.e. 1 hour).
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nill. If an error occurred it
 *        contains an object describing the error.
 */
- (void)setQueueStatisticsRefreshInterval:(NSInteger)refreshInterval ccompletionHandler:(void (^)(NSError *error)) handler;

/**
 * Sends the specified call work code. Result is notified via callbacks
 * defined in AgentServiceCompletionHandler object. <br>
 * When the agent is on an ACD call, at any time he or she can invoke the
 * work code feature and enter the digits (max 16 digits) for the code. <br>
 * To use call work code feature, an agent must be on an ACD call or in the After Call Work
 * (ACW) mode.
 * Example: The agent is on a call and half way through he or she realize
 * that the call is a sales call. Agent would invoke work-code feature and
 * enter 250 (if this is the number for the code). This will register in the
 * Call Management System (CMS) and record the data.
 *
 * @param callWorkCode The work code to send.
 * @param handler        An Object that wants to learn about the result of work code
 *                       send operation i.e., whether it was successful.
 */
-(void)sendCallWorkCode:(NSString *)callWorkCode completionHandler:(void (^)(NSError *error)) handler;

/**
 * Returns an indication as to whether the work code can be sent over the existing call.
 *
 * @return CSCapability object describing whether the work code can be sent over the
 * existing call.
 */
@property (nonatomic,readonly) CSCapability *sendCallWorkCodeCapability;

/**
 * Requests for supervisor assistance based on skill.
 * If supervisor assistance is requested based on skill id then new call will
 * be placed for supervisor.
 *
 * @param skillId The skill id for which supervisor assistance is required.
 * @param handler Completion handler instance that receives the result of the operation.
 *                If not provided, failure feedback cannot be provided.
 */
-(void)callSupervisor:(NSInteger)skillId completionHandler:(void (^)(CSCall *supervisorCall, NSError *error)) handler;

/**
 * Returns an indication as to whether the supervisor assistance is available based
 * on skill.
 *
 * @param skillId The skill id for which supervisor assistance is required.
 *
 * @return Capability object describing whether the supervisor assistance is available.
 */
-(CSCapability *)callSupervisorCapability:(NSInteger)skillId;

/**
 * Requests for supervisor assistance for active call.
 * If active call is in progress then existing call will go in hold state and the agent connects
 * to the skill supervisor. The caller hears nothing or music on hold but the agent and the supervisor
 * can talk with each other. After speaking with the supervisor, the agent can drop the call with
 * supervisor and return to the ACD call, set up a conference call with the supervisor and the calling party,
 * or transfer the call to the supervisor. <br>
 * Result is notified via completion handler.
 * This completion handler is invoked as soon as call with supervisor has been successfully
 * initiated, not when the call is established with the supervisor.
 *
 * @param handler Completion handler instance that receives the result of the operation.
 *               If not provided, failure feedback cannot be provided.
 */
-(void)consultSupervisor: (void (^)(CSCall *supervisorCall, NSError *error)) handler;

/**
 * Returns an indication as to whether the supervisor assistance is available for active call.
 *
 * @return Capability object describing whether the supervisor assistance is available.
 */
-(CSCapability *)consultSupervisorCapability;

/**
 * Returns an indication as to whether the change skill is available.
 *
 * @return Capability object describing whether the change skill is available.
 */
-(CSCapability *)changeSkillCapability;

/**
 * Request to add a skill to the skills assigned to an agent.
 *
 * @param skill The skill to be added.
 * @param agentId The extension of the agent the change applies to.
 * @param handler Completion handler instance that receives the result of the operation.
 *                If not provided, failure feedback cannot be provided.
 */
-(void)addSkill: (CSAgentSkill *) skill forAgentId:(NSString *) agentId completionHandler:(void (^)(CSButtonLampState lampState, NSError *error))handler;

/**
 * Request to remove (unassign) a skill that is assigned to an agent.
 *
 * @param skill The skill to be removed.
 * @param agentId The extension of the agent the change applies to.
 * @param handler Completion handler instance that receives the result of the operation.
 *                If not provided, failure feedback cannot be provided.
 */
-(void)removeSkill: (CSAgentSkill *) skill forAgentId:(NSString *) agentId completionHandler:(void (^)(CSButtonLampState lampState, NSError *error))handler;

/**
 * Enables or disables agent's forced logout override operation.
 *
 * @param handler Completion handler instance that receives the result of the operation.
 */
-(void)setOverrideForcedLogoutWithCompletionHandler:(void (^)(NSError *error)) handler;

/**
 * Returns an indication as to whether the forced logout override is available.
 *
 * @return Capability object describing whether the forced logout override is available.
 */
@property (nonatomic,readonly) CSCapability *forcedLogoutOverrideCapability;

@end

/**
 * An interface that the client application needs to implement to receive the result of an agent
 * login or logout operation and agent state updates. One or more listeners can be registered with an instance of the
 * AgentService object to retrieve updates. All of the callback methods defined in AgentLoginListener
 * interface identify the user the callback is associated with, using the 'user' argument.
 */
@protocol CSAgentStateDelegate <NSObject>

/**
 * Reports agent state changed.
 *
 * @param agentService instance of Agent service callback is associated with
 * @param agentState new agent state
 */
- (void)agentService:(CSAgentService *)agentService didChangeAgentState:(CSAgentState) agentState;

/**
 * Reports agent successfully logged-in.
 *
 * @param agentService instance of Agent service callback is associated with
 */
- (void)agentDidLogin:(CSAgentService *)agentService;

/**
 * Reports agent successfully logged-out.
 *
 * @param agentService instance of Agent service callback is associated with
 */
- (void)agentDidLogout:(CSAgentService *)agentService;

/**
 * Reports automatic agent login success.
 *
 * @param agentService Agent service instance the callback is associated with.
 */
- (void)agentAutoLoginSucceeded:(CSAgentService *)agentService;

/**
 * Reports automatic agent login failure.
 *
 * @param agentService Agent service instance the callback is associated with.
 * @param error The reason of failure.
 */
- (void)agentService:(CSAgentService *)agentService didFailToPerformAgentAutoLoginWithError:(NSError *)error;

/**
 * Reports automatic agent logout success.
 *
 * @param agentService Agent service instance the callback is associated with.
 */
- (void)agentAutoLogoutSucceeded:(CSAgentService *)agentService;

/**
 * Reports automatic agent logout failure.
 *
 * @param agentService Agent service instance the callback is associated with.
 * @param error The reason of failure.
 */
- (void)agentService:(CSAgentService *)agentService didFailToPerformAgentAutoLogoutWithError:(NSError *)error;

@end

/**
 * Represents an interface that the client application needs to implement to
 * receive the result of a requested agent operations. This handler may be
 * implemented as an anonymous class to receive initial feedback about the
 * outcome of a previously invoked operation by the client application.
 */
@protocol CSAgentServiceStatusDelegate <NSObject>

/**
 * Reports agent service become available.
 *
 * @param agentService instance of Agent service callback is associated with
 */
- (void)agentServiceDidBecomeAvailable:(CSAgentService *)agentService;

/**
 * Reports agent service become unavailable.
 *
 * @param agentService instance of Agent service callback is associated with
 */
- (void)agentServiceDidBecomeUnavailable:(CSAgentService *)agentService;

/**
 * Reports agent information updated.
 *
 * @see CSAgentInformation
 * @param agentService instance of Agent service callback is associated with
 * @param agentInformation updated agent information
 */
- (void)agentService:(CSAgentService *)agentService didUpdateAgentInformation:(CSAgentInformation *)agentInformation;

/**
 * Reports agent information updated.
 *
 * @see CSAgentWorkMode
 * @param agentService instance of Agent service callback is associated with
 * @param agentWorkMode updated agent work mode
 * @param reasonCode reason code for associated work mode
 */
- (void)agentService:(CSAgentService *)agentService didUpdateWorkMode:(CSAgentWorkMode) agentWorkMode withResonCode:(NSInteger) reasonCode;

/**
 * Sent when the entire queue statistics list is changed.
 *
 * @param agentService instance of Agent service callback is associated with
 * @param queueStatisticsList new queue statistics list 
 */
- (void)agentService:(CSAgentService *)agentService didChangeQueueStatisticsList:(NSArray *) queueStatisticsList;
/**
 * Sent when agent capabilities updated.
 *
 * @param agentService instance of Agent service callback is associated with
 */
- (void)agentDidUpdateCapabilities:(CSAgentService *)agentService;
/**
 * Sent when agent features list updated.
 *
 * @param agentService instance of Agent service callback is associated with
 */
- (void)agentDidChangeFeatureList:(CSAgentService *)agentService;

@end
