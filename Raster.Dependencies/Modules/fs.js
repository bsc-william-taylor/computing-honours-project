
var Cpp = cpp;

exports.readFile = function(path) {
    var file = new Cpp.TextFile();
    file.read(path);
    return file;
}

exports.readImage = function (path) {
    var file = new Cpp.Image();
    file.read(path);
    return file;
}

exports.readJson = function (path) {
    var file = new Cpp.TextFile();
    file.read(path);
    return JSON.parse(file.contents);
}