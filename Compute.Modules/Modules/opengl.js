
exports.GL_COLOR_BUFFER_BIT = 16384;
exports.GL_DEPTH_BUFFER_BIT = 256;
exports.GL_PROJECTION = 0x1701;
exports.GL_DEPTH_TEST = 0x0B71;
exports.GL_MODELVIEW = 5888;
exports.GL_TRIANGLES = 4;
exports.GL_QUADS = 7;

exports.glBegin = function(type) {
    compute.glBegin(type);
};

exports.glEnd = function() {
    compute.glEnd();
}

exports.glClearColor = function(r, g, b, a) {
    compute.glClearColor(r, g, b, a);
}

exports.glClear = function(buffers) {
    compute.glClear(buffers);
}

exports.glVertex2f = function(x, y) {
    compute.glVertex2f(x, y);
}

exports.gluPerspective = function(fov, aspect, near, far) {
    compute.gluPerspective(fov, aspect, near, far);
}

exports.glVertex3f = function (x, y, z) {
    compute.glVertex3f(x, y, z);
}

exports.glColor3f = function (r, g, b) {
    compute.glColor3f(r, g, b);
}

exports.glTranslatef = function(x, y, z) {
    compute.glTranslatef(x, y, z);
};

exports.glRotatef = function(rotate, x, y, z) {
    compute.glRotatef(rotate, x, y, z);
}

exports.glMatrixMode = function (matrixMode) {
    compute.glMatrixMode(matrixMode);
}

exports.glLoadIdentity = function() {
    compute.glLoadIdentity();
}

exports.glEnable = function(enable) {
    compute.glEnable(enable);
}