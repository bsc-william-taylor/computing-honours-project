
const { openFullscreenWindow, openMessageBox } = require('display');
const { setTimeout, setInterval } = require('datetime');
const console = require('console');
const http = require('http');
const gl = require('opengl');
const fs = require('fs');

let renderData = {};
let rotation = 0.0;

function bootstrap() {
    setTimeout(() => {
        http.get('www.williamsamtaylor.co.uk', '/shapes', 3010, res => {
            renderData = JSON.parse(res);
        });
    }, 1000);

    openFullscreenWindow(window => {
        window.setTitle('OpenGL Example');
        window.show();
        window.enableOpenGL();

        with(gl) {
            glEnable(GL_DEPTH_TEST);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0, 16.0 / 9.0, 0.1, 100.0);

            window.onFrame(() => {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearColor(0.0, 0.0, 0.0, 0.0);

                if(Object.keys(renderData).length > 0) {
                    renderObject(renderData.pyramid, GL_TRIANGLES);
                    renderObject(renderData.cube, GL_QUADS);
                    rotation += renderData.speed;
                }

                window.swapBuffers();
            });
        }
    });
}

function renderObject(object, type) {
    const { x, y, z } = object.translate;

    with(gl) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(x, y, z);
        glRotatef(rotation, 1.0, 1.0, 0.0);
        glBegin(type);

        object.faces.forEach((face, index) => {
            const { r, g, b } = object.colours[index]; 
            glColor3f(r, g, b);
            face.vertices.forEach(({ x, y, z }) => { 
                glVertex3f(x, y, z);
            });
        });

        glEnd();
    }
}

bootstrap();