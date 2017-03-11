
const maths = require('maths'), cl = require('cl'), fs = require('fs');
const matrixData = fs.readJson('in-mat4.json'), out = [];
const { platform, device } = acquireRuntime();

function acquireRuntime() {
    const platforms = [], devices = [];
    cl.clGetPlatformIDs(0, null, platforms);
    cl.clGetPlatformIDs(platforms.length, platforms, null);
    cl.clGetDeviceIDs(platforms[0], cl.CL_DEVICE_TYPE_ALL, 0, null, devices);
    cl.clGetDeviceIDs(platforms[0], cl.CL_DEVICE_TYPE_ALL, devices.length, devices, null);
    return { platform: platforms[0], device: devices[0] };
}

with (cl) {
    const properties = [CL_CONTEXT_PLATFORM, platform, 0];
    const context = clCreateContextFromType(properties, CL_DEVICE_TYPE_ALL, null, null, null);
    const commandQueue = clCreateCommandQueue(context, device, 0, null);
    const program = clCreateProgramWithSource(context, 1, fs.read('matrix.cl').contents, null, null);
    const err = clBuildProgram(program, 0, null, null, null, null);
    const kernel = clCreateKernel(program, 'mul', null);
    const param = CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR;
    
    matrixData.matrices.forEach(matrix => {
        const multiply = Float32Array.from(matrixData.multiply.mat4);
        const input = Float32Array.from(matrix.mat4);
        const output = new Float32Array(input.length);
        const aBuffer = clCreateBuffer(context, param, input.byteLength, input, null);
        const bBuffer = clCreateBuffer(context, param, multiply.byteLength, multiply, null);
        const cBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, output.byteLength, null, null);

        clSetKernelArg(kernel, 0, Uint32Array.BYTES_PER_ELEMENT, aBuffer);
        clSetKernelArg(kernel, 1, Uint32Array.BYTES_PER_ELEMENT, bBuffer);
        clSetKernelArg(kernel, 2, Uint32Array.BYTES_PER_ELEMENT, cBuffer);
        clEnqueueNDRangeKernel(commandQueue, kernel, 2, null, Uint32Array.from([4, 4]), null, 0, null, null);
        clEnqueueReadBuffer(commandQueue, cBuffer, CL_TRUE, 0, output.byteLength, output, 0, null, null, null);
        clReleaseMemObject(aBuffer);
        clReleaseMemObject(bBuffer);
        clReleaseMemObject(cBuffer);

        out.push({ "mat4": Array.from(output) });
    });

    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(commandQueue);
    clReleaseContext(context);
}

fs.writeJson('out-mat4.json', { "matrices": out });
