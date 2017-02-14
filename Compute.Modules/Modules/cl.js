
const makeNative = (object) => {
    object.prototype.toString = () => {
        return '[native cl object]';
    }
}

const getKeyByValue = (object, value) => {
    for (let prop in object) {
        if (object.hasOwnProperty(prop)) {
            if (object[prop] === value) {
                return prop;
            }
        }
    }
};

/* cl_addressing_mode */
exports.CL_ADDRESS_NONE = 0x1130;
exports.CL_ADDRESS_CLAMP_TO_EDGE = 0x1131;
exports.CL_ADDRESS_CLAMP = 0x1132;
exports.CL_ADDRESS_REPEAT = 0x1133;
exports.CL_ADDRESS_MIRRORED_REPEAT = 0x1134;

/* cl_filter_mode */
exports.CL_FILTER_NEAREST = 0x1140;
exports.CL_FILTER_LINEAR = 0x1141;

/* cl_sampler_info */
exports.CL_SAMPLER_REFERENCE_COUNT = 0x1150;
exports.CL_SAMPLER_CONTEXT = 0x1151;
exports.CL_SAMPLER_NORMALIZED_COORDS = 0x1152;
exports.CL_SAMPLER_ADDRESSING_MODE = 0x1153;
exports.CL_SAMPLER_FILTER_MODE = 0x1154;
exports.CL_SAMPLER_MIP_FILTER_MODE = 0x1155;
exports.CL_SAMPLER_LOD_MIN = 0x1156;
exports.CL_SAMPLER_LOD_MAX = 0x1157;

/* cl_map_flags - bitfield */
exports.CL_MAP_READ = (1 << 0);
exports.CL_MAP_WRITE = (1 << 1);
exports.CL_MAP_WRITE_INVALIDATE_REGION = (1 << 2);

/* cl_channel_type */
exports.CL_SNORM_INT8 = 0x10D0;
exports.CL_SNORM_INT16 = 0x10D1;
exports.CL_UNORM_INT8 = 0x10D2;
exports.CL_UNORM_INT16 = 0x10D3;;
exports.CL_UNORM_SHORT_565 = 0x10D4;
exports.CL_UNORM_SHORT_555 = 0x10D5;
exports.CL_UNORM_INT_101010 = 0x10D6;
exports.CL_SIGNED_INT8 = 0x10D7;
exports.CL_SIGNED_INT16 = 0x10D8;
exports.CL_SIGNED_INT32 = 0x10D9;
exports.CL_UNSIGNED_INT8 = 0x10DA;;
exports.CL_UNSIGNED_INT16 = 0x10DB;
exports.CL_UNSIGNED_INT32 = 0x10DC;
exports.CL_HALF_FLOAT = 0x10DD;
exports.CL_FLOAT = 0x10DE;
exports.CL_UNORM_INT24 = 0x10DF;

/* cl_channel_order */
exports.CL_R = 0x10B0;
exports.CL_A = 0x10B1;
exports.CL_RG = 0x10B2;
exports.CL_RA = 0x10B3;
exports.CL_RGB = 0x10B4;
exports.CL_RGBA = 0x10B5;
exports.CL_BGRA = 0x10B6;
exports.CL_ARGB = 0x10B7;
exports.CL_INTENSITY = 0x10B8;
exports.CL_LUMINANCE = 0x10B9;
exports.CL_Rx = 0x10BA;
exports.CL_RGx = 0x10BB;
exports.CL_RGBx = 0x10BC;
exports.CL_DEPTH = 0x10BD;
exports.CL_DEPTH_STENCIL = 0x10BE;
exports.CL_sRGB = 0x10BF;
exports.CL_sRGBx = 0x10C0;
exports.CL_sRGBA = 0x10C1;
exports.CL_sBGRA = 0x10C2;
exports.CL_ABGR = 0x10C3;

exports.CL_TRUE = 1;
exports.CL_FALSE = 0;
exports.CL_SUCCESS = 0;
exports.CL_BUILD_SUCCESS = 0;
exports.CL_DEVICE_NAME = 0x102B;

/* cl_program_build_info */
exports.CL_PROGRAM_BUILD_STATUS = 0x1181;
exports.CL_PROGRAM_BUILD_OPTIONS = 0x1182;
exports.CL_PROGRAM_BUILD_LOG = 0x1183;
exports.CL_PROGRAM_BINARY_TYPE = 0x1184;
exports.CL_PROGRAM_BUILD_GLOBAL_VARIABLE_TOTAL_SIZE = 0x1185;

/* cl_context_properties */
exports.CL_CONTEXT_PLATFORM = 0x1084;
exports.CL_CONTEXT_INTEROP_USER_SYNC = 0x1085;

// Device Type Constants
exports.CL_DEVICE_TYPE_DEFAULT = (1 << 0);
exports.CL_DEVICE_TYPE_CPU = (1 << 1);
exports.CL_DEVICE_TYPE_GPU = (1 << 2);
exports.CL_DEVICE_TYPE_ACCELERATOR = (1 << 3);
exports.CL_DEVICE_TYPE_CUSTOM = (1 << 4);
exports.CL_DEVICE_TYPE_ALL = 0xFFFFFFFF;

// Platform Info Constants
exports.CL_PLATFORM_PROFILE = 0x0900;
exports.CL_PLATFORM_VERSION = 0x0901;
exports.CL_PLATFORM_NAME = 0x0902;
exports.CL_PLATFORM_VENDOR = 0x0903;
exports.CL_PLATFORM_EXTENSIONS = 0x0904;

// Device Info Constants
exports.CL_DEVICE_TYPE = 0x1000;
exports.CL_DEVICE_VENDOR_ID = 0x1001;
exports.CL_DEVICE_MAX_COMPUTE_UNITS = 0x1002;
exports.CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS = 0x1003;
exports.CL_DEVICE_MAX_WORK_GROUP_SIZE = 0x1004;
exports.CL_DEVICE_MAX_WORK_ITEM_SIZES = 0x1005;
exports.CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR = 0x1006;
exports.CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT = 0x1007;
exports.CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT = 0x1008;
exports.CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG = 0x1009;
exports.CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT = 0x100A;
exports.CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE = 0x100B;
exports.CL_DEVICE_MAX_CLOCK_FREQUENCY = 0x100C;
exports.CL_DEVICE_ADDRESS_BITS = 0x100D;
exports.CL_DEVICE_MAX_READ_IMAGE_ARGS = 0x100E;
exports.CL_DEVICE_MAX_WRITE_IMAGE_ARGS = 0x100F;
exports.CL_DEVICE_MAX_MEM_ALLOC_SIZE = 0x1010;
exports.CL_DEVICE_IMAGE2D_MAX_WIDTH = 0x1011;
exports.CL_DEVICE_IMAGE2D_MAX_HEIGHT = 0x1012;
exports.CL_DEVICE_IMAGE3D_MAX_WIDTH = 0x1013;
exports.CL_DEVICE_IMAGE3D_MAX_HEIGHT = 0x1014;
exports.CL_DEVICE_IMAGE3D_MAX_DEPTH = 0x1015;
exports.CL_DEVICE_IMAGE_SUPPORT = 0x1016;
exports.CL_DEVICE_MAX_PARAMETER_SIZE = 0x1017;
exports.CL_DEVICE_MAX_SAMPLERS = 0x1018;
exports.CL_DEVICE_MEM_BASE_ADDR_ALIGN = 0x1019;
exports.CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE = 0x101A;
exports.CL_DEVICE_SINGLE_FP_CONFIG = 0x101B;
exports.CL_DEVICE_GLOBAL_MEM_CACHE_TYPE = 0x101C;
exports.CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE = 0x101D;
exports.CL_DEVICE_GLOBAL_MEM_CACHE_SIZE = 0x101E;
exports.CL_DEVICE_GLOBAL_MEM_SIZE = 0x101F;
exports.CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE = 0x1020;
exports.CL_DEVICE_MAX_CONSTANT_ARGS = 0x1021;
exports.CL_DEVICE_LOCAL_MEM_TYPE = 0x1022;
exports.CL_DEVICE_LOCAL_MEM_SIZE = 0x1023;
exports.CL_DEVICE_ERROR_CORRECTION_SUPPORT = 0x1024;
exports.CL_DEVICE_PROFILING_TIMER_RESOLUTION = 0x1025;
exports.CL_DEVICE_ENDIAN_LITTLE = 0x1026;
exports.CL_DEVICE_AVAILABLE = 0x1027;
exports.CL_DEVICE_COMPILER_AVAILABLE = 0x1028;
exports.CL_DEVICE_EXECUTION_CAPABILITIES = 0x1029;
exports.CL_DEVICE_QUEUE_PROPERTIES = 0x102A;    /* deprecated */
exports.CL_DEVICE_QUEUE_ON_HOST_PROPERTIES = 0x102A;
exports.CL_DEVICE_NAME = 0x102B;
exports.CL_DEVICE_VENDOR = 0x102C;
exports.CL_DRIVER_VERSION = 0x102D;
exports.CL_DEVICE_PROFILE = 0x102E;
exports.CL_DEVICE_VERSION = 0x102F;
exports.CL_DEVICE_EXTENSIONS = 0x1030;
exports.CL_DEVICE_PLATFORM = 0x1031;
exports.CL_DEVICE_DOUBLE_FP_CONFIG = 0x1032;
/* 0x1033 reserved for CL_DEVICE_HALF_FP_CONFIG */
exports.CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF = 0x1034;
exports.CL_DEVICE_HOST_UNIFIED_MEMORY = 0x1035;   /* deprecated */
exports.CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR = 0x1036;
exports.CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT = 0x1037;
exports.CL_DEVICE_NATIVE_VECTOR_WIDTH_INT = 0x1038;
exports.CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG = 0x1039;
exports.CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT = 0x103A;
exports.CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE = 0x103B;
exports.CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF = 0x103C;
exports.CL_DEVICE_OPENCL_C_VERSION = 0x103D;
exports.CL_DEVICE_LINKER_AVAILABLE = 0x103E;
exports.CL_DEVICE_BUILT_IN_KERNELS = 0x103F;
exports.CL_DEVICE_IMAGE_MAX_BUFFER_SIZE = 0x1040;
exports.CL_DEVICE_IMAGE_MAX_ARRAY_SIZE = 0x1041;
exports.CL_DEVICE_PARENT_DEVICE = 0x1042;
exports.CL_DEVICE_PARTITION_MAX_SUB_DEVICES = 0x1043;
exports.CL_DEVICE_PARTITION_PROPERTIES = 0x1044;
exports.CL_DEVICE_PARTITION_AFFINITY_DOMAIN = 0x1045;
exports.CL_DEVICE_PARTITION_TYPE = 0x1046;
exports.CL_DEVICE_REFERENCE_COUNT = 0x1047;
exports.CL_DEVICE_PREFERRED_INTEROP_USER_SYNC = 0x1048;
exports.CL_DEVICE_PRINTF_BUFFER_SIZE = 0x1049;
exports.CL_DEVICE_IMAGE_PITCH_ALIGNMENT = 0x104A;
exports.CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT = 0x104B;
exports.CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS = 0x104C;
exports.CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE = 0x104D;
exports.CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES = 0x104E;
exports.CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE = 0x104F;
exports.CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE = 0x1050;
exports.CL_DEVICE_MAX_ON_DEVICE_QUEUES = 0x1051;
exports.CL_DEVICE_MAX_ON_DEVICE_EVENTS = 0x1052;
exports.CL_DEVICE_SVM_CAPABILITIES = 0x1053;
exports.CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE = 0x1054;
exports.CL_DEVICE_MAX_PIPE_ARGS = 0x1055;
exports.CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS = 0x1056;
exports.CL_DEVICE_PIPE_MAX_PACKET_SIZE = 0x1057;
exports.CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT = 0x1058;
exports.CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT = 0x1059;
exports.CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT = 0x105A;

/* cl_mem_flags and cl_svm_mem_flags - bitfield */
exports.CL_MEM_READ_WRITE = (1 << 0);
exports.CL_MEM_WRITE_ONLY = (1 << 1);
exports.CL_MEM_READ_ONLY = (1 << 2);
exports.CL_MEM_USE_HOST_PTR = (1 << 3);
exports.CL_MEM_ALLOC_HOST_PTR = (1 << 4);
exports.CL_MEM_COPY_HOST_PTR = (1 << 5);
/* reserved                                         (1 << 6)    */
exports.CL_MEM_HOST_WRITE_ONLY = (1 << 7);
exports.CL_MEM_HOST_READ_ONLY = (1 << 8);
exports.CL_MEM_HOST_NO_ACCESS = (1 << 9);
exports.CL_MEM_SVM_FINE_GRAIN_BUFFER = (1 << 10);  /* used by cl_svm_mem_flags only */
exports.CL_MEM_SVM_ATOMICS = (1 << 11);  /* used by cl_svm_mem_flags only */
exports.CL_MEM_KERNEL_READ_AND_WRITE = (1 << 12);

exports.clCreateProgramWithSource = compute.createProgramWithSource;
exports.clGetProgramBuildInfo = compute.getProgramBuildInfo;
exports.clBuildProgram = compute.buildProgram;
exports.clCreateKernel = compute.createKernel;
exports.clSetKernelArg = compute.setKernelArg;
exports.clEnqueueNDRangeKernel = compute.enqueueNDRangeKernel;
exports.clEnqueueReadBuffer = compute.enqueueReadBuffer;

exports.clCreateBuffer = compute.createBuffer;
exports.clReleaseContext = compute.releaseContext;
exports.clReleaseProgram = compute.releaseProgram;
exports.clReleaseKernel = compute.releaseKernel;
exports.clReleaseCommandQueue = compute.releaseCommandQueue;

exports.clCreateContextFromType = compute.createContextFromType;
exports.clCreateCommandQueue = compute.createCommandQueue;
exports.clGetPlatformIDs = compute.getPlatformIDs;
exports.clGetDeviceIDs = compute.getDeviceIDs;

exports.clGetPlatformInfo = function(platform, info) {
    compute.getPlatformInfo(platform, info);

    const keyName = getKeyByValue(exports, info);
    const value = platform.info;

    delete platform.info;
    platform[keyName] = value;
};

exports.clGetDeviceInfo = (device, info) => {
    compute.getDeviceInfo(device, info);

    const keyName = getKeyByValue(exports, info);
    const value = device.info;

    delete device.info;
    device[keyName] = value;
};

exports.clCreateImage2D = function () {
    const method = compute.createImage2D;
    return method.apply(null, arguments);
}

exports.clCreateSampler = function () {
    const method = compute.createSampler;
    return method.apply(null, arguments);
}

exports.clReleaseMemObject = compute.releaseMemObject;
exports.clReleaseSampler = compute.releaseSampler;

exports.clEnqueueReadImage = compute.enqueueReadImage;
exports.hasImageSupport = compute.hasImageSupport;