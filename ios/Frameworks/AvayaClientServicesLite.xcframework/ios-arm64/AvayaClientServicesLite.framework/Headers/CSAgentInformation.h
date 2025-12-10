/* Copyright Avaya Inc. */

#import "CSAgentFeature.h"
#import "CSAgentWorkMode.h"
#import "CSButtonLampState.h"

/**
 * Represents policy how agents provide reason codes while performing various agent operations.
 * Reason code policy is administered on contact center solution.
 */
typedef NS_ENUM(NSUInteger, CSAgentReasonCodeMode) {
	
	/**
	 * Reason code is not required for agent operation.
	 */
	CSAgentReasonCodeModeNone = 0,
	
	/**
	 * Reason code is requested but not forced. If reason code not provided then
	 * default values will be used to complete agent operation.
	 */
	CSAgentReasonCodeModeOptional,
	
	/**
	 * Reason code is must for completing agent operation.
	 */
	CSAgentReasonCodeModeForced
};

/**
 * Represents a policy that is configured on contact center solution that whether
 * the agent will be forced to log out at a certain time or the agent is overriding the forced logout.
 */
typedef NS_ENUM(NSUInteger, CSAgentLogoutOverrideType) {
	
    /**
     * Agent is not configured for forced logout.
     */
    CSAgentLogoutOverrideTypeUndefined = 0,
    
	/**
	 * Agent is not configured for forced logout.
	 */
	CSAgentLogoutOverrideTypeNone,
	
	/**
	 * Agent is configured to logout after after certain period of time.
	 */
	CSAgentLogoutOverrideTypeTimedLogout
	
};

/**
 * Represents the policy used to describe the length of reason codes
 * used by agents for logout and work mode change operations.
 */
typedef NS_ENUM(NSUInteger, CSAgentReasonCodeLength) {

    /**
	 * Reason code length is not defined.
	 */
	CSAgentReasonCodeLengthNotAvailable = 0,

    /**
	 * Reason code is administered to use single digit i.e range is between 0-9.
	 */
	CSAgentReasonCodeLengthSingleDigit,

    /**
	 Reason code is administered to use double digits i.e range is between 0-99.
	 */
	CSAgentReasonCodeLengthDoubleDigit

};

/**
 * Represents an agent information sent from signalling server to the
 * Represents the policies used to describe the use of reason codes for pending logout.
 */
typedef NS_ENUM(NSUInteger, CSPendingLogoutReason) {
	
	/**
	 * Reason code is not defined.
	 */
	CSPendingLogoutReasonUndefined = 0,

	/**
	 * A reason code for logout pending is "timed-logout".
	 */
	CSPendingLogoutReasonTimed,
	
	/**
	 * A reason code for logout pending is "forced-logout".
	 */
	CSPendingLogoutReasonForced,
	
	/**
	 * A reason code for logout pending is "agent-requested".
	 */
	CSPendingLogoutReasonRequested
};

/**
 * Represents an agent information sent from contact center solution to the
 * registered agent's application.
 */
@interface CSAgentInformation : NSObject

/**
 * Agents logical extension as a URI, also known as agent loginId on contact center solution.
 */
@property (nonatomic, readonly) NSString *agentAddress;

/**
 * Information about agent's current work mode.
 */
@property (nonatomic, readonly) CSAgentWorkMode currentAgentWorkMode;

/**
 * Information about agent's pending work mode.
 */
@property (nonatomic, readonly) CSAgentWorkMode pendingAgentWorkMode;

/**
 * Reason code used by an agent to change to current work mode.
 */
@property (nonatomic, readonly) NSInteger reasonCode;

/**
 * Reason code used by an agent to change to pending work mode.
 */
@property (nonatomic, readonly) NSInteger pendingReasonCode;

/**
 * Indicates whether there is a direct agent call in the agent's queue or
 * not. It is set to 0 (i.e. false) if there is no call in the queue. It is
 * set to 1 (i.e. true) if there is one or more calls in the queue.
 * Returns '0' if there is no direct agent call in the queue.
 * Returns '1' if there is one or more calls in the queue.
 *
 * @remarks For Communication Manager 7 onwards it returns the value of actual
 * number of direct agent calls in queue.
 */
@property (nonatomic, readonly) NSInteger numberOfDirectAgentCallsQueued;

/**
 * Indicates whether the configured threshold for interruptible auxiliary
 * work mode has been reached for an agent in an interruptible auxiliary
 * state. A Boolean value indicating whether the InterruptibleAuxThreshold has reached.
 *
 * Returns a boolean value indicating whether the configured threshold for interruptible
 * auxiliary work mode has been reached for an agent in an interruptible auxiliary state.<br>
 * Interruptible auxiliary Work allows the contact center solution to notify agents that are in the
 * auxiliary work mode with an interruptible reason code (RC) that they should become available
 * because one of the configured thresholds has been exceeded.
 * For example: The thresholds could be "More than X calls are in a queue waiting for an agent".
 * In this case contact center solution activates interruptible aux threshold reached to true if the
 * number of calls in a queue exceeds the threshold.
 */
@property (nonatomic, readonly, getter=isInterruptibleAuxThresholdReached) BOOL interruptibleAuxThresholdReached;


/**
 * Agents skill set information.It is numeric list of agent skill set that
 * the agent is configured with. The maximum number of skills that can be
 * configured per agent is 120 and the skill numbers can range from 1 to
 * 8000.
 */
@property (nonatomic, strong) NSMutableArray *skills;

/**
 * Provides information about whether a logout reason code is required
 * (optional or forced) for agent logout operation.
 */
@property (nonatomic, readonly) CSAgentReasonCodeMode logoutReasonCodeEnforcement;

/**
 * Provides information about reason code length that is required for agent logout operation
 * i.e. whether a single digit (range 0-9) or double digit (range 0-99) reason code required
 * to complete logout operation.
 */
@property (nonatomic, readonly) CSAgentReasonCodeLength logoutReasonLength;

/**
 * Provides information about whether an auxiliary reason code is required
 * (optional or forced)for agent to change auxiliary work mode.
 */
@property (nonatomic, readonly) CSAgentReasonCodeMode auxiliaryReasonCodeEnforcement;

/**
 * Provides information about reason code length that is required to change to auxiliary work
 * mode i.e. whether a single digit (range 0-9) or double digit (range 0-99) reason code required
 * to change work mode.
 */
@property (nonatomic, readonly) CSAgentReasonCodeLength auxiliaryReasonLength;

/**
 * True if voice messaging status updates will indicate the status for the agent instead of the physical station
 * for as long as the agent is logged in
 */
@property (readonly, getter=isMwiForAgent) BOOL mwiForAgent;

/**
 * Indicates if there were voicemail messages waiting for the agent at login
 */
@property (readonly, getter=isMessagesWaitingAtLogin) BOOL messagesWaitingAtLogin;

/**
 * A Boolean value indicating whether the auto-answer feature is enabled.
 */
@property (readonly, getter=isAutoAnswerEnabled) BOOL autoAnswer;

/**
 * Represents whether the agent has a forced logout time administered.
 * (None | Timed logout)
 */
@property (nonatomic, readonly, getter=agentLogoutOverrideType) CSAgentLogoutOverrideType logoutOverrideType;

/**
 * A boolean flag indicating whether the agent is currently overriding the
 * forced logout.
 */
@property (nonatomic, readonly, getter=isAgentOverridingForcedLogout) BOOL agentOverridingForcedLogout;

/**
 * If there is a forced logout time defined for agent, then at time, the agent will be
 * forced to logout.
 *
 * Returns agent logout override time. If an agent is configured to logout at certain time this
 * is the time that an agent will logout. If the agent is still on an ACD call when the forced
 * agent logout time is reached, the agent is put into the pending logout mode.
 * The forced logout occurs when the call is disconnected.
 * Note:
 * The forced logout time the client gets from the server has the format HH:MM in the server time.
 * The time stored here is the time of the next forced logout assuming the client is in
 * the same timezone as the server.
 */
@property (nonatomic, readonly) NSDate *agentLogoutOverrideTime;

/**
 * A boolean flag indicating whether the agent logout is pending.
 */
@property (nonatomic, readonly, getter=isAgentLogoutPending) BOOL agentLogoutPending;

/**
 * Represents the information about pending logout reason code.
 */
@property (nonatomic, readonly) CSPendingLogoutReason pendingLogoutReasonCode;

@end
