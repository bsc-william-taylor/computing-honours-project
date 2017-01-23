
const { openMessage, openWindow } = require('display');
const { setTimeout } = require('datetime')
const console = require('console');

let title = console.read();
let body = console.read();

openMessage(title, body, () => {
    openWindow({}, window => {
        window.setTitle('HelloWorld');
        window.show();

        window.enableOpenGL();
        window.onFrame(() => {
            window.swapBuffers();
        });
    }); 
});