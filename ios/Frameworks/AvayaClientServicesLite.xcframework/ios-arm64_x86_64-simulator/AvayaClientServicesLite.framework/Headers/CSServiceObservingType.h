/* Copyright Avaya Inc. */

/**
 * The service observing modes a supervisor may choose to use
 * in order to monitor handling of a customer call by an agent.
 *
 */
typedef NS_ENUM(NSInteger, CSServiceObservingType) {
    
	/**
	 * The default state. Service observing is not active.
	 */
	CSServiceObservingTypeNone = 0,
	
	/**
	 * Standard Service Observing - starts in listen-only mode and can be changed to listen-talk mode and back.
	 */
	CSServiceObservingTypeBasic,
	
	/**
	 * No-talk Service Observing - starts in listen-only mode and cannot be changed to basic mode (i.e., listen and talk)
	 */
	CSServiceObservingTypeNoTalk,
	
	/**
	 * Service Observing Next Call - starts call-observing associtation for the next call handled by the agent
	 * in listen-only mode.
	 *  The supervisor is allowed to change the mode to listen and talk mode.
	 */
	CSServiceObservingTypeNextCall,
	
	/**
	 * VDN Observing by Location - enter the VDN extension and the location
	 * number on the Service Observing activation screen. The observer only starts hearing the
	 * call to the VDN when the agent in the desired location is connected. This 
	 * type will require the endpoint to prompt for the desired location to select calls
	 * to observe.  Starts in listen-only, allows change to listen-talk mode and back
	 */
	CSServiceObservingTypeByLocation
};
