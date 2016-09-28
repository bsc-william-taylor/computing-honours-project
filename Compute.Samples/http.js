
const console = require('console');
const http = require('http');

const address = 'localhost';
const page = '/';
const port = 3000;
const body = {};

http.get(address, page, port, res => {
    console.log(res);
});

http.post(address, page, port, body, res => {
    console.log(res);
});
