
const console = require('console');
const fs = require('fs');

const launchFile = fs.readJson('./vscode/launch.json');

console.log(launchFile);
