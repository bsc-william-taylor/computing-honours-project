
const console = require('console');
const math = require('gl-matrix');


const myVector = math.vec4.create(1, 2, 3, 4);

const newVector = math.vec4.clone(myVector);
newVector[0] = 100;
console.log(newVector);