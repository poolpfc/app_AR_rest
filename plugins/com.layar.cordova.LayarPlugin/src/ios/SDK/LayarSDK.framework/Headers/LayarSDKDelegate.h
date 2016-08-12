/**
 * @file LayarSDKDelegate.h
 * @brief This file contains protocol declaration for LayarSDKDelegate.
 *
 * @copyright Copyright (c) 2013 Layar. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <LayarSDK/LayarSDKViewController.h>

@class LayarSDK;

/**
 * @brief	The LayarSDKDelegate provides you with several callback methods
 *			to inform you and allow you to override some activities.
 *
 * You get information about which layer has been loaded and when a
 * certain reference image is tracked etc.
 *
 * All callbacks are optional, so you only need to implement the ones you're
 * interested in.
 *
 * Many callbacks pass Layer and POI objects in form of dictionaries that contain
 * extended information about the campaign/layer and POI for which the callback is made.
 *
 * These dictionaries always use strings (NSString*) as keys.
 *
 * The following structure is guaranteed for POI objects:
 *<pre>
 *			{
 *				"id"		: (NSString*) The unique id which identifies a POI in the getPOIs response.
 *				"object"	: (NSDictionary*)
 *					{
 *						"url"			: (NSString*) The URL of the object to be displayed.
 *						"contentType"	: (NSString*) The content type of the object.
 *					}
 *			}
 </pre>
 *
 * For more information on POI objects see 'hotspots' documentation in the GetPOIs API doc
 * (https://www.layar.com/documentation/browser/api/getpois-response/hotspots/).
 * Note that not all fields specified in the GetPOIs API are available in POI object.
 *
 * The following structure is guaranteed for Layer objects:
 *<pre>
 *			{
 *				"name"		: (NSString*) The name of the layer
 *				"title"		: (NSString*) The title of the layer
 *				"icon"		: (NSString*) The URL of the layer's icon
 *			}
 </pre>
 *
 * Internally campaigns are related to layers
 * so the layer name is your campaign's name and the layer title is your
 * campaign's title.
 *
 * @headerfile LayarSDK/LayarSDK.h
 */
@protocol LayarSDKDelegate <NSObject>

@optional

/**
 * @brief	Called when the user has scanned a reference image
 *			and this reference image has been detected to be one of your pages
 *			in one of your campaigns, or when the user did launch a geo layer.
 *
 * @note	Internally campaigns are related to layers
 *			so the layerName is your campaign's name and the layerTitle is your
 *			campaign's title.
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	layerName						NSString*			The	name of the detected campaign
 * @param	layerTitle						NSString*			The title of the detected campaign
 * @param	recognizedReferenceImageName	NSString*			Name of recognized reference image in case the user has scanned a reference image, nil otherwise
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didLaunchLayer:(NSString*)layerName
	withTitle:(NSString*)layerTitle
	recognizedReferenceImageName:(NSString*)recognizedReferenceImageName
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when the user has scanned a reference image
 *			and this reference image has been detected to be one of your pages
 *			in one of your campaigns, or when the user did launch a geo layer.
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	layerObject						NSDictionary*		The	layer object for detected campaign. See protocol reference for detailed structure.
 * @param	recognizedReferenceImageName	NSString*			Name of recognized reference image in case the user has scanned a reference image, nil otherwise
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didLaunchLayerWithLayerObject:(NSDictionary*)layerObject
	recognizedReferenceImageName:(NSString*)recognizedReferenceImageName
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when the user has scanned a QR code and it is shown in AR
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	qrCodeText						NSString*			Full text of recognized QR code
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didRecognizeQRCode:(NSString*)qrCodeText
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called whenever the user scans something and a visual search query 
 *			will be sent to the server. The callee will get the image that will be
 *			sent to the Layar server for image recognition.
 *			Allows you to override the visual search API call.
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	image							UIImage*			Image captured from camera
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 *
 * @return	boolean indicating whether API call should be made or not
 *
 * @note	If this callback is not implemented by the delegate object, the SDK behaves as if the return value was YES.
 */
- (BOOL)layarSDK:(LayarSDK*)layarSdk shouldPerformVisualSearchForImage:(UIImage*)image
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when the layar sdk will make a request for pois. This callback enables the user of the SDK to customize the parameters being sent with the poi request. The entries in the returned dictionary will override the entries in the parameters before being sent to the server. New entries will be added. Note that in this manner a parameter cannot be removed. It can either be modified or added. 
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	parameters						NSDictionary*		The parameters being sent with the poi request.
 *
 * @return	NSDictionary* containing keys for entries that need to be modified or added to parameters with their value.
 */
- (NSDictionary*)layarSDK:(LayarSDK*)layarSdk willSendPOIRequestWithParameters:(NSDictionary*)parameters;

/**
 * @brief	Called whenever a response is received from the server for a visual search query
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	responseCode					NSUInteger			Response code received from the server. 0 for no error, nonzero for an error
 * @param	responseMessage					NSString*			Response message received from the server
 * @param	recognizedReferenceImagesForLayers		NSArray*	Dictionary containing all layer/campaign names and corresponding reference image names
 *																found by visual search. Dictionary keys are NSString* layer/campaign names.
 *																Dictionary values are NSArray* arrays of NSString* reference image names recognized 
 *																for the layer specified by dictionary key.
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didReceiveVisualSearchResultsWithResponseCode:(NSUInteger)responseCode
	responseMessage:(NSString*)responseMessage
	recognizedReferenceImagesForLayers:(NSDictionary*)recognizedReferenceImagesForLayers
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called whenever the SDK is going to pop-up a message indicating to the user 
 *			that no results were found. This will allow you to intercept this situation 
 *			and program your own behavior when this happens, e.g. replacing the pop-up message
 *			with your own instructions.
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	image							UIImage*			Image used for visual search (captured from camera)
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 *
 * @return	boolean indicating whether the SDK built-in pop-up should be shown.
 *
 * @note	Customization could also be done just by replacing assets and strings for these messages.
 * @note	If this callback is not implemented by the delegate object, the SDK behaves as if the return value was YES.
 */
- (BOOL)layarSDK:(LayarSDK*)layarSdk shouldShowNoResultsFoundForImage:(UIImage*)image
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Informs your application that after a campaign is loaded the visual 
 *			tracking of one of the pages has started. You are provided with the
 *			referenceImageName which relates to one of your pages as well as the
 *			layarName (campaign name) and the layarTitle (campaign title).
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	referenceImageName				NSString*			The name of the reference image
 * @param	layerName						NSString*			The name of the tracked campaign
 * @param	layerTitle						NSString*			The title of the tracked campaign
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didStartTrackingReferenceImage:(NSString*)referenceImageName
	withLayer:(NSString*)layerName
	withLayerTitle:(NSString*)layerTitle
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Informs your application that after a campaign is loaded the visual 
 *			tracking of one of the pages has started. You are provided with the
 *			referenceImageName which relates to one of your pages as well as the
 *			layarName (campaign name) and the layarTitle (campaign title).
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	referenceImageName				NSString*			The name of the reference image
 * @param	layerObject						NSDictionary*		The	layer object for tracked campaign. See protocol reference for detailed structure.
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didStartTrackingReferenceImage:(NSString*)referenceImageName
	withLayerObject:(NSDictionary*)layerObject
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Informs your application that visual tracking of one of the pages has stopped.
 *			You are provided with the referenceImageName which relates to one of your pages as well as the
 *			layarName (campaign name) and the layarTitle (campaign title).
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	referenceImageName				NSString*			The name of the reference image
 * @param	layerObject						NSDictionary*		The	layer object for tracked campaign. See protocol reference for detailed structure.
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didStopTrackingReferenceImage:(NSString*)referenceImageName
	withLayerObject:(NSDictionary*)layerObject
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when an augment is displayed on a POI
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiId							NSString*			The ID of the POI
 * @param	referenceImageName				NSString*			The name of the reference image
 * @param	layerName						NSString*			The name of the layer/campaign
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didShowAugmentForPOI:(NSString*)poiId
	referenceImageName:(NSString*)referenceImageName
	layer:(NSString*)layerName
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when an augment is displayed on a POI
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiObject						NSDictionary*		The	POI object. See protocol reference for detailed structure.
 * @param	referenceImageName				NSString*			The name of the reference image
 * @param	layerObject						NSDictionary*		The	layer object. See protocol reference for detailed structure.
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didShowAugmentForPOIWithPOIObject:(NSDictionary*)poiObject
	referenceImageName:(NSString*)referenceImageName
	layerObject:(NSDictionary*)layerObject
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when the user clicked on an augment
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiId							NSString*			The ID of the POI
 * @param	referenceImageName				NSString*			The name of the reference image or nil for Geo layers
 * @param	layerName						NSString*			The name of the layer/campaign
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didClickOnAugmentForPOI:(NSString*)poiId
	referenceImageName:(NSString*)referenceImageName
	layer:(NSString*)layerName
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when the user clicked on an augment
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiObject						NSDictionary*		The	POI object. See protocol reference for detailed structure.
 * @param	referenceImageName				NSString*			The name of the reference image or nil for Geo layers
 * @param	layerObject						NSDictionary*		The	layer object. See protocol reference for detailed structure.
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didClickOnAugmentForPOIWithPOIObject:(NSDictionary*)poiObject
	referenceImageName:(NSString*)referenceImageName
	layerObject:(NSDictionary*)layerObject
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when an AR video starts playing (either directly, or when the user clicks the play/replay button)
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiId							NSString*			The ID of the POI
 * @param	referenceImageName				NSString*			The name of the reference image
 * @param	layerName						NSString*			The name of the layer/campaign
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didStartPlayingVideoForPOI:(NSString*)poiId
	referenceImageName:(NSString*)referenceImageName
	layer:(NSString*)layerName
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when an AR video starts playing (either directly, or when the user clicks the play/replay button)
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiObject						NSDictionary*		The	POI object. See protocol reference for detailed structure.
 * @param	referenceImageName				NSString*			The name of the reference image
 * @param	layerObject						NSDictionary*		The	layer object. See protocol reference for detailed structure.
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didStartPlayingVideoForPOIWithPOIObject:(NSDictionary*)poiObject
	referenceImageName:(NSString*)referenceImageName
	layerObject:(NSDictionary*)layerObject
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when an AR audio starts playing (either directly, or when the user clicks the play/replay button)
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiId							NSString*			The ID of the POI
 * @param	referenceImageName				NSString*			The name of the reference image
 * @param	layerName						NSString*			The name of the layer/campaign
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didStartPlayingAudioForPOI:(NSString*)poiId
referenceImageName:(NSString*)referenceImageName
		   layer:(NSString*)layerName
onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when an AR audio starts playing (either directly, or when the user clicks the play/replay button)
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiObject						NSDictionary*		The	POI object. See protocol reference for detailed structure.
 * @param	referenceImageName				NSString*			The name of the reference image
 * @param	layerObject						NSDictionary*		The	layer object. See protocol reference for detailed structure.
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didStartPlayingAudioForPOIWithPOIObject:(NSDictionary*)poiObject
referenceImageName:(NSString*)referenceImageName
	 layerObject:(NSDictionary*)layerObject
onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when a POI gets the focus
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiId							NSString*			The ID of the POI
 * @param	layerName						NSString*			The name of the layer/campaign
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */

- (void)layarSDK:(LayarSDK*)layarSdk didFocusPOI:(NSString*)poiId
	layer:(NSString*)layerName
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when a POI gets the focus
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiObject						NSDictionary*		The	POI object. See protocol reference for detailed structure.
 * @param	layerObject						NSDictionary*		The	layer object. See protocol reference for detailed structure.
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didFocusPOIWithPOIObject:(NSDictionary*)poiObject
	layerObject:(NSDictionary*)layerObject
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when an action will be triggered, either by a user click or automatically
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiId							NSString*			The ID of the POI
 * @param	referenceImageName				NSString*			The name of the reference image (nil for geo layers)
 * @param	layerName						NSString*			The name of the layer/campaign
 * @param	action							NSDictionary*		Action object. Refer to GetPOIs API doc for field descriptions (http://layar.com/documentation/browser/api/getpois-response/actions/)
																String field values are stored using NSString objects, numerical ans boolean field values are stored as NSNumber objects
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 *
 * @return	boolean indicating whether the action should be triggered or not.
 *
 * @note	If this callback is not implemented by the delegate object, the SDK behaves as if the return value was YES.
 */
- (BOOL)layarSDK:(LayarSDK*)layarSdk shouldTriggerActionForPOI:(NSString*)poiId
	referenceImageName:(NSString*)referenceImageName
	layer:(NSString*)layerName
	action:(NSDictionary*)action
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when an action will be triggered, either by a user click or automatically
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiObject						NSDictionary*		The	POI object. See protocol reference for detailed structure.
 * @param	referenceImageName				NSString*			The name of the reference image (nil for geo layers)
 * @param	layerObject						NSDictionary*		The	layer object. See protocol reference for detailed structure.
 * @param	action							NSDictionary*		Action object. Refer to GetPOIs API doc for field descriptions (http://layar.com/documentation/browser/api/getpois-response/actions/)
																String field values are stored using NSString objects, numerical ans boolean field values are stored as NSNumber objects
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 *
 * @return	boolean indicating whether the action should be triggered or not.
 *
 * @note	If this callback is not implemented by the delegate object, the SDK behaves as if the return value was YES.
 */
- (BOOL)layarSDK:(LayarSDK*)layarSdk shouldTriggerActionForPOIWithPOIObject:(NSDictionary*)poiObject
	referenceImageName:(NSString*)referenceImageName
	layerObject:(NSDictionary*)layerObject
	action:(NSDictionary*)action
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when an action is triggered, either by a user click or automatically
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiId							NSString*			The ID of the POI
 * @param	referenceImageName				NSString*			The name of the reference image (nil for geo layers)
 * @param	layerName						NSString*			The name of the layer/campaign
 * @param	action							NSDictionary*		Action object. Refer to GetPOIs API doc for field descriptions (http://layar.com/documentation/browser/api/getpois-response/actions/)
																String field values are stored using NSString objects, numerical and boolean field values are stored as NSNumber objects
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didTriggerActionForPOI:(NSString*)poiId
	referenceImageName:(NSString*)referenceImageName
	layer:(NSString*)layerName
	action:(NSDictionary*)action
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when an action is triggered, either by a user click or automatically
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	poiObject						NSDictionary*		The	POI object. See protocol reference for detailed structure.
 * @param	referenceImageName				NSString*			The name of the reference image (nil for geo layers)
 * @param	layerObject						NSDictionary*		The	layer object. See protocol reference for detailed structure.
 * @param	action							NSDictionary*		Action object. Refer to GetPOIs API doc for field descriptions (http://layar.com/documentation/browser/api/getpois-response/actions/)
																String field values are stored using NSString objects, numerical and boolean field values are stored as NSNumber objects
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk didTriggerActionForPOIWithPOIObject:(NSDictionary*)poiObject
	referenceImageName:(NSString*)referenceImageName
	layerObject:(NSDictionary*)layerObject
	action:(NSDictionary*)action
	onViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when a view controller enters pop-out mode
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk
	didEnterPopOutModeOnViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when a view controller exits pop-out mode
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk
	didExitPopOutModeOnViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when a view controller goes into the screenshot view
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk
didEnterScreenshotModeOnViewController:(UIViewController<LayarSDKViewController>*)viewController;

/**
 * @brief	Called when a view controller goes out of the screenshot view
 *
 * @param	layarSdk						LayarSDK*			Reference to the LayarSDK object
 * @param	viewController					UIViewController<LayarSDKViewController>*	Reference to a view controller where this callback originates
 */
- (void)layarSDK:(LayarSDK*)layarSdk
didExitScreenshotModeOnViewController:(UIViewController<LayarSDKViewController>*)viewController;
@end
