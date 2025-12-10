/* Copyright Avaya Inc. */

/**
 * Represents all supported agent states for contact cetner elite agent
 *
 * It is read only information exposed by signaling server, although looks
 * similar to agent work mode which can be updated by client. AgentState is
 * usually consumed by UI layer to show agent avalability
 */
typedef NS_ENUM(NSUInteger, CSAgentState) {
    
    /**
     * Default state after agent logout, no work mode.
     */
    CSAgentStateNone = 0,
    
    /**
     * The Available state indicates that the agent is available for accepting
     * an Automatic Call Distribution (ACD) call.
     */
    CSAgentStateAvailable,
    
    /**
     * The On call state indicates that the agent is currently busy on an
     * Automatic Call Distribution (ACD) call or Direct Agent Call (DAC).
     */
    CSAgentStateOnCall,
    
    /**
     * The agent is engaged in work associated with a call, but not on a call,
     * The agent is unavailable to receive Automatic Call Distribution (ACD) call
     * but can receive non ACD calls.
     */
    CSAgentStateAfterCallWork,
    
    /**
     * The agent is invloved in non ACD work, is on break, in a meeting, or
     * at lunch. To receive ACD call the agent presses the manual in or auto-in button
     */
    CSAgentStateAuxiliary
};
