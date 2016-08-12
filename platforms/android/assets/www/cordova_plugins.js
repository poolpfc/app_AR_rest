cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "id": "com.layar.cordova.LayarPlugin.underscorejs",
        "file": "plugins/com.layar.cordova.LayarPlugin/www/lib/underscore-min-1.6.js",
        "pluginId": "com.layar.cordova.LayarPlugin",
        "runs": true
    },
    {
        "id": "com.layar.cordova.LayarPlugin.Q",
        "file": "plugins/com.layar.cordova.LayarPlugin/www/lib/q.min.js",
        "pluginId": "com.layar.cordova.LayarPlugin",
        "runs": true
    },
    {
        "id": "com.layar.cordova.LayarPlugin.LayarPlugin",
        "file": "plugins/com.layar.cordova.LayarPlugin/www/LayarPlugin.js",
        "pluginId": "com.layar.cordova.LayarPlugin",
        "merges": [
            "LayarPlugin"
        ]
    },
    {
        "id": "cordova-plugin-camera.Camera",
        "file": "plugins/cordova-plugin-camera/www/CameraConstants.js",
        "pluginId": "cordova-plugin-camera",
        "clobbers": [
            "Camera"
        ]
    },
    {
        "id": "cordova-plugin-camera.CameraPopoverOptions",
        "file": "plugins/cordova-plugin-camera/www/CameraPopoverOptions.js",
        "pluginId": "cordova-plugin-camera",
        "clobbers": [
            "CameraPopoverOptions"
        ]
    },
    {
        "id": "cordova-plugin-camera.camera",
        "file": "plugins/cordova-plugin-camera/www/Camera.js",
        "pluginId": "cordova-plugin-camera",
        "clobbers": [
            "navigator.camera"
        ]
    },
    {
        "id": "cordova-plugin-camera.CameraPopoverHandle",
        "file": "plugins/cordova-plugin-camera/www/CameraPopoverHandle.js",
        "pluginId": "cordova-plugin-camera",
        "clobbers": [
            "CameraPopoverHandle"
        ]
    }
];
module.exports.metadata = 
// TOP OF METADATA
{
    "cordova-plugin-whitelist": "1.2.2",
    "com.layar.cordova.LayarPlugin": "8.4.4",
    "cordova-plugin-compat": "1.0.0",
    "cordova-plugin-camera": "2.2.0"
};
// BOTTOM OF METADATA
});