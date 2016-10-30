
const randomArray = require('random-array');
const console = require('console');
const http = require('http');
const cl = require('cl');
const fs = require('fs');

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

    return platforms[0];//console.read(platforms)];
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

    return devices[0];//console.read(devices)];
}

const platform = acquirePlatform();
const device = acquireDevice(platform);
const source = fs.read('./kernel.cl');

with(cl) {
    const properties = [ CL_CONTEXT_PLATFORM, platform, 0 ];
    const context = clCreateContextFromType(properties, CL_DEVICE_TYPE_ALL, null, null, null);
    const commandQueue = clCreateCommandQueue(context, device, 0, null);

    const program = clCreateProgramWithSource(context, 1, source.contents, null, null);
    const err = clBuildProgram(program, 0, null, null, null, null);
    
    if(err != CL_SUCCESS) {
        const buildLog = {};
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 1, buildLog, null);
        console.log(buildLog.log);
    }

    const size = Number(console.read('Enter size:'));
    const kernel = clCreateKernel(program, "hello_kernel", null);
    const a = Float32Array.from(randomArray(1, 10).oned(size));
    const b = Float32Array.from(randomArray(1, 10).oned(size));
    const c = Float32Array.from(randomArray(1, 10).oned(size));

    const buffers = [,,,];
    buffers[0] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, a.byteLength, a, null);
    buffers[1] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, b.byteLength, b, null);
    buffers[2] = clCreateBuffer(context, CL_MEM_WRITE_ONLY, c.byteLength, null, null);

    clSetKernelArg(kernel, 0,  4, buffers[0]);
    clSetKernelArg(kernel, 1,  4, buffers[1]);
    clSetKernelArg(kernel, 2,  4, buffers[2]);
    
    const globalWorkSize = Uint32Array.from([size]);
    const localWorkSize = Uint32Array.from([1]);
    clEnqueueNDRangeKernel(commandQueue, kernel, 1, null, globalWorkSize, localWorkSize, 0, null, null);
    clEnqueueReadBuffer(commandQueue, buffers[2], CL_TRUE, 0, c.byteLength, c, 0, null, null);

    console.log('Output:', c)

    clReleaseContext(context);
    clReleaseCommandQueue(commandQueue);
    clReleaseProgram(program);
    clReleaseKernel(program);
}