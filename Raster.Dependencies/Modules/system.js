
//const raster = raster;

exports.hardware = function() {
    return {
        'CPU Cache Line Size': raster.cpuCacheLineSize(),
        'CPU count': raster.cpuCount(),
        'RAM': raster.systemRam()
    };
}

exports.instructions = function() {
    return {
        '3DNow': raster.has3DNow(),
        'AVX': raster.hasAVX(),
        'AVX2': raster.hasAVX2(),
        'AltiVec': raster.hasAltiVec(),
        'MMX': raster.hasMMX(),
        'RDTSC': raster.hasRDTSC(),
        'SSE': raster.hasSSE(),
        'SSE2': raster.hasSSE2(),
        'SSE3': raster.hasSSE3(),
        'SSE41': raster.hasSSE41(),
        'SSE42': raster.hasSSE42()
    };
}