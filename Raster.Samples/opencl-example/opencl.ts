
import opencl, { CL_Context, CL_Program, CL_Buffer, CL_Kernel, CL_CommandQueue } from 'opencl';
import * as helpers from './opencl-helpers';
import console from 'console';

const A = helpers.randomArray(100);
const B = helpers.randomArray(100);
const C = [];

const kernals = helpers.getKernelSource('kernels.cl');

function bootstrap(device, platform) {
    const context = new CL_Context(device);
    const program = new CL_Program(context, kernals);

    // Build Program
    if (program.build(device) == opencl.CL_BUILD_SUCCESS) {
        const bufferSize = A.length;
        const bufferBytes = 4 * A.length;

        const bufferA = new CL_Buffer(context, bufferSize, bufferBytes);
        const bufferB = new CL_Buffer(context, bufferSize, bufferBytes);
        const bufferC = new CL_Buffer(context, bufferSize, bufferBytes);

        const kernel = new CL_Kernel(program, "simple_add");
        kernel.setArg(0, bufferA);
        kernel.setArg(1, bufferB);
        kernel.setArg(2, bufferC);

        const queue = new CL_CommandQueue(context, device);
        queue.enqueueWriteBuffer(bufferA, true, 0, bufferBytes, A);
        queue.enqueueWriteBuffer(bufferB, true, 0,bufferBytes, B);
        queue.enqueueNDRangeKernel(kernel, 0, bufferSize, 0);
        queue.enqueueReadBuffer(bufferC, true, 0, bufferBytes, C);
        queue.finish();

        console.log(C);
    }
}

const chosenPlatform = helpers.getPlatform();
const chosenDevice = helpers.getDevices(chosenPlatform);

bootstrap(chosenDevice, chosenPlatform);
