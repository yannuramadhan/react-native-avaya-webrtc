/******************************************************************************/
/*                                                                            */
/* Copyright Avaya Inc.                                                       */
/*                                                                            */
/******************************************************************************/

#ifndef clientsdk_AUDIOMUTELISTENER_H_
#define clientsdk_AUDIOMUTELISTENER_H_

#import <Foundation/Foundation.h>
#import "CSAudioMuteDeviceType.h"

@protocol CSAudioMuteListener
 
/**
 * Notificates about mute status change
 * @param deviceType type of audio device, generated event
 * @param enabled true if mute is enabled
 */
- (void)onMute:(CSAudioMuteDeviceType)deviceType enabled:(BOOL)enabled;
 
@end

#endif
