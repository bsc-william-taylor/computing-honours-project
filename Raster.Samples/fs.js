
const {log} = require('console');
const fs = require('fs');

const shapesFile = fs.readFile('http.js');

console.log(shapesFile.filename);
console.log(shapesFile.path);
console.log(shapesFile.ext);
console.log(shapesFile.contents.length);
console.log(shapesFile.contents);


