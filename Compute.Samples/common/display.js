
const { openMessage, openWindow } = require('display');
const { setTimeout } = require('datetime')
const console = require('console');

let title = 'Hello';//console.read();
let body = 'Hello';//console.read();

openMessage(' ', ' ', () => {
    openWindow({}, window => {
        window.setTitle('HelloWorld');
        window.show();

        window.enableOpenGL();
        window.onFrame(() => {
            let x = 0;
            let y = 0;
            let z = 0;
            let str = "";
            window.swapBuffers(x, y, z, str);
        });
    }); 
});