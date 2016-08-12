package org.apache.cordova.core;

import com.layar.sdk.LayarSDK;
import com.layar.sdk.LayarSDKClient;
import com.layar.sdk.LayarSDKFragment;
import android.os.AsyncTask;
import android.util.Log;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;

public class LayarPlugin extends CordovaPlugin {
	public static final String TAG = "org.apache.cordova.core.LayarPlugin";

	public static final String ACTION_INITIALIZE = "initialize";
	public static final String ACTION_OPEN_SCANVIEW = "openScanView";
	public static final String ACTION_OPEN_URL = "openURL";
	public static final String ACTION_OPEN_LAYAR = "openLayar";
	
	public static final String ACTION_APPEND_TO_DEVICE_LOG = "appendToDeviceLog";
	public static final String ACTION_DISABLE_DEBUGLOGS = "disableDebugLogs";
	public static final String ACTION_ENABLE_DEBUGLOGS = "enableDebugLogs";

	private boolean debugEnabled = false;
	public void initialize(CordovaInterface cordova, CordovaWebView webView) {
		super.initialize(cordova, webView);
		debugEnabled = false;
	}

	@Override
	public void onDestroy() {
		super.onDestroy(); 
	}

	@Override
	public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
		if (action.equals(ACTION_INITIALIZE)) {
			this.initializeLayarSDK(args.optString(0), args.optString(1), callbackContext);
			return true;
		}
		if (action.equals(ACTION_OPEN_SCANVIEW)) {
			this.openScanView(callbackContext);
			return true;
		}
		if (action.equals(ACTION_OPEN_URL)) {
			this.openURL(args.optString(0), callbackContext);
			return true;
		}
		if (action.equals(ACTION_OPEN_LAYAR)) {
			this.openLayar(args.optString(0), callbackContext);
			return true;
		}
		if (action.equals(ACTION_APPEND_TO_DEVICE_LOG)) {
			this.appendToDeviceLog(args.optString(0), callbackContext);
			return true;
		}
		if (action.equals(ACTION_DISABLE_DEBUGLOGS)) {
			this.disableDebugLogs(callbackContext);
			return true;
		}
		if (action.equals(ACTION_ENABLE_DEBUGLOGS)) {
			this.enableDebugLogs(callbackContext);
			return true;
		}
		return false;
	}

	private void initializeLayarSDK(final String key, final String secret, CallbackContext callbackContext) {
		handleCommand(callbackContext, new LayarPluginCommand(){
			@Override
			public PluginResult run() {
				if	((key.length()<=0) || (secret.length()<=0)) {
					String message = "LayarPlugin Initialization Error: Invalid Key or Secret";
					javascriptConsoleWarn(message);
					return new PluginResult(PluginResult.Status.ERROR, message);
				}
				
				LayarSDK.initialize(cordova.getActivity(), key, secret);
				String message = "Layar Initialization Success";
				javascriptConsoleLog("Layar Initialization Success");
				return new PluginResult(PluginResult.Status.OK,message);
			}
		});
	}

	private void openScanView(CallbackContext callbackContext) {
		handleCommand(callbackContext, new LayarPluginCommand(){
			@Override
			public PluginResult run() {
				LayarSDKClient sdkClient = null;
				LayarSDK.startLayarActivity(cordova.getActivity(), sdkClient);	
				String message = "Open ScanView Success";
				return new PluginResult(PluginResult.Status.OK,message);
			}
		});
	}
	
	private void openURL(final String url,CallbackContext callbackContext) {
		handleCommand(callbackContext, new LayarPluginCommand(){
			@Override
			public PluginResult run() {
				if	(url.length()<=0) {
					String message = "LayarPlugin OpenURL Error: Invalid URL";
					javascriptConsoleWarn(message);
					return new PluginResult(PluginResult.Status.ERROR, message);
				}
				
				LayarSDKClient sdkClient = null;
				LayarSDK.startLayarActivity(cordova.getActivity(), sdkClient);					
				String message = "Open URL Success: "+url;
				return new PluginResult(PluginResult.Status.OK,message);
			}
		});
	}

	private void openLayar(final String layarName,CallbackContext callbackContext) {
		handleCommand(callbackContext, new LayarPluginCommand(){
			@Override
			public PluginResult run() {
				if	(layarName.length()<=0) {
					String message = "LayarPlugin OpenLayar Error: Invalid LayarName";
					javascriptConsoleWarn(message);
					return new PluginResult(PluginResult.Status.ERROR, message);
				}	
				
				LayarSDKClient sdkClient = null;
				LayarSDK.startLayarActivity(cordova.getActivity(), sdkClient, layarName);	
				String message = "Open Layar Success: " + layarName;
				return new PluginResult(PluginResult.Status.OK,message);
			}
		});
	}

	private void appendToDeviceLog(final String message, CallbackContext callbackContext) {
		handleCommand(callbackContext, new LayarPluginCommand() {
			@Override
			public PluginResult run() {
				if (message!=null && message.length()>0) {
					debugLog("[DOM] "+message);
					return new PluginResult(PluginResult.Status.OK,message);
				} else {
					return new PluginResult(PluginResult.Status.ERROR,"Log message not provided");
				}
			}
		}, true);			
	}

	private void disableDebugLogs(CallbackContext callbackContext) {
		handleCommand(callbackContext, new LayarPluginCommand() {

			@Override
			public PluginResult run() {
				debugEnabled = false;
				return new PluginResult(PluginResult.Status.OK);
			}
		}, true);
	}

	private void enableDebugLogs(CallbackContext callbackContext) {
		handleCommand(callbackContext, new LayarPluginCommand() {

			@Override
			public PluginResult run() {
				debugEnabled = false;
				return new PluginResult(PluginResult.Status.OK);
			}
		}, true);	
	}

	////////Async Task Handling ////////////////////////////////

	private void handleCommand(CallbackContext callbackContext, final LayarPluginCommand task) {
		handleCommand(callbackContext, task, false);
	}

	private void handleCommand(final CallbackContext callbackContext, final LayarPluginCommand task, boolean runInBackground) {
		if (runInBackground) {
			new AsyncTask<Void, Void, Void>() {

				@Override
				protected Void doInBackground(final Void... params) {

					try {
						sendResultOfCommand(callbackContext, task.run());
					} catch (Exception ex) {
						handleExceptionOfCommand(callbackContext, ex);
					}
					return null;
				}

			}.execute();
		} else {
			cordova.getActivity().runOnUiThread(new Runnable() {
				public void run() {

					try {
						sendResultOfCommand(callbackContext, task.run());
					} catch (Exception ex) {
						handleExceptionOfCommand(callbackContext, ex);
					}
				}
			});
		}
	}

	private void handleExceptionOfCommand(CallbackContext callbackContext, Exception exception) {

		Log.e(TAG, "Uncaught exception: " + exception.getMessage());
		Log.e(TAG, "Stack trace: " + exception.getStackTrace());

		// When calling without a callback from the client side the command can be null.
		if (callbackContext == null) {
			return;
		}

		callbackContext.error(exception.getMessage());
	}

	private void sendResultOfCommand(CallbackContext callbackContext, PluginResult pluginResult) {

		//debugLog("Send result: " + pluginResult.getMessage());
		if (pluginResult.getStatus()!=PluginResult.Status.OK.ordinal())
			debugWarn("WARNING: " + PluginResult.StatusMessages[pluginResult.getStatus()]);

		// When calling without a callback from the client side the command can be null.
		if (callbackContext == null) {
			return;
		}

		callbackContext.sendPluginResult(pluginResult);
	}

	private void debugLog(String message) {
		if (debugEnabled) {
			Log.d(TAG, message);
		}
	}

	private void debugWarn(String message) {
		if (debugEnabled) {
			Log.w(TAG, message);
		}
	}

	@SuppressWarnings("deprecation")
	private void javascriptConsoleLog(String message) {
		webView.sendJavascript("console.log('[Layar-Phonegap-Plugin] "+message+"')");
	}

	@SuppressWarnings("deprecation")
	private void javascriptConsoleWarn(String message) {
		webView.sendJavascript("console.warn('[Layar-Phonegap-Plugin] "+message+"')");
	}
}