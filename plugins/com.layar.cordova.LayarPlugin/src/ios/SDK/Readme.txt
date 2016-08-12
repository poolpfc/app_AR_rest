Product:  
Layar SDK version 8.4.2

Hardware and software requirements
- iPhone 3GS or higher
- iPad 2 or higher
- iOS version 6.0 or higher
- Xcode 6.0 or higher
- iPhone SDK 8.0 or higher
- A published layer or campaign in your Layar account. For getting started please see http://devsupport.layar.com/forums/20604191-getting-started or http://devsupport.layar.com/forums/20603886-getting-started

License: 
By embedding the Layar SDK framework in your application, you agree to the Terms and Conditions described in the Layar_SDK_License_Agreement_v5_4_20131016.pdf file which can be found in the Layar SDK package or as Attachment 4 to our Layar Terms and Conditions for Developers and Publishers at https://www.layar.com/legal/terms-developers/

Contents of this package:
- LayarSDK.framework: The actual framework 
- LayarSDK.framework/Resources/LayarSDKResources.bundle: The bundle with resources that you may change to your convenience
- Libraries: Includes external libraries used by the LayarSDK
- Layar SDK Documentation/html/index.html: start here for the documentation
- Layar SDK Documentation/html/com.layar.layarSDK.docset: the same documentation as a docset that you can add to XCode.
- Layar SDK Documentation/InstallDocSet.sh: shell script to install docset to XCode
- Layar_SDK_License_Agreement_v5_4_20131016.pdf: The license agreement for the Layar SDK
- Layar SDK app submission guidelines_20131023_DG.pdf: A document giving some guidelines to help you through the Apple app review process
- This readme.txt file

Changelog:
- May 18th 2015 - SDK 8.4.2
Fixed another crash that happened while deallocating LayarSDK
Added Custom Exposure for better tracking
Made webview smoother and fixed a bug that was making them hard to touch on landscape
Supporting Installation through cocoapods

- April 13th 2015 - SDK 8.4.1
Fixed a crash that happened on upgrade from older versions

- March 3rd 2015 - SDK 8.4
Fully customisable UI for your scan view
Added support to change the view-angle of the pop-out view (2d or 3d view)
Added support to hide the trigger image in the pop-out view
Added support to automatically re-attach the content back to the trigger image after it was opened in the pop-out view
Added support to tak and share a screenshot

Added support to loop AR videos (only available using the Layar API)
Added support to hide the audio player (only available using the Layar API)
Added support to hide the loading indicators (only available using the Layar API)
Added support to hide the replay button for AR videos (only available using the Layar API)

- October 21st 2014 - SDK 8.3.2
Fixed location support in geo layers for iOS 8 and above 

- July 29th 2014 - SDK 8.3.1
Fixed ARM64 support.

- June 24th 2014 - SDK 8.3
Added new capabilities for 3D models to support POI anchors, texture override, support for video and animated GIF textures
updated our pop-out view so users can double tap or pinch to zoom, drag to move the 3D model around and rotate with two fingers.
various bug fixes and improvements.

- May 13th 2014 - SDK 8.2
Fix for transparent animated GIF
Fix for reporting stats for HTML-panels
Fix for buttons not shown in front or back in regards to other buttons
Removed dependency on SBJson library
Added support for ARM64
Various other bug fixes and improvements

- March 11th 2014 - SDK 8.1
The Layar SDK has been supplied with pop-out and additional APIs to alter the behaviour for this feature
Various bug fixes and improvements

- October 24th 2013 - SDK 8.0
Support for Geo layers is back. Using Vision layers or Geo layers inside the SDK is subject to you having purchased the appropriate key to unlock that class of content.
A lot of new delegate methods added allowing easier customization.
Multiple bug-fixes and performance improvements.

- June 24th 2013 - SDK 7.2.4
Layar SDK has been supplied with delegate methods to receive callbacks for successfully scanned reference images and campaigns. A bug has been fixed that caused all statistics to be send twice.

- April 11th 2013 - SDK 7.2.3
Layar SDK now supports 5 additional languages: Dutch, German, Spanish, French and Japanese.

- March 15th 2013 - SDK 7.2.0
Layar SDK now supports QR-code scanning. Multiple bug-fixes and performance improvements.

- March 6th 2013 - SDK 7.1.2
Fixed crash to improve stability.

- February 14th 2013 - SDK 7.1.1
Fixed crash to improve stability.

- January 15th 2013 - SDK 7.1.0
Release of the LayarSDK.

Contact and Information:
- Layar: http://www.layar.com
- Layar SDK support:  http://devsupport.layar.com/categories/6169-layar-sdk
