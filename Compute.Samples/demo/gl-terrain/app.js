
const { openWindow } = require('display');
const maths = require('maths');
const gl = require('gl');
const fs = require('fs');

const terrain = fs.readJson('./terrain.json');
const shaders = {
    vs: fs.read('./terrain.vs.glsl'),
    fs: fs.read('./terrain.fs.glsl')
};

function createShader(shaderType, shaderSource) {
    with (gl) {
        const shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, shaderSource, 0);
        glCompileShader(shader);
        return shader;
    }
}

Math.seed = seed => {
    return () => {
        if (seed == 0) return 0;
        seed = Math.sin(seed) * 10000;
        return (seed - Math.floor(seed)) / 2.0
    };
};

const makeTerrain = desc => {
    const incX = desc.grid.x, incY = desc.grid.y;
    const random = Math.seed(desc.seed);
    const vertices = [], heights = {};

    for (let y = 0; y < desc.grid.h; y += desc.grid.y) {
        for (let x = 0; x < desc.grid.w; x += desc.grid.x) {
            heights[x + incX] = heights[x + incX] || {};
            heights[x] = heights[x] || {};
            heights[x + incX][y + incY] = random();
            heights[x + incX][y] = random();
            heights[x][y + incY] = random();
            heights[x][y] = random();
        }
    }

    for (let y = 0; y < desc.grid.h; y += desc.grid.y) {
        for (let x = 0; x < desc.grid.w; x += desc.grid.x) {
            vertices.push(x, heights[x][y], y);
            vertices.push(x + incX, heights[x + incX][y], y);
            vertices.push(x + incX, heights[x + incX][y + incY], y + incY);
            vertices.push(x + incX, heights[x + incX][y + incY], y + incY);
            vertices.push(x, heights[x][y + incY], y + incY);
            vertices.push(x, heights[x][y], y);
        }
    }

    return vertices;
}

function createProgram() {
    with (gl) {
        const program = glCreateProgram();
        glAttachShader(program, createShader(GL_VERTEX_SHADER, shaders.vs.contents));
        glAttachShader(program, createShader(GL_FRAGMENT_SHADER, shaders.fs.contents));
        glLinkProgram(program);
        glUseProgram(program);
        return program;
    }
}

openWindow({ x: 450, y: 250, w: 800, h: 600 }, window => {
    window.setTitle('Terrain Generation Example');
    window.show();
    window.enableOpenGL();

    with (gl) {
        const vertexArrayObject = new Uint32Array(1), vertexBuffer = new Uint32Array(1);
        const terrainData = makeTerrain(terrain.terrain);
        const vertexData = Float32Array.from(terrainData);
        const program = createProgram();

        glGenVertexArray(1, vertexArrayObject);
        glBindVertexArray(vertexArrayObject[0]);
        glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glGenBuffers(1, vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, vertexData.byteLength, vertexData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        const projection = maths.mat4.create();
        const model = maths.mat4.create();
        const view = maths.mat4.create();

        maths.mat4.perspective(projection, maths.glMatrix.toRadian(45.0), 4.0 / 3.0, 0.1, 100.0);
        maths.mat4.lookAt(view,
            maths.vec3.fromValues(0, 4.5, 0),
            maths.vec3.fromValues(8, 0, 8),
            maths.vec3.fromValues(0, 1, 0)
        );

        window.onFrame(() => {
            const projectionLocation = glGetUniformLocation(program, "projection");
            const modelLocation = glGetUniformLocation(program, "model");
            const viewLocation = glGetUniformLocation(program, "view");

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.5, 0.5, 0.5, 0.5);
            glUniformMatrix4(projectionLocation, 1, GL_FALSE, Float32Array.from(projection));
            glUniformMatrix4(modelLocation, 1, GL_FALSE, Float32Array.from(model));
            glUniformMatrix4(viewLocation, 1, GL_FALSE, Float32Array.from(view));
            glDrawArrays(GL_TRIANGLES, 0, vertexData.length / 3);

            window.swapBuffers();
        });
    }
});
