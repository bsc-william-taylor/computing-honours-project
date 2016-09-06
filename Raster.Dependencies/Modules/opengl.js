
exports.GL_COLOR_BUFFER_BIT = 16384;
exports.GL_DEPTH_BUFFER_BIT = 256;
exports.GL_PROJECTION = 5889;
exports.GL_DEPTH_TEST = 2929;
exports.GL_MODELVIEW = 5888;
exports.GL_TRIANGLES = 4;
exports.GL_QUADS = 7;

exports.glBegin = function(type) {
    raster.glBegin(type);
};

exports.glEnd = function() {
    raster.glEnd();
}

exports.glClearColor = function(r, g, b, a) {
    raster.glClearColor(r, g, b, a);
}

exports.glClear = function(buffers) {
    raster.glClear(buffers);
}

exports.glVertex2f = function(x, y) {
    raster.glVertex2f(x, y);
}

exports.gluPerspective = function(fov, aspect, near, far) {
    raster.gluPerspective(fov, aspect, near, far);
}

exports.glVertex3f = function (x, y, z) {
    raster.glVertex3f(x, y, z);
}

exports.glColor3f = function (r, g, b) {
    raster.glColor3f(r, g, b);
}

exports.glTranslatef = function(x, y, z) {
    raster.glTranslatef(x, y, z);
};

exports.glRotatef = function(rotate, x, y, z) {
    raster.glRotatef(rotate, x, y, z);
}

exports.glMatrixMode = function(matrixMode) {
    raster.glMatrixMode(matrixMode);
}

exports.glLoadIdentity = function() {
    raster.glLoadIdentity();
}

exports.glEnable = function(enable) {
    raster.glEnable(enable);
}