const cl = require('cl'), fs = require('fs');

function acquireRuntime() {
  const platforms = [], devices = [];
  cl.clGetPlatformIDs(0, null, platforms);
  cl.clGetPlatformIDs(platforms.length, platforms, null);
  cl.clGetDeviceIDs(platforms[0], cl.CL_DEVICE_TYPE_ALL, 0, null, devices);
  cl.clGetDeviceIDs(platforms[0], cl.CL_DEVICE_TYPE_ALL, devices.length, devices, null);
  return { platform: platforms[0], device: devices[0] };
}

with (cl) {
  const image = fs.readImage("image.jpg"), kernelSrc = fs.read('./kernel.cl').contents;
  const { platform, device } = acquireRuntime();
  const props = [CL_CONTEXT_PLATFORM, platform, 0];
  const context = clCreateContextFromType(props, CL_DEVICE_TYPE_ALL, null, null, null);
  const commandQueue = clCreateCommandQueue(context, device, 0, null);
  const program = clCreateProgramWithSource(context, 1, kernelSrc, null, null);
  const error = {}, format = {
    image_channel_order: CL_RGBA,
    image_channel_data_type: CL_UNORM_INT8
  };

  const w = image.width, h = image.height;
  const globalWork = Uint32Array.from([1920, 1200]);
  const localWork = Uint32Array.from([16, 16]);
  const region = Uint32Array.from([w, h, 1]);
  const origin = Uint32Array.from([0, 0, 0]);
  const output = new ArrayBuffer(w * h * 4);

  clBuildProgram(program, 0, null, null, null, null);

  const kernel = clCreateKernel(program, "grayscale", null);
  const buffers = [
    clCreateImage2D(context, (1 << 2)|(1 << 5), format, w, h, 0, image.data, error),
    clCreateImage2D(context, (1 << 0), format, w, h, 0, null, error)
  ];

  clSetKernelArg(kernel, 0, Uint32Array.BYTES_PER_ELEMENT, buffers[0]);
  clSetKernelArg(kernel, 1, Uint32Array.BYTES_PER_ELEMENT, buffers[1]);
  clEnqueueNDRangeKernel(commandQueue, kernel, 2, null, globalWork, localWork, 0, null, null);
  clEnqueueReadImage(commandQueue, buffers[1], CL_TRUE, origin, region, 0, 0, output, 0, null, null);
  clReleaseCommandQueue(commandQueue);
  clReleaseKernel(kernel);
  clReleaseContext(context);
  clReleaseProgram(program);

  fs.writeImage("grayscale.png", output, w, h);
  fs.freeImage(image);
}
