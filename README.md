
<img src="demo.gif" />

<img align='right' width='150' height='150' src="src/Compute/icon.png" />

# Compute.js

Compute.js is a JavaScript runtime for prototyping and learning OpenCL and OpenGL. It was made as part of my final year of university as a proof of concept that a dedicated toolkit could make GPU programming and experimentation easier. It is built on top of the V8 JavaScript engine and popular open source frameworks such as SDL2 and Poco.
 
## Assignment

In the honours project module, you choose your own project. I decided to work on a project which aimed to develop a GPU toolkit for developers to use when learning or prototyping GPU applications. Basically, MATLAB for those interested in OpenGL & OpenCL. In this application users should be able to write the app in modern JavaScript where you can then import libraries that enable you to make calls to OpenCL or OpenGL. An example of what this would look like can be found below. The below code was from a working prototype used to demonstrate the possibilities of the project.

```js
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

## Submission

A full honours report setting out initial research and the development was submitted. Along with a buildable version of the source code and a runnable version build for Windows.
Samples were also submitted so markers could play around with the platform should they wish to. Several additional documents were also submitted as they were mandatory. This included Gantt charts for planning, an interim report to set out the progress made and a planning report to describe how I used effectively project management skills to ensure all items were submitted with good value.

*Requirements*

* Windows 7/8/10
* Visual Studio 2015
* OpenCL SDK
* OpenGL hardware

## License

Apache 2.0