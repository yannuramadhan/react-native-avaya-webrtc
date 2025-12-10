/* Copyright Avaya Inc. */

/**
 * @file AOCallDetails.h
 * @brief Defines the AOCallDetails protocol.
 */

/**
 * Supported media encryption types.
 */
typedef NS_ENUM(uint32_t, AOMediaEncryptionType) {
    /**
     * No media encryption is being done.
     */
    AOMediaEncryptionTypeNone = 0,
    
    /**
     * AES 128 SHA 1 HMAC 80 encryption is being used.
     */
    AOMediaEncryptionTypeAES128SHA1HMAC80,
    
    /**
     * AES 128 SHA 1 HMAC 32 encryption is being used.
     */
    AOMediaEncryptionTypeAES128SHA1HMAC32,
    
    /**
     * AES 256 SHA 1 HMAC 80 encryption is being used.
     */
    AOMediaEncryptionTypeAES256SHA1HMAC80,
    
    /**
     * AES 256 SHA 1 HMAC 32 encryption is being used.
     */
    AOMediaEncryptionTypeAES256SHA1HMAC32,
};

/**
 * Call-related details for a session.
 */
@protocol AOCallDetails  <NSObject>

/**
 * The local IP address used for the session.
 */
@property (nonatomic, readonly) NSString *localIPAddress;

/**
 * The local RTP receive port for the session (as per SDP offer/answer exchange).
 */
@property (nonatomic, readonly) NSUInteger localPort;

/**
 * The remote IP address used for the session.
 */
@property (nonatomic, readonly) NSString *remoteIPAddress;

/**
 * The remote RTP receive port for the session (as per SDP offer/answer exchange).
 */
@property (nonatomic, readonly) NSUInteger remotePort;

/**
 * The name of the codec being used.
 */
@property (nonatomic, readonly) NSString *codec;

/**
 * Media encryption mode for the session.
 */
@property (nonatomic, readonly) AOMediaEncryptionType mediaEncryptionType;

/**
 * Status indication for whether media is tunnelled or not.
 */
@property(nonatomic, readonly) BOOL mediaTunnelled;

/**
 * Status indication for whether tunneled media goes through proxy or not.
 */
@property(nonatomic, readonly) BOOL mediaProxied;

/**
 * RTCP encryption status for the session.
 * True if feedback RTCP packets are encrypted false otherwise.
 * If it is true RTCP packets should be decripted before reading
 * session stream details.
 */
@property (nonatomic, readonly) BOOL mediaEncrypted;

/**
 * The round-trip audio delay (in milliseconds) calculated as per RFC 3550.
 * This is the time required for an RTP packet to go from sender to receiver and back.
 */
@property (nonatomic, readonly) NSUInteger roundTripTimeMilliseconds;

@end
