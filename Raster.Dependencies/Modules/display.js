
function getDefaultWindowArgs(givenArgs) {
    var args = {};
    args.title = givenArgs.title || "";
    args.x = givenArgs.x || 0;
    args.y = givenArgs.y || 0;
    args.w = givenArgs.w || 240;
    args.h = givenArgs.h || 240;
    return args;
}

exports.openMessage = function (title, body, callback) {
    if (title && body && callback) {
        raster.showMessageBox(title, body, callback);
    } else {
        throw 'Expected 3 args to openMessage';
    }
}

exports.openFullscreenWindow = function(callback) {

};

exports.openWindow = function (args, callback) {
    if (args && callback) {
        var windowSettings = getDefaultWindowArgs(args);
        raster.createWindow(new raster.Window(windowSettings), callback);
    }
}