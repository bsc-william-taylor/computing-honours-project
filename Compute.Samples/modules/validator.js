
const validator = require('validator');
const console = require('console');

const email = console.read('enter an email');

console.log(`IsEmail ${validator.isEmail(email)}`);