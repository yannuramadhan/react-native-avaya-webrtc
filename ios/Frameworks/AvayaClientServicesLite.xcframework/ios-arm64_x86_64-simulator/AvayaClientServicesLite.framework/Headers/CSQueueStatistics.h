/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@protocol CSQueueStatisticsDelegate;

/**
 * Queue statistics feature provides statistics about particular skill.
 */
@interface CSQueueStatistics : NSObject

/**
 * The delegate responsible for handling queue statistics related events.
 */
@property (nonatomic, weak) id<CSQueueStatisticsDelegate> delegate;

/**
 * A Boolean value indicating  whether queue monitoring operation is active or not for queue statistics feature.
 */
@property (nonatomic, readonly, getter=isActive) BOOL active;
/**
 * The button number associated with the queue for an application.
 */
@property (nonatomic, readonly) NSInteger buttonNumber;
/**
 * The hunt group/skill number associated with the queue.
 */
@property (nonatomic, readonly) NSInteger skillId;
/**
 * The name of the skill associated with this queue.
 */
@property (nonatomic, readonly) NSString *skillName;
/**
 * The number of calls in the queue.
 */
@property (nonatomic, readonly) NSInteger queuedCallsNumber;
/**
 * A Boolean value indicating whether number of calls waiting in queue has reached or exceeded the threshold.
 */
@property (nonatomic, readonly, getter=isQueuedCallsThresholdReached) BOOL queuedCallsThresholdReached;
/**
 * The time of oldest call in queue in seconds.
 */
@property (nonatomic, readonly) NSInteger oldestQueueTime;
/**
 * A Boolean value indicating whether the oldest call in queue has reached or exceeded the maximum call queued threshold time.
 */
@property (nonatomic, readonly, getter=isQueueTimeThresholdReached) BOOL queueTimeThresholdReached;

@end

/**
 * Describes methods that are implemented by the delegate of a @c CSQueueStatistics.
 */
@protocol CSQueueStatisticsDelegate <NSObject>

/**
 * Sent when the queue monitoring operation has been started or stopped
 *
 * @param queueStatistics The queue statistics sending the message.
 * @param isActive The queue statistics status.
 */
- (void)queueStatistics:(CSQueueStatistics *)queueStatistics didChangeActiveStatus:(BOOL)isActive;

/**
 * Sent  when the skill name has been changed.
 *
 * @param queueStatistics The queue statistics sending the message.
 * @param skillName The new skill name.
 */
- (void)queueStatistics:(CSQueueStatistics *)queueStatistics didChangeSkillName:(NSString *)skillName;

/**
 * Sent when queue statistics information is updated.
 *
 * @param queueStatistics The queue statistics sending the message.
 */
- (void)queueStatisticsDidUpdateInformation:(CSQueueStatistics *)queueStatistics;

@end
