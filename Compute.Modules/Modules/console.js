const { printLine, print, read, clear } = compute;
const jsonReplacer = null;
const jsonSpacing = 2;
const readToken = "";

const stringArguments = args => {
    let output = "";

    for (let i = 0; i < args.length; ++i) {
        if (args[i] != null && Array.isArray(args[i]) && typeof(args[i][0]) !== "object") {
            output += JSON.stringify(args[i]);
        } else if (typeof (args[i] != null && args[i]) === "object") {
            output += args[i].toString() + '\n'; 
        } else {
            output += args[i] + ' ';
        }
    }

    return output;
};

exports.clear = clear;
exports.cls = clear;

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

exports.dir = function() {
    const output = stringArguments(arguments);
    printLine(output);
}

exports.read = function() {
    const output = stringArguments(arguments);
    print(output + readToken);
    return read();   
}