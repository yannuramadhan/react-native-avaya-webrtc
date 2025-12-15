# react-native-avaya-webrtc

React Native **Native Module** untuk integrasi **Avaya Oceana / Aura Elite WebRTC**
(Audio & Video Call) di **Android** dan **iOS**.

Library ini membungkus **Avaya Customer Web Voice Video SDK** agar dapat digunakan
langsung dari **JavaScript (React Native)** dengan **API yang konsisten** antara
Android dan iOS.

---

## ✨ Fitur

- 📞 Audio Call (Aura Elite / Oceana)
- 🎥 Video Call *(opsional, tergantung SDK Avaya)*
- 🔐 Token-based authentication (Token Generation Service)
- 🔄 API parity Android & iOS
- 🧩 Cocok sebagai internal SDK / shared package

---

## 📦 Instalasi

### 1️⃣ Install via npm (GitHub)

```bash
npm install git+https://github.com/yannuramadhan/react-native-avaya-webrtc.git
```

atau menggunakan **Yarn**:

```bash
yarn add https://github.com/yannuramadhan/react-native-avaya-webrtc.git
```

---

### 2️⃣ iOS Setup

```bash
cd ios
pod install
```

#### ⚠️ Catatan iOS

- Minimal **iOS 15.0**
- **Xcode 14+**
- Buka project menggunakan:
  ```
  ios/*.xcworkspace
  ```

---

### 3️⃣ Android Setup

**Requirement:**
- Android Gradle Plugin **7+**
- Minimum SDK mengikuti requirement Avaya SDK

Autolinking React Native akan berjalan otomatis.

---

## 🧠 Arsitektur

```
React Native (JavaScript)
        ↓
Native Module (Android / iOS)
        ↓
Avaya WebRTC SDK
        ↓
Avaya Aura Elite / Oceana
```

---

## 🔐 Flow Panggilan

1. Request token ke Token Generation Service
2. Set OCS / WebGateway configuration
3. Inisialisasi Avaya SDK
4. Start Audio / Video Call

---

## 🧪 Contoh Penggunaan

```js
import { NativeModules } from 'react-native';

const { CustomModule } = NativeModules;

async function startCallFlow(phoneNumber, config) {
  const tokenResponse = await CustomModule.requestTokenFromServer(
    config.use,
    phoneNumber,
    config.callingNumber,
    config.display_name,
    config.expiration
  );

  const configWithToken = {
    ...config,
    token: tokenResponse.encryptedToken,
  };

  await CustomModule.setOcsConfig(JSON.stringify(configWithToken));
  await CustomModule.startAudioCall(phoneNumber);
}
```

---

## 📚 API

### requestTokenFromServer
Request token ke Token Generation Service.

### setOcsConfig
Set konfigurasi OCS / WebGateway dan inisialisasi SDK Avaya.

### startAudioCall
Memulai panggilan audio ke destination.

---

## 📄 Lisensi

Internal / Private SDK  
Gunakan sesuai kebijakan perusahaan dan lisensi Avaya SDK.

---

## 👤 Author

Yanuar Arif Ramadhan  
https://github.com/yannuramadhan
