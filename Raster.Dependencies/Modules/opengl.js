
var _cpp = cpp;

if (!exports) {
    throw 'Error global exports not defined';
}

if (!cpp) {
    throw 'Error global cpp not defined';
}

/** Exports for CommonJs modules  */
exports.GL_COLOR_BUFFER_BIT = 16384;
exports.GL_DEPTH_BUFFER_BIT = 256;
exports.GL_PROJECTION = 5889;
exports.GL_DEPTH_TEST = 2929;
exports.GL_MODELVIEW = 5888;
exports.GL_TRIANGLES = 4;
exports.GL_QUADS = 7;

exports.apply = function (caller) {
    for (var exp in exports) {
        if (!caller[exp]) {
            caller[exp] = exports[exp];
        }
    }
}

exports.glBegin = function(type) {
    _cpp.glBegin(type);
};

exports.glEnd = function() {
    _cpp.glEnd();
}

exports.glClearColor = function(r, g, b, a) {
    _cpp.glClearColor(r, g, b, a);
}

exports.glClear = function(buffers) {
    _cpp.glClear(buffers);
}

exports.glVertex2f = function(x, y) {
    _cpp.glVertex2f(x, y);
}

exports.gluPerspective = function(fov, aspect, near, far) {
    _cpp.gluPerspective(fov, aspect, near, far);
}

exports.glVertex3f = function (x, y, z) {
    _cpp.glVertex3f(x, y, z);
}

exports.glColor3f = function (r, g, b) {
    _cpp.glColor3f(r, g, b);
}

exports.glTranslatef = function(x, y, z) {
    _cpp.glTranslatef(x, y, z);
};

exports.glRotatef = function(rotate, x, y, z) {
    _cpp.glRotatef(rotate, x, y, z);
}

exports.glMatrixMode = function(matrixMode) {
    _cpp.glMatrixMode(matrixMode);
}

exports.glLoadIdentity = function() {
    _cpp.glLoadIdentity();
}

exports.glEnable = function(enable) {
    _cpp.glEnable(enable);
}