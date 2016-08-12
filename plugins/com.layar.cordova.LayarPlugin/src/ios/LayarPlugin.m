//
//  LayarPlugin.m
//  phonegap-layar-plugin
//
//  Created by Sumeru Chatterjee on 05/12/2014.
//  Copyright (c) 2014 Layar B.V. All rights reserved.
//

#import <LayarSDK/LayarSDK.h>
#import "LayarPlugin.h"

typedef CDVPluginResult* (^LayarPluginCommandHandler)(CDVInvokedUrlCommand*);

@interface LayarPlugin () <LayarSDKDelegate>

@property (atomic, strong) LayarSDK* layarSDK;

@property (atomic, assign) BOOL initialized;

@property (atomic, assign) BOOL initializing;

@property (atomic, assign) BOOL scanning;

@property (nonatomic, assign) BOOL debugLogEnabled;

@property (nonatomic, strong) UIButton* closeButton;

@end

@implementation LayarPlugin

#pragma mark - PhoneGap Commands

- (void)pluginInitialize
{
	self.debugLogEnabled = NO;
	self.initialized = NO;
	self.scanning = NO;
	self.initializing = NO;
}

#pragma mark - PhoneGap Commands for Layar API

- (void)initialize:(CDVInvokedUrlCommand*)command
{
	[self handleCommand:command inBackground:NO withBlock:^CDVPluginResult*(CDVInvokedUrlCommand* command) {
		
		NSString* consumerKey = [command.arguments objectAtIndex:0];
		NSString* consumerSecret = [command.arguments objectAtIndex:1];
		
		if (self.initialized)
		{
			[self javascriptConsoleLog:@"LayarPlugin Already Initialized"];
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"LayarPlugin Already Initialized"];
		}
		
		if (self.initializing)
		{
			[self javascriptConsoleLog:@"LayarPlugin Already Initialing"];
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"LayarPlugin Already Initializing"];
		}
		
		if (![consumerKey isKindOfClass:[NSString class]] || !consumerKey.length || ![consumerSecret isKindOfClass:[NSString class]] || !consumerSecret.length) {
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"LayarPlugin Intialization Error: Invalid Consumer Key or Secret"];
		}
		
		self.initializing = YES;
		@synchronized(self)
		{
			if (!self.initialized) {
				self.layarSDK = [LayarSDK layarSDKWithConsumerKey:consumerKey  andConsumerSecret:consumerSecret andDelegate:self];
				self.initialized = YES;
			}
		}
		
		CDVPluginResult *pluginResult = nil;
		if (self.layarSDK)
		{
			self.layarSDK.popOutsEnabled = YES;
			pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"LayarPlugin Intialization Success"];
			[self javascriptConsoleLog:@"LayarPlugin Intialization Success"];
		} else
		{
			pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"LayarPlugin Intialization Error"];
			[self javascriptConsoleWarn:@"LayarPlugin Intialization Error"];
		}
		
		self.initializing = NO;
		return pluginResult;
	}];
}

- (void)openScanView:(CDVInvokedUrlCommand*)command
{
	[self handleCommand:command inBackground:YES withBlock:^CDVPluginResult*(CDVInvokedUrlCommand* command) {
		if (!self.initialized)
		{
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"LayarPlugin Not Initialized"];
		}
		
		if (self.scanning)
		{
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"LayarPlugin Already Scanning"];
		}
		
		__block CDVPluginResult *pluginResult = nil;
		dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
		[self.layarSDK viewControllerForScanningWithCompletion:^(UIViewController<LayarSDKViewController>* viewController) {
			
			if (!viewController) {
				pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"LayarPlugin OpenScanView Error: Could not open scan view"];
				[self javascriptConsoleWarn:@"LayarPlugin Open ScanView Error"];
				dispatch_semaphore_signal(semaphore);
				return;
			}
			
			[self.viewController presentViewController:viewController animated:YES completion:^{
				[viewController.view addSubview:self.closeButton];
			}];
			
			self.scanning = YES;
			pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"ScanView Open Success"];
			dispatch_semaphore_signal(semaphore);
		}];
		
		while(dispatch_semaphore_wait(semaphore, DISPATCH_TIME_NOW)) {
			[[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
		}
		return pluginResult;
	}];
}

- (void)openURL:(CDVInvokedUrlCommand*)command
{
	[self handleCommand:command inBackground:YES withBlock:^CDVPluginResult*(CDVInvokedUrlCommand* command) {
		
		if (!self.initialized)
		{
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"LayarPlugin Not Initialized"];
		}
		
		if (self.scanning)
		{
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"LayarPlugin Already Scanning"];
		}
		
		NSString* url = [command.arguments objectAtIndex:0];
		if (![url isKindOfClass:[NSString class]] || !url.length || ![NSURL URLWithString:url]) {
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[NSString stringWithFormat:@"LayarPlugin OpenURL Error: Invalid URL %@",url]];
		}
		
		__block CDVPluginResult *pluginResult = nil;
		dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
		[self.layarSDK viewControllerForURL:[NSURL URLWithString:url] withCompletion:^(UIViewController<LayarSDKViewController>* viewController) {
			
			if (!viewController) {
				pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[NSString stringWithFormat:@"LayarPlugin OpenURL Error: Invalid URL %@",url]];
				[self javascriptConsoleWarn:@"LayarPlugin OpenURL Error"];
				dispatch_semaphore_signal(semaphore);
				return;
			}
			
			[self.viewController presentViewController:viewController animated:YES completion:^{
				[viewController.view addSubview:self.closeButton];
			}];
			
			pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[NSString stringWithFormat:@"OpenURL Success %@",url]];
			self.scanning = YES;
			dispatch_semaphore_signal(semaphore);
		}];
		
		while(dispatch_semaphore_wait(semaphore, DISPATCH_TIME_NOW)) {
			[[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
		}
		return pluginResult;
	}];
}

- (void)openLayar:(CDVInvokedUrlCommand*)command
{
	[self handleCommand:command inBackground:YES withBlock:^CDVPluginResult*(CDVInvokedUrlCommand* command) {
		
		
		if (!self.initialized)
		{
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"LayarPlugin Not Initialized"];
		}
		
		if (self.scanning)
		{
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"LayarPlugin Already Scanning"];
		}
		
		NSString* layarName = [command.arguments objectAtIndex:0];
		if (![layarName isKindOfClass:[NSString class]] || !layarName.length ) {
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[NSString stringWithFormat:@"LayarPlugin OpenLayar Error: Invalid Layar Name %@",layarName]];
		}
		
		NSString* url = [NSString stringWithFormat:@"layar://%@",layarName];
		
		__block CDVPluginResult *pluginResult = nil;
		dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
		[self.layarSDK viewControllerForURL:[NSURL URLWithString:url] withCompletion:^(UIViewController<LayarSDKViewController>* viewController) {
			
			if (!viewController) {
				[self javascriptConsoleWarn:@"LayarPlugin OpenLayar Error"];
				pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[NSString stringWithFormat:@"LayarPlugin OpenLayar Error: Invalid Layar Name %@",layarName]];
				dispatch_semaphore_signal(semaphore);
				return;
			}
			
			[self.viewController presentViewController:viewController animated:YES completion:^{
				[viewController.view addSubview:self.closeButton];
			}];
			
			pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[NSString stringWithFormat:@"OpenLayar Success %@",layarName]];
			self.scanning = YES;
			dispatch_semaphore_signal(semaphore);
		}];
		
		while(dispatch_semaphore_wait(semaphore, DISPATCH_TIME_NOW)) {
			[[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
		}
		return pluginResult;
	}];
}

#pragma mark - Accessors

- (UIButton*)closeButton
{
	if (!_closeButton) {
		_closeButton = [[UIButton alloc]
								 initWithFrame:CGRectMake(0.0f, 20.0f, 80.0f, 40.0f)];
		[_closeButton setTitle:@"Close" forState:UIControlStateNormal];
		[_closeButton addTarget:self action:@selector(dismissScanView) forControlEvents:UIControlEventTouchUpInside];
	}
	return _closeButton;
}

#pragma mark - Selectors

- (void)dismissScanView
{
	__weak LayarPlugin* weakSelf = self;
	[self.viewController dismissViewControllerAnimated:YES completion:^{
		weakSelf.scanning = NO;
	}];
}

#pragma mark - Phonegap commands for debugging

- (void)appendToDeviceLog:(CDVInvokedUrlCommand*)command
{
	[self handleCommand:command withBlock:^CDVPluginResult*(CDVInvokedUrlCommand* command) {
		NSString* message = [command.arguments objectAtIndex:0];
		if (message.length)
		{
			[self deviceLog:[@"[DOM] " stringByAppendingString:message]];
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:message];
		}
		else
		{
			return [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
		}
	}];
}

- (void)disableDebugLogs:(CDVInvokedUrlCommand*)command
{
	[self handleCommand:command withBlock:^CDVPluginResult*(CDVInvokedUrlCommand* command) {
		self.debugLogEnabled = false;
		[self javascriptConsoleLog:@"Device Logging Disabled"];
		return [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
	}];
}

- (void)enableDebugLogs:(CDVInvokedUrlCommand*)command
{
	[self handleCommand:command withBlock:^CDVPluginResult*(CDVInvokedUrlCommand* command) {
		self.debugLogEnabled = true;
		[self javascriptConsoleLog:@"Device Logging Enabled"];
		return [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
	}];
}

#pragma mark - Private Methods for Handling Cordova Commands

- (void)handleCommand:(CDVInvokedUrlCommand*)command withBlock:(LayarPluginCommandHandler)handlerBlock
{
	[self handleCommand:command inBackground:NO withBlock:handlerBlock];
}

- (void)handleCommand:(CDVInvokedUrlCommand*)command inBackground:(BOOL)inBackground withBlock:(LayarPluginCommandHandler)handlerBlock
{
	//NSLog(@"Received Message: %@.%@", command.className, command.methodName);
	[self deviceLog:@"Received Message: %@.%@", command.className, command.methodName];
	void (^safeExecutionBlock)() = ^{
		@try {
			CDVPluginResult* commandResult = handlerBlock(command);
			[self.commandDelegate sendPluginResult:commandResult callbackId:command.callbackId];
			[self deviceLog:@"Sent Response: (%@) %@",commandResult.status, commandResult.message];
		}
		@catch (NSException * exception) {
			[self handleException:exception forCommand:command];
		}
	};

	if (inBackground)
	{
		[self.commandDelegate runInBackground:safeExecutionBlock];
	}
	else
	{
		safeExecutionBlock();
	}
}

- (void)handleException:(NSException*)exception forCommand:(CDVInvokedUrlCommand*)command
{
	[self deviceLog:@"Uncaught exception: %@", exception.description];
	[self deviceLog:@"Stack trace: %@", [exception callStackSymbols]];

	if (command.callbackId)
	{
		CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:exception.description];
		[self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
	}
}

#pragma mark - Logging Methods

- (void)deviceLog:(NSString*)format, ...
{
	if (self.debugLogEnabled)
	{
		va_list args;
		va_start(args, format);
		NSString* msg = [[NSString alloc] initWithFormat:format arguments:args];
		va_end(args);
		NSLog(@"%@", msg);
	}
}

- (void)javascriptConsoleWarn:(NSString*)format, ...
{
	va_list args;
	va_start(args, format);
	NSString* msg = [[NSString alloc] initWithFormat:format arguments:args];
	va_end(args);

	NSString* javascriptErrorLoggingStatement = [NSString stringWithFormat:@"console.warn('[Phonegap-Layar-Plugin] %@')", msg];
	[self.commandDelegate evalJs:javascriptErrorLoggingStatement];
}

- (void)javascriptConsoleLog:(NSString*)format, ...
{
	va_list args;
	va_start(args, format);
	NSString* msg = [[NSString alloc] initWithFormat:format arguments:args];
	va_end(args);

	NSString* javascriptErrorLoggingStatement = [NSString stringWithFormat:@"console.log('[Phonegap-Layar-Plugin] %@')", msg];
	[self.commandDelegate evalJs:javascriptErrorLoggingStatement];
}

#pragma mark - LayarSDKDelegate

- (void)layarSDK:(LayarSDK*)layarSdk didLaunchLayer:(NSString*)layerName withTitle:(NSString*)layerTitle recognizedReferenceImageName:(NSString*)recognizedReferenceImageName onViewController:(UIViewController<LayarSDKViewController>*)viewController {
	
	[self deviceLog:@"Did Open Layar: %@",layerName];
}

@end