
const console = require('console');
const http = require('http');

const address = 'www.williamsamtaylor.co.uk';
const page = '/apps/mgd/index.html';
const port = 80;

console.log(http.get(address, page, 80));
