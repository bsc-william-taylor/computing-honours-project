
const console = require('console');
const http = require('http');
const cl = require('opencl');
const fs = require('fs');

const randomArray = len => [...new Array(len)].map(x => Math.floor(Math.random() * 100));

function acquirePlatform(){ 
    const platforms = [];

    with(cl) {
        clGetPlatformIDs(0, null, platforms);
        clGetPlatformIDs(platforms.length, platforms, null);

        platforms.forEach(platform => {
            clGetPlatformInfo(platform, CL_PLATFORM_NAME);
            clGetPlatformInfo(platform, CL_PLATFORM_VERSION);
            clGetPlatformInfo(platform, CL_PLATFORM_PROFILE);
            clGetPlatformInfo(platform, CL_PLATFORM_VENDOR);
        });
    }

    return platforms[console.read(platforms)];
}

function acquireDevice(platform) {
    const devices = [];

    with(cl) {
        clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, null, devices);
        clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, devices.length, devices, null);

        devices.forEach(device => {
            clGetDeviceInfo(device, CL_DEVICE_NAME);
            clGetDeviceInfo(device, CL_DEVICE_VERSION);
            clGetDeviceInfo(device, CL_DEVICE_VENDOR);
        });
    }

    return devices[console.read(devices)];
}

function start() {
    const platform = acquirePlatform();
    const device = acquireDevice(platform);

    with(cl) {
        const properties = [ CL_CONTEXT_PLATFORM, platform, 0 ];
        const context = clCreateContextFromType(properties, CL_DEVICE_TYPE_ALL, null, null, null);

        clReleaseContext(context);
    }
}

start();