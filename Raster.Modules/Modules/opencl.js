
exports.CommandQueue = raster.CommandQueue;
exports.Context = raster.Context;
exports.Program = raster.Program;
exports.Buffer = raster.Buffer;
exports.Kernel = raster.Kernel;

exports.CL_BUILD_SUCCESS = 0;
exports.CL_DEVICE_NAME = 0x102B;
exports.CL_PLATFORM_NAME = 0x0902;
exports.CL_PLATFORM_VERSION = 0x0901;

exports.Platform =  {
    get: () => raster.getPlatforms()
}
