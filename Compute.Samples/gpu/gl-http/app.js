
const { openWindow } = require('display');
const { setTimeout } = require('datetime');
const console = require('console');
const async = require('async');
const http = require('http');
const gl = require('gl');
const fs = require('fs');

function renderObject(object, type, rotation) {
    with(gl) {
        const { x, y, z } = object.translate;

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(x, y, z);
        glRotatef(rotation, 1.0, 1.0, 0.0);
        glBegin(type);

        object.faces.forEach((face, index) => {
            const { r, g, b } = object.colours[index];
            glColor3f(r, g, b);
            face.vertices.forEach(({ x, y, z }) => glVertex3f(x, y, z));
        });

        glEnd();
    }
}

function bootstrap(renderData) {
    openWindow({ w: 800, h: 500 }, window => {
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
}

async.series([
    function(next) {
        http.get('www.williamsamtaylor.co.uk', '/shapes', 3010, (res, err) => {
            if(err) {
                next('Could not get drawing data', null);
            } else {
                next(null, JSON.parse(res));
            }
        });
    }
], function(err, json) {
    if(err) {
        console.log(err)
    } else {
        bootstrap(json[0]);
    }
});
