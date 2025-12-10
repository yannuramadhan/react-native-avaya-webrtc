/* Copyright Avaya Inc. */

/**
 * @file AOSessionEnum.h
 * @brief Defines the Session enums.
 */

/**
 * Interaction types.
 */
typedef NS_ENUM(NSInteger, AOInteractionType) {
    AOAUDIO_ONLY,
    AOVIDEO
};

/**
* Client Platform types
*/
typedef NS_ENUM(NSInteger, AOPlatformType) {
    AOPlatFormType_OCEANA,
    AOPlatFormType_ELITE
};


/**
 * Interaction states.
 */
typedef NS_ENUM(NSInteger, AOInteractionState) {
    AOInteractionStateIdle,              // Uninitialized.
    AOInteractionStateInitiating,        // Interaction initiated (outgoing only). No response from far-end has been received.
    AOInteractionStateRemoteAlerting,    // Interaction is alerting remotely (outgoing session).
    AOInteractionStateEstablished,       // Interaction has been established and is active (not held).
    AOInteractionStateEnding,            // Interaction is ending.
    AOInteractionStateEnded,             // Interaction ended by far-end, or end request has been responded to by the remote party.
    AOInteractionStateFailed,            // Failed.
};

/**
 * DTMF tone types.
 */
typedef NS_ENUM(NSUInteger, AODTMFTone) {
    AODTMFToneZero = 0,
    AODTMFToneOne,
    AODTMFToneTwo,
    AODTMFToneThree,
    AODTMFToneFour,
    AODTMFToneFive,
    AODTMFToneSix,
    AODTMFToneSeven,
    AODTMFToneEight,
    AODTMFToneNine,
    AODTMFToneStar,
    AODTMFTonePound,
    AODTMFToneA,
    AODTMFToneB,
    AODTMFToneC,
    AODTMFToneD
};
