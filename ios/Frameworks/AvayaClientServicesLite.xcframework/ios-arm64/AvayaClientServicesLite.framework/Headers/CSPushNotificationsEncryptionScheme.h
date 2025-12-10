/* Copyright Avaya Inc. */

typedef NS_ENUM(NSInteger, CSPushNotificationsEncryptionScheme) {

	/**
	 * This represents encryption scheme "AES-128/ECB/PKCS5Padding".
	 */
	CSPushNotificationsEncryptionSchemeAES128ECBPKCS5Padding,
	/**
	 * This represents encryption scheme "AES-128/CBC/PKCS5Padding".
	 */
	CSPushNotificationsEncryptionSchemeAES128CBCPKCS5Padding,
	/**
	 * This represents encryption scheme "AES-256/CBC/PKCS5Padding".
	 */
	CSPushNotificationsEncryptionSchemeAES256CBCPKCS5Padding
};
