/* Copyright Avaya Inc. */

/**
 * All supported agent work modes for contact center Elite Agent.
 *
 */
typedef NS_ENUM(NSInteger, CSAgentWorkMode) {
    
	/**
	 * Default state. No work mode.
	 */
	CSAgentWorkModeNone = 0,
	
	/**
	 * The auto-in mode indicates that the agent is available for an Automatic
	 * Call Distribution (ACD) call. When the call ends, the agent is
	 * immediately available for another ACD call based on the administered call
	 * distribution method. The agent does not have to press any button to
	 * receive another ACD call.
	 */
	CSAgentWorkModeAutoIn,
	
	/**
	 * The manual-in mode indicates that the agent is available for an Automatic
	 * Call Distribution (ACD) call. When the call ends, the agent automatically
	 * enters the AFTER_CALL_WORK mode. While in AFTER_CALL_WORK mode, the agent
	 * is unavailable to receive ACD calls. When AFTER_CALL_WORK ends, the agent
	 * presses manual-in to receive another ACD call.
	 */
	CSAgentWorkModeManualIn,
	
	/**
	 * The After call work mode indicates that the agent is engaged in work associated with an
	 * Automatic Call Distribution (ACD) call such as filling a form related to the ACD call, but
	 * not on a call. The agent is unavailable to receive an ACD calls but can receive non-ACD calls.
	 */
	CSAgentWorkModeAfterCallWork,
	
	/**
	 * The auxiliary work mode indicates that the agent is involved in non ACD work, is on break,
	 * in a meeting, or at lunch. To receive ACD calls, the agent presses the manual-in or auto-in
	 * button.
	 */
	CSAgentWorkModeAuxilary
};
