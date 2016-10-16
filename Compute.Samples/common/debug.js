
const { setInterval, pause } = require('datetime');
const moment = require('moment');
const console = require('console');

function example() {
    console.log(moment().format())
}

for(var i = 0; i < 1000; i++)
{
    console.log(moment().format());
    pause(100);
}
//setInterval(example, 2500);