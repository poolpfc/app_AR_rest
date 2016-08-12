/**
 * @file LayarSDKLocationProvider.h
 * @brief This file contains protocol declaration for LayarSDKLocationProvider.
 *
 * @copyright Copyright (c) 2015 Layar. All rights reserved.
 */

#import <CoreLocation/CoreLocation.h>

/**
 * @brief	The LayarSDKLocationProvider provides you with several callback methods that you can use to 
 *          a custom location provider in the SDK.
 *
 */
@protocol LayarSDKLocationProvider <NSObject>

- (void)setLocationUpdateBlock:(void(^)(CLLocation* location))completion;

- (void)setDesiredAccuracy:(CLLocationAccuracy)desiredAccuracy;

- (void)startLocationUpdates;

- (void)stopLocationUpdates;

@end
