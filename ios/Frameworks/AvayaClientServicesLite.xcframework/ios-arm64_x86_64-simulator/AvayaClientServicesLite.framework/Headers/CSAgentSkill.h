/* Copyright Avaya Inc. */

@interface CSAgentSkill : NSObject

/**
 * Skill id that can range from 1 to 8000.
 */
@property (nonatomic, readonly) NSInteger skillId;

/**
 * The level number. The valid range is 0 to 16.
 * The server doesn't provide the level number, so csdk fills it as 0 by default.
 * When the Skill is created by client and will be used for Add/Remove skill request:
 * 1-16 mean that the skill is being added,
 * 0 means that the skill is being removed and doesn't need a skill level input.
 */
@property (nonatomic, readonly) NSInteger skillLevel;

/**
 * Represents whether this skill is active on current agent or not.
 */
@property (nonatomic, readonly, getter=isActive) BOOL active;

/**
 * Represents whether supervisor assistance is available for current agent or not.
 */
@property (nonatomic, readonly, getter=isSupervisorAssistanceAvailable) BOOL supervisorAssistanceAvailable;

/**
 * Constructs an CSAgentSkill object from the specified parameters.
 *
 * This constructor must be used to create a new skill object before calling AgentService.RemoveSkill method.
 * Skill level will be set to 0.
 *
 * @param skillId The skill number.
 */
- (instancetype)initWithSkillId:(NSInteger) skillId;

/**
 * Constructs an CSAgentSkill object from the specified parameters.
 *
 * This constructor must be used to create a new skill object before calling the AgentService.AddSkill method.
 *
 * @param skillId The skill number.
 * @param skillLevel The level number for the skill..
 */
- (instancetype)initWithSkillId:(NSInteger) skillId
                     skillLevel:(NSInteger) skillLevel;

@end
