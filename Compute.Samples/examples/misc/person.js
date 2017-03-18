
// Using ES2015 new class keyword
class Person extends ArrayBuffer {
    constructor() {
        super(268); // 268 bytes

        this.height = new Float64Array(this, 0, 1);
        this.name = new Int8Array(this, 4, 256);
        this.age = new Int32Array(this, 260, 1);
    }
}

let p = new Person();



let characters = new Uint8Array(10); 
let positive = new Uint32Array(10); 
let ratios = new Float64Array(100);


for(var i = 0; true; i++) {
    break;
}

for(let j = 0; true; j++) {
    break;
}

i++; // valid operation, i is a global variable
j++; // not valid operation j not in scope

const y = 0.0;
y = 0.0; // error can’t reassign const var


let x = 100.0;
let y = 100.0;

console.log(`${x} : ${y}`) // > 100 : 100

class Number extends Object {
    constructor() {
        this.value = 0.0;
    }
}


