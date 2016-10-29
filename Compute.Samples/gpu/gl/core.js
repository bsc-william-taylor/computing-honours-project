
const { openWindow } = require('display');
const console = require('console');
const gl = require('gl');

openWindow({}, window => {
    window.setTitle('');
    window.show();
    window.enableOpenGL();
    with(gl) {       
        const major = [,], minor = [,];
        glGetIntergerv(GL_MAJOR_VERSION, major);
        glGetIntergerv(GL_MINOR_VERSION, minor);

        console.log(glGetError(), glGetGraphicsResetStatus());
        console.log(major, minor);

        const vertices = Float64Array.from([ 1, 2, 3, 4, 5 ]);
        const buffer = new Uint32Array(1);
        glGenBuffers(1, buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices.byteLength, vertices, GL_STATIC_DRAW);

        console.log('Buffer ', buffer[0], glGetError() == GL_NO_ERROR);

        glDeleteBuffers(1, buffer);
    }
})


