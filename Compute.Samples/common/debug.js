
const { setTimeout } = require('datetime');
const console = require('console');
const debug = require('debug');

const process = this;
process.pid = debug.get();

function incoming(msg, port) {
    console.log(`incoming: ${msg}`);
}

function outgoing(msg) {
    console.log(`outgoing: ${msg}`);
}

debug.onmessage(incoming, outgoing);
debug.init();

setTimeout(x => x, 100000);