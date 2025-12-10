/* Copyright Avaya Inc. */

/**
 * All supported button lamp state.
 */
typedef NS_ENUM(NSInteger, CSButtonLampState) {

	/**
	 * Default button lamp state.
	 */
	CSButtonLampStateNone = 0,

	/**
	 * Dark button lamp state.
	 */
	CSButtonLampStateDark,

	/**
	 * Steady button lamp state.
	 */
	CSButtonLampStateSteady,

	/**
	 * Broken flutter lamp state.
	 */
	CSButtonLampStateBrokenFlutter,

	/**
	 * Wink button lamp state.
	 */
	CSButtonLampStateWink,

	/**
	 * Flash button lamp state.
	 */
	CSButtonLampStateFlash
};
