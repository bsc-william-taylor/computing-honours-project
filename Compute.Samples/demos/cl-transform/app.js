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

  return platforms[0];
}

function pretty(json) {
  return JSON.stringify(json, null, 4) + '\n';
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

  return devices[0];
}

function image(program, context, commandQueue, kernalName, inputName, outputName) {
  with(cl) {
    const kernel = clCreateKernel(program, kernalName, null);
    const img = fs.readImage(inputName);

    const format = {}, error = {};
    format.image_channel_order = CL_RGBA;
    format.image_channel_data_type = CL_UNORM_INT8;

    const imageMemory = [,,];
    imageMemory[0] = clCreateImage2D(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, format, img.width, img.height, 0, img.data, error);
    imageMemory[1] = clCreateImage2D(context, CL_MEM_READ_WRITE, format, img.width, img.height, 0, null, error);

    const sampler = clCreateSampler(context, CL_FALSE, CL_ADDRESS_CLAMP_TO_EDGE, CL_FILTER_NEAREST, error);
    const globalWorkSize = Uint32Array.from([1920, 1200]);
    const localWorkSize = Uint32Array.from([16, 16]);

    clSetKernelArg(kernel, 0, 4, imageMemory[0]);
    clSetKernelArg(kernel, 1, 4, imageMemory[1]);
    clSetKernelArg(kernel, 2, 4, sampler);
    clSetKernelArg(kernel, 3, 4, img.width);
    clSetKernelArg(kernel, 4, 4, img.height);

    const output = new ArrayBuffer(img.width * img.height * 4);
    const region = Uint32Array.from([img.width, img.height, 1]);
    const origin = Uint32Array.from([0, 0, 0]);

    clEnqueueNDRangeKernel(commandQueue, kernel, 2, null, globalWorkSize, localWorkSize, 0, null, null);
    clEnqueueReadImage(commandQueue, imageMemory[1], CL_TRUE, origin, region, 0, 0, output, 0, null, null);

    fs.writeImage(outputName, output, img.width, img.height);
    fs.freeImage(img);

    clReleaseSampler(sampler);
    clReleaseKernel(kernel);
  }
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

  image(program, context, commandQueue, "gaussian_filter", "image.jpg", "blur.png");
  image(program, context, commandQueue, "grayscale", "image.jpg", "grayscale.png");

  clReleaseCommandQueue(commandQueue);
  clReleaseContext(context);
  clReleaseProgram(program);
}
