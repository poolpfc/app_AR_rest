# Phonegap Layar Plugin

This is the official plugin for Layar in Apache Cordova/PhoneGap!

The Layar plugin for [Apache Cordova](http://incubator.apache.org/cordova/) allows you to use the JavaScript code in your Cordova application as you use in your web application to build an augmented reality app.

* Supported on PhoneGap (Cordova) v3.3.0 and above.
* This plugin is built with
	* iOS Layar SDK 8_4_4 20160315 b4e8c76
	* Android Layar SDK 8_4_4 20160229 1c600ef

## Plugin Requirements and Set-Up

To use this plugin you will need to make sure you've registered with Layar and obtained your Layar Key and Layar Secret.

## Limitations

Callbacks are not supported in the plugin. With the plugin you can launch a scan view or open a layar but cannot get javascript callbacks about what is going on. To implement callbacks please use the iOS and Android SDK natively.

## Install Guide

This plugin requires [Cordova CLI](http://cordova.apache.org/docs/en/3.5.0/guide_cli_index.md.html).

To install the plugin in your app, execute the following (replace variables where necessary):

```sh
# Create initial Cordova app
$ cordova create myApp
$ cd myApp/

$ cordova platform add ios (For iOS)
$ cordova platform add android (For Android)

# Add the plugin
$ cordova -d plugin add <path-to-phonegap-layar-plugin>
```

Its that simple!

## Example App

We have provided an example app with the plugin. You can just copy the javascript file [index.js](https://bitbucket.org/layardev/phonegap-layar-plugin/src/master/test/sample_www_assets/js/index.js) and the corresponding html file [index.html](https://bitbucket.org/layardev/phonegap-layar-plugin/src/master/test/sample_www_assets/index.html)and use it in your example app. Please dont forget to replace your key and secret in the index.js file.

Optionally you can also automatically generate an example and run it using dart. Just run 'dart test/run-sample.dart <ios/android>' from the command line.

## API 

### Initialize

`LayarPlugin.initialize(Layar Key, Layar Secret)`

 Initializes the layar plugin with a consumer key and secret

 parameter (key) The oauth consumer key. Please contact layer support to obtain a license if you dont have one.

 parameter (secret) The consumer secret. Please contact layer support to obtain a license if you dont have one.
 
 return {Q.Promise}  which you can use to implement success and failure callbacks. 

 For example:

 `LayarPlugin.initialize('asdasd;adiaspdiasdpa', 'asdasdasdasdadsasd').
  then(Layar.success).
  fail(Layar.failure).
  done()`

### Open Scan View

`LayarPlugin.openScanView()`
	
 Opens the scan view.

 return {Q.Promise}  which you can use to implement success and failure callbacks. 

 For example:

 `LayarPlugin.openScanView().
  then(Layar.success).
  fail(Layar.failure).
  done()`

### Open URL

`LayarPlugin.openURL(Layar URL)`

 Opens a layar view with a layar URL. Especially useful for opening geo layers

 parameter (url) The URL to open. Example-> layar://carscen7g?param=value
 
 return {Q.Promise}  which you can use to implement success and failure callbacks. 

 For example:.

 `LayarPlugin.openURL('layar://carscen7g?param=value').
  then(Layar.success).
  fail(Layar.failure).
  done()`

### Open Layar

`LayarPlugin.openLayar(Layar Name)`

Opens a layar view with a layar name. Especially useful for opening geo layers

 parameter (layarname) The name of the layar to open. Example-> carscen7g
 
 return {Q.Promise}  which you can use to implement success and failure callbacks. 

 For example:

 `LayarPlugin.openLayar('carscen7g').
  then(Layar.success).
  fail(Layar.failure).
  done()`
