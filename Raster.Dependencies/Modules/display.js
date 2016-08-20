
var _cpp = cpp;

function getDefaultWindowArgs(givenArgs) {
    var args = {};
    args.title = givenArgs.title || "";
    args.x = givenArgs.x || 0;
    args.y = givenArgs.y || 0;
    args.w = givenArgs.w || 240;
    args.h = givenArgs.h || 240;
    return args;
}

exports.openMessageBox = function (title, body, callback) {
    if (title && body && callback) {
        _cpp.showMessageBox(title, body, callback);
    } else {
        throw 'Expected 3 args to openMessageBox';
    }
}

exports.openFullscreenWindow = function(callback) {

};

exports.openWindow = function (args, callback) {
    if (args && callback) {
        var windowSettings = getDefaultWindowArgs(args);
        _cpp.createWindow(new _cpp.Window(windowSettings), callback);
    }
}