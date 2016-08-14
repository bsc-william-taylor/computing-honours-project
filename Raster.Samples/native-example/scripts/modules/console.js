
var _cpp = cpp;

/** Functions here are used in multiple ways due to ES5 -> ES6 module syntax **/
function parseBoolean(string) {
    var value = string || "";

    switch (value.toLowerCase().trim()) {
        case "true":
        case "yes":
        case "1":
            return true;
        case "false":
        case "no":
        case "0":
            return false;
        default:
            return Boolean(value);
    }
}

function argumentsToString() {
    var combinedString = "";

    for (var i = 0; i < arguments.length; ++i) {
        var arg = arguments[i];

        if (typeof (arg) === "object") {
            combinedString += JSON.stringify(arg);
        } else {
            combinedString += arg;
        }

        combinedString += " ";
    }

    return combinedString;
};

function print() {
    var combinedInputs = argumentsToString.apply(this, arguments);
    _cpp.print(combinedInputs);
};

function readObject() {
    this.log.apply(this, arguments);
    return JSON.parse(_cpp.read());
};

function readBoolean() {
    this.log.apply(this, arguments);
    return parseBoolean(_cpp.read());
};

function readString() {
    this.log.apply(this, arguments);
    return _cpp.read();
};

function readNumber() {
    this.log.apply(this, arguments);
    return parseInt(_cpp.read());
};

/** Default exports for ES6 default module syntax eg: import console from 'console'; **/
exports.default = {
    log: function () {
        print.apply(this, arguments);
    },

    warn: function () {
        print.apply(this, arguments);
    },

    error: function () {
        print.apply(this, arguments);
    },

    readBoolean: function () {
        return readBoolean.apply(this, arguments);
    },

    readString: function () {
        return readString.apply(this, arguments);
    },

    readObject: function () {
        return readObject.apply(this, arguments);
    },

    readNumber: function () {
        return readNumber.apply(this, arguments);
    }
}

/** Exports for CommonJs modules eg: var console = require('console'); **/
exports.readBoolean = function () {
    return readBoolean.apply(this, arguments);
};

exports.readString = function () {
    return readString.apply(this, arguments);
};

exports.readObject = function () {
    return readObject.apply(this, arguments);
};

exports.readNumber = function () {
    return readNumber.apply(this, arguments);
};

exports.error = function () {
    print.apply(this, arguments);
};

exports.warn = function () {
    print.apply(this, arguments);
};

exports.log = function () {
    print.apply(this, arguments);
};
