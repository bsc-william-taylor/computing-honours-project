
const { setInterval} = require('datetime');
const console = require('console');
const http = require('http');

http.get('www.williamsamtaylor.co.uk', '/apps/mgd/index.html', 80, () => {
    console.log('Got response');
});

setInterval(() => {}, 10000);