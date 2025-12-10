/* Copyright Avaya Inc. */

#import <AvayaClientServicesLite/CSActiveParticipant.h>
#import <AvayaClientServicesLite/CSAudioDetails.h>
#import <AvayaClientServicesLite/CSBasicShape.h>
#import <AvayaClientServicesLite/CSCall.h>
#import <AvayaClientServicesLite/CSCallFeatureService.h>
#import <AvayaClientServicesLite/CSCallForwardingStatus.h>
#import <AvayaClientServicesLite/CSCallLogItem.h>
#import <AvayaClientServicesLite/CSCallLogParticipant.h>
#import <AvayaClientServicesLite/CSCallLogService.h>
#import <AvayaClientServicesLite/CSCallPickupAlertParameters.h>
#import <AvayaClientServicesLite/CSCallPickupAlertStatus.h>
#import <AvayaClientServicesLite/CSCallPickupFeatureRinger.h>
#import <AvayaClientServicesLite/CSCallService.h>
#import <AvayaClientServicesLite/CSCameraControl.h>
#import <AvayaClientServicesLite/CSCertificateInfo.h>
#import <AvayaClientServicesLite/CSChat.h>
#import <AvayaClientServicesLite/CSChatMessage.h>
#import <AvayaClientServicesLite/CSCircleShape.h>
#import <AvayaClientServicesLite/CSClient.h>
#import <AvayaClientServicesLite/CSClientConfiguration.h>
#import <AvayaClientServicesLite/CSClipboardEvent.h>
#import <AvayaClientServicesLite/CSCollaboration.h>
#import <AvayaClientServicesLite/CSCollaborationService.h>
#import <AvayaClientServicesLite/CSConference.h>
#import <AvayaClientServicesLite/CSConferenceSlideViewer.h>
#import <AvayaClientServicesLite/CSConferenceMobileLink.h>
#import <AvayaClientServicesLite/CSConferenceRoomSystemInformation.h>
#import <AvayaClientServicesLite/CSConferenceSlide.h>
#import <AvayaClientServicesLite/CSConnectionPolicy.h>
#import <AvayaClientServicesLite/CSContact.h>
#import <AvayaClientServicesLite/CSContactBoolField.h>
#import <AvayaClientServicesLite/CSContactDoubleField.h>
#import <AvayaClientServicesLite/CSContactEmailAddressField.h>
#import <AvayaClientServicesLite/CSContactField.h>
#import <AvayaClientServicesLite/CSContactIMAddressField.h>
#import <AvayaClientServicesLite/CSContactPhoneField.h>
#import <AvayaClientServicesLite/CSContactService.h>
#import <AvayaClientServicesLite/CSContactStringField.h>
#import <AvayaClientServicesLite/CSCollaborationDetails.h>
#import <AvayaClientServicesLite/CSEditableContactBoolField.h>
#import <AvayaClientServicesLite/CSEditableContactDoubleField.h>
#import <AvayaClientServicesLite/CSEditableContactEmailAddressField.h>
#import <AvayaClientServicesLite/CSContactField.h>
#import <AvayaClientServicesLite/CSEditableContactIMAddressField.h>
#import <AvayaClientServicesLite/CSEditableContactPhoneField.h>
#import <AvayaClientServicesLite/CSContactService.h>
#import <AvayaClientServicesLite/CSContactStringField.h>
#import <AvayaClientServicesLite/CSContentSharing.h>
#import <AvayaClientServicesLite/CSCredentialProvider.h>
#import <AvayaClientServicesLite/CSDataRetrievalWatcher.h>
#import <AvayaClientServicesLite/CSDefines.h>
#import <AvayaClientServicesLite/CSDroppedParticipant.h>
#import <AvayaClientServicesLite/CSEditableContact.h>
#import <AvayaClientServicesLite/CSEnhancedCallForwardingStatus.h>
#import <AvayaClientServicesLite/CSError.h>
#import <AvayaClientServicesLite/CSFeatureInvocationParameters.h>
#import <AvayaClientServicesLite/CSFeatureStatusParameters.h>
#import <AvayaClientServicesLite/CSFeatureType.h>
#import <AvayaClientServicesLite/CSIdentified.h>
#import <AvayaClientServicesLite/CSKeyboardEvent.h>
#import <AvayaClientServicesLite/CSLibraryDocument.h>
#import <AvayaClientServicesLite/CSLibraryManager.h>
#import <AvayaClientServicesLite/CSLibrarySharing.h>
#import <AvayaClientServicesLite/CSLocalContactConfiguration.h>
#import <AvayaClientServicesLite/CSMeetingMediaType.h>
#import <AvayaClientServicesLite/CSMeetingMinutes.h>
#import <AvayaClientServicesLite/CSMessage.h>
#import <AvayaClientServicesLite/CSMessageBodyPart.h>
#import <AvayaClientServicesLite/CSMessageDeliveryDetails.h>
#import <AvayaClientServicesLite/CSMessageWaitingStatus.h>
#import <AvayaClientServicesLite/CSMessagingAddressValidation.h>
#import <AvayaClientServicesLite/CSMessagingAttachment.h>
#import <AvayaClientServicesLite/CSMessagingConversation.h>
#import <AvayaClientServicesLite/CSMessagingSearchConversation.h>
#import <AvayaClientServicesLite/CSMessagingEnums.h>
#import <AvayaClientServicesLite/CSMessagingLeaveConversationResponse.h>
#import <AvayaClientServicesLite/CSMessagingLimits.h>
#import <AvayaClientServicesLite/CSMessagingParticipant.h>
#import <AvayaClientServicesLite/CSMessagingQuery.h>
#import <AvayaClientServicesLite/CSMessagingService.h>
#import <AvayaClientServicesLite/CSMinuteMessage.h>
#import <AvayaClientServicesLite/CSMouseEvent.h>
#import <AvayaClientServicesLite/CSMaxSupportedVideoResolutionsCapability.h>
#import <AvayaClientServicesLite/CSParticipant.h>
#import <AvayaClientServicesLite/CSPendingParticipant.h>
#import <AvayaClientServicesLite/CSPhysicalAddress.h>
#import <AvayaClientServicesLite/CSPresence.h>
#import <AvayaClientServicesLite/CSPresenceConfiguration.h>
#import <AvayaClientServicesLite/CSPresenceListSubscription.h> 
#import <AvayaClientServicesLite/CSAgentFeature.h>
#import <AvayaClientServicesLite/CSAgentInformation.h>
#import <AvayaClientServicesLite/CSAgentService.h>
#import <AvayaClientServicesLite/CSAgentWorkMode.h>

#import <AvayaClientServicesLite/CSIPOfficeConfiguration.h>
#ifdef INCLUDE_WATCHER_REQUEST
#import <AvayaClientServicesLite/CSPresenceWatcherRequest.h>
#endif
#import <AvayaClientServicesLite/CSRegistrationGroup.h>
#import <AvayaClientServicesLite/CSRenderingBlock.h>
#import <AvayaClientServicesLite/CSScreenSharingListener.h>
#import <AvayaClientServicesLite/CSSettingsFileParser.h>
#import <AvayaClientServicesLite/CSShape.h>
#import <AvayaClientServicesLite/CSSharingBlock.h>
#import <AvayaClientServicesLite/CSSharingDisplay.h>
#import <AvayaClientServicesLite/CSSignalingServer.h>
#import <AvayaClientServicesLite/CSSignalingServerGroup.h>
#import <AvayaClientServicesLite/CSSIPUserConfiguration.h>
#import <AvayaClientServicesLite/CSSlide.h>
#import <AvayaClientServicesLite/CSSlider.h>
#import <AvayaClientServicesLite/CSSliderSlide.h>
#import <AvayaClientServicesLite/CSUnifiedPortalConferencingConfiguration.h>
#import <AvayaClientServicesLite/CSUnifiedPortalConfiguration.h>
#import <AvayaClientServicesLite/CSUnifiedPortalResources.h>
#import <AvayaClientServicesLite/CSUnifiedPortalMeetingInfo.h>
#import <AvayaClientServicesLite/CSUnifiedPortalService.h>
#import <AvayaClientServicesLite/CSUser.h>
#import <AvayaClientServicesLite/CSUserConfiguration.h>
#import <AvayaClientServicesLite/CSUserCredential.h>
#import <AvayaClientServicesLite/CSVersion.h>
#import <AvayaClientServicesLite/CSVideoChannel.h>
#import <AvayaClientServicesLite/CSVideoResolutionPreference.h>
#import <AvayaClientServicesLite/CSVideoResolutionCapability.h>
#import <AvayaClientServicesLite/CSVideoLayout.h>
#import <AvayaClientServicesLite/CSVideoUserConfiguration.h>
#import <AvayaClientServicesLite/CSVirtualRoom.h>
#import <AvayaClientServicesLite/CSVoiceMessagingService.h>
#import <AvayaClientServicesLite/CSVoiceMessagingStatusParameters.h>
#import <AvayaClientServicesLite/CSWhiteboard.h>
#import <AvayaClientServicesLite/CSWhiteboardSurface.h>
#import <AvayaClientServicesLite/CSWhiteboardText.h>
#import <AvayaClientServicesLite/CSLineAppearance.h>
#import <AvayaClientServicesLite/CSSecurityPolicyConfiguration.h>
#import <AvayaClientServicesLite/CSSpaceService.h>
#import <AvayaClientServicesLite/CSSpaceParticipant.h>
#import <AvayaClientServicesLite/CSExportService.h>

#if TARGET_OS_IPHONE
// iOS specific functionality
#import <AvayaClientServicesLite/CSIOSScreenSharingView.h>
#import <AvayaClientServicesLite/CSIOSWhiteboardCanvas.h>
#import <AvayaClientServicesLite/CSPushNotificationConfiguration.h>
#import <AvayaClientServicesLite/CSPushNotificationsEncryptionScheme.h>
#import <AvayaClientServicesLite/CSPushNotificationService.h>
#else
// OS X specific functionality
#import <AvayaClientServicesLite/CSSharingApplicationWindow.h>
#import <AvayaClientServicesLite/CSOSXScreenSharingView.h>
#import <AvayaClientServicesLite/CSPresentationSlideCanvas.h>
#import <AvayaClientServicesLite/CSPresentationSlidesListener.h>
#import <AvayaClientServicesLite/CSWhiteboardCanvas.h>
#endif

// Media engine

#if __has_warning("-Wobjc-property-assign-on-object-type")
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-property-assign-on-object-type"
#endif

#import <AvayaClientMedia/CSMediaServicesProvider.h>

#if TARGET_OS_IPHONE
#import <AvayaClientMedia/CSVideoCapturerIOS.h>
#import <AvayaClientMedia/CSVideoRendererIOS.h>
#else
#import <AvayaClientMedia/CSVideoCapturerOSX.h>
#import <AvayaClientMedia/CSVideoRendererOSX.h>
#endif

#if __has_warning("-Wobjc-property-assign-on-object-type")
#pragma clang diagnostic pop
#endif
