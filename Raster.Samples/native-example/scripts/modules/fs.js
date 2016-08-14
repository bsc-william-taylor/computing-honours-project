
var Cpp = cpp;

exports.default = {
    readFile: function (path) {
        var file = new Cpp.TextFile();
        file.read(path);
        return file;
    },

    readImage: function (path) {
        var file = new Cpp.Image();
        file.read(path);
        return file;
    },

    readJson: function (path) {
        var file = this.readFile(path);
        // Try catch block ?
        return JSON.parse(file.contents);
    }
};