
const console = require('console');
console.log(this);


// Int8Array, Int16Array, Int32Array
// Uint8Array, Uint8ClampedArray Uint16Array, Uint32Array
// Float32Array, Float62Array
const int8Array = new Int8Array(10);

for(let i = 0; i < int8Array.length; ++i) {
    int8Array[i] = Math.random() * 100;
}

//console.log(int8Array);