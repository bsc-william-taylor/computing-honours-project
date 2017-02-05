
const console = require('console');
const http = require('http');

const address = 'localhost';
const page = '/';
const port = 3000;
const body = {};

http.post(address, page, port, body, (res, err) => console.log(res, err));
http.get(address, page, port, (res, err) => console.log(res, err));