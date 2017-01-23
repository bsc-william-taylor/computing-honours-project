
const console = require('console');
const gl = require('gl');
const cl = require('cl');

with(cl && gl) {
    console.log(glGetError() == GL_NO_ERROR);
}