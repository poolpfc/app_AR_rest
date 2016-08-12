/**
 * @file LayarSDK.h (Version:8.4.4 Revision:b4e8c76)
 * @brief Main include file of the Layar SDK
 *
 * Include this file to include all public header files of the Layar SDK
 * By implementing the Layar SDK in your application, you agree to the Terms and Conditions described in the Layar_SDK_License_Agreement_*.pdf.
 * file which can be found in the Layar SDK package.
 *
 * @copyright Copyright (c) 2013 Layar. All rights reserved.
 */

/**
 * @mainpage Layar SDK Documentation
 *
 * @section introduction Introduction
 *
 * The Layar SDK is an Xcode framework that implements the core functionality of Layar. Using the Layar SDK it is
 * possible to present the Augmented Reality view to the user. The user will be able to scan objects that may be 
 * augmented using Layar Vision or the Layar Creator, and open Geo layers.
 *
 * The Layar SDK will only return content linked to the user account who registered the application in which the Layar SDK is embedded. The Layar SDK will start all necessary
 * services such as the camera and device motion control.
 *
 * @section minimumrequirements Minimum requirements
 *
 * The Layar SDK requires a minimum iOS version of 7.0 to be installed on the device.
 * 
 * The Layar SDK is built for ARM7 and ARM64 architecture using iOS 9 SDK and it also contains bitcode markers. Applications that use the SDK should also be built using iOS 9 SDK.
 * The iOS 9 SDK requirement also applies if you target devices running iOS 7.
 * Using the iOS 9 SDK in turn requires you to use XCode version 7+ to build your application.
 *
 * The device capabilities include OpenGL ES 2 support, location support, a camera, magnetometer and an accelerometer.
 * The application in which the LayarSDK.framework is used should reflect this by specifying the following values
 * in the application's Info.plist for the key UIRequiredDeviceCapabilities:
 *
 * @li opengles-2
 * @li video-camera
 * @li accelerometer
 * @li magnetometer
 * @li location-services
 * @li armv7
 *
 * If using the LayarSDK for opening Geo Layers, your application must specify that it will be requesting location from the user. 
 * You will need to add one or both of the following keys to your Info.plist file:
 *
 * @li @c NSLocationWhenInUseUsageDescription
 * @li @c NSLocationAlwaysUsageDescription
 *
 * The LayarSDK only requires the first key to be set. The value should be a descriptive string telling the user why he should
 * enable location services for your app. E.g. "We need your location to show interesting spots around you". Only set the second key 
 * if your own application requires location in the background, i.e. if within your own code you use [self.locationManager requestAlwaysAuthorization].
 
 * @section cocoapodsprojectconfiguration CocoaPods Project configuration (Recommended)
 *
 * Unzip the contents of the LayarSDK Zip Folder that you have downloaded into a folder inside your repository.
 
 * In your podfile specify add a pod called LayarSDK and specify the path to the saved LayarSDK Folder 
 * on your local filesystem where you unzipped the LayarSDK.
 *
 * pod 'LayarSDK', :path => '~/MyProject/LayarSDK'
 *
 * Then Run 'pod install' on your command line to install LayarSDK.
 *
 * @section customprojectconfiguration Custom Project configuration
 *
 * Any project using the Layar SDK must have the "Minimum OS Version" set to 7.0. It must also specify "Architectures" of armv7, armv7s and/or arm64.
 *
 * To use SDK in an application project do the following:
 * @li add LayarSDK.framework to the “Link Binary With Libraries” build phase
 * @li add dependent frameworks there also (list below)
 * @li add -ObjC flag to “Other Linker Flags” in build settings (otherwise it will crash for class categories)
 * @li add LayarSDK.framework/Resources/LayarSDKResources.bundle to your app resources, e.g. in the "Supporting Files" group (a group that XCode automatically creates when you create a new project).

 * @subsection frameworks List of dependent frameworks
 *
 * @li libstdc++.dylib
 * @li libiconv.dylib
 * @li libxml2.dylib
 * @li libz.dylib
 
 * @li AddressBook.framework
 * @li AddressBookUI.framework
 * @li AudioToolbox.framework
 * @li AVFoundation.framework
 * @li CFNetwork.framework
 * @li CoreAudio.framework
 * @li CoreData.framework
 * @li CoreGraphics.framework
 * @li CoreLocation.framework
 * @li CoreMedia.framework
 * @li CoreMotion.framework
 * @li CoreTelephony.framework
 * @li CoreVideo.framework
 * @li Foundation.framework
 * @li MapKit.framework
 * @li MessageUI.framework
 * @li OpenAL.framework
 * @li OpenGLES.framework
 * @li QuartzCore.framework
 * @li Security.framework
 * @li Social.framework
 * @li SystemConfiguration.framework
 * @li Twitter.framework
 * @li UIKit.framework
 
 * @subsection externallibs External Libraries
 *
 * The Layar SDK uses some external open source libraries that you might want to use in your own project. In order to avoid symbol conflicts, we're distributing the libraries as separate static libraries together with the Layar SDK. You need to link you project against the binary static libraries (see Build Configuration section below).
 *
 * If you use the libraries in your application, you'll need to include the path to the header files in the "Header search paths" of your project's build configuration.
 * You may want to use newer versions of these libraries, in such cases make sure you link against those compiled static libraries. As long as backward compatibility is maintained, it should work, but Layar makes no guarantees if a different version is used. The two libraries are:
 *
 * @li libMPOAuth.a by Karl Adam: https://github.com/thekarladam/MPOAuth
 *
 * @li libCocoaLumberjack.a: https://github.com/CocoaLumberjack/CocoaLumberjack
 *
 * @li libREComposeViewController.a: https://github.com/romaonthego/REComposeViewController
 *
 * All other open-source libraries we use should be obfuscated or consist of header files only, so they shouldn't lead to conflicts. If nevertheless you hit a conflict just let us know and we'll send you the relevant header files.
 *
 * @subsubsection armv7 Armv7 Build Configuration
 *
 * When building the application the following steps must be taken to ensure that the project links against the "LayarSDK.framework" framework. The instructions below were made using XCode 7.0.
 *
 * The project settings should have the following changes made:
 *
 * @li The "Architectures" option set to "Standard (armv7, arm64)"
 * @li The "Valid Architectures" option should contain "armv7" and "armv7s"
 $ @li The "Base SDK" option should be set to "Latest iOS"
 * @li The "iOS Deployment Target" option should be set to "iOS 7.0"
 * @li If you wish to use the "#import <...>" import directive, you must ensure that the "Always search user paths" option is enabled
 * @li In the "Build Phases" of your target, the "Link Binary with Libraries" option must also contain libMPOAuth.a, libCocoaLumberjack.a and libREComposeViewController.a from external libraries supplied with Layar SDK. Note: If your project already includes these libraries, you can skip this step.
 * @li The "Other linker flags" option must contain the flags @c -ObjC.
 * @li The "C Language Dialect" option must be set to GNU99.
 * @li The "C++ Language Dialect" option must be set to GNU++11.
 * @li The "C++ Standard Library" option must be set to libC++.
 *
 * @section usage Usage
 *
 * In order to use the Layar SDK in an application, you need to import the LayarSDK.h in the class file that will launch the AR view controller.
 *
 * You need to allocate an instance of LayarSDK class that you will use to open AR view controllers. There should only be one single instance of LayarSDK class in your application.
 * You need to provide your OAuth consumer key and secret, and a reference to your delegate when creating LayarSDK instance.
 *
 * LayarSDK class has methods to open an AR view controller for scanning, and to directly launch layers or campaigns.
 *
 * View controllers that you get from LayarSDK can be either shown modally or in a navigation view controller.
 *
 * The LayerSDK also supports backgrounding, and will pause all OpenGL rendering as well as relinquishing all device hardware usage.
 *
 * @subsection example Example
 *
 * The following code snippet can be used to present an Augmented Reality View and load a layer:
 *
 * @code
 * #import <LayarSDK/LayarSDK.h>
 *
 * ...
 *
 * // This goes into your class declaration
 * @property (nonatomic, retain) LayarSDK *layarSDK;
 *
 * ...
 *
 * // This goes into your initialization code
 * NSString *consumerKey = ...; // your OAuth key
 * NSString *consumerSecret = ...; // your OAuth secret
 * self.layarSDK = [LayarSDK layarSDKWithConsumerKey:consumerKey andConsumerSecret:consumerSecret andDelegate:self];
 *
 * ...
 *
 * // This is how you construct a view controller for scanning
 * [self.layarSDK viewControllerForScanningWithCompletion:
 * ^(UIViewController<LayarSDKViewController> *viewController)
 * {
 *     // Present the view controller you get here, e.g. push it to your navigation view controller.
 * }];
 *
 * ...
 *
 * // This is how you open a view controller for layer/campaign directly
 * NSURL *layarUrl = ...; // a 'layar://...' URL specifying which layer/campaign to open
 * [self.layarSDK viewControllerForURL:layarUrl withCompletion:
 *  ^(UIViewController<LayarSDKViewController> *viewController)
 * {
 * 	 if (viewController)
 * 	 {
 *     // Present the view controller you get here, e.g. push it to your navigation view controller.
 * 	 }
 * }];
 * @endcode
 *
 * @subsubsection oauth OAuth signing
 *
 * All requests made by the Layar SDK need have a valid OAuth key and secret sent with them in order to successfully pass authentication checks by the Layar server.
 * This information is specific to each app, and must be configured by Layar staff. Please contact devsupport@layar.com to ensure your signing keys are valid.
 *
 * @subsubsection delegatemethods Delegate methods
 *
 * By implementing the LayarSDKDelegate protocol a program can receive events from the Layar SDK and override several actions.
 * E.g. you get information about which layer has been loaded and when a certain reference image is tracked etc.
 * Please refer to LayarSDKDelegate protocol documentation for a complete list of callbacks you can receive.
 *
 * @section launchingfromopenglapp Launching the Layar SDK from OpenGL applications
 *
 * Extra attention must be paid to resource management when launching the Layar SDK from an application that makes use of OpenGL to render content. The Layar SDK is a resource
 * intensive application, and to avoid spawning memory warnings on the device it is running on, any application launching the Layar SDK should free up as many resources as possible.
 * For OpenGL applications this means that all texture resources should be deleted, and if possible any framebuffers that are in use. Any OpenGL timers or display links should be paused
 * as well. Care should be taken to set the application's own OpenGL context when doing so. More information on OpenGL context switching can be found here:
 * http://developer.apple.com/library/ios/#documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/WorkingwithOpenGLESContexts/WorkingwithOpenGLESContexts.html
 *
 
 * @section branding Overriding strings and graphics
 
 * Everything that you can override is inside the LayarSDK.framework/Resources/LayarSDKResources.bundle. It includes localizable strings and graphical assets that can be replaced.
 
 * There are basically two ways to do this.
 * @subsection easy The easy way
 
 * @li Pro: easy
 * @li Con: default resources will still be present in your app bundle (inside LayarSDKResources.bundle), though not used.
 
 * For text strings the SDK uses iOS localization mechanics. Thus, all strings are contained in LayarSDKResources.bundle/en.lproj/Localizable.strings file. The SDK is also built in a way to allow overriding/localizing any string. It first looks for strings in main bundle localization tables, then if not found falls back to LayarSDKResources.bundle localizations. So to replace a string do this:
 * @li Add localization .strings file(s) to your application
 * @li Look into LayarSDKResources.bundle/en.lproj/Localizable.strings file to find a string to replace
 * @li Add a string with the same key into your app’s .strings file(s).
 
 * For images the SDK tries to load files from main bundle first, and if not found falls back to a file in LayarSDKResources.bundle. So, to replace an image:
 * @li Look into LayarSDKResources.bundle and find the asset you want to replace
 * @li Create the files with the same names (usually there are several versions of the same file for different screen resolutions, e.g. …@2x for retina etc.)
 * @li Add the files to your app resources (main bundle).
 
 
 * @subsection hard The hard way
 
 * @li Pro: you have full control of what is included in your app
 * @li Con: you need to keep track of what was changed when we update the sdk
 
 * Copy LayarSDK.framework/Resources/LayarSDKResources.bundle, modify it and include a modified version into your project.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <LayarSDK/LayarSDKDelegate.h>
#import <LayarSDK/LayarSDKViewController.h>
#import <LayarSDK/LayarSDKLocationProvider.h>

#define LayarSDKLocalizedString(key, comment) [LayarSDK localizedStringForKey:key andComment:comment]

@class CLLocation;

/**
 * @brief	Completion block for opening a layer/campaign URL.
 *
 * @param	viewController		A reference to the view controller that has the URL open and is ready to be displayed.
 *								Can be nil if the URL is invalid.
 */
typedef void (^LayarSDKURLCompletion)(UIViewController<LayarSDKViewController>* viewController);

/**
 * @brief	Completion block for opening a http/web URL.
 *
 * @param	viewController	A reference to the view controller that has the URL open and is ready to be displayed.
 *							Can be nil if the web URL is invalid.
 */
typedef void (^LayarSDKWebURLCompletion)(UIViewController<UIWebViewDelegate> *viewController);

/**
 * @brief	Completion block for opening a layer/campaign URL.
 *
 * @param	viewController		A reference to the view controller in scan mode that is ready to be displayed.
 */
typedef void (^LayarSDKViewControllerForScanningCompletion)(UIViewController<LayarSDKViewController>* viewController);

/**
 * @brief	This is the main class for Layar SDK. You use this class to configure the SDK and to construct
 *			required AR view controllers.
 *
 *			Ideally, there should only be one single instance of this class in your application.
 *
 * @headerfile LayarSDK/LayarSDK.h
 */
@interface LayarSDK : NSObject

/**
 * @brief	Returns a localized string from the LayarSDK Bundle.
 */
+ (NSString*)localizedStringForKey:(NSString*)key andComment:(NSString*)comment;

/**
 * @brief	Construct an instance of LayarSDK object and configure it.
 *
 * @param	consumerKey			NSString*				Your OAuth consumer key used to sign all Layar API requests
 * @param	consumerSecret		NSString*				Your OAuth consumer secret used to sign all Layar API requests
 * @param	delegate			id<LayarSDKDelegate>	Reference to an object of a class that implements LayarSDKDelegate protocol. Can be nil. Will be weakly held.
 *
 * @return	Constructed and configured autoreleased instance of LayarSDK class.
 */
+ (LayarSDK*)layarSDKWithConsumerKey:(NSString*)consumerKey andConsumerSecret:(NSString*)consumerSecret andDelegate:(id<LayarSDKDelegate>)delegate;

/**
 * @brief	Initialize an instance of LayarSDK object and configure it.
 *
 * @param	consumerKey			NSString*				Your OAuth consumer key used to sign all Layar API requests
 * @param	consumerSecret		NSString*				Your OAuth consumer secret used to sign all Layar API requests
 * @param	delegate			id<LayarSDKDelegate>	Reference to an object of a class that implements LayarSDKDelegate protocol. Can be nil. Will be weakly held.
 *
 * @return	Configured instance of LayarSDK class.
 */
- (id)initWithConsumerKey:(NSString*)consumerKey andConsumerSecret:(NSString*)consumerSecret andDelegate:(id<LayarSDKDelegate>)delegate;

/**
 * @brief	Construct an instance of LayarSDK object and configure it.
 *
 * @param	consumerKey             NSString*				Your OAuth consumer key used to sign all Layar API requests
 * @param	consumerSecret         NSString*				Your OAuth consumer secret used to sign all Layar API requests
 * @param	delegate                id<LayarSDKDelegate>	Reference to a class that implements LayarSDKDelegate protocol. Can be nil. Will be weakly held.
 * @param   customLocationProvider  id<LayarSDKLocationProvider>    Reference to an object of a class that implements LayarSDKDelegate protocol. Can be nil. Will be strongly held.
 *
 * @return	Constructed and configured autoreleased instance of LayarSDK class.
 */
+ (LayarSDK*)layarSDKWithConsumerKey:(NSString*)consumerKey andConsumerSecret:(NSString*)consumerSecret andDelegate:(id<LayarSDKDelegate>)delegate  customLocationProvider:(id<LayarSDKLocationProvider>)customLocationProvider;;

/**
 * @brief	Initialize an instance of LayarSDK object and configure it.
 *
 * @param	consumerKey             NSString*				Your OAuth consumer key used to sign all Layar API requests
 * @param	consumerSecret         NSString*				Your OAuth consumer secret used to sign all Layar API requests
 * @param	delegate                id<LayarSDKDelegate>	Reference to an object of a class that implements LayarSDKDelegate protocol. Can be nil. Will be weakly held.
 * @param   customLocationProvider  id<LayarSDKLocationProvider>    Reference to an object of a class that implements LayarSDKDelegate protocol. Will be strongly held.
 *
 * @return	Configured instance of LayarSDK class.
 */
- (id)initWithConsumerKey:(NSString*)consumerKey andConsumerSecret:(NSString*)consumerSecret andDelegate:(id<LayarSDKDelegate>)delegate customLocationProvider:(id<LayarSDKLocationProvider>)customLocationProvider;

/**
 * @brief	Reference to Layad SDK delegate
 */
@property (nonatomic, weak, readonly) id<LayarSDKDelegate> delegate;

/**
 * @brief	Fixed location to use for Geo layers.
 *
 *			Using this property you can test your Geo layers for any arbitrary Geo location. Setting it to an instance of CLLocation object will override
 *			GPS location used for Geo layers. Set to nil to disable the override.
 */
@property (nonatomic, strong) CLLocation *fixedLocation;

/**
 * @brief	Use this property to control if 'pop out' functionality is enabled in AR view controllers.
 *
 *			Defaults to YES. Setting this property does not affect AR view controllers that are already created.
 */
@property (nonatomic, assign) BOOL popOutsEnabled;

/**
 * @brief	Open an web view controller with http url loaded
 *
 * @param	url			A URL pointing to the web page. Can have http or https schemes.
 *						Example: http://www.google.com
 *
 * @param	completion	Completion block that will be executed when the view controller is ready to be displayed. 
						You get a reference to the view controller as a parameter to the completion block.
 */
- (void)webViewControllerForURL:(NSURL*)url withCompletion:(LayarSDKWebURLCompletion)completion;

/**
 * @brief	Open an AR view controller with layer/campaign loaded
 *
 * @param	url			A URL pointing to layer or campaign. Should have 'layar://' scheme and contain layer name and optionally additional parameters.
 *						Example: layar://layername
 *						See Layar client API docs for a detailed description.
 *
 * @param	completion	Completion block that will be executed when the view controller is ready to be displayed.
 You get a reference to the view controller as a parameter to the completion block.
 */
- (void)viewControllerForURL:(NSURL*)url withCompletion:(LayarSDKURLCompletion)completion;

/**
 * @brief	Load a layer/campaign on an existing view controller
 *
 * @param	url			A URL pointing to layer or campaign. Should have 'layar://' scheme and contain layer name and optionally additional parameters.
 *						Example: layar://layername
 *						See Layar client API docs for a detailed description.
 *
 * @param	completion	Completion block that will be executed when the view controller has loaded the new URL
 */
- (void)openURL:(NSURL *)url onExistingViewController:(UIViewController<LayarSDKViewController>*)viewController completion:(void(^)(BOOL completed, NSError* error))completion;
/**
 * @brief	Open an AR view controller for scanning
 *
 * @param	completion	Completion block that will be executed when the view controller is ready to be displayed. 
						You get a reference to the view controller as a parameter to the completion block.
 */
- (void)viewControllerForScanningWithCompletion:(LayarSDKViewControllerForScanningCompletion)completion;

@end
