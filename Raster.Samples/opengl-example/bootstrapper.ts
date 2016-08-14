
import { openWindow } from 'display';
import gl from 'opengl';

export class Bootstrapper {
    setupOpenGL({ glEnable, glMatrixMode, glLoadIdentity, gluPerspective }) {
        glEnable(gl.GL_DEPTH_TEST);
        glMatrixMode(gl.GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, 16.0 / 9.0, 0.1, 100.0);
    }

    bootstrap(windowSettings, onRender) {
        openWindow(windowSettings, window => {
            window.setTitle('Basic OpenGL Triangle');
            window.show();
            window.enableOpenGL();

            this.setupOpenGL(gl);

            window.onFrame(60, () => {
                onRender(gl);
                window.swapBuffers();
            });
        });
    }
}
