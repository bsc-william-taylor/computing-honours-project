
var _cpp = cpp;

exports.CL_CommandQueue = _cpp.CL_CommandQueue;
exports.CL_Context = _cpp.CL_Context;
exports.CL_Program = _cpp.CL_Program;
exports.CL_Buffer = _cpp.CL_Buffer;
exports.CL_Kernel = _cpp.CL_Kernel;

exports.default = {
    Platform: {
        get: function () {
            return _cpp.getPlatforms();
        }
    },

    CL_BUILD_SUCCESS: 0,
    CL_DEVICE_NAME: 0,
    CL_PLATFORM_NAME: 0,
    CL_PLATFORM_VERSION: 1
}