
const { openWindow } = require('display');
const maths = require('maths');
const gl = require('gl');
const fs = require('fs');

const shaders = { vs: fs.read('./vert.glsl'), fs: fs.read('./frag.glsl') };
const geometry = fs.readJson('./cube.json');
const texture = fs.readImage('./crate.jpg');

const translations = [], rotations = [];
const projection = maths.mat4.create();
const model = maths.mat4.create();
const view = maths.mat4.create();

function createShader(shaderType, shaderSource) {
    with (gl) {
        const shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, shaderSource, 0);
        glCompileShader(shader);
        return shader;
    }
}

function createShaders() {
    with (gl) {
        const program = glCreateProgram();
        const vs = createShader(GL_VERTEX_SHADER, shaders.vs.contents);
        const fs = createShader(GL_FRAGMENT_SHADER, shaders.fs.contents);
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glUseProgram(program);
        return program;
    }
}

function createBuffer(data, index, count) {
    with (gl) {
        const vertexBuffer = new Uint32Array(1);
        glGenBuffers(1, vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, data.byteLength, data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, 0, 0);
        return vertexBuffer;
    }
}

function createTexture(texture) {
    with (gl) {
        const textureID = new Uint32Array(1);
        glGenTextures(1, textureID);
        glBindTexture(GL_TEXTURE_2D, textureID[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
        glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        return textureID;
    }
}

function onRender(program, rotation) {
    const projectionLocation = gl.glGetUniformLocation(program, "projection");
    const modelLocation = gl.glGetUniformLocation(program, "model");
    const viewLocation = gl.glGetUniformLocation(program, "view");

    for (let i = 0; i < translations.length; i++) {
        const { x, y, z } = translations[i];
        const scaleValue = 0.3 + x / 50.0;
        const scaleVector = maths.vec3.fromValues(scaleValue, scaleValue, scaleValue);
        const rotationVector = maths.vec3.fromValues(rotations[i].x, rotations[i].y, rotations[i].z);

        maths.mat4.identity(model);
        maths.mat4.translate(model, model, maths.vec3.fromValues(x, y, z));
        maths.mat4.scale(model, model, scaleVector);
        maths.mat4.rotate(model, model, maths.glMatrix.toRadian(rotation), rotationVector);

        gl.glUniformMatrix4(projectionLocation, 1, gl.GL_FALSE, Float32Array.from(projection));
        gl.glUniformMatrix4(modelLocation, 1, gl.GL_FALSE, Float32Array.from(model));
        gl.glUniformMatrix4(viewLocation, 1, gl.GL_FALSE, Float32Array.from(view));
        gl.glDrawArrays(gl.GL_TRIANGLES, 0, 36);
    }
}

function onLoad() {
    const vao = new Uint32Array(1);
    gl.glGenVertexArray(1, vao);
    gl.glBindVertexArray(vao[0]);
    gl.glEnable(gl.GL_DEPTH_TEST);
    gl.glEnable(gl.GL_TEXTURE_2D);

    createTexture(texture);
    createBuffer(Float32Array.from(geometry.cube), 0, 3);
    createBuffer(Float32Array.from(geometry.colour), 1, 3);
    createBuffer(Float32Array.from(geometry.uvs), 2, 2);

    maths.mat4.perspective(projection, maths.glMatrix.toRadian(45.0), 4.0 / 3.0, 0.1, 100.0);
    maths.mat4.lookAt(view, maths.vec3.fromValues(4, 3, -3),
        maths.vec3.fromValues(0, 0, 0),
        maths.vec3.fromValues(0, 1, 0)
    );

    for (let i = 0; i < 100; ++i) {
        translations.push({ x: Math.random() * 10 - 5, y: Math.random() * 10 - 5, z: Math.random() * 10 - 5 });
        rotations.push({ x: Math.random(), y: Math.random(), z: Math.random() });
    }
}

openWindow({ x: 450, y: 250, w: 800, h: 600 }, window => {
    window.onClose(() => fs.freeImage(texture));
    window.setTitle('Cubes Example');
    window.show();
    window.enableOpenGL();

    onLoad();

    let program = createShaders();
    let rotation = 1.0;
    window.onFrame(() => {
        gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT);
        gl.glClearColor(0.0, 0.0, 0.0, 0.0);

        onRender(program, rotation);
        rotation += 0.5;

        window.swapBuffers();
    });
});
