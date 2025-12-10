#import <Foundation/Foundation.h>
#import <OceanaCustomerWebVoiceVideo/AOAudioInteraction.h>
@interface AudioInteractionDelegate : NSObject <AOAudioInteractionDelegate>

// Definisikan blocks supaya React Native atau caller bisa handle callback ini:
@property(nonatomic, copy) void (^onInteractionInitiating)(void);
@property(nonatomic, copy) void (^onInteractionRemoteAlerting)(void);
@property(nonatomic, copy) void (^onInteractionActive)(void);
@property(nonatomic, copy) void (^onInteractionEnded)(void);
@property(nonatomic, copy) void (^onInteractionFailed)(NSError *error);
@property(nonatomic, copy) void (^onInteractionAudioMuteStatusChanged)(BOOL muted);
@property(nonatomic, copy) void (^onDiscardComplete)(void);
@property(nonatomic, copy) void (^onHoldComplete)(void);
@property(nonatomic, copy) void (^onUnholdComplete)(void);
@property(nonatomic, copy) void (^onRemoteHoldComplete)(void);
@property(nonatomic, copy) void (^onRemoteUnholdComplete)(void);
@property(nonatomic, copy) void (^onInteractionQualityChanged)(NSInteger quality);

@end
