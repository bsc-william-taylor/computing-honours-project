const { printLine, print, read } = raster;
const jsonReplacer = null;
const jsonSpacing = 2;
const readToken = "\n:";

const stringArguments = args => {
    let output = "";

    for (let i = 0; i < args.length; ++i) {
        if (typeof (args[i]) === "object") {
            output += JSON.stringify(args[i], jsonReplacer, jsonSpacing);
        } else {
            output += args[i];
        }

        output += " ";
    }

    return output;
};

exports.error = function() {
    const output = stringArguments(arguments);
    printLine(output);
}

exports.warn = function() {
    const output = stringArguments(arguments);
    printLine(output);
}

exports.log = function() {
    const output = stringArguments(arguments);
    printLine(output);
}

exports.read = function() {
    const output = stringArguments(arguments);
    print(output + readToken);
    return read();   
}