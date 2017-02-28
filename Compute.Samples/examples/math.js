
const { mat4, vec4, vec3 } = require('maths');
const console = require('console');

let matrix = mat4.create(); // identity matrix
let vector = vec4.create(); // empty vector

mat4.translate(matrix, matrix, vec3.fromValues(5.0, 0.0, 0.0));
mat4.scale(matrix, matrix, vec3.fromValues(2.0, 2.0, 2.0));

vec4.add(vector, vector, vec4.fromValues(1.0, 1.0, 0.0, 0.0));
vec4.sub(vector, vector, vec4.fromValues(5.0, 0.0, 2.0, 0.0));

console.log(`Matrix: ${matrix}`);
console.log(`Vector: ${vector}, Length: ${vec4.length(vector)}`);