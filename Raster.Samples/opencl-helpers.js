
const opencl, { Platform } = require('opencl');
const console = require('opencl');
const fs = require('opencl');

export function getPlatform() {
    console.log('\n');
    const platforms = opencl.Platform.get();
    platforms.forEach((platform, index) => {
        const version = platform.getInfo(opencl.CL_PLATFORM_VERSION);
        const name = platform.getInfo(opencl.CL_PLATFORM_NAME);

        console.log(`${index}. Name: ${name} Version: ${version}`);
    });

    const index = console.readNumber("\nEnter the platform to run on: ");
    console.log('\n');
    return platforms[index];
}

exports.randomArray = function(size){
    const randomValueArray = [];
    for(let i = 0; i < size; ++i) {
        randomValueArray.push(Math.floor((Math.random() * 100) + 1));
    }
    return randomValueArray;
}

exports.getKernelSource = function(filename) {
    const kernelCode = fs.readFile(filename);

    if(kernelCode.contents.length > 0) {
        return kernelCode.contents;
    } else {
        throw `Error couldnt find file ${filename}`;
    }
}

exports.getDevices = function(chosenPlatform) {
    const devices = chosenPlatform.getDevices();
    devices.forEach((device, index) => {
        console.log(`${index}. Device Name: ${device.getInfo(opencl.CL_DEVICE_NAME)}`);
    });

    const index = console.readNumber("\nEnter the device to run on: ");
    console.log('\n');
    return devices[index];
}
