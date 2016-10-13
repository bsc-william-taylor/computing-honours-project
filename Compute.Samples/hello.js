
var global = this;

if(global.console) {
    console.log("HelloWorld");
} else {
    const console = require("console");
    console.log("HelloWorld");
}