
const console = require('console');

// Int8Array, Int16Array, Int32Array
// Uint8Array, Uint8ClampedArray Uint16Array, Uint32Array
// Float32Array, Float62Array
let intArray = new Int32Array(10);

for(let i = 0; i < intArray.length; ++i) {
    intArray[i] = Math.random() * 100;
}

console.log(intArray);