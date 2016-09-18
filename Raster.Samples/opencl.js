
const console = require('console');
const http = require('http');
const cl = require('opencl');
const fs = require('fs');

const randomArray = len => [...new Array(len)].map(x => Math.floor(Math.random() * 100));

function acquirePlatform() {
    const platforms = [];
    cl.getPlatformIDs(0, null, platforms);
    cl.getPlatformIDs(platforms.length, platforms, null);

    platforms.forEach(platform => {
        cl.getPlatformInfo(platform, cl.CL_PLATFORM_NAME);
        cl.getPlatformInfo(platform, cl.CL_PLATFORM_VERSION);
        cl.getPlatformInfo(platform, cl.CL_PLATFORM_PROFILE);
        cl.getPlatformInfo(platform, cl.CL_PLATFORM_VENDOR);
    });

    return platforms[console.read(platforms)];
}

function acquireDevice(platform) {
    const devices = [];
    cl.getDeviceIDs(platform, cl.CL_DEVICE_TYPE_ALL, 0, null, devices);
    cl.getDeviceIDs(platform, cl.CL_DEVICE_TYPE_ALL, devices.length, devices, null);

    devices.forEach(device => {
        cl.getDeviceInfo(device, cl.CL_DEVICE_NAME);
    })

    return devices[console.read(devices)];
}

const platform = acquirePlatform();
const device = acquireDevice(platform);
