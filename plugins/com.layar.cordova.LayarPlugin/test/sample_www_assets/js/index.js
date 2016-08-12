var Layar = {
    key : '<<<<<<<< YOUR KEY HERE >>>>>>>',

    secret : '<<<<<<<< YOUR KEY HERE >>>>>>>',
    
    success: function(result) {
        console.log(result);
    },

    failure: function(error) {
        alert("Error: " + error);
    },
};

var app = {
    // Application Constructor
    initialize: function() {
        this.bindEvents();
    },
    // Bind Event Listeners
    //
    // Bind any events that are required on startup. Common events are:
    // 'load', 'deviceready', 'offline', and 'online'.
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
    },
    
    // deviceready Event Handler
    //
    // The scope of 'this' is the event. In order to call the 'receivedEvent'
    // function, we must explicitly call 'app.receivedEvent(...);'
    onDeviceReady: function() {
        app.receivedEvent('deviceready');
        app.initializeLayarPlugin();
    },
    
    // Update DOM on a Received Event
    receivedEvent: function(id) {
        var parentElement = document.getElementById(id);
        var listeningElement = parentElement.querySelector('.listening');
        var receivedElement = parentElement.querySelector('.received');
        listeningElement.setAttribute('style', 'display:none;');
        receivedElement.setAttribute('style', 'display:block;');
        console.log('Received Event: ' + id);
    },
    
    //Initialize the Layar Plugin
    initializeLayarPlugin: function() {
        console.log('Enabling Debug Logs');
        LayarPlugin.enableDebugLogs()
        console.log('Initializing Layar Plugin');
        LayarPlugin.initialize(Layar.key, Layar.secret)
    },
    
    // Open the layar scan view
    openScanView: function() {
        LayarPlugin.openScanView().
        then(Layar.success).
        fail(Layar.failure).
        done()
    },
    
    // Open a layar URL
    openURL: function(url) {
        LayarPlugin.openURL(url).
        then(Layar.success).
        fail(Layar.failure).
        done()
    },
    
    // Open a layar URL
    openLayar: function(layarName) {
        LayarPlugin.openLayar(layarName).
        then(Layar.success).
        fail(Layar.failure).
        done()
    },
};
