react-native-avaya-webrtc
React Native Native Module untuk integrasi Avaya Oceana / Aura Elite WebRTC (Audio & Video Call) di Android dan iOS.
Library ini membungkus Avaya Customer Web Voice Video SDK agar bisa digunakan langsung dari JavaScript (React Native), dengan API yang konsisten antara Android dan iOS.
✨ Fitur
📞 Audio Call (Aura Elite / Oceana)
🎥 Video Call (opsional, tergantung SDK Avaya)
🔐 Token-based authentication (via Token Generation Service)
🔄 API Android & iOS parity
🧩 Cocok dijadikan internal SDK atau shared package
📦 Instalasi
1️⃣ Install via npm (GitHub)
npm install git+https://github.com/yannuramadhan/react-native-avaya-webrtc.git
atau jika menggunakan yarn:
yarn add https://github.com/yannuramadhan/react-native-avaya-webrtc.git
iOS
cd ios
pod install
⚠️ Pastikan menggunakan Xcode 14+ dan iOS minimum 15.0
Android
Android Gradle Plugin 7+
Min SDK sesuai requirement Avaya SDK
🧠 Arsitektur Singkat
React Native JS
      ↓
Native Module
(Android / iOS)
      ↓
Avaya WebRTC SDK
      ↓
Avaya Aura Elite / Oceana
🔐 Flow Panggilan (High Level)
Request token ke Token Generation Service
Set OCS / WebGateway configuration
Inisialisasi Avaya SDK
Start Audio / Video Call