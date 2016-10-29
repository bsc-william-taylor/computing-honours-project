
const { openWindow } = require('display');
const console = require('console');
const gl = require('gl');

openWindow({}, window => {
    window.setTitle('');
    window.show();
    window.enableOpenGL();

    
    with(gl) {
        const err = glGetError();
        
        if(err != GL_NO_ERROR)
        {
            console.log('Oh dear we have an error', err)
        }
        
        const major = [,], minor = [,];
        glGetIntergerv(GL_MAJOR_VERSION, major);
        glGetIntergerv(GL_MINOR_VERSION, minor);
        
        console.log(major, minor);

        glFinish();
        glFlush();
    }
})


