const { openWindow } = require('display');
const gl = require('gl');

openWindow({ w: 800, h: 500 }, screen => {
    screen.show();
    screen.enableOpenGL();
    screen.onFrame(() => {
        gl.glClear(gl.GL_COLOR_BUFFER_BIT);
        gl.glBegin(gl.GL_TRIANGLES);
        gl.glVertex2f(-0.5, -0.5);
        gl.glVertex2f(0.0, 0.5);
        gl.glVertex2f(0.5, -0.5);
        gl.glEnd();

        screen.swapBuffers();
    });
});