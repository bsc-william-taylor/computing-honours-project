
const { setTimeout } = require('time');
const console = require('console');

setTimeout(() => {
    for(let i = 0; i < 5; ++i) {
        console.log(`HelloWorld ${i}`)
    }
}, 1500);