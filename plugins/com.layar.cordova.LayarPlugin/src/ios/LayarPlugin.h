//
//  LayarPlugin.h
//  phonegap-layar-plugin
//
//  Created by Sumeru Chatterjee on 05/12/2014.
//  Copyright (c) 2014 Layar B.V. All rights reserved.
//

#import <Cordova/CDV.h>

@interface LayarPlugin : CDVPlugin

- (void)initialize:(CDVInvokedUrlCommand*)command;

- (void)openScanView:(CDVInvokedUrlCommand*)command;

- (void)openURL:(CDVInvokedUrlCommand*)command;

- (void)openLayar:(CDVInvokedUrlCommand*)command;

- (void)appendToDeviceLog:(CDVInvokedUrlCommand*)command;

- (void)disableDebugLogs:(CDVInvokedUrlCommand*)command;

- (void)enableDebugLogs:(CDVInvokedUrlCommand*)command;

@end
