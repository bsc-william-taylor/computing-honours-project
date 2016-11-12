const { read, write, img } = compute;
const defaultSpacing = 2;

let jsonSpacing = defaultSpacing;
let jsonReplacer = null;
let jsonReviver = null;

exports.readJson = path => {
    const jsonString = read(path);
    const characters = jsonString.contents;

    return JSON.parse(characters, jsonReviver);
}

exports.writeJson = (path, json) => {
    const string = JSON.stringify(json, jsonReplacer, jsonSpacing);
    
    if (string.length > 0) {
        write(path, string);
    }
}


exports.readImage = compute.readImage;
exports.writeImage = compute.writeImage;
exports.freeImage = compute.freeImage

exports.write = (path, string) => write(path, string);
exports.read = path => read(path);

exports.replacer = replacer => jsonReplacer = replacer;
exports.reviver = reviver => jsonReviver = reviver;
exports.spacing = spacing => jsonSpacing = spacing;
