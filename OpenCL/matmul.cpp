#include <CL/cl2.hpp>
#include <iostream>
#include <vector>

const char* kernelSource = R"CLC(
__kernel void matrix_mul(__global float* A, __global float* B, __global float* C, int N) {
    int row = get_global_id(0);
    int col = get_global_id(1);

    float value = 0.0;
    for (int k = 0; k < N; k++) {
        value += A[row * N + k] * B[k * N + col];
    }
    C[row * N + col] = value;
}
)CLC";

const int N = 8192; // Matrix size

int main() {
    // Initialize matrices
    std::vector<float> A(N * N, 1.0f);
    std::vector<float> B(N * N, 1.0f);
    std::vector<float> C(N * N, 0.0f);

    // Set up OpenCL
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    auto platform = platforms.front();

    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
    auto device = devices.front();

    cl::Context context(device);
    cl::CommandQueue queue(context, device, CL_QUEUE_PROFILING_ENABLE);

    // Create buffers
    cl::Buffer bufferA(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * N * N, A.data());
    cl::Buffer bufferB(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * N * N, B.data());
    cl::Buffer bufferC(context, CL_MEM_WRITE_ONLY, sizeof(float) * N * N);

    // Compile kernel
    cl::Program program(context, kernelSource);
    program.build("-cl-std=CL1.2");
    cl::Kernel kernel(program, "matrix_mul");

    // Set kernel arguments
    kernel.setArg(0, bufferA);
    kernel.setArg(1, bufferB);
    kernel.setArg(2, bufferC);
    kernel.setArg(3, N);

     cl::Event writeEvent, kernelEvent, readEvent;  // Define events for timing
     
     cl::NDRange global(N, N); // Launch N x N work-items.

    // Write data to GPU
    queue.enqueueWriteBuffer(bufferA, CL_FALSE, 0, sizeof(float) * N * N, A.data(), nullptr, &writeEvent);
    queue.enqueueWriteBuffer(bufferB, CL_FALSE, 0, sizeof(float) * N * N, B.data());

    // Execute kernel
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, cl::NullRange, nullptr, &kernelEvent);

    // Read result back from GPU
    queue.enqueueReadBuffer(bufferC, CL_TRUE, 0, sizeof(float) * N * N, C.data(), nullptr, &readEvent);

    // Calculate elapsed time for each operation
    cl_ulong startTime, endTime;

    writeEvent.getProfilingInfo(CL_PROFILING_COMMAND_START, &startTime);
    writeEvent.getProfilingInfo(CL_PROFILING_COMMAND_END, &endTime);
    double writeTime = (endTime - startTime) * 1.0e-6;  // Convert to milliseconds

    kernelEvent.getProfilingInfo(CL_PROFILING_COMMAND_START, &startTime);
    kernelEvent.getProfilingInfo(CL_PROFILING_COMMAND_END, &endTime);
    double kernelTime = (endTime - startTime) * 1.0e-6;

    readEvent.getProfilingInfo(CL_PROFILING_COMMAND_START, &startTime);
    readEvent.getProfilingInfo(CL_PROFILING_COMMAND_END, &endTime);
    double readTime = (endTime - startTime) * 1.0e-6;

    std::cout << "Buffer Write Time: " << writeTime << " ms\n";
    std::cout << "Kernel Execution Time: " << kernelTime << " ms\n";
    std::cout << "Buffer Read Time: " << readTime << " ms\n";
    
    // For verification: print some elements from the resulting matrix
    for(int i = 0; i < 10; ++i) {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

