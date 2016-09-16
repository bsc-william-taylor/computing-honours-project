const PowerStateNoBattery = 2;
const PowerStateOnBattery = 1;
const PowerStateCharging = 3;
const PowerStateCharged = 4;
const PowerStateUnknown = 0;

exports.PowerStateOnBattery = 'On Battery';
exports.PowerStateNoBattery = 'No Battery';
exports.PowerStateCharging = 'Charging';
exports.PowerStateCharged = 'Charged';
exports.PowerStateUnknown = 'Unknown';

exports.exit = raster.exit;

exports.battery = function () {
    const info = raster.battery();

    switch (info.status) {
        case PowerStateNoBattery: info.status = 'No Battery'; break;
        case PowerStateOnBattery: info.status = 'On Battery'; break;
        case PowerStateCharging: info.status = 'Charging'; break;
        case PowerStateUnknown: info.status = 'Unknown'; break;
        case PowerStateCharged: info.status = 'Charged'; break;

        default:
            break;
    }

    return info;
}

exports.os = {
    'Name': raster.osName,
    'Version': raster.osVersion,
    'Architecture': raster.osArchitecture
};

exports.hardware = {
    'CPU Cache Line Size': raster.cpuCacheLineSize,
    'CPU count': raster.cpuCount,
    'RAM': raster.systemRam
}

exports.instructions = {
    '3DNow': raster.has3DNow,
    'AltiVec': raster.hasAltiVec,
    'AVX': raster.hasAVX,
    'AVX2': raster.hasAVX2,
    'MMX': raster.hasMMX,
    'RDTSC': raster.hasRDTSC,
    'SSE': raster.hasSSE,
    'SSE2': raster.hasSSE2,
    'SSE3': raster.hasSSE3,
    'SSE41': raster.hasSSE41,
    'SSE42': raster.hasSSE42
};