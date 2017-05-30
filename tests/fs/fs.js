
const console = require('console');
const fs = require('fs');

let image = fs.readImage('image.jpg');
let json = fs.readJson('demo.json');

console.log(`${image.width} : ${image.height}`);
console.log(JSON.stringify(json));

fs.freeImage(image);
