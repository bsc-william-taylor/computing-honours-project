
const console = require('console');
const fs = require('fs');

const httpFile = fs.readJson('./vscode/launch.json');
console.log(httpFile);
