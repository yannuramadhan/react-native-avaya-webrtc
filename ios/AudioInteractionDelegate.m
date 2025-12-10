#import "AudioInteractionDelegate.h"

@implementation AudioInteractionDelegate

// Contoh metode callback yang dipanggil oleh SDK.  
// Karena protokol delegate tidak ada, kamu harus pasang method dengan nama yang sama seperti dokumentasi.

// Interaction initiating
- (void)interactionInitiating {
    if (self.onInteractionInitiating) {
        self.onInteractionInitiating();
    }
}

// Interaction remote alerting
- (void)interactionRemoteAlerting {
    if (self.onInteractionRemoteAlerting) {
        self.onInteractionRemoteAlerting();
    }
}

// Interaction active
- (void)interactionActive {
    if (self.onInteractionActive) {
        self.onInteractionActive();
    }
}

// Interaction ended
- (void)interactionEnded {
    if (self.onInteractionEnded) {
        self.onInteractionEnded();
    }
}

// Interaction failed
- (void)interactionFailed:(NSError *)error {
    if (self.onInteractionFailed) {
        self.onInteractionFailed(error);
    }
}

// Audio mute status changed
- (void)interactionAudioMuteStatusChanged:(BOOL)muted {
    if (self.onInteractionAudioMuteStatusChanged) {
        self.onInteractionAudioMuteStatusChanged(muted);
    }
}

// Discard complete
- (void)discardComplete {
    if (self.onDiscardComplete) {
        self.onDiscardComplete();
    }
}

// Hold complete
- (void)holdComplete {
    if (self.onHoldComplete) {
        self.onHoldComplete();
    }
}

// Unhold complete
- (void)unholdComplete {
    if (self.onUnholdComplete) {
        self.onUnholdComplete();
    }
}

// Remote hold complete
- (void)remoteHoldComplete {
    if (self.onRemoteHoldComplete) {
        self.onRemoteHoldComplete();
    }
}

// Remote unhold complete
- (void)remoteUnholdComplete {
    if (self.onRemoteUnholdComplete) {
        self.onRemoteUnholdComplete();
    }
}

// Interaction quality changed (as example using NSInteger)
- (void)onInteractionQualityChanged:(NSInteger)quality {
    if (self.onInteractionQualityChanged) {
        self.onInteractionQualityChanged(quality);
    }
}

@end
