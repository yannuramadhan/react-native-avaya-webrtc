/* Copyright Avaya Inc. */

#import "AOAudioInteraction.h"
#import "AOAttributeList.h"
#import "AOVideoInteraction.h"
#import "AOResource.h"
#import "AOService.h"

/**
 * @file AOWork.h
 * @brief Defines the AOWork class.
 */

@interface AOWork : NSObject

/**
 * Set the customer specific context, this value is available for screenpop's within Oceana Workspaces (screenpop's must be configured in Avaya Control Manager).
 */
@property (nonatomic) NSString* context;

/**
 * Sets the customer specific topic, this value is passed on to the agent within Oceana Workspaces.
 */
@property (nonatomic) NSString* topic;

/**
 * Returns an attribute list object.
 */
@property (nonatomic, readonly) AOAttributeList* createAttributeList;

/**
 * Set the work request Id for a work request to Oceana.
 * The returned value may be undefined if no work request Id is available.
 * If a work request Id has been provided by the equivalent setter, then the value provided will be returned.
 * The value provided must be a existing context Id obtained from context store, this would allow interaction context
 * and interaction schema to be associated with already existing context in context store
 */
@property (nonatomic) NSString* workRequestId;

/**
 * Set the locale to be used in the work request to Oceana.
 * The provided locale will be available in the Oceana WebRTC Engagement Designer workflows.
 * Where one potential use is to play media announcements based on the locale. (Note for this use-case,
 * the announcements must be correctly configured on Avaya Aura Media Server).
 */
@property (nonatomic) NSString* locale;

/**
 * Set the routing strategy for the work request, this will determine the resource selection strategy for any
 * interactions created.
 */
@property (nonatomic) NSString* routingStrategy;

/**
 * Set the {@link AOService} list to be used for resource selection as part of the work request.
 * If a service list is provided, attributes should not be provided via a AttributeList this will cause a work request to be rejected.
 * A channel attribute should be excluded from services in the list, as this will be ignored and the interaction type will determine the channel attribute
 *
 */
@property (nonatomic) NSMutableArray <AOService*> *services;

/**
 * Set the {@link AOResource} list to be used for resource selection as part of the work request.
 * Providing a resource list, means the work request can only be handling by a resource in the list and no one else.
 * If a resource list is provided, attributes should not be provided via a AttributeList this will cause a work request to be rejected.
 * If a service list and resource list are provided together, this will be accepted. If the work request cannot be offered to the
 * specified resource, a resource will be selected based on the service list
 *
 */
@property (nonatomic) NSMutableArray <AOResource*> *resources;

/**
 * Returns an Audio Interaction object which allows an audio interaction to be initiated.
 */
@property (nonatomic, readonly) AOAudioInteraction* createAudioInteraction;

/**
 * Returns a Video Interaction object which allows a video interaction to be initiated.
 */
@property (nonatomic, readonly) AOVideoInteraction* createVideoInteraction;

@end
