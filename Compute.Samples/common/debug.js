
const { setTimeout, setInterval, pause } = require('datetime');
const console = require('console');
const debug = require('debug');

const process = this;
process.pid = debug.get();

function incoming(msg, port) {
    //console.log(`incoming: ${msg}`);
}

function outgoing(msg) {
    const json = JSON.parse(msg);

    if(!json.success) 
    {
        //console.log(`outgoing: ${msg}`);
    }
}

debug.onmessage(incoming, outgoing);
debug.init();


setInterval(() => {
    console.log('Hi');
}, 2000);