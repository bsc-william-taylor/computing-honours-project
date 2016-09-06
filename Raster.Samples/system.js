
const console = require('console');
const system = require('system');

console.log(system.os);
console.log(system.battery());
console.log(system.hardware);
console.log(system.instructions);

system.exit();
