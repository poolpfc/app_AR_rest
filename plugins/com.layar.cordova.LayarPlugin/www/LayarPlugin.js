/****************************************
 *
 * LayarPlugin.js
 *
 * Created By Sumeru Chatterjee on 5/12/2014.
 *
 * Version: 0.1
 ****************************************
 * See the README.md for instructions on how to use this file
 ****************************************/

var exec = require('cordova/exec');
var _ = require('com.layar.cordova.LayarPlugin.underscorejs');
var Q = require('com.layar.cordova.LayarPlugin.Q');

function LayarPlugin () {
}

//Methods for layar javascript api

/**
 * Initializes the layar plugin with a consumer key and secret
 *
 * @param {key} The consumer key. Please contact layer support to obtain a license if you dont have one.
 *
 * @param {secret} The consumer secret. Please contact layer support to obtain a license if you dont have one.
 *
 * @return {Q.Promise} Returns a promise which is resolved as soon as the
 * native layer acknowledged the dispatch of the request to stop advertising.
 */
LayarPlugin.prototype.initialize = function(key, secret) {
  return this._promisedExec('initialize', [key, secret]);
};

/**
 * Opens a scan view which you can then use to scan for vision layars.
 *
 * @return {Q.Promise} Returns a promise which is resolved as soon as the
 * native layer acknowledged the dispatch of the request to stop advertising.
 */
LayarPlugin.prototype.openScanView = function() { 
  return this._promisedExec('openScanView', []);
};

         
/**
 * Opens the layar for a given URL. This is especially useful when you want to open a geo layer.
 *
 * @return {Q.Promise} Returns a promise which is resolved as soon as the
 * native layer acknowledged the dispatch of the request to stop advertising.
 */
LayarPlugin.prototype.openURL = function(url) {
  return this._promisedExec('openURL', [url]);
};
         
         
/**
 * Opens the layar with a given name. This is especially useful when you want to open a geo layer.
 *
 * @return {Q.Promise} Returns a promise which is resolved as soon as the
 * native layer acknowledged the dispatch of the request to stop advertising.
 */
LayarPlugin.prototype.openLayar = function(layarName) {
  return this._promisedExec('openLayar', [layarName]);
};

//Methods for layar javascript api debugging

/**
 * Disables debug logging in the native layer. Use this method if you want
 * to prevent this plugin from writing to the device logs.
 *
 * @returns {Q.Promise} Returns a promise which is resolved as soon as the
 * native layer has set the logging level accordingly.
 */
LayarPlugin.prototype.disableDebugLogs = function() {
  return this._promisedExec('disableDebugLogs', []);
};

/**
 * Enables debug logging in the native layer. Use this method if you want
 * a debug the inner workings of this plugin.
 *
 * @returns {Q.Promise} Returns a promise which is resolved as soon as the
 * native layer has set the logging level accordingly.
 */
LayarPlugin.prototype.enableDebugLogs = function() {
   return this._promisedExec('enableDebugLogs', []);
};

/**
 * Appends the provided [message] to the device logs.
 * Note: If debug logging is turned off, this won't do anything.
 *
 * @param {String} message The message to append to the device logs.
 *
 * @returns {Q.Promise} Returns a promise which is resolved with the log
 * message received by the native layer for appending. The returned message
 * is expected to be equivalent to the one provided in the original call.
 */
LayarPlugin.prototype.appendToDeviceLog = function(message) {
   return this._promisedExec('appendToDeviceLog', [message]);
};

//Private Methods

/**
 * Wraps a Cordova exec call into a promise, allowing the client code to
 * operate with those promises instead of callbacks.
 *
 * @param {String} method The name of the method in the native layer to be
 * called by Cordova.
 *
 * @param {Array} commandArgs An array of arguments to be passed for the
 * native layer. Defaults to an empty array if omitted.
 *
 * @returns {Q.Promise}
 */
LayarPlugin.prototype._promisedExec = function (method, commandArgs) {
  commandArgs = _.isArray(commandArgs) ? commandArgs : [];
  var deferred = Q.defer();
  exec(deferred.resolve, deferred.reject, 'LayarPlugin', method, commandArgs);
  return deferred.promise;
};

module.exports = new LayarPlugin()