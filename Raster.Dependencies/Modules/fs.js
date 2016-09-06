
exports.readFile = function (path) {
    const file = new raster.TextFile();
    file.read(path);
    return file;
}

exports.readImage = function (path) {
    const file = new raster.Image();
    file.read(path);
    return file;
}

exports.readJson = function (path) {
    const file = new raster.TextFile();
    file.read(path);
    return JSON.parse(file.contents);
}