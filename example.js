// Node.js OkHound phrase spotter example script
// * npm install
// * node example.js

var okhound = require('okhound');
var mic = require('mic');


okhound.setThreshold(0.4);


var micInstance = mic({ 'rate': '16000', 'channels': '1' });
var micInputStream = micInstance.getAudioStream();

micInputStream.on('data', function(data) {
  var arrayBuffer = new Uint8Array(data).buffer;
  var arrayBufferView = new Int16Array(arrayBuffer);

  var phraseDetected = okhound.processSamples(arrayBufferView);
  if (phraseDetected) {
    console.log("'Ok Hound' spotted! Sensitivity:", okhound.getThreshold());
    micInstance.stop();
  }
});
 
micInputStream.on('error', function(err) {
  console.log("Error in Input Stream", err);
});
 
micInstance.start();