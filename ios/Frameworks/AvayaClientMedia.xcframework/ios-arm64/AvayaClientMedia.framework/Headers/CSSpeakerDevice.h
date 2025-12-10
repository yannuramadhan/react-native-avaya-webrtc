//
//  CSSpeakerDevice.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-21.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSSpeakerDevice_h
#define clientsdk_CSSpeakerDevice_h
#import <Foundation/Foundation.h>
#import "CSAudioDevice.h"

@interface CSSpeakerDevice : CSAudioDevice

/**
 * Default initializer. Unavailable.
 */
- (instancetype)init NS_UNAVAILABLE;
/**
 * Constructs speaker device of specific type
 */
- (instancetype)initWithType:(CSAudioDeviceType)type;

@end
#endif
