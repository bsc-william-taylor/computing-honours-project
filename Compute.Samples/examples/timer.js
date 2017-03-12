
const datetime = require('datetime');
const console = require('console');

const { setTimeout, setInterval, pause } = datetime;

setInterval(() => console.log('1 second has passed'), 1000);
setTimeout(() => console.log('5 second has passed'), 5000);

pause(100);