
const console = require('console');
const maths = require('maths');
const cl = require('cl');
const fs = require('fs');

const matrixData = fs.readJson('in-mat4.json');
const source = fs.read('matrix.cl');
const out = [];

function acquireEnv(){
  const platforms = [], devices = [];

  with(cl) {
    clGetPlatformIDs(0, null, platforms);
    clGetPlatformIDs(platforms.length, platforms, null);

    const platform = platforms[0];
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, null, devices);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, devices.length, devices, null);
    return { platform, device: devices[0],};
  }
}

const { platform, device } = acquireEnv();

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

    const kernel = clCreateKernel(program, 'mul', null);
    matrixData.matrices.forEach(matrix => {
        const multiply = Float32Array.from(matrixData.multiply.mat4);
        const input = Float32Array.from(matrix.mat4);
        const output = new Float32Array(input.length);
        
        const aBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, input.byteLength, input, null);
        const bBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, multiply.byteLength, multiply, null);
        const cBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, output.byteLength, null, null);

        clSetKernelArg(kernel, 0, input.byteLength, aBuffer);
        clSetKernelArg(kernel, 1, multiply.byteLength, bBuffer);
        clSetKernelArg(kernel, 2, output.byteLength, cBuffer);

        clEnqueueNDRangeKernel(commandQueue, kernel, 2, null, Uint32Array.from([4, 4]), null, 0, null, null);
        clEnqueueReadBuffer(commandQueue, cBuffer, CL_TRUE, 0, output.byteLength, output, 0, null, null, null);
        
        out.push({ "mat4": Array.from(output) });

        clReleaseMemObject(aBuffer);
        clReleaseMemObject(bBuffer);
        clReleaseMemObject(cBuffer);
    });

    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(commandQueue);
    clReleaseContext(context);
}


fs.writeJson('out-mat4.json', { "matrices": out });
