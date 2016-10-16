
const process = this;

const { setInterval, setTimeout } = require('datetime');
const console = require('console');
const debug = require('debug');
process.pid = debug.get();
debug.init();


setInterval(function() {
    console.log('HelloWorld');
}, 2000);






function incoming(msg, port) {
    //console.log(Object.keys(v8debug.Debug));
    //console.log(v8debug.Debug.debuggerFlags())
}

function outgoing(msg) {
    //console.log(`outgoing: ${msg}`);
}

debug.onmessage(incoming, outgoing);
