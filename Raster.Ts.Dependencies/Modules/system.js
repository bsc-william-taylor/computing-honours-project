
var _cpp = cpp;

exports.cpuCacheLineSize = function() {
    return _cpp.cpuCacheLineSize();
}

exports.cpuCount = function() {
    return _cpp.cpuCount();
}

exports.systemRam = function() {
    return _cpp.systemRam();
}

exports.has3DNow = function() {
    return _cpp.has3DNow();
}

exports.hasAVX = function() {
    return _cpp.hasAVX();
}

exports.hasAVX2 = function() {
    return _cpp.hasAVX2();
}

exports.hasAltiVec = function() {
    return _cpp.hasAltiVec();
}

exports.hasMMX = function() {
    return _cpp.hasMMX();
}

exports.hasRDTSC = function() {
    return _cpp.hasRDTSC();
}

exports.hasSSE = function() {
    return _cpp.hasSSE();
}

exports.hasSSE2 = function() {
    return _cpp.hasSSE2();
}

exports.hasSSE3 = function() {
    return _cpp.hasSSE3();
}

exports.hasSSE41 = function () {
    return _cpp.hasSSE41();
}

exports.hasSSE42 = function() {
    return _cpp.hasSSE42();
}

exports.default = {};
for (var key in exports) {
    if (key !== 'default') {
        exports.default[key] = exports[key];
    }
}