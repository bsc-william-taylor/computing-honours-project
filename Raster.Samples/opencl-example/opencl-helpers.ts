
import opencl, { Platform } from 'opencl';
import console from 'console';
import fs from 'fs';

export function getPlatform() : Platform {
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

export function randomArray(size) : number[] {
    const randomValueArray = [];
    for(let i = 0; i < size; ++i) {
        randomValueArray.push(Math.floor((Math.random() * 100) + 1));
    }
    return randomValueArray;
}

// Get kernel source code
export function getKernelSource(filename: string) {
    const kernelCode = fs.readFile(filename);

    if(kernelCode.contents.length > 0) {
        return kernelCode.contents;
    } else {
        throw `Error couldnt find file ${filename}`;
    }
}

// Get Devices/Hardware
export function getDevices(chosenPlatform: Platform) {
    const devices = chosenPlatform.getDevices();
    devices.forEach((device, index) => {
        console.log(`${index}. Device Name: ${device.getInfo(opencl.CL_DEVICE_NAME)}`);
    });

    const index = console.readNumber("\nEnter the device to run on: ");
    console.log('\n');
    return devices[index];
}
