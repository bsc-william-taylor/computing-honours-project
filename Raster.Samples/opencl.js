
const console = require('console');
const http = require('http');
const cl = require('opencl');
const fs = require('fs');

function getPlatform() {
    const platforms =  cl.Platform.get();
    platforms.forEach((platform, index) => {
        const version = platform.getInfo(cl.CL_PLATFORM_VERSION);
        const name = platform.getInfo(cl.CL_PLATFORM_NAME);

        console.log(`${index}. Name: ${name} Version: ${version}`);
    });

    console.log("\nEnter the platform to run on: ");
    return platforms[Number(console.read())];
}

function randomArray(size) {
    const randomValueArray = [];
    for(let i = 0; i < size; ++i) {
        randomValueArray.push(Math.floor((Math.random() * 100) + 1));
    }
    return randomValueArray;
}

function getDevices(chosenPlatform) {
    const devices = chosenPlatform.getDevices();
    devices.forEach((device, index) => {
        console.log(`${index}. Device Name: ${device.getInfo(cl.CL_DEVICE_NAME)}`);
    });

    console.log("\nEnter the device to run on: ");
    return devices[Number(console.read())];
}

const A = randomArray(100);
const B = randomArray(100);
const C = [];

const kernals = JSON.parse(http.get('www.williamsamtaylor.co.uk', '/kernels', 3010)).text;
const platform = getPlatform();
const device = getDevices(platform);

function bootstrap(device, platform) {
    const context = new cl.Context(device);
    const program = new cl.Program(context, kernals);

    if (program.build(device) ==  cl.CL_BUILD_SUCCESS) {
        const bufferSize = A.length;
        const bufferBytes = 4 * A.length;
        const bufferA = new cl.Buffer(context, bufferSize, bufferBytes);
        const bufferB = new cl.Buffer(context, bufferSize, bufferBytes);
        const bufferC = new cl.Buffer(context, bufferSize, bufferBytes);

        const kernel = new cl.Kernel(program, "simple_add");
        kernel.setArg(0, bufferA);
        kernel.setArg(1, bufferB);
        kernel.setArg(2, bufferC);

        const queue = new cl.CommandQueue(context, device);
        queue.enqueueWriteBuffer(bufferA, true, 0, bufferBytes, A);
        queue.enqueueWriteBuffer(bufferB, true, 0, bufferBytes, B);
        queue.enqueueNDRangeKernel(kernel, 0, bufferSize, 0);
        queue.enqueueReadBuffer(bufferC, true, 0, bufferBytes, C);
        queue.finish();

        console.log('Result: ', C);
    }
}

bootstrap(device, platform);
