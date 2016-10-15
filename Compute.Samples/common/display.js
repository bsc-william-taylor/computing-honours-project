
const { openMessage, openFullscreenWindow } = require('display');
const { setTimeout } = require('datetime')
const console = require('console');

console.log('Enter a title and a body');

let title = 'Hello';//console.read();
let body = 'Hello';//console.read();

openMessage(title, body, () => {
    //console.log('Hope you enjoyed your message!');

    openFullscreenWindow(window => {
        window.setTitle('HelloWorld');
        window.show();

        window.enableOpenGL();
        window.onFrame(() => {
            window.swapBuffers();
        });
    });
});