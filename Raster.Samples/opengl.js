
const { openWindow, openMessageBox } = require('display');
const { setInterval } = require('datetime');
const console = require('console');
const http = require('http');
const gl = require('opengl');
const fs = require('fs');

let renderData = {};
let rotation = 0.0;

function enableOpenGL({ glEnable, glMatrixMode, glLoadIdentity, gluPerspective }) {
    glEnable(gl.GL_DEPTH_TEST);
    glMatrixMode(gl.GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 16.0 / 9.0, 0.1, 100.0);
}

function bootstrap(windowSettings, onRender) {
    setInterval(() => renderData = JSON.parse(http.get('www.williamsamtaylor.co.uk', '/shapes', 3010)), 1000);

    openWindow(windowSettings, window => {
        window.setTitle('OpenGL Example');
        window.show();
        window.enableOpenGL();

        enableOpenGL(gl);

        window.onFrame(() => {
            if(Object.keys(renderData).length) {
                onRender(gl);
                window.swapBuffers();
            }
        });
    });
}

function renderObject(gl, object, type) {
    const { x, y, z } = object.translate;

    gl.glMatrixMode(gl.GL_MODELVIEW);
    gl.glLoadIdentity();
    gl.glTranslatef(x, y, z);
    gl.glRotatef(rotation, 1.0, 1.0, 0.0);
    gl.glBegin(type);

    object.faces.forEach((face, index) => {
        const { r, g, b } = object.colours[index]; 
        gl.glColor3f(r, g, b);
        face.vertices.forEach(({ x, y, z }) => {
            gl.glVertex3f(x, y, z);
        });
    });

    gl.glEnd();
}

bootstrap({ x: '100', y: '100', w: '800', h: '500'}, gl => {
    gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT);
    gl.glClearColor(0.0, 0.0, 0.0, 0.0);

    renderObject(gl, renderData.pyramid, gl.GL_TRIANGLES);
    renderObject(gl, renderData.cube, gl.GL_QUADS);

    rotation += renderData.speed;
});