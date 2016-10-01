
const { openMessage, openWindow } = compute;
const { Window, displayInfo } = compute;

exports.openMessage = function (title, body, callback) {
    if (title && body && callback) {
        openMessage(title, body, callback);
    } else {
        throw 'Expected 3 args to openMessage';
    }
}

exports.openFullscreenWindow = function(callback) {
    if (callback) {        
        const display = displayInfo();

        const settings = { title: "", x: 0, y: 0 };
        settings.fullscreen = true;
        settings.h = display.h;
        settings.w = display.w;

        openWindow(new Window(settings), callback);
    }
};

exports.openWindow = function (args, callback) {
    if (args && callback) {
        const settings = { title: args.title || "" };
        settings.fullscreen = false;
        settings.h = args.h || 250;
        settings.w = args.w || 250;
        settings.y = args.y || 50;
        settings.x = args.x || 50;

        openWindow(new Window(settings), callback);
    }
}