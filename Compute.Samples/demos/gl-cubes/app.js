
const { openWindow } = require('display');
const console = require('console');
const glm = require('maths');
const gl = require('gl');
const fs = require('fs');

const shaders = { vs: fs.read('./vert.glsl'), fs: fs.read('./frag.glsl') };
const geometry = fs.readJson('./cube.json');
const texture = fs.readImage('./crate.jpg');

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

openWindow({ w: 1600, h: 900 }, window => {
    window.setTitle('Cubes Example');
    window.show();
    window.enableOpenGL();
    window.onClose(() => {
        fs.freeImage(texture)
    });

    with (gl) {
        const vs = createShader(GL_VERTEX_SHADER, shaders.vs.contents);
        const fs = createShader(GL_FRAGMENT_SHADER, shaders.fs.contents);
        const program = glCreateProgram();
        
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glUseProgram(program);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

        const vertexArrayObject = new Uint32Array(1);
        const vertexBuffer = new Uint32Array(1);
        const colourBuffer = new Uint32Array(1);
        const uvBuffer = new Uint32Array(1);
        const textureID = new Uint32Array(1);

        glGenTextures(1, textureID);
        glBindTexture(GL_TEXTURE_2D, textureID[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
        glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        const vertexData = Float32Array.from(geometry.cube);
        const colourData = Float32Array.from(geometry.colour);
        const uvData = Float32Array.from(geometry.uvs);

        glGenVertexArray(1, vertexArrayObject);
        glBindVertexArray(vertexArrayObject[0]);

        glGenBuffers(1, vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, vertexData.byteLength, vertexData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glGenBuffers(1, colourBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colourBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, colourData.byteLength, colourData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glGenBuffers(1, uvBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer[0]);
        glBufferData(GL_ARRAY_BUFFER, uvData.byteLength, uvData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

        const projection = glm.mat4.create();
        const model = glm.mat4.create();
        const view = glm.mat4.create();

        glm.mat4.perspective(projection, glm.glMatrix.toRadian(45.0), 4.0 / 3.0, 0.1, 100.0);
        glm.mat4.lookAt(view,
            glm.vec3.fromValues(4, 3, -3),
            glm.vec3.fromValues(0, 0, 0),
            glm.vec3.fromValues(0, 1, 0)
        );

        let rotation = 1.0;

        const number = 100;
        const translations = [], rotations = [];

        for(let i = 0; i < number; ++i) {
            const randScale = () => Math.random() * 10 - 5
            translations.push({x: randScale(), y: randScale(), z: randScale() });   
            rotations.push({x: Math.random(), y: Math.random(), z: Math.random() });   
        }

        window.onFrame(() => {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0, 0.0, 0.0, 0.0);

            const projectionLocation = glGetUniformLocation(program, "projection");
            const modelLocation = glGetUniformLocation(program, "model");
            const viewLocation = glGetUniformLocation(program, "view");

            for(let i = 0; i < translations.length; i++)
            {
                const {x, y, z} = translations[i];
                const scaleValue = 0.3 + x / 50.0;
                const scaleVector = glm.vec3.fromValues(scaleValue, scaleValue, scaleValue);
                const rotationVector = glm.vec3.fromValues(rotations[i].x, rotations[i].y, rotations[i].z);

                glm.mat4.identity(model);
                glm.mat4.translate(model, model, glm.vec3.fromValues(x, y, z));
                glm.mat4.scale(model, model, scaleVector);
                glm.mat4.rotate(model, model, glm.glMatrix.toRadian(rotation), rotationVector);
                
                glUniformMatrix4(projectionLocation, 1, GL_FALSE, Float32Array.from(projection));
                glUniformMatrix4(modelLocation, 1, GL_FALSE, Float32Array.from(model));
                glUniformMatrix4(viewLocation, 1, GL_FALSE, Float32Array.from(view));
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
         
            rotation++;

            window.swapBuffers();
        });
    }
});
