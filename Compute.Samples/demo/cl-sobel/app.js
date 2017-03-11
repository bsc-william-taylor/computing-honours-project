const cl = require('cl'), fs = require('fs');

function acquireRuntime() {
  const platforms = [], devices = [];
  cl.clGetPlatformIDs(0, null, platforms);
  cl.clGetPlatformIDs(platforms.length, platforms, null);
  cl.clGetDeviceIDs(platforms[0], cl.CL_DEVICE_TYPE_ALL, 0, null, devices);
  cl.clGetDeviceIDs(platforms[0], cl.CL_DEVICE_TYPE_ALL, devices.length, devices, null);
  return { platform: platforms[0], device: devices[0] };
}

const { platform, device } = acquireRuntime();
const source = fs.read('./kernel.cl');

with (cl) {
  const properties = [CL_CONTEXT_PLATFORM, platform, 0];
  const context = clCreateContextFromType(properties, CL_DEVICE_TYPE_ALL, null, null, null);
  const cmdQueue = clCreatecmdQueue(context, device, 0, null);
  const program = clCreateProgramWithSource(context, 1, source.contents, null, null);
  const err = clBuildProgram(program, 0, null, null, null, null);
  const kernel = clCreateKernel(program, 'sobel', null);
  const img = fs.readImage('image.png');
  const format = {}, error = {};
  format.image_channel_order = CL_RGBA;
  format.image_channel_data_type = CL_UNORM_INT8;

  const output = new ArrayBuffer(img.width * img.height * 4);
  const region = Uint32Array.from([img.width, img.height, 1]);
  const global = Uint32Array.from([600, 600]);
  const local = Uint32Array.from([1, 1]);
  const origin = Uint32Array.from([0, 0, 0]);
  const imageMemory = [
    clCreateImage2D(context, (1 << 2)|(1 << 5), format, img.width, img.height, 0, img.data, error),
    clCreateImage2D(context, CL_MEM_READ_WRITE, format, img.width, img.height, 0, null, error)
  ];

  clSetKernelArg(kernel, 0, Uint32Array.BYTES_PER_ELEMENT, imageMemory[0]);
  clSetKernelArg(kernel, 1, Uint32Array.BYTES_PER_ELEMENT, imageMemory[1]);
  clEnqueueNDRangeKernel(cmdQueue, kernel, 2, null, global, local, 0, null, null);
  clEnqueueReadImage(cmdQueue, imageMemory[1], CL_TRUE, origin, region, 0, 0, output, 0, null, null);

  clReleaseKernel(kernel);
  clReleasecmdQueue(cmdQueue);
  clReleaseContext(context);
  clReleaseProgram(program);

  fs.writeImage('output.png', output, img.width, img.height);
  fs.freeImage(img);
}
