
const console = require('console');
const http = require('http');

const html = JSON.parse(http.get('localhost', '/', 3000));

console.log(html);