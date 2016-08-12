/**
 * @file LayarSDKViewController.h
 * @brief This file contains protocol declaration for LayarSDKViewController.
 *
 * @copyright Copyright (c) 2013 Layar. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 * @brief	The LayarSDKViewController gives you access to extended
 *			functionality of AR view controller, e.g. allows you to launch
 *			map view representation of layers or open layer settings screen.
 *
 * @headerfile LayarSDK/LayarSDK.h
 */
@protocol LayarSDKViewController <NSObject>

/**
 * @brief	This property is set to YES when layer settings are available for
 *			currently loaded layer.
 */
@property (nonatomic, readonly) BOOL layerSettingsAvailable;

/**
 * @brief	This property is set to YES when it is possible to open a map view for
 *			currently loaded layer.
 */
@property (nonatomic, readonly) BOOL mapViewAvailable;

/**
 * @brief	This property is set to YES when pop-out mode can be entered on this view controller.
 */
@property (nonatomic, readonly) BOOL popOutAvailable;

/**
 * @brief	This property is set to YES by default but you can set it no to disable tap to scan. Please do this before you show the view controller. It wont work if you do it after you have already presented or shown the view controller.
 */
@property (nonatomic, assign) BOOL tapToScanEnabled;

/**
 * @brief	This property is set to YES by default but you can set it no to hide the preview image when popped out
 */
@property (nonatomic, assign) BOOL showPreviewImageWhenPoppedOut;

/**
 * @brief	This property is set to NO by default but you can set it YES to continue tracking when popped out. Useful if you want to implement auto-attach functionality.
 */
@property (nonatomic, assign) BOOL trackingEnabledWhenPoppedOut;

/**
 * @brief	By default we fit all the content in the screen when we are popping out. You can change this behaviour by setting this property to NO. Then we will try to fit the reference image only.
 */
@property (nonatomic, assign) BOOL fitContentWhenPoppedOut;

/**
 * @brief	By default we tilt the popped out content only if it is 3D. By setting this property to NO you can disable that behavior for 3D Content. However by setting it to YES you can enable this behaviour for 2D and 3D. It should be noted that in case the 3D Mode is not enabled then the 3D Tilt is not done.
 */
@property (nonatomic, assign) BOOL perform3DTiltWhenPoppedOut;

/**
 * @brief	By default we enable 3D mode on the popped out content, so that the user can tilt it by panning and also zoom with two fingers. You can disable that behaviour on 3D content by setting it to NO. However by setting it to YES you can enable this behaviour for 2D and 3D.
 */
@property (nonatomic, assign) BOOL enable3DModeWhenPoppedOut;

/**
 * @brief	This property specifies if the view controller is in a detached/popped out state.
 */
@property (nonatomic, readonly) BOOL isCurrentlyPoppedOut;

/**
 * @brief	By default we have a popout UI which tells the user that he can pop out when we lose tracking and when in popout mode we show a close button. Setting this property to NO will disable that behaviour and the user of the SDK can show custom UI.
 */
@property (nonatomic, assign) BOOL defaultPopoutUIEnabled;

/**
 * @brief	By default we show a status message for geo layers where we specify the number of points of interest found. Setting this property to NO will hide this message.
 */
@property (nonatomic, assign) BOOL geoStatusMessagesEnabled;

/**
 * @brief	By default we show a radar view in a geo layer. Setting this property to NO will hide this radar view.
 */
@property (nonatomic, assign) BOOL geoRadarEnabled;


/**
 * @brief	Open a screen with layer settings for currently loaded layer.
 *			If the settings are not available this method does nothing.
 *
 * @sa layerSettingsAvailable
 */
- (void)showLayerSettings;

/**
 * @brief	Start Scanning. Used to start a scan programmatically for example when 
 *			tap to scan is disabled
 *
 * @sa layerSettingsAvailable
 */
- (void)startScan;

/**
 * @brief	Open a map view for currently loaded layer.
 *			If the map representation is not available this method does nothing.
 *
 * @sa mapViewAvailable
 */
- (void)showMapView;

/**
 * @brief	Open the screenshot mode so that the user can take a screenshot and share it.
 */
- (void)openScreenshotMode;

/**
 * @brief	Pops out content attached to given reference image.
 *			If reference image or content is not available does nothing.
 */
- (void)popOutReferenceImageID:(NSString*)referenceImageId;

/**
 * @brief	Exits the popout mode and tries to lay the content on top of the reference image again.
 *			If its not in a popout mode then does nothing.
 */
- (void)exitPopout;
/**
 * @brief	Popout all tracked content
 */
- (void)popOutAllTrackedTargets;

@end
