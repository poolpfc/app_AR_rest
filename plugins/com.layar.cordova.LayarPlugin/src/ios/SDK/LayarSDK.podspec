Pod::Spec.new do |s|
    s.name     = 'LayarSDK'
    s.version  = '8.4.4'
    s.summary  = 'An augmented reality SDK for creating apps with augmented reality experiences'
    s.homepage = 'https://www.layar.com/solutions/'
    s.authors  = 'Layar B.V.'
    s.license  = 'Layar_SDK_License_Agreement_v5_4_20131016 (Please see document in zip folder for details'
    s.platform = :ios, '8.0'

    s.ios.vendored_frameworks = 'LayarSDK.framework'
    s.ios.vendored_libraries = 'External-Libraries/libMPOAuth.a'
    s.ios.xcconfig = { 'FRAMEWORK_SEARCH_PATHS' => '$(inherited)' }
    s.ios.preserve_paths = 'LayarSDK.framework', ''
    s.ios.dependency 'CocoaLumberjack', '~> 2.0.0'
    s.ios.dependency 'REComposeViewController', '~> 2.3.2'
    s.ios.libraries = 'stdc++', 'z' , 'iconv', 'xml2'
    s.ios.frameworks = 'AVFoundation', 'SystemConfiguration', 'CoreMedia', 'AddressBook', 'AddressBookUI', 'CoreData', 'Social', 'CoreMotion', 'MapKit' , 'MessageUI', 'CoreLocation', 'CoreTelephony', 'WebKit'
    s.ios.resources = 'LayarSDK.framework/LayarSDKResources.bundle'
end