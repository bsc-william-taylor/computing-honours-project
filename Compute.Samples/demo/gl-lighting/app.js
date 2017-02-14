
const { openWindow } = require('display');
const console = require('console');
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

        const compileStatus = [,], logLength = [,];
        glGetShaderiv(shader, GL_COMPILE_STATUS, compileStatus);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, logLength);

        if (compileStatus[0] != GL_TRUE) {
            const log = [,];
            glGetShaderInfoLog(shader, logLength[0], logLength[0], log)
            console.log('Compile error', log[0]);
        }

        return shader;
    }
}

openWindow({ x: 450, y: 250, w: 800, h: 600 }, window => {
    window.setTitle('Basic Lighting');
    window.show();
    window.enableOpenGL();

    with (gl) {
        const vs = createShader(GL_VERTEX_SHADER, shaders.vs.contents);
        const fs = createShader(GL_FRAGMENT_SHADER, shaders.fs.contents);
        const program = glCreateProgram();
        
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glUseProgram(program);
        glEnable(GL_DEPTH_TEST);

        const vertexArrayObject = new Uint32Array(1);
        const vertexBuffer = new Uint32Array(1);
        const normalBuffer = new Uint32Array(1);
        const vertexData = Float32Array.from(geometry.cube);
        const normalData = Float32Array.from(geometry.normals);

        glGenVertexArray(1, vertexArrayObject);
        glBindVertexArray(vertexArrayObject[0]);

        glGenBuffers(1, vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, vertexData.byteLength, vertexData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glGenBuffers(1, normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, normalData.byteLength, normalData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        const projection = maths.mat4.create(), view = maths.mat4.create();

        maths.mat4.perspective(projection, maths.glMatrix.toRadian(45.0), 4.0 / 3.0, 0.1, 100.0);
        maths.mat4.lookAt(view,
            maths.vec3.fromValues(4, 3, -3),
            maths.vec3.fromValues(0, 0, 0),
            maths.vec3.fromValues(0, 1, 0)
        );

        let rotation = 0;

        window.onFrame(() => {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2, 0.2, 0.2, 0.2);

            const projectionLocation = glGetUniformLocation(program, "projection");
            const modelLocation = glGetUniformLocation(program, "model");
            const viewLocation = glGetUniformLocation(program, "view");

            const model = maths.mat4.create();
            maths.mat4.rotate(model, model, maths.glMatrix.toRadian(rotation), maths.vec3.fromValues(0.0, -1.0, 0.0));
            rotation += 0.25;

            glUniformMatrix4(projectionLocation, 1, GL_FALSE, Float32Array.from(projection));
            glUniformMatrix4(modelLocation, 1, GL_FALSE, Float32Array.from(model));
            glUniformMatrix4(viewLocation, 1, GL_FALSE, Float32Array.from(view));
            glDrawArrays(GL_TRIANGLES, 0, vertexData.length / 3);
            
            window.swapBuffers();
        });
    }
});
