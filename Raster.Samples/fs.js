
const console = require('console');
const fs = require('fs');

const shapesFile = fs.readFile('shapes.json');

console.log(shapesFile.contents);