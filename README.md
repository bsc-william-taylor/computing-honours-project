
<img src="demo.gif" />

<img align='right' width='150' height='150' src="Compute/icon.png" />

# Compute.js

Compute.js is a JavaScript runtime for prototyping and learning OpenCL and OpenGL. It was 
made as part of my final year of university as a proof of concept that a dedicated toolkit
could make GPU programming easier.

## Introduction

This was my honours project which aimed to develop a GPU toolkit for developers to use when learning or prototyping 
GPU applications. Basically MATLAB for thoose interested in OpenGL & OpenCL. You write your app in JavaScript where you can
then import libraries that enable you to make calls to OpenCL or OpenGL. An example can be found below.

```javascript
const { openWindow } = require('display');
const gl = require('gl');

openWindow({ w: 800, h: 500 }, screen => {
    screen.show();
    screen.enableOpenGL();
    screen.onFrame(() => {
        gl.glClear(gl.GL_COLOR_BUFFER_BIT);
        gl.glBegin(gl.GL_TRIANGLES);
        gl.glVertex2f(-0.5, -0.5);
        gl.glVertex2f(0.0, 0.5);
        gl.glVertex2f(0.5, -0.5);
        gl.glEnd();

        screen.swapBuffers();
    });
});

```

## Requirements

* Windows 10
* Visual Studio 2015
* OpenCL SDK

## Folders

 * Compute.Documents - Documents required for the honours project.
 * Compute.Samples   - Example code and tests for the platform
 * Compute.Modules   - JavaScript modules which call native C++ methods
 * Compute.Core      - Core classes and functions for the platform
 * Compute           - Application which bootstraps Compute.

## Technologies

### C++

Poco, V8, SDL2, GLEW, FreeImage

### JavaScript

gl-matrix, npm

## License

MIT

<img align='right' src="http://forthebadge.com/images/badges/built-with-love.svg" />
