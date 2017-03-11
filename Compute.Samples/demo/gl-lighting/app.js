
const { openWindow } = require('display');
const maths = require('maths');
const gl = require('gl');
const fs = require('fs');

const geometry = fs.readJson('./cube.json');
const shaders = {
    vs: fs.read('lighting.vs.glsl'),
    fs: fs.read('lighting.fs.glsl')
};

function createShader(shaderType, shaderSource) {
    with (gl) {
        const shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, shaderSource, 0);
        glCompileShader(shader);
        return shader;
    }
}

function configureDisplay(callback) {
    openWindow({ x: 450, y: 250, w: 800, h: 600 }, window => {
        window.setTitle('Basic Lighting');
        window.show();
        window.enableOpenGL();

        callback(window);
    });
}

function createProgram() {
    with (gl) {
        const vs = createShader(GL_VERTEX_SHADER, shaders.vs.contents);
        const fs = createShader(GL_FRAGMENT_SHADER, shaders.fs.contents);

        const program = glCreateProgram();
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

configureDisplay(window => {
    let projection = maths.mat4.create(), view = maths.mat4.create();
    let program = createProgram(), vao = new Uint32Array(1);
    let rotation = 0;

    with (gl) {
        glGenVertexArray(1, vao);
        glBindVertexArray(vao[0]);
        glEnable(GL_DEPTH_TEST);

        createBuffer(Float32Array.from(geometry.cube), 0, 3);
        createBuffer(Float32Array.from(geometry.normals), 1, 3);

        maths.mat4.perspective(projection, maths.glMatrix.toRadian(45.0), 4.0 / 3.0, 0.1, 100.0);
        maths.mat4.lookAt(view,
            maths.vec3.fromValues(4, 3, -3),
            maths.vec3.fromValues(0, 0, 0),
            maths.vec3.fromValues(0, 1, 0)
        );

        window.onFrame(() => {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2, 0.2, 0.2, 0.2);

            const projectionLocation = glGetUniformLocation(program, "projection");
            const modelLocation = glGetUniformLocation(program, "model");
            const viewLocation = glGetUniformLocation(program, "view");
            const model = maths.mat4.create();

            maths.mat4.rotate(model, model, maths.glMatrix.toRadian(rotation), maths.vec3.fromValues(0.0, -1.0, 0.0));

            glUniformMatrix4(projectionLocation, 1, GL_FALSE, Float32Array.from(projection));
            glUniformMatrix4(modelLocation, 1, GL_FALSE, Float32Array.from(model));
            glUniformMatrix4(viewLocation, 1, GL_FALSE, Float32Array.from(view));
            glDrawArrays(GL_TRIANGLES, 0, geometry.cube.length / 3);

            window.swapBuffers();
            rotation += 0.25;
        });
    }
});