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

exports.exit = compute.exit;

exports.battery = function () {
    const info = compute.battery();

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
    'Name': compute.osName,
    'Version': compute.osVersion,
    'Architecture': compute.osArchitecture
};

exports.hardware = {
    'CPU Cache Line Size': compute.cpuCacheLineSize,
    'CPU count': compute.cpuCount,
    'RAM': compute.systemRam
}

exports.instructions = {
    '3DNow': compute.has3DNow,
    'AltiVec': compute.hasAltiVec,
    'AVX': compute.hasAVX,
    'AVX2': compute.hasAVX2,
    'MMX': compute.hasMMX,
    'RDTSC': compute.hasRDTSC,
    'SSE': compute.hasSSE,
    'SSE2': compute.hasSSE2,
    'SSE3': compute.hasSSE3,
    'SSE41': compute.hasSSE41,
    'SSE42': compute.hasSSE42
};