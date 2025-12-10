/******************************************************************************/
/*                                                                            */
/* Copyright Avaya Inc.                                                       */
/*                                                                            */
/******************************************************************************/

#ifndef clientsdk_CSLevelListener_h
#define clientsdk_CSLevelListener_h
#import <Foundation/Foundation.h>

/**
 * Audio file player notification interface
 */
@protocol CSLevelListener

/**
 * Notifies about level changes
 * @param level new level
 */
- (void)onLevel:(int)level;

@end


#endif // clientsdk_CSLevelListener_h
