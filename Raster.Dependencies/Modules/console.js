
const raster = cpp;
const module = this;

function argumentsToString(functionArgs) {
    let combinedString = "";

    for (let i = 0; i < functionArgs.length; ++i) {
        const arg = functionArgs[i];

        if (typeof (arg) === "object") {
            combinedString += JSON.stringify(arg);
        } else {
            combinedString += arg;
        }

        combinedString += " ";
    }

    return combinedString;
};

exports.error = function () {
    raster.print(argumentsToString(arguments));
}

exports.warn = function() {
    raster.print(argumentsToString(arguments));
}

exports.log = function() {
    raster.print(argumentsToString(arguments));
}

exports.read = function() {
    return raster.read();
}