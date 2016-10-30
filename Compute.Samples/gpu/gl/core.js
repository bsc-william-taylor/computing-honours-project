
const { openWindow } = require('display');
const console = require('console');
const fs = require('fs');
const gl = require('gl');

const triangle = [ -0.8, -1.0, 0.1, 0.0, 1.0, 0.1, 0.8, -1.0, 0.1 ];
const vertShader = fs.read('./vert.glsl');
const fragShader = fs.read('./frag.glsl');

function createShader(shaderType, shaderSource) {
    with(gl) {
        const shader = glCreateShader(shaderType);
        glShaderSource(shader, shaderSource.length, shaderSource, 0);
        glCompileShader(shader);

        const compileStatus = [,], logLength = [,];
        glGetShaderiv(shader, GL_COMPILE_STATUS, compileStatus);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, logLength);

        if(compileStatus[0] != GL_TRUE) {
            const log = [,];
            glGetShaderInfoLog(shader, logLength[0], logLength[0], log)
            console.log('Compile error', log[0]);
        }

        return shader;
    }
}

openWindow({ w: 720, h: 480 }, window => {
    window.setTitle('VAO + VBO');
    window.show();
    window.enableOpenGL();

    with(gl) {       
        const VAO = new Uint32Array(1), VBO = new Uint32Array(1), data = Float32Array.from(triangle);
        const program = glCreateProgram();
        const vs = createShader(GL_VERTEX_SHADER, vertShader.contents);
        const fs = createShader(GL_FRAGMENT_SHADER, fragShader.contents);
        
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glUseProgram(program);
        glGenVertexArray(1, VAO);
        glBindVertexArray(VAO[0]);
        glGenBuffers(1, VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, data.byteLength, data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        window.onFrame(() => {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            window.swapBuffers();
        });

        window.onClose(() => {
            glDeleteVertexArray(1, VAO);
            glDeleteBuffers(1, VBO);
            glDeleteProgram(program);
            glDeleteShader(vs);
            glDeleteShader(fs);
        });
    }
})