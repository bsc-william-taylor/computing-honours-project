
const console = require('console');
const fs = require('fs');

const httpFile = fs.readJson('./web-page/server/shapes.json');

console.log(httpFile);


fs.spacing(2);
fs.writeJson('helloworld.json', httpFile);
