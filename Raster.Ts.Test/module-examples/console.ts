
import console from 'console';

console.error('We have an error here !!!');
console.warn('Warning! This is a msg');
console.log('Log some logs...');

const boolean = console.readBoolean('Enter a boolean: ');
const number = console.readNumber('Enter a number: ');
const string = console.readString('Enter a string: ');
const object = console.readObject('Enter a object: ');

console.log(boolean, number, string, object);
