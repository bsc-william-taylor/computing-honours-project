

import { Bootstrapper } from './bootstrapper.ts';
import { setInterval } from 'time';
import console from 'console';
import fs from 'fs';

let renderData = fs.readJson('shapes.json');
let rotation = 0.0;

const app = new Bootstrapper();

function renderObject(gl, object, type) {
    const { x, y, z } = object.translate;

    gl.glMatrixMode(gl.GL_MODELVIEW);
    gl.glLoadIdentity();
    gl.glTranslatef(x, y, z);
    gl.glRotatef(rotation, 1.0, 1.0, 0.0);
    gl.glBegin(type);

    object.faces.forEach((face, index) => {
        const colour = object.colours[index];
        gl.glColor3f(colour.r, colour.g, colour.b);
        face.vertices.forEach(vertex => {
            gl.glVertex3f(vertex.x, vertex.y, vertex.z);
        });
    });

    gl.glEnd();
}

setInterval(() => {
    renderData = fs.readJson('shapes.json');
}, 1000);


app.bootstrap({ x: '100', y: '100', w: '800', h: '500'}, gl => {
    gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT);
    gl.glClearColor(0.0, 0.0, 0.0, 0.0);

    renderObject(gl, renderData.pyramid, gl.GL_TRIANGLES);
    renderObject(gl, renderData.cube, gl.GL_QUADS);

    rotation += 0.5;
});
