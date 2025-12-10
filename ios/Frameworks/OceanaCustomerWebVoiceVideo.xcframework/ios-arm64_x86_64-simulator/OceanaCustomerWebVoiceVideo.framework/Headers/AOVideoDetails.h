/* Copyright Avaya Inc. */

#import "AOCallDetails.h"

/**
 * @file AOVideoDetails.h
 * @brief Defines the AOVideoDetails class.
 */

/**
 * Video channel common statistics receive.
 */
@interface AOVideoStatistics : NSObject

/**
 * Target sent/received frame rate in frames per second.
 */
@property (nonatomic, readonly) NSUInteger targetFrameRate;

/**
 * Actual sent/received frame rate in frames per second.
 */
@property (nonatomic, readonly) NSUInteger actualFrameRate;

/**
 * Width of the sent/received video stream.
 */
@property (nonatomic, readonly) NSUInteger width;

/**
 * Height of the sent/received video stream.
 */
@property (nonatomic, readonly) NSUInteger height;

/**
 * Actual send/receive side jitter buffer size in milliseconds.
 *
 * In VoIP, a jitter buffer is a shared data area where video packets can be
 * collected, stored, and sent to the video processor in evenly spaced intervals.
 * Variations in packet arrival time, called jitter, can occur because of
 * network congestion, timing drift, or route changes. The jitter buffer,
 * which is located at the receiving end of the video connection, intentionally
 * delays the arriving packets so that the end user experiences a clear connection
 * with very little video delays.
 */
@property (nonatomic, readonly) NSUInteger jitterBufferSizeMilliseconds;

/**
 * Target sent/received bit rate per second.
 */
@property (nonatomic, readonly) NSUInteger targetBitrate;

/**
 * Actual sent/received bit rate per second.
 */
@property (nonatomic, readonly) NSUInteger actualBitrate;

/**
 * Total number of packets sent/received.
 */
@property (nonatomic, readonly) NSUInteger packetCount;

/**
 * Total number of bytes sent/received.
 */
@property (nonatomic, readonly) NSUInteger byteCount;

/**
 * Number of key frames locally requested (receive direction), or remotely requested (send direction).
 */
@property (nonatomic, readonly) NSUInteger keyFrameCount;

/**
 * Total number of packets lost in transmit/receive direction.
 */
@property (nonatomic, readonly) NSUInteger packetLossTotal;

/**
 * Fraction of packets lost in transmit/receive direction.
 */
@property (nonatomic, readonly) NSUInteger packetLossFraction;

@end

/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

/**
 * Video channel common statistics for send.
 */
@interface AOVideoTransmitStatistics : AOVideoStatistics

/**
 * 802.1p Layer 2 priority tag, if set.
 */
@property (nonatomic, readonly) NSUInteger RTP8021pTag;

/**
 * DSCP tag, if set.
 */
@property (nonatomic, readonly) NSUInteger RTPDSCPTag;

@end

/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

/**
 * Video related statistics for session.
 */
@interface AOVideoDetails : NSObject<AOCallDetails>

/**
 * Payload type
 */
@property (nonatomic, readonly) NSUInteger payloadType;

/**
 * Video channel id associated with media engine resources.
 */
@property (nonatomic, readonly) NSUInteger channelId;

/**
 * Receive stream statistics.
 */
@property (nonatomic, readonly) AOVideoStatistics *receiveStatistics;

/**
 * Send stream statistics.
 */
@property (nonatomic, readonly) AOVideoTransmitStatistics *transmitStatistics;

@end
