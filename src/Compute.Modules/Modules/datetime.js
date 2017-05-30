
let counter = 0;
let timers = {};

function beginTimer(callback, ms, repeat, identifier) {
    const uniqueIdentifier = identifier || ++counter;
    timers[uniqueIdentifier] = timers[uniqueIdentifier] || { callback, cancel: false, repeat };

    const timer = timers[uniqueIdentifier];
    const invoke = () => {
        if (!timer.cancel) {
            timer.callback(uniqueIdentifier);
            if (timer.repeat) {
                beginTimer(callback, ms, true, uniqueIdentifier);
            }
        }
    };

    compute.timeout(uniqueIdentifier, ms, invoke);
    return uniqueIdentifier;
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
        return beginTimer(() => callback(), ms, true);
    } else {
        throw 'Error function takes 2 arguments';
    }
};

exports.setTimeout = function (callback, ms) {
    if (callback && ms >= 0) {
        return beginTimer(() => callback(), ms, false);
    } else {
        throw 'Error function takes 2 arguments';
    }
};

exports.pause = function (ms) {
    if (ms >= 0) {
        compute.pause(ms);
    } else {
        throw 'Error function takes 1 argument';
    }
};