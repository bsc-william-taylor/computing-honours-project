
const { openMessage, openWindow } = require('display');
const { setTimeout } = require('datetime')
const console = require('console');

console.log('Enter a title and a body');

let title = console.read();
let body = console.read();

openMessage(title, body, () => {
    console.log('Hope you enjoyed your message!');

    openWindow({ x: 100, y: 100, w: 500, h:500 }, window => {
        window.setTitle('HelloWorld');
        window.show();
    });
});