
const { openWindow } = require('display');
const console = require('console');
const maths = require('maths');
const gl = require('gl');
const fs = require('fs');

const shaders = { vs: fs.read('./vert.glsl'), fs: fs.read('./frag.glsl') };
const terrain = fs.readJson('./terrain.json');

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

Math.seed = function(s) {
    return function() {
        if(s == 0) {
            return 0;
        } else {
            s = Math.sin(s) * 10000; 
            return (s - Math.floor(s)) / 20.0
        }
    };
};

const makeTerrain = desc => {
    const vertices = [];
    const random = Math.seed(desc.seed);
    
    for(let y = 0; y < desc.grid.h; y += desc.grid.y) {
        for(let x = 0; x < desc.grid.w; x += desc.grid.x) {       
            vertices.push(x,   0.0, y);
            vertices.push(x+1, 0.0, y);
            vertices.push(x+1, 0.0, y+1);
            vertices.push(x+1, 0.0, y+1);
            vertices.push(x,   0.0, y+1);
            vertices.push(x,   0.0, y);
        }
    }

    return vertices;
}

openWindow({ x: 450, y: 250, w: 800, h: 600 }, window => {
    window.setTitle('Terrain Generation Example');
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

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_DEPTH_TEST);

        const terrainData = makeTerrain(terrain.terrain);
        const vertexArrayObject = new Uint32Array(1);
        const vertexBuffer = new Uint32Array(1);
        const vertexData = Float32Array.from(terrainData);

        glGenVertexArray(1, vertexArrayObject);
        glBindVertexArray(vertexArrayObject[0]);
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
            maths.vec3.fromValues(0, 0.5, 0),
            maths.vec3.fromValues(1, 0, 1),
            maths.vec3.fromValues(0, 1, 0)
        );

        window.onFrame(() => {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0, 0.0, 0.0, 0.0);

            const projectionLocation = glGetUniformLocation(program, "projection");
            const modelLocation = glGetUniformLocation(program, "model");
            const viewLocation = glGetUniformLocation(program, "view");
            
            glUniformMatrix4(projectionLocation, 1, GL_FALSE, Float32Array.from(projection));
            glUniformMatrix4(modelLocation, 1, GL_FALSE, Float32Array.from(model));
            glUniformMatrix4(viewLocation, 1, GL_FALSE, Float32Array.from(view));
            glDrawArrays(GL_TRIANGLES, 0, vertexData.length / 3);

            window.swapBuffers();
        });
    }
});
