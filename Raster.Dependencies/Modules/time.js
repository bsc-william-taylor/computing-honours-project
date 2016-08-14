
var timerCounter = 0;
var timers = {};
var _cpp = cpp;

function setTimeout(callback, ms, usedID) {
    var returnValue = -1;

    if (ms >= 0) {
        var id = usedID || ++timerCounter;
        if (!timers[id]) {
            timers[id] = { callback: callback, cancel: false };
        }

        _cpp.timeout(ms, function () {
            if (!timers[id].cancel) {
                timers[id].callback();
            }
        });

        returnValue = id;
    }

    return returnValue;
}

function setInterval(callback, ms, usedID) {
    var assignedID = setTimeout(function () {
        callback();
        setInterval(callback, ms, assignedID);
    }, ms, usedID);
    return assignedID;
}

function clearTimedCallback(timerID) {
    if (timerID >= 0) {
        timers[timerID].cancel = true;
        return true;
    }

    return false;
}

/** Exports for CommonJs modules eg: var time = require('time');  **/
exports.clearInterval = clearTimedCallback;
exports.clearTimeout = clearTimedCallback;
exports.setInterval = function(callback, ms) {
    return setInterval(callback, ms);
};

exports.setTimeout = function(callback, ms) {
    return setTimeout(callback, ms);
};

exports.pause = function (ms) {
    if (ms >= 0) {
        _cpp.pause(ms);
    }
};

/** Exports for ES6 modules eg: import time from 'time' */
exports.default = {
    pause: function(ms) {
        if (ms >= 0) {
            _cpp.pause(ms);
        }
    },

    clearInterval: function(timerID) {
        clearTimedCallback(timerID);
    },

    clearTimeout: function(timerID) {
        clearTimedCallback(timerID);
    },

    setTimeout: function(callback, ms) {
        return setTimeout(callback, ms);
    },

    setInterval: function(callback, ms) {
        return setInterval(callback, ms);
    }
}