/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Defines the list of supported features. This enum is for all of the features
 * supported by the signaling engine, not tailored based on capabilities provisioned
 * for the user in the network. It is also not tailored based on which features are
 * client invokable via -[CSUser invokeFeature:].
 */
typedef NS_ENUM(NSInteger, CSFeatureType) {
	/**
	 * The uninitialized (or unknown) feature type.
	 */
	CSFeatureTypeUninitialized = 0,

	/**
	 * Send All Calls is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that is used to activate/deactivate coverage path for calls coming in
	 * at a CM station (extension). In summary, the feature activates/de-activates
	 * call coverage at CM. Depending on how CM extension is provisioned, the calls
	 * may be covered to another extension, voice mail, etc. Incoming priority calls
	 * are not affected by the feature's status, that is, incoming priority calls
	 * do not get covered as a result of activating the SAC feature.
	 *
	 * It should be noted that the SAC feature FNU may be used to apply to local user's
	 * CM extension as well as to a third party CM extension (avaya-cm-destination).
	 */
	CSFeatureTypeSendAllCalls,

	/**
	 * Call Forward All is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that is used to activate/deactivate call forwarding for calls coming in
	 * at a CM station (extension). In summary, the feature
	 * activates/de-activates call forwarding at CM.
	 *
	 * It should be noted that the call forward all feature FNU may be used to apply to
	 * local user's CM extension as well as to a third party CM extension (avaya-cm-destination).
	 */
	CSFeatureTypeForwardAllCalls,

	/**
	 * Call Forward Busy No Answer is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that is used to activate/deactivate call forwarding for incoming calls when busy
	 * or when not answered by the user at a CM station (extension). In summary, the feature
	 * activates/de-activates call forwarding at CM.
	 *
	 * It should be noted that this feature FNU may be used to apply to
	 * local user's CM extension as well as to a third party CM extension (avaya-cm-destination).
	 */
	CSFeatureTypeForwardBusyNoAnswerCalls,

	/**
	 * Exclusion is an AST-I feature that uses a 'Feature-Named-URI' (FNU) that is
	 * used to activate/deactivate exclusion by a bridged line appearance user.
	 * In summary, the feature activates/de-activates exclusion at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeExclusion,

	/**
	 * EC500 is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that is used to activate/deactivate EC 500 cellular call extension
	 * at a CM station (extension). In summary, the feature
	 * activates/de-activates EC500 feature at CM station.
	 */
	CSFeatureTypeEC500,

	/**
	 * Extend Call is an AST-I feature that uses a 'Feature-Named-URI' (FNU) that
	 * is used to extend a call to the off-PBX destinations associated with the
	 * extension.
	 * In summary, the feature invokes extend call at the CM station
	 * associated with the user.
	 */
	CSFeatureTypeExtendCall,

	/**
	 * Call Park is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows the user to place the current call in the call park state
	 * so it can be retrieved from another phone.
	 * In summary, the feature invokes call park at the CM station
	 * associated with the user.
	 */
	CSFeatureTypeCallPark,

	/**
	 * Call Unpark is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows the user to retrieve a call parked at another extension.
	 *
	 * In summary, the feature invokes call unpark at the CM station
	 * associated with the user.
	 */
	CSFeatureTypeCallUnpark,

	/**
	 * Auto Callback is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user who placed a call to a busy or unanswered telephone
	 * to be called back automatically when the called telephone becomes available
	 * to receive a call.
	 *
	 * In summary, the feature activates/de-activates auto-callback at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeAutoCallback,

	/**
	 * Whisper Page is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows the user to to make and receive whisper pages. A whisper page
	 * is an announcement sent to another extension that is active on a call where only
	 * the person on the extension hears the announcement; any other parties on the call
	 * cannot hear the announcement.
	 *
	 * In summary, the feature activates/de-activates whisper page at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeWhisperPage,

	/**
	 * Group Call Pickup is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows the user to answer a call that is ringing in the user's
	 * pickup group.
	 *
	 * In summary, the feature invokes group call pickup at the CM station
	 * associated with the user.
	 */
	CSFeatureTypeGroupCallPickup,

	/**
	 * Extended Group Call Pickup is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to answer calls directed to another call pickup group.
	 *
	 * In summary, the feature invokes extended group call pickup at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeExtendedGroupCallPickup,

	/**
	 * Calling Party Number Block is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to block the sending of the calling party number for
	 * one call.
	 *
	 * In summary, the feature invokes calling party number block at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeCallingPartyNumberBlock,

	/**
	 * Calling Party Number Unblock is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to deactivate calling party number (CSN) blocking and
	 * allows the CSN to be sent for a single call.
	 *
	 * In summary, the feature invokes calling party number unblock at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeCallingPartyNumberUnblock,

	/**
	 * One-Touch Recording is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to start and end the recording of an in-progress
	 * conversation using the AUDIX system recording facility.
	 *
	 * In summary, the feature invokes one-touch recording at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeOneTouchRecording,

	/**
	 * Directed Call Pickup is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows the user to answer a call ringing at another extension without
	 * having to be a member of a pickup group.
	 *
	 * In summary, the feature invokes directed call pickup at the CM
	 * station associated with the user.
	 */
	CSFeatureTypeDirectedCallPickup,

	/**
	 * Priority Call is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to place priority calls or change an existing call to
	 * a priority call.
	 *
	 * In summary, the feature invokes priority call at the CM station
	 * associated with the user.
	 */
	CSFeatureTypePriorityCall,

	/**
	 * Enhanced Call Forwarding is feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to configure call forwarding for internal or
	 * external calls with seprate settings for busy, no reply, and
	 * unconditional forwarding. In summary, the feature invokes enhanced
	 * call forwarding at the CM station associated with the user.
	 */
	CSFeatureTypeEnhancedCallForwarding,
	
	/**
	 * Busy Indicator is a feature that allows one to observe another extension
	 * for its availability.
	 * When the far end destination goes off-hook, CM notifies
	 * the same via \<feature name ="busy-indicator" status="on"/\>
	 * When the far end destination goes on-hook, CM notifies
	 * the same via \<feature name ="busy-indicator" status="off"/\>
	 */
	CSFeatureTypeBusyIndicator,
	
	/**
	 * Autodial is a feature button which can be configured as a speed-dial
	 * either by Admin or the user. User can edit the autodial Label
	 * and/or number.
	 *
	 * User can always edit the destinationLabel
	 * User can edit the destinationExtension if the 
	 * isDestinationExtensionEditable flag is true.
	 */
	CSFeatureTypeAutodial,
	
	/**
	 * Hunt Group Busy Position is a feature button which allows user to opt-in/opt-out
	 * from Hunt Group calls.
	 * If your admin have configured your extension as a member of a hunt group,
	 * you will be eligible to receive calls made to that hunt group.
	 * When you don't want to receive calls on that hunt group, the feature needs to be enabled.
	 * When feature is enabled, user will not receive any calls on that Hunt Group.
	 * When feature is disabled, user will start recieving the calls on that hunt group again.
	 *
	 * User can also set the personalized label for the button.
	 */
	CSFeatureTypeHuntGroupBusyPosition,

    /**
     * The Team Button feature allows the user to view the state of another
     * station and allow the user to answer any calls which are actively
     * ringing on that station. The button can also be used as a speed dial
     * to call the monitored station when it is idle.
     */
    CSFeatureTypeTeamButton,

#if !TARGET_OS_IPHONE
	/**
	 * The Crisis Alert feature allows the admin to configure crisis alert button for the watcher (attendant) user.
	 * When a user makes a call to emergency services, the watcher is alerted.
	 * The watcher should acknowledge the alert.
	 */
	CSFeatureTypeCrisisAlert,
#endif
	


    /**
     * Malicious Call Trace (MCT) feature lets a user to notify SM about a malicious call when
     * a user invokes the Malicious Call Trace feature on an incoming call.
     */
    CSFeatureTypeMaliciousCallTrace,
 
    /**
     * The No Hold Conference feature allows a user to set up a conference call without interrupting the current
     * conversation. The called party is automatically added to the conference as soon as they answer.
     */
    CSFeatureTypeNoHoldConference,
	
    /**
     * Limit Number of Concurrent Calls feature: Users can use this to limit the number of concurrent calls at
     * a station to one call, where normally multiple call appearances can terminate at the station.
     */
    CSFeatureTypeLimitCalls,
	
	/**
	 * The Service Observing (SO) features allow a supervisor or other authorized user to use their telephone to
	 * activate an observing session towards a station, an agent LoginID or VDN to listen in and
	 * possibly talk on calls received by the station/agent or VDN for the purposes of quality control and training.
	*/
	CSFeatureTypeServiceObserving,

    /**
     * This feature enables forwarding when the user's extension is busy. It uses the Forward Number destination or,
     * if set, the Forward on Busy Number destination. If the user has call appearance buttons programmed,
     * the system will not treat them as busy until all the call appearance buttons are in use.
     * Note that this feature differs from the feature FORWARD_BUSY_NO_ANSWER_CALLS since the latter one serves
     * invocation of both busy and not answered cases (for platforms where the two cases can not be supported separately).
     */
    CSFeatureTypeForwardBusyCall,

    /**
     * This feature enables forwarding when the user's extension is not answered within the period defined by their No Answer Time.
     * It uses the Forward Number destination or, if set, the Forward on Busy Number destination.
     * Note that this feature differs from the feature FORWARD_BUSY_NO_ANSWER_CALLS since the latter one serves
     * invocation of both busy and not answered cases (for platforms where the two cases can not be supported separately).
     */
    CSFeatureTypeForwardNoAnswerCalls,

    /**
     * This feature sets the number to which the user's calls are redirected. This can be an internal or external number.
     * This feature does not activate forwarding; it only sets the number for the forwarding destination.
     * This number is used for all forward types; Forward Unconditional, Forward on Busy and Forward on No Answer,
     * unless the user has a separate Forward on Busy Number set for forward on busy and forward on no answer functions.
     */
    CSFeatureTypeForwardNumber,

    /**
     * This feature sets the number to which the user's calls are forwarded when Forward on Busy or Forward on No Answer are on.
     * If no Forward on Busy Number is set, those functions use the Forward Number.
     * This feature does not activate the forwarding, it only sets the number for the forwarding destination.
     */
    CSFeatureTypeForwardBusyNumber,

    /**
     * This feature can be used to place the user, his current call and any calls he has on hold into a conference.
     * If the call on hold is an existing conference, the user and any current call are added to that conference.
     */
    CSFeatureTypeAutoConference,

    /**
     * This feature cancels all forms of forwarding on the user's extension including "Follow Me" and "Do Not Disturb".
     */
    CSFeatureTypeCancelAllForwarding,

    /**
     * This feature allows the user to define voicemail box usage.
     * When feature is enabled: the user's voicemail mailbox is used to answer calls which ring unanswered or arrive when the user is busy.
     * When feature is disabled: the user's voicemail mailbox box is not being used to answer calls. This does not disable the voicemail mailbox
     * being used as the target for other functions such as call recording or messages forwarded from other mailboxes.
     */
    CSFeatureTypeForwardToVoiceMail,

    /**
     * This feature logs the user off the phone or soft client he is currently logged in.
     * Results in regular logout process for the environments/platforms which do not let the user to logout without this
     * feature assigned.
     */
    CSFeatureTypeStationLogout,

    /**
     * This feature allows to call an extension and have the call automatically answered on speaker phone after 3 beeps.
     * The called extension must support a handsfree speaker. If the extension does not have a handsfree microphone then the user
     * must use the handset if he wants to talk. If the extension is not free when called, the call is presented as a normal call
     * on a call appearance button if available.
     */
    CSFeatureTypeDirectDial,

    /**
     * This feature allows the user to move the active call to either a simultaneous client or twinned destination.
     */
    CSFeatureTypeMoveCall,

    /**
     * This feature allows the user to retrieve the active call from either a simultaneous client or twinned destination.
     */
    CSFeatureTypeRetrieveCall,
    
    /**
     * When this feature is active, incoming calls will ring on the user's own extension and another extension within the same IP Office.
     * This feature can only be configured by the IP Office administrator.
     * User will not be able to activate/deactivate this feature.
     */
    CSFeatureTypeInternalTwinning
};
