
const { openFullscreenWindow, openMessage } = require('display');
const { setTimeout } = require('datetime');
const console = require('console');
const http = require('http');
const gl = require('opengl');
const fs = require('fs');

function renderObject(object, type, rotation) {
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

const promise = new Promise((resolve, reject) => {
    http.get('www.williamsamtaylor.co.uk', '/shapes', 3010, (res, err) => {
        if(err) {
            reject('Could not get drawing data');
        } else {
            resolve(JSON.parse(res));
        }
    });
}).then(renderData => {
    openFullscreenWindow(window => {
        window.setTitle('OpenGL Example');
        window.show();
        window.enableOpenGL();
  
        let rotation = 0.0;

        with(gl) {
            glEnable(GL_DEPTH_TEST);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0, 16.0 / 9.0, 0.1, 100.0);

            window.onFrame(() => {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearColor(0.0, 0.0, 0.0, 0.0);

                if(Object.keys(renderData).length > 0) {
                    renderObject(renderData.pyramid, GL_TRIANGLES, rotation);
                    renderObject(renderData.cube, GL_QUADS, rotation);
                    rotation += renderData.speed;
                }

                window.swapBuffers();
            });
        }
    });
}, error => openMessage('Error', error));