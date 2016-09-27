
const console = require('console');
const http = require('http');

const address = 'localhost';
const page = '/hkj';
const port = 3000;

http.get(address, page, port, res => {
    console.log(res);
});

http.post(address, page, port, {}, res => {
    console.log(res);
});
