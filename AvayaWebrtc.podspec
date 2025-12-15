require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name         = "react-native-avaya-webrtc"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]

  s.platforms    = { :ios => min_ios_version_supported }

  # ⬇️ INI PENTING: path HARUS local package
  s.source       = { :path => "." }

  s.source_files = "ios/**/*.{h,m,mm,swift,cpp}"
  s.private_header_files = "ios/**/*.h"

  # ⬇️ INI YANG SELAMA INI HILANG
  s.vendored_frameworks = [
    "ios/Frameworks/AvayaClientMedia.xcframework",
    "ios/Frameworks/AvayaClientServicesLite.xcframework",
    "ios/Frameworks/OceanaCustomerWebVoiceVideo.xcframework",
    "ios/Frameworks/RVVideoCodec.xcframework"
  ]

  s.frameworks = [
    "AVFoundation",
    "AudioToolbox",
    "CoreMedia",
    "VideoToolbox",
    "UIKit"
  ]

  s.libraries = "c++"

  install_modules_dependencies(s)
end
