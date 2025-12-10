#import <Foundation/Foundation.h>
#import <React/RCTBridgeModule.h>
#import <React/RCTEventEmitter.h>
#import <AvayaClientServicesLite/AvayaClientServicesLite.h>
#import <OceanaCustomerWebVoiceVideo/AOAudioInteraction.h>
#import <OceanaCustomerWebVoiceVideo/AOVideoInteraction.h>
#import <OceanaCustomerWebVoiceVideo/AOVideoDevice.h>
#import <OceanaCustomerWebVoiceVideo/AOWork.h>
#import <OceanaCustomerWebVoiceVideo/AOSessionEnum.h>
#import <OceanaCustomerWebVoiceVideo/AOOceanaCustomerWebVoiceVideo.h>
#import <OceanaCustomerWebVoiceVideo/AOClientConfiguration.h>


@interface CustomModule : RCTEventEmitter <RCTBridgeModule, AOAudioInteractionDelegate, AOVideoInteractionDelegate, AOConnectionListenerDelegate>

@property(nonatomic, strong) CSClient *csClient;
@property(nonatomic, strong) NSString *token;
@property(nonatomic, strong) AOWebGatewayConfiguration *webConfig;
@property(nonatomic, strong) CSClientConfiguration *clientConfig;
@property(nonatomic, weak) id<AOAudioInteractionDelegate> audioDelegate;
@property(nonatomic, strong) AOAudioInteraction *audioInteraction;
@property(nonatomic, strong) AOVideoInteraction *videoInteraction;
@property(nonatomic, strong) AOVideoDevice *videoDevice;
@property(nonatomic, strong) AOOceanaCustomerWebVoiceVideo *oceanaCustomerWebVoiceVideo;
@property(nonatomic, strong) AOClientConfiguration *oceanaClientConfig;
@property (nonatomic, assign) AOCameraType currentCamera;
@property (nonatomic, strong) UIView *pendingLocalView;
@property (nonatomic, strong) UIView *pendingRemoteView;

@end
