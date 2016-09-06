
function argumentsToString(functionArgs) {
    if (functionArgs.length === 0) {
        throw 'Invalid Arguments: No arguments given';
    }

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