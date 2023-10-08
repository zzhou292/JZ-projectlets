#include <CL/cl2.hpp>
#include <iostream>
#include <vector>

const char* kernelSource = 
    "__kernel void hello() { \n"
    "  printf(\"Hello, World! from work-item %d\\n\", get_global_id(0)); \n"
    "} \n";

int main() {
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    auto platform = platforms.front();
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    auto device = devices.front();
    
    // Print device name and type
    std::string deviceName = device.getInfo<CL_DEVICE_NAME>();
    cl_device_type deviceType = device.getInfo<CL_DEVICE_TYPE>();
    std::cout << "Running on Device: " << deviceName << std::endl;
    std::cout << "Device Type: ";
    switch (deviceType) {
        case CL_DEVICE_TYPE_CPU:
            std::cout << "CPU";
            break;
        case CL_DEVICE_TYPE_GPU:
            std::cout << "GPU";
            break;
        case CL_DEVICE_TYPE_ACCELERATOR:
            std::cout << "Accelerator";
            break;
        default:
            std::cout << "Other";
            break;
    }
    std::cout << std::endl;


    cl::Context context(device);

    cl::Program program(context, kernelSource);
    program.build("-cl-std=CL1.2");

    cl::Kernel kernel(program, "hello");

    cl::CommandQueue queue(context, device);
    cl::NDRange global_work_size(10);

    queue.enqueueNDRangeKernel(kernel, cl::NullRange, global_work_size, cl::NullRange);

    queue.finish();

    return 0;
}

