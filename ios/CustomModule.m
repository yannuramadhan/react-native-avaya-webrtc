#import "CustomModule.h"
#import <React/RCTLog.h>
#import <React/RCTUIManager.h>
#import "VideoViewManager.h"


@implementation CustomModule
{
  BOOL hasListeners;
}

RCT_EXPORT_MODULE();

#pragma mark - React Native Event Emitter

- (NSArray<NSString *> *)supportedEvents {
  return @[
    @"interactionInitiating",
    @"interactionRemoteAlerting",
    @"interactionActive",
    @"interactionEnded",
    @"interactionFailed",
    @"onCallStateChanged"
  ];
}

+ (BOOL)requiresMainQueueSetup
{
  return YES;
}

- (void)startObserving {
  hasListeners = YES;
}

- (void)stopObserving {
  hasListeners = NO;
}

- (instancetype)init {
  self = [super init];
  if (self) {
    _oceanaCustomerWebVoiceVideo = [[AOOceanaCustomerWebVoiceVideo alloc] init];
    NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler);
  }
  return self;
}

void uncaughtExceptionHandler(NSException *exception) {
  NSLog(@"❌ Uncaught Exception: %@", exception.reason);
  NSLog(@"📄 Stack trace: %@", exception.callStackSymbols);
}

- (void)setupClientWithConfig:(NSDictionary *)config {
    // 1️⃣ Buat konfigurasi client
    CSClientConfiguration *clientConfig = [[CSClientConfiguration alloc] init];
    // set server/port/SIP/etc dari config dictionary
    // misal: clientConfig.acsServer = config[@"acsServer"];

    // 2️⃣ Queue delegate di main thread supaya aman untuk React Native
    dispatch_queue_t delegateQueue = dispatch_get_main_queue();

    // 3️⃣ Init client
    self.csClient = [[CSClient alloc] initWithConfiguration:clientConfig
                                                   delegate:self
                                              delegateQueue:delegateQueue];

    CSClient.logLevel = CSLogLevelDebug; // untuk log penuh di Xcode


    RCTLogInfo(@"✅ CSClient siap");
}



#pragma mark - Request token from server (async with POST)

RCT_EXPORT_METHOD(requestTokenFromServer:(NSString *)use
                  phoneNumber:(NSString *)phoneNumber
                  callingNumber:(NSString *)callingNumber
                  displayName:(NSString *)displayName
                  expiration:(NSString *)expiration
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
  NSString *tokenServerUrl = @"https://sipsignal.whnmandiri.co.id:443/token-generation-service/token/getEncryptedToken";
  NSURL *url = [NSURL URLWithString:tokenServerUrl];
  if (!url) {
    reject(@"bad_url", @"Invalid token server URL", nil);
    return;
  }

  NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
  request.HTTPMethod = @"POST";
  NSDictionary *body = @{
    @"use": use ?: @"",
    @"phoneNumber": phoneNumber ?: @"",
    @"callingNumber": callingNumber ?: @"",
    @"displayName": displayName ?: @"",
    @"expiration": expiration ?: @""
  };

  NSLog(@"[DEBUG] Request body dictionary: %@", body);

  NSError *jsonErr = nil;
  NSData *bodyData = [NSJSONSerialization dataWithJSONObject:body options:0 error:&jsonErr];
  if (jsonErr) {
    reject(@"json_error", @"Failed to create request body", jsonErr);
    return;
  }
  request.HTTPBody = bodyData;
  [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];

  NSURLSessionDataTask *task = [[NSURLSession sharedSession] dataTaskWithRequest:request
                                                               completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
    if (error) {
      reject(@"network_error", @"Request token failed", error);
      return;
    }
    if ([response isKindOfClass:[NSHTTPURLResponse class]]) {
      NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse *)response;
      NSLog(@"[DEBUG] Response status code: %ld", (long)httpResponse.statusCode);
      NSLog(@"[DEBUG] Response headers: %@", httpResponse.allHeaderFields);
    }
    NSString *rawResponse = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    NSLog(@"[DEBUG] Raw response string: %@", rawResponse);

    if (!data) {
      reject(@"no_data", @"No data returned from token server", nil);
      return;
    }
    NSError *parseErr = nil;
    id json = [NSJSONSerialization JSONObjectWithData:data options:0 error:&parseErr];
    if (parseErr) {
      // Jika gagal parsing, return string mentah
      NSString *responseString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
      resolve(responseString ?: @"");
      return;
    }
    resolve(json);
  }];
  [task resume];
}

#pragma mark - Set OCS Config (Aura Elite)
RCT_EXPORT_METHOD(setOcsConfig:(NSString *)configJson
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    @try {
        NSError *error;
        NSData *data = [configJson dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary *config = [NSJSONSerialization JSONObjectWithData:data options:0 error:&error];
        if (error) {
            reject(@"json_parse_error", @"Failed to parse config JSON", error);
            return;
        }

        RCTLogInfo(@"[CustomModule] 🔍 Parsed config: %@", config);

        self.token = config[@"token"];

        self.oceanaCustomerWebVoiceVideo = [[AOOceanaCustomerWebVoiceVideo alloc]
                                            initWithClientConfiguration:self.oceanaClientConfig];
      
        AOWebGatewayConfiguration *webConfig = [[AOWebGatewayConfiguration alloc] init];
        webConfig.webGatewayAddress = config[@"aawg_server"] ?: @"sipsignal.whnmandiri.co.id";
        webConfig.port = config[@"aawg_port"] ?: @"443";
        webConfig.isSecure = YES;
        webConfig.webGatewayUrlPath = config[@"aawg_url_path"] ?: @"csa/resources/tenants/default";

        // Logging properti
        NSArray *keys = @[@"webGatewayAddress", @"port", @"isSecure", @"webGatewayUrlPath"];
        for (NSString *key in keys) {
            id value = [webConfig valueForKey:key];
            RCTLogInfo(@"[CustomModule] %@ = %@", key, value);
        }
      
        self.oceanaClientConfig = [[AOClientConfiguration alloc] init];
        self.oceanaClientConfig.webGatewayConfiguration = webConfig;

        // Jika menggunakan Oceana (Aura Elite tidak pakai AOConfiguration)
        self.oceanaClientConfig.configuration = nil;

        // 3️⃣ Buat SDK instance
        self.oceanaCustomerWebVoiceVideo = [[AOOceanaCustomerWebVoiceVideo alloc] initWithClientConfiguration:self.oceanaClientConfig];

      
        self.clientConfig = webConfig;

        RCTLogInfo(@"[CustomModule] 🚀 Aura Elite SDK initialized and connecting...");

        resolve(@(YES));

    } @catch (NSException *exception) {
        reject(@"exception", exception.reason, nil);
    }
}



#pragma mark - Start Audio Call
RCT_EXPORT_METHOD(startAudioCall:(NSString *)destination
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    RCTLogInfo(@"[CustomModule] 📞 startAudioCall called with destination: %@", destination);

    @try {
        if (!self.clientConfig) {
            reject(@"no_config", @"Client configuration not set", nil);
            return;
        }
        if (!self.token) {
            reject(@"no_token", @"Token not set", nil);
            return;
        }

        // 1️⃣ Buat audio interaction
        AOWork *work = [self.oceanaCustomerWebVoiceVideo createWork];
        self.audioInteraction = [work createAudioInteraction];
        self.audioInteraction.delegate = self;
        RCTLogInfo(@"Delegate set: %@", self.audioInteraction.delegate);

        // 2️⃣ Set platform
        self.audioInteraction.platformType = AOPlatFormType_ELITE;

        // 3️⃣ Set token dan destination
        self.audioInteraction.authorizationToken = self.token;
        self.audioInteraction.destinationAddress = destination;

        // 5️⃣ Start call
        [self.audioInteraction start];


        RCTLogInfo(@"[CustomModule] ✅ Audio call started");

        resolve(@(YES));

    } @catch (NSException *exception) {
        reject(@"CALL_ERROR", exception.reason, nil);
    }
}

RCT_EXPORT_METHOD(startVideoCall:(NSString *)destination
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
  @try {
    if (!self.clientConfig) {
      reject(@"no_config", @"Client configuration not set", nil);
      return;
    }
    if (!self.token) {
      reject(@"no_token", @"Token not set", nil);
      return;
    }

    AOWork *work = [self.oceanaCustomerWebVoiceVideo createWork];
    self.videoInteraction = [work createVideoInteraction];
    self.videoInteraction.delegate = self;
    self.videoInteraction.connectionListenerDelegate = self;

    // 1. set token
    self.videoInteraction.authorizationToken = self.token;

    // 2. set platform type SEBELUM start
    [self.videoInteraction setPlatformType:AOPlatFormType_ELITE];

    // 3. set camera + view
    self.videoDevice = self.videoInteraction.videoDevice;
    // [self.videoDevice setVideoCaptureOrientation:AOVideoCaptureOrientation_LandscapeOnly];
    // [self.videoDevice setVideoCapturePreference:AOVideoCapturePreference_Min];
    [self.videoDevice setVideoCaptureResolutionWithCaptureOrientation:
            AOVideoCapturePreference_Min
            orientationPreference:AOVideoCaptureOrientation_LandscapeOnly];
    
    [self.videoDevice selectCamera:AOCameraTypeFront];
    [self.videoInteraction muteVideo:FALSE];

    if (self.pendingLocalView) [self.videoDevice setLocalView:self.pendingLocalView];
    if (self.pendingRemoteView) [self.videoDevice setRemoteView:self.pendingRemoteView];

    // 4. set tujuan
    self.videoInteraction.destinationAddress = destination;

    [self.videoInteraction enableVideo:YES];

    // 5. terakhir: start
    [self.videoInteraction start];


    resolve(@(YES));
  }
  @catch (NSException *e) {
    reject(@"OCS_CONFIG_ERROR", e.reason, nil);
  }
}

RCT_EXPORT_METHOD(attachLocalView:(nonnull NSNumber *)reactTag
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
  dispatch_async(dispatch_get_main_queue(), ^{
    UIView *view = [self.bridge.uiManager viewForReactTag:reactTag];
    self.pendingLocalView = view;

    if (self.videoDevice && view) {
      [self.videoDevice setLocalView:view];
      NSLog(@"✅ LocalView attached: %@", view);
      resolve(@(YES));
    } else {
      NSLog(@"⚠️ videoDevice belum siap, simpan dulu LocalView");
      resolve(@(NO));
    }
  });
}

RCT_EXPORT_METHOD(attachRemoteView:(nonnull NSNumber *)reactTag
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
  dispatch_async(dispatch_get_main_queue(), ^{
    UIView *view = [self.bridge.uiManager viewForReactTag:reactTag];
    self.pendingRemoteView = view;

    if (self.videoDevice && view) {
      [self.videoDevice setRemoteView:view];
      NSLog(@"✅ RemoteView attached: %@", view);
      resolve(@(YES));
    } else {
      NSLog(@"⚠️ videoDevice belum siap, simpan dulu RemoteView");
      resolve(@(NO));
    }
  });
}



#pragma mark - End Call
RCT_EXPORT_METHOD(endCall:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    @try {
      if (self.audioInteraction) {
          [self.audioInteraction end]; // delegate akan kirim "ended"
      }
      if (self.videoInteraction) {
          [self.videoInteraction end]; // delegate akan kirim "ended"
      }
        resolve(@(YES));
    } @catch (NSException *e) {
        reject(@"END_CALL_ERROR", e.reason, nil);
    }
}


#pragma mark - Toggle Mute
RCT_EXPORT_METHOD(toggleMute:(BOOL)mute
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
  @try {
    if (self.audioInteraction) {
      [self.audioInteraction muteAudio:mute];
    }
    if (self.videoInteraction) {
      [self.videoInteraction muteAudio:mute];
    }
    resolve(@(YES));
  }
  @catch (NSException *e) {
    reject(@"MUTE_ERROR", e.reason, nil);
  }
}

#pragma mark - Toggle Speaker
RCT_EXPORT_METHOD(toggleSpeaker:(BOOL)enable
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
  @try {
    AVAudioSession *session = [AVAudioSession sharedInstance];
    [session setCategory:AVAudioSessionCategoryPlayAndRecord
             withOptions:enable ? AVAudioSessionCategoryOptionDefaultToSpeaker : 0
                   error:nil];
    [session setActive:YES error:nil];
    resolve(@(YES));
  }
  @catch (NSException *e) {
    reject(@"SPEAKER_ERROR", e.reason, nil);
  }
}

#pragma mark - Toggle Camera
RCT_EXPORT_METHOD(toggleCamera:(BOOL)enable
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
  @try {
    if (self.videoInteraction) {
      [self.videoInteraction muteVideo:!enable]; // ✅ true kalau disable
      NSLog(@"📷 Camera %@", enable ? @"enabled" : @"disabled");
      resolve(@(enable));
    } else {
      reject(@"NO_VIDEO_INTERACTION", @"videoInteraction is nil", nil);
    }
  }
  @catch (NSException *e) {
    reject(@"CAMERA_TOGGLE_ERROR", e.reason, nil);
  }
}

#pragma mark - Switch Camera
RCT_EXPORT_METHOD(switchCamera:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
  @try {
    if (self.videoDevice) {
      // toggle manual kamera
      AOCameraType target = (self.currentCamera == AOCameraTypeFront) ? AOCameraTypeBack : AOCameraTypeFront;
      [self.videoDevice selectCamera:target];
      self.currentCamera = target;

      NSLog(@"🔄 Switched camera to %@", target == AOCameraTypeFront ? @"FRONT" : @"BACK");
      resolve(@"Camera switched");
    } else {
      reject(@"CAMERA_ERROR", @"videoDevice not available", nil);
    }
  }
  @catch (NSException *e) {
    reject(@"SWITCH_CAMERA_ERROR", e.reason, nil);
  }
}




#pragma mark - Send DTMF
RCT_EXPORT_METHOD(sendDtmf:(NSString *)digit
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
  @try {
    AODTMFTone tone = [self getDtmfToneFromString:digit];
    if (tone == -1) {
      RCTLogWarn(@"📟 Invalid DTMF digit: %@", digit);
      reject(@"DTMF_ERROR", [NSString stringWithFormat:@"Digit DTMF tidak valid: %@", digit], nil);
      return;
    }

    BOOL sent = NO;
    if (self.audioInteraction) {
      RCTLogInfo(@"📟 Sending DTMF to AudioInteraction: %@", digit);
      [self.audioInteraction sendDTMF:tone];
      sent = YES;
    } else if (self.videoInteraction) {
      RCTLogInfo(@"📟 Sending DTMF to VideoInteraction: %@", digit);
      [self.videoInteraction sendDTMF:tone];
      sent = YES;
    }

    if (sent) {
      resolve([NSString stringWithFormat:@"DTMF sent: %@", digit]);
    } else {
      reject(@"DTMF_ERROR", @"Tidak ada panggilan aktif", nil);
    }
  }
  @catch (NSException *e) {
    reject(@"DTMF_ERROR", e.reason, nil);
  }
}


- (AODTMFTone)getDtmfToneFromString:(NSString *)digit {
  if ([digit isEqualToString:@"0"]) return AODTMFToneZero;
  if ([digit isEqualToString:@"1"]) return AODTMFToneOne;
  if ([digit isEqualToString:@"2"]) return AODTMFToneTwo;
  if ([digit isEqualToString:@"3"]) return AODTMFToneThree;
  if ([digit isEqualToString:@"4"]) return AODTMFToneFour;
  if ([digit isEqualToString:@"5"]) return AODTMFToneFive;
  if ([digit isEqualToString:@"6"]) return AODTMFToneSix;
  if ([digit isEqualToString:@"7"]) return AODTMFToneSeven;
  if ([digit isEqualToString:@"8"]) return AODTMFToneEight;
  if ([digit isEqualToString:@"9"]) return AODTMFToneNine;
  if ([digit isEqualToString:@"*"]) return AODTMFToneStar;
  if ([digit isEqualToString:@"#"]) return AODTMFTonePound;
  return -1; // invalid
}


- (void)sendCallEventToReact:(NSString *)status {
    if (hasListeners) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self sendEventWithName:@"onCallStateChanged" body:@{@"status": status}];
        });
    }
}


// Audio interaction delegate
- (void)interactionInitiating {
  RCTLogInfo(@"📞 interactionInitiating called");
  if (hasListeners) {
    [self sendEventWithName:@"interactionInitiating" body:@{}];
    [self sendCallEventToReact:@"ringing"];
  }
}
- (void)interactionRemoteAlerting {
  if (hasListeners) {
    [self sendEventWithName:@"interactionRemoteAlerting" body:@{}];
  }
}
- (void)interactionActive {
  if (hasListeners) {
    [self sendEventWithName:@"interactionActive" body:@{}];
    [self sendCallEventToReact:@"connected"];
    // ✅ attach remote view setelah benar-benar aktif
    dispatch_async(dispatch_get_main_queue(), ^{
      if (self.pendingRemoteView && self.videoDevice) {
        [self.videoDevice setRemoteView:self.pendingRemoteView];
        NSLog(@"✅ RemoteView attached after Active: %@", self.pendingRemoteView);
      }
      if (self.pendingLocalView && self.videoDevice) {
        [self.videoDevice setLocalView:self.pendingLocalView];
        NSLog(@"✅ LocalView re-attached after Active: %@", self.pendingLocalView);
      }
    });
  }
}
- (void)interactionEnded {
  if (hasListeners) {
    [self sendEventWithName:@"interactionEnded" body:@{}];
    [self sendCallEventToReact:@"ended"];
  }
}
- (void)interactionFailed:(NSError *)error {
  if (hasListeners) {
    [self sendEventWithName:@"interactionFailed" body:@{@"error": error.localizedDescription}];
    [self sendCallEventToReact:@"error"];
  }
}

#pragma mark - AOAudioInteractionDelegate
- (void)audioInteractionDidStart:(AOAudioInteraction *)interaction {
    RCTLogInfo(@"📞 Audio call started");
}

- (void)audioInteraction:(AOAudioInteraction *)interaction didChangeState:(AOInteractionState)state {
    RCTLogInfo(@"📞 Audio call state changed: %ld", (long)state);
}

#pragma mark - AOVideoInteractionDelegate
- (void)videoInteractionDidStart:(AOVideoInteraction *)interaction {
    RCTLogInfo(@"📹 Video call started");
}

- (void)videoInteraction:(AOVideoInteraction *)interaction didChangeState:(AOInteractionState)state {
    RCTLogInfo(@"📹 Video call state changed: %ld", (long)state);
}

- (void)interactionVideoEnabledStatusChanged:(BOOL)isEnabled {
    RCTLogInfo(@"🎥 Video enabled status: %@", isEnabled ? @"YES" : @"NO");
}


#pragma mark - AOConnectionListenerDelegate
- (void)connectionEstablished {
    RCTLogInfo(@"✅ Connection established");
}

- (void)connectionLostWithError:(NSError *)error {
    RCTLogInfo(@"❌ Connection lost: %@", error.localizedDescription);
}


// Connection listener delegate
- (void)interactionServiceConnected {}
- (void)onInteractionServiceConnecting {}
- (void)onInteractionServiceDisconnectedWithError:(NSError *)error {
  if (hasListeners) {
    [self sendEventWithName:@"interactionFailed" body:@{@"error": error.localizedDescription}];
  }
}

@end
