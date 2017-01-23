
const console = require('console');
const system = require('system');

const toString = str => JSON.stringify(str, null, 4)

console.log(toString(system.instructions));
console.log(toString(system.os));
console.log(toString(system.battery()));
console.log(toString(system.hardware))