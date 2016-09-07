
function argumentsToString(functionArgs) {
    let combinedString = "";

    for (let i = 0; i < functionArgs.length; ++i) {
        const arg = functionArgs[i];

        if (typeof (arg) === "object") {
            combinedString += JSON.stringify(arg, null, 2);
        } else {
            combinedString += arg;
        }

        combinedString += " ";
    }

    return combinedString;
};

exports.error = function () {
    raster.printLine(argumentsToString(arguments));
}

exports.warn = function() {
    raster.printLine(argumentsToString(arguments));
}

exports.log = function() {
    raster.printLine(argumentsToString(arguments));
}

exports.read = function () {
    raster.print(argumentsToString(arguments));
    return raster.read();
}