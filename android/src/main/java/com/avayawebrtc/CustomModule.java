package com.avayawebrtc;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.modules.core.DeviceEventManagerModule;
import com.facebook.react.uimanager.UIManagerModule;
import com.facebook.react.uimanager.NativeViewHierarchyManager;
import com.facebook.react.bridge.UiThreadUtil;
import com.facebook.react.uimanager.UIManagerHelper;


import com.avaya.ocs.Services.Work.Enums.InteractionError;
import com.avaya.ocs.Services.Work.Enums.PlatformType;
import com.avaya.ocs.OceanaCustomerWebVoiceVideo;
import com.avaya.ocs.Config.ClientConfiguration;
import com.avaya.ocs.Config.Config;
import com.avaya.ocs.Config.WebGatewayConfiguration;
import com.avaya.ocs.Services.Device.Video.VideoDevice;
import com.avaya.ocs.Services.Work.Enums.AudioDeviceError;
import com.avaya.ocs.Services.Work.Enums.AudioDeviceType;
import com.avaya.ocs.Services.Work.Enums.DTMFTone;
import com.avaya.ocs.Services.Work.Work;
import com.avaya.ocs.Services.Work.Interactions.AudioInteraction;
import com.avaya.ocs.Services.Work.Interactions.Listeners.OnAudioDeviceChangeListener;
import com.avaya.ocs.Services.Device.Video.Enums.CallQuality;
import com.avaya.ocs.Services.Device.Video.Enums.CameraType;
import com.avaya.ocs.Services.Work.Interactions.Listeners.AudioInteractionListener;
import com.avaya.ocs.Services.Work.Interactions.Listeners.InteractionListener;
import com.avaya.ocs.Services.Device.Video.VideoSurfaceView;
import com.avaya.ocs.Services.Device.Video.Enums.VideoSurfaceDirection;
import com.avaya.ocs.Services.Device.Video.Enums.VideoSurfaceStyle;
import com.avaya.ocs.Services.Device.Video.Enums.VideoCapturePreference;
import com.avaya.ocs.Services.Device.Video.Enums.VideoCaptureOrientation;

import android.content.SharedPreferences;
import android.content.Context;
import android.media.AudioManager;
import android.app.Activity;
import android.app.Application;
import android.util.Log;
import android.view.ViewGroup;
import android.os.Handler;
import android.os.Looper;
import android.view.View;
import android.view.WindowManager;
import android.widget.TextView;
import android.graphics.Color;
import android.view.LayoutInflater;
import android.view.ViewTreeObserver;
import android.widget.FrameLayout;
import android.view.ViewTreeObserver;

import java.util.Iterator;
import java.util.List;
import java.util.logging.Level;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.lang.reflect.Field;

import org.json.JSONObject;


public class CustomModule extends ReactContextBaseJavaModule {

    private static OceanaCustomerWebVoiceVideo oceanaCustomerWebVoiceVideo;
    private static Application app; // Simpan Application Context untuk digunakan nanti
    private String lastToken; // Simpan token terakhir yang diterima
    private AudioInteraction currentAudioInteraction;
    private FrameLayout videoContainer;
    private FrameLayout pendingContainer = null;
    private Integer pendingVideoContainerTag = null;
    private volatile VideoSurfaceView pendingVideoSurface = null;
    private volatile boolean videoSurfaceAttached = false;
    private VideoDevice videoDevice = null;
    private volatile boolean surfaceRegistered = false;



    private void sendCallEventToReact(String status) {
        ReactApplicationContext context = getReactApplicationContext();
        if (context != null) {
            WritableMap params = Arguments.createMap();
            params.putString("status", status);
            context.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class)
                .emit("onCallStateChanged", params);
        }
    }

    private void sendCallEventVideoReact(String event) {
        ReactApplicationContext context = getReactApplicationContext();
        if (context != null) {
            WritableMap params = Arguments.createMap();
            params.putString("event", event); // beri tahu RN remote sudah siap
            context.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class)
                .emit("onVideoEvent", params);
        }
    }


    public CustomModule(ReactApplicationContext reactContext) {
        super(reactContext);
        app = (Application) reactContext.getApplicationContext();
        try {
            ClientConfiguration config = new ClientConfiguration();
            oceanaCustomerWebVoiceVideo = new OceanaCustomerWebVoiceVideo(config);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public String getName() {
        return "CustomModule";
    }

    @ReactMethod
    public void getVersionNumber(Promise promise) {
        try {
        String version = oceanaCustomerWebVoiceVideo.getVersionNumber();
        promise.resolve(version);
        } catch (Exception e) {
        promise.reject("Error", e);
        }
    }

    @ReactMethod
    public void createWork(Promise promise) {
        try {
        Work work = oceanaCustomerWebVoiceVideo.createWork();
        promise.resolve("Work created successfully");
        } catch (Exception e) {
        promise.reject("Error", e);
        }
    }

    @ReactMethod
    public void setOcsConfig(String jsonConfig, Promise promise) {
        try {
            Log.d("CustomModule", "📥 Menerima Konfigurasi OCS: " + jsonConfig);
            JSONObject json = new JSONObject(jsonConfig);

            // PERBAIKAN #1: Membuat konfigurasi sesuai dokumentasi (Halaman 35)
            ClientConfiguration clientConfig = new ClientConfiguration();
            WebGatewayConfiguration webGatewayConfig = new WebGatewayConfiguration();

            // Gunakan metode yang benar pada WebGatewayConfiguration
            webGatewayConfig.setWebGatewayAddress(json.getString("aawg_server"));
            webGatewayConfig.setPort(Integer.parseInt(json.getString("aawg_port")));
            webGatewayConfig.setSecure(true); // Asumsi selalu true

            clientConfig.setWebGatewayConfiguration(webGatewayConfig);
            
            // Token TIDAK diatur di sini.

            // Inisialisasi SDK dengan konfigurasi yang benar
            oceanaCustomerWebVoiceVideo = new OceanaCustomerWebVoiceVideo(clientConfig);

            oceanaCustomerWebVoiceVideo.registerLogger(java.util.logging.Level.FINE);


            // Simpan token untuk digunakan di startAudioCall/startVideoCall
            this.lastToken = json.getString("token");

            Log.d("CustomModule", "✅ Konfigurasi OCS berhasil diterapkan dan SDK diinisialisasi");
            promise.resolve("✅ Konfigurasi OCS berhasil diatur");

        } catch (Exception e) {
            Log.e("CustomModule", "❌ Error saat menerapkan konfigurasi OCS: " + e.getMessage(), e);
            promise.reject("CONFIG_ERROR", e);
        }
    }
    
    @ReactMethod
    public void requestTokenFromServer(
            String use,
            String calledNumber,
            String callingNumber,
            String displayName,
            String expiration,
            Promise promise) {
        new Thread(() -> {
            try {
                String tokenServerUrl = "https://sipsignal.whnmandiri.co.id:443/token-generation-service/token/getEncryptedToken";

                JSONObject jsonBody = new JSONObject();
                jsonBody.put("use", use);
                jsonBody.put("calledNumber", calledNumber);
                jsonBody.put("callingNumber", callingNumber);
                jsonBody.put("displayName", displayName);
                jsonBody.put("expiration", expiration);

                String requestBody = jsonBody.toString();
                Log.d("CustomModule", "📤 Token Request Body: " + requestBody);

                java.net.URL url = new java.net.URL(tokenServerUrl);
                java.net.HttpURLConnection conn = (java.net.HttpURLConnection) url.openConnection();

                conn.setRequestMethod("POST");
                conn.setRequestProperty("Content-Type", "application/json");
                conn.setDoOutput(true);

                java.io.OutputStream os = conn.getOutputStream();
                os.write(requestBody.getBytes());
                os.flush();
                os.close();

                int responseCode = conn.getResponseCode();
                Log.d("CustomModule", "✅ Token server HTTP Status Code: " + responseCode);

                java.io.InputStream is = (responseCode == 200) ? conn.getInputStream() : conn.getErrorStream();
                java.util.Scanner scanner = new java.util.Scanner(is).useDelimiter("\\A");
                String response = scanner.hasNext() ? scanner.next() : "";

                Log.d("CustomModule", "📥 Token Server Response Body: " + response);

                if (responseCode == 200) {
                    try {
                        JSONObject jsonResponse = new JSONObject(response);
                        WritableMap mapResponse = Arguments.createMap();

                        Iterator<String> keys = jsonResponse.keys();
                        while (keys.hasNext()) {
                            String key = keys.next();
                            mapResponse.putString(key, jsonResponse.getString(key));
                        }

                        promise.resolve(mapResponse);
                    } catch (Exception e) {
                        promise.resolve(response);
                    }
                } else {
                    promise.reject("TOKEN_ERROR", "Token request failed. Code: " + responseCode + ", Body: " + response);
                }

            } catch (Exception e) {
                Log.e("CustomModule", "❌ Token request failed: " + e.getMessage(), e);
                promise.reject("TOKEN_ERROR", e);
            }
        }).start();
    }


    @ReactMethod
    public void endCall(Promise promise) {
        try {
            boolean ended = false;

            if (currentAudioInteraction != null) {
                currentAudioInteraction.end();
                currentAudioInteraction = null;
                ended = true;
            }

            if (ended) {
                promise.resolve("Call ended");
            } 
        } catch (Exception e) {
            promise.reject("END_CALL_ERROR", "Gagal mengakhiri panggilan: " + e.toString());
        }
    }


    @ReactMethod
    public void toggleMute(boolean shouldMute, Promise promise) {
        try {
            if (currentAudioInteraction != null) {
                currentAudioInteraction.muteAudio(shouldMute);
            } 
            promise.resolve(true);
        } catch (Exception e) {
            promise.reject("MUTE_ERROR", e);
        }
    }

    @ReactMethod
    public void toggleSpeaker(boolean speakerOn, Promise promise) {
        try {
            AudioManager audioManager = (AudioManager) app.getSystemService(Context.AUDIO_SERVICE);
            audioManager.isSpeakerphoneOn();
            promise.resolve(true);
        } catch (Exception e) {
            promise.reject("SPEAKER_ERROR", e);
        }
    }


    @ReactMethod
    public void sendDtmf(String digit, Promise promise) {
        Log.d("CustomModule", "📟 sendDtmf called with digit: " + digit);

        DTMFTone tone = getDtmfToneFromString(digit);
        if (tone == null) {
            Log.w("CustomModule", "📟 Invalid DTMF digit: " + digit);
            promise.reject("DTMF_ERROR", "Digit DTMF tidak valid: " + digit);
            return;
        }

        try {
            Log.d("CustomModule", "📟 currentAudioInteraction = " + (currentAudioInteraction != null));

            if (currentAudioInteraction == null) {
                Log.w("CustomModule", "📟 No active interaction to send DTMF");
                promise.reject("DTMF_ERROR", "Tidak ada panggilan aktif");
                return;
            }

            // Ensure call to SDK happens on main/UI thread
            new Handler(Looper.getMainLooper()).post(() -> {
                try {
                    if (currentAudioInteraction != null) {
                        Log.d("CustomModule", "📟 Sending DTMF to AudioInteraction: " + digit);
                        currentAudioInteraction.sendDtmf(tone);
                    } 
                    Log.d("CustomModule", "📟 sendDtmf: call to SDK completed for digit: " + digit);
                    promise.resolve("DTMF sent: " + digit);
                } catch (Exception e) {
                    Log.e("CustomModule", "❌ Error while calling SDK sendDtmf", e);
                    promise.reject("DTMF_ERROR", "Gagal mengirim DTMF: " + e.toString());
                }
            });
        } catch (Exception e) {
            Log.e("CustomModule", "❌ Unexpected error in sendDtmf", e);
            promise.reject("DTMF_ERROR", e.toString());
        }
    }




    private DTMFTone getDtmfToneFromString(String digit) {
        switch (digit) {
            case "0": return DTMFTone.ZERO;
            case "1": return DTMFTone.ONE;
            case "2": return DTMFTone.TWO;
            case "3": return DTMFTone.THREE;
            case "4": return DTMFTone.FOUR;
            case "5": return DTMFTone.FIVE;
            case "6": return DTMFTone.SIX;
            case "7": return DTMFTone.SEVEN;
            case "8": return DTMFTone.EIGHT;
            case "9": return DTMFTone.NINE;
            case "*": return DTMFTone.STAR;
            case "#": return DTMFTone.POUND;
            default: return null;
        }
    }


    
    private WritableMap createEventParams(String status) {
        WritableMap params = Arguments.createMap();
        params.putString("status", status);
        return params;
    }

    // --- Tambahkan ini di awal class CustomModule (sejajar dengan globalVideoListener) ---
    private final AudioInteractionListener globalAudioListener = new AudioInteractionListener() {
        @Override
        public void onInteractionInitiating() {
            Log.d("CustomModule", "🎧 Audio initiating...");
            sendCallEventToReact("initiating");
        }

        @Override
        public void onInteractionRemoteAlerting() {
            Log.d("CustomModule", "🎧 Remote ringing...");
            sendCallEventToReact("ringing");
        }

        @Override
        public void onInteractionActive() {
            Log.d("CustomModule", "🎧 Audio call active");
            sendCallEventToReact("connected");
        }

        @Override
        public void onInteractionEnded() {
            Log.d("CustomModule", "🎧 Audio call ended");
            sendCallEventToReact("ended");
            currentAudioInteraction = null;
        }

        @Override
        public void onInteractionFailed(InteractionError error) {
            Log.e("CustomModule", "❌ Audio call failed: " + error);
            sendCallEventToReact("error");
        }

        @Override
        public void onInteractionAudioMuteStatusChanged(boolean muted) {
            Log.d("CustomModule", "🔇 Audio mute status changed: " + muted);
        }

        @Override public void onInteractionHeld() {}
        @Override public void onInteractionUnheld() {}
        @Override public void onInteractionHeldRemotely() {}
        @Override public void onInteractionUnheldRemotely() {}
        @Override public void onInteractionQualityChanged(CallQuality quality) {}
        @Override public void onDiscardComplete() {}
    };



    @ReactMethod
    public void startAudioCall(String destination, Promise promise) {
        if (oceanaCustomerWebVoiceVideo == null || this.lastToken == null) {
            promise.reject("SETUP_ERROR", "SDK belum diinisialisasi atau token tidak ada. Panggil setOcsConfig dulu.");
            return;
        }

        try {
            Log.d("CustomModule", "📞 Memulai Panggilan Audio ke: " + destination);
            Work work = oceanaCustomerWebVoiceVideo.createWork();

            OnAudioDeviceChangeListener listener = new OnAudioDeviceChangeListener() {
                @Override
                public void onAudioDeviceListChanged(List<AudioDeviceType> deviceList) {}
                @Override
                public void onAudioDeviceChanged(AudioDeviceType newDevice) {}
                @Override
                public void onAudioDeviceError(AudioDeviceError error) {}
            };

            AudioInteraction audioInteraction = work.createAudioInteraction(app, listener);
            audioInteraction.setPlatformType(PlatformType.ELITE);            
            audioInteraction.setAuthorizationToken(this.lastToken);
            audioInteraction.setDestinationAddress(destination);
            currentAudioInteraction = audioInteraction;

            audioInteraction.registerListener(globalAudioListener);

            audioInteraction.start();

            promise.resolve("Panggilan audio dimulai ke: " + destination);

        } catch (Exception e) {
            Log.e("CustomModule", "❌ Gagal memulai panggilan audio", e);
            promise.reject("CALL_ERROR", "Gagal memulai panggilan audio: " + e.toString());
        }
    }


    @ReactMethod
    public void addListener(String eventName) {
        // Required for RN built-in EventEmitter calls (no implementation needed)
    }

    @ReactMethod
    public void removeListeners(Integer count) {
        // Required for RN built-in EventEmitter calls (no implementation needed)
    }

}