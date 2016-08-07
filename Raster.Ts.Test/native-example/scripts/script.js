
var windowSize = { x: 100, y: 100, w: 800, h: 500 };
var display = require('display');
var gl = require('opengl');

display.openWindow(windowSize, function(window) {
    window.setTitle('HelloWorld')
    window.show();
    window.enableOpenGL();
    window.onFrame(60, function() {
        gl.glMatrixMode(gl.GL_MODELVIEW);
        gl.glLoadIdentity();
        gl.glTranslatef(-0.5, -0.5, 0.0);

        gl.glClear(gl.GL_CLEAR_BUFFER_BIT);
        gl.glBegin(gl.GL_QUADS);
        gl.glColor3f(1.0, 0.0, 0.0);
        gl.glVertex2f(0.0, 0.0);
        gl.glVertex2f(1.0, 0.0);
        gl.glVertex2f(1.0, 1.0);
        gl.glVertex2f(0.0, 1.0);
        gl.glEnd();

        window.swapBuffers();
    })
});
