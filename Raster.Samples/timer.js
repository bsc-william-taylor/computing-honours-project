
const { setTimeout, setInterval, clearInterval, pause } = require('datetime');
const console = require('console');

pause(100);

const number = setInterval(() => {
    for(let i = 0; i < 3; ++i) {
        console.log(`HelloWorld ${i}`)
    }
}, 1000);


setTimeout(() => clearInterval(number), 2000);

for(let i = 0; i < 5; i++){
    setTimeout(() => console.log(`${i}`), i * 1000);
}