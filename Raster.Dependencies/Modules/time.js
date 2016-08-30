
// Replace with Date.now()
let timerCounter = 0;

const raster = cpp;
const timers = {};

function setTimeout(callback, ms, identifier) {
    const id = identifier || ++timerCounter;
    timers[id] = timers[id] || { callback: callback, cancel: false };

    const timer = timers[id];
    raster.timeout(ms, () => {
        if (!timer.cancel) {
            timer.callback(id);
         }
    });

    return id;
}

exports.clearInterval = function (uniqueIdentifier) {
    if (uniqueIdentifier >= 0) {
        timers[uniqueIdentifier].cancel = true;
        return true;
    }

    return false;
};

exports.clearTimeout = function (uniqueIdentifier) {
    if (uniqueIdentifier >= 0) {
        timers[uniqueIdentifier].cancel = true;
        return true;
    }

    return false;
};

exports.setInterval = function (callback, ms) {
    if (callback && ms >= 0) {
        const reschedule = (identifier) => {
            setInterval(callback, ms, identifier);
            callback();
        }

        return setTimeout(reschedule, ms);
    } else {
        throw 'Error function takes 2 arguments';
    }
};

exports.setTimeout = function (callback, ms) {
    if (callback && ms >= 0) {
        return setTimeout(() => callback(), ms);
    } else {
        throw 'Error function takes 2 arguments';
    }
};

exports.pause = function (ms) {
    if (ms >= 0) {
        raster.pause(ms);
    } else {
        throw 'Error function takes 1 argument, 0 provided';
    }
};