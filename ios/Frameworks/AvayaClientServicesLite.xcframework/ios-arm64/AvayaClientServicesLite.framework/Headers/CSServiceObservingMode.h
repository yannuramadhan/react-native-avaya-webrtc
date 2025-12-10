/* Copyright Avaya Inc. */

/**
 * All supported service observing mode.
 *
 */
typedef NS_ENUM(NSInteger, CSServiceObservingMode) {
    
	/**
	 * The default state. Service observing is not active.
	 */
	CSServiceObservingModeNone = 0,
	
	/**
	 * Listen-only service observing mode.
	 */
	CSServiceObservingModeListenOnly,
	
	/**
	 * Listen-talk service observing mode
	 */
	CSServiceObservingModeListenTalk,
	
	/**
	 * Coaching service observing mode.
	 * This mode is used when Service Observing Coaching is activated on a service observed call.	
	 */
	CSServiceObservingModeCoaching
};
