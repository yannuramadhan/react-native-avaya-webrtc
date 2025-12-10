
/* Copyright Avaya Inc. */

/**
 * Defines the list of supported Agent features buttons. This enum is applicable for all of the features
 * supported by client services, not tailored based on capabilities provisioned for an agent in
 * the network (available features).
 */
typedef NS_ENUM(NSUInteger, CSAgentFeatureType) {
	
	/**
	 * Default value if not initialized.
	 */
	CSAgentFeatureTypeUninitialized = 0,

	/**
	 * Auto-In feature is a mode which allows the agent to be available to accept subsequent
	 * Automatic Call Distribution (ACD) call right after previous call ends.
	 * <p>
	 * In summary, it is a call-answering mode in which an agent automatically receives ACD calls
	 * without pressing any button to receive subsequent ACD calls.
	 */
	CSAgentFeatureTypeAutoIn,
	
	/**
	 * Manual-In feature is a call-answering mode in which an agent must press manual-in to receive
	 * subsequent Automatic Call Distribution (ACD) call after previous call ends.
	 * <p>
	 * In summary, it is a call-answering mode in which an agent chooses manually when he or she is
	 * ready to receive next ACD call instead of automatically become available for next ACD call.
	 */
	CSAgentFeatureTypeManualIn,
	
	/**
	 * Auxiliary feature is an agents work mode which allows the agent to make him or her self
	 * temporary unavailable to receive Automatic Call Distribution (ACD) calls.
	 */
	CSAgentFeatureTypeAuxilary,
	
	/**
	 * After call work feature is an agents work mode which allows the agent to complete work
	 * associated with previous Automatic Call Distribution (ACD) call such as filling a form
	 * related to ACD call without receiving new ACD call.
	 */
	CSAgentFeatureTypeAfterCallWork,
	
	/**
	 * User to user information feature allows agents to get the user to user information (UUI)
	 * associated with the call.
	 */
	CSAgentFeatureTypeUserToUserInformation,
	
	/**
	 * Caller information feature allows agents to get the collected digits (maximum 16 digits)
	 * associated with the call.
	 */
	CSAgentFeatureTypeCallerInformation,
	
	/**
	 * Agent login feature allows agents to login to signalling server in order to receive an
	 * Automatic Call Distribution (ACD) calls. The signalling server treats logged-in agents as
	 * staffed agents.
	 */
	CSAgentFeatureTypeAgentLogin,
	
	/**
	 * Agent logout feature allows agents to logout from signalling server and will not receive any
	 * Automatic Call Distribution (ACD) calls.
	 */
	CSAgentFeatureTypeAgentLogout,
	
	/**
	 * Call Work Code(CWC) feature allows agents to type up to 16 digits to record or report
	 * customer-related information in reporting system (e.g. Call Management System CMS).
	 */
	CSAgentFeatureTypeCallWorkCode,
	
	/**
	 * Stroke counts feature allows agents to record in Call Management System (CMS) the number
	 * of times that a particular customer related event occurs. Agents can record up to nine events
	 * for each call.
	 */
	CSAgentFeatureTypeStrokeCount,
	
	/**
	 * The signalling server configuration allows it to forcefully logout an agent after a
	 * pre-configured time duration. This feature allows an agent to override the forced logout
	 * operation to prevent forced logout.
	 */
	CSAgentFeatureTypeForcedLogoutOverride,
	
	/**
	 * View statistics (VuStats) feature allows agents, supervisors, call center managers, and other
	 * users to view the statistics for agents, skills, VDNs, and trunk groups. The
	 * statistics reflect information collected since the agent logged in, since the day began, or
	 * historical data accumulated over an administered number of intervals. The information is
	 * limited to 40 characters at a time but it can be updated on demand or periodically.
	 */
	CSAgentFeatureTypeViewStatistics,
	
	/**
	 * Queue statistics feature provides statistics about particular skill or queue for an agent as
	 * administered on signalling server.
	 * In summary, this feature provides, the number of calls in a queue and the time the oldest
	 * call is in a queue.
	 */
	CSAgentFeatureTypeQueueStatistics,
	
	/**
	 * Supervisor assist feature allows agents to request for supervisor assistance based on active
	 * Automatic Call Distribution (ACD) call or the skill that agent is active on.
	 */
	CSAgentFeatureTypeSupervisorAssist,
    
	/**
	 * The Add Skill feature allows an agent or other station user to add a skill to the skills assigned to an agent.
	 * The Remove Skill feature allows the agent or other station user to remove (unassign) a skill that is assigned to an agent.
	 * The activation of these features is combined under one feature button.
	 */
	CSAgentFeatureTypeChangeAgentSkill
};
