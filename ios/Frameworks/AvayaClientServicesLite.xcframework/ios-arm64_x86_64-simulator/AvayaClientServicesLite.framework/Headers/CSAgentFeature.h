/* Copyright Avaya Inc. */

#import "CSAgentFeatureType.h"

/**
 * Represents the contact center agent feature or the feature button administered on
 * the contact center solution.
 */
@interface CSAgentFeature : NSObject <NSCoding>

/**
 * The unique button number for the agent feature exclusive for an application.
 */
@property (nonatomic, readonly) NSUInteger buttonNumber;

/**
 * Represents type of the agent feature.
 */
@property (nonatomic, readonly) CSAgentFeatureType agentFeatureType;

/**
 * Represents label administered for the agent feature or button.
 */
@property (nonatomic, copy) NSString *label;

/**
 * Represents contact center elite Auxiliary work mode agent feature or feature button administered
 * on signalling server.<br>
 * An agent in auxiliary work mode means he or she is not on active call but might be busy with non
 * call related work i.e. on break, in a meeting, or at lunch.<br>
 * With reason codes, staffed agents can enter a numeric 1–digit or 2–digit code that describes
 * the reason for change in work mode (to auxiliary in this case). Reason codes give call center
 * managers information about how agents spend time.<br>
 * The need for reason code is administered via a policy on signalling server.
 *
 * Represents the reason code associated with the auxiliary work mode button if administered on
 * signalling server.
 *
 */
@property (nonatomic, readonly) NSUInteger auxilaryWorkModeReasonCode;

/**
 * Represents contact center elite queue status feature or feature button administered
 * on signaling server.<br>
 * It provides information about particular skill or queue for the agent as administered on
 * signalling server. Queue status feature can provide skill information on demand or update it
 * periodically.<br>
 * For example: The number of calls in a queue and the time the oldest call is in a queue.<br>
 * Note: This feature can also be used without an agent login but post sip user login.
 *
 * The hunt group/skill number associated with the queue.
 *
 */
@property (nonatomic, readonly) NSUInteger skillId;

/**
 * Represents contact center elite view status feature or feature button administered
 * on signalling server.<br>
 * With View Status feature (VuStats), contact center agents, supervisors, call center managers,
 * and other users can view the statistics for agents, splits or skills, VDNs, and trunk groups. The
 * statistics reflect information collected since the agent logged in, since the day began, or
 * historical data accumulated over an administered number of intervals. View status feature can
 * provide information on demand or update it periodically.<br>
 * For example, for an agent object type, VuStats provides the total number of calls that an agent
 * has answered since login, the average time that the agent has spent on ACD calls, the number of
 * agents available to receive calls for a split or skill, and the percent of calls within the
 * acceptable service levels. <br>
 * For skill object types, VuStats provides skill description and performance information, such as
 * Average Speed of Answer (ASA), number of calls in a queue, and agent work states. VuStats also
 * provides the acceptable service levels or percent of calls answered within the acceptable service
 * levels for a split or skill.<br>
 * For trunk group object types, VuStats provides trunk group name and number, the average holding
 * time for an incoming or outgoing trunk calls, the number of trunks in a specified trunk group and
 * the percent of time all the trunks in a specified trunk group were busy during a specified
 * period/day.<br>
 * For Vector Directory Number (VDN) object types, VuStats provides VDN name and extension, the total
 * time agents spent talking on skill calls and direct agent calls, the number of calls that have
 * encountered a VDN, but have not been answered, abandoned, or outflowed and the time the oldest
 * call has been waiting in the VDN.<br>
 * Note: This feature can also be used without an agent login but post sip user login.
 */

@property (nonatomic, readonly) NSUInteger formatNumber;

/**
 * (VuStats) resource id associated with the view status feature button. It can be a skill (1-8000), a
 * trunk (1-2000), a Vector Directory Number (VDN) or an agent id (extension).
 */
@property (nonatomic, copy) NSString *resourceId;

@end
