
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

#include "ParticleSystem.h"
#include "Render.h"
#include "C:/ProgramData/NVIDIA Corporation/CUDA Samples/v8.0/common/inc/GL/freeglut.h"	


__host__ cudaError_t simulateParticles(int);

__global__ void simulateParticles()
{
	

}

int main(int argc, char* argv[])
{
	int *argc_ptr = &argc;
	Render render;
	render.InitGL(argc ,argv);
	glutMainLoop();


//	// Add vectors in parallel.
//	cudaError_t cudaStatus = simulateParticles(1);
//	if (cudaStatus != cudaSuccess) {
//		fprintf(stderr, "addWithCuda failed!");
//		return 1;
//	}
//
//	// cudaDeviceReset must be called before exiting in order for profiling and
//	// tracing tools such as Nsight and Visual Profiler to show complete traces.
//	cudaStatus = cudaDeviceReset();
//	if (cudaStatus != cudaSuccess) {
//		fprintf(stderr, "cudaDeviceReset failed!");
//		return 1;
//	}

	return 0;
}


__host__ cudaError_t simulateParticles(int)
{
	    cudaError_t cudaStatus;
	//
	//    // Choose which GPU to run on, change this on a multi-GPU system.
	//    cudaStatus = cudaSetDevice(0);
	//    if (cudaStatus != cudaSuccess) {
	//        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
	//        goto Error;
	//    }
	//
	//    // Allocate GPU buffers for three vectors (two input, one output)    .
	//    cudaStatus = cudaMalloc((void**)&dev_c, size * sizeof(int));
	//    if (cudaStatus != cudaSuccess) {
	//        fprintf(stderr, "cudaMalloc failed!");
	//        goto Error;
	//    }
	//
	//    cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(int));
	//    if (cudaStatus != cudaSuccess) {
	//        fprintf(stderr, "cudaMalloc failed!");
	//        goto Error;
	//    }
	//
	//    cudaStatus = cudaMalloc((void**)&dev_b, size * sizeof(int));
	//    if (cudaStatus != cudaSuccess) {
	//        fprintf(stderr, "cudaMalloc failed!");
	//        goto Error;
	//    }
	//
	//    // Copy input vectors from host memory to GPU buffers.
	//    cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
	//    if (cudaStatus != cudaSuccess) {
	//        fprintf(stderr, "cudaMemcpy failed!");
	//        goto Error;
	//    }
	//
	//    cudaStatus = cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
	//    if (cudaStatus != cudaSuccess) {
	//        fprintf(stderr, "cudaMemcpy failed!");
	//        goto Error;
	//    }
	//
	//    // Launch a kernel on the GPU with one thread for each element.
	//    addKernel<<<1, size>>>(dev_c, dev_a, dev_b);
	//
	//    // Check for any errors launching the kernel
	//    cudaStatus = cudaGetLastError();
	//    if (cudaStatus != cudaSuccess) {
	//        fprintf(stderr, "addKernel launch failed: %s\number_of_particles", cudaGetErrorString(cudaStatus));
	//        goto Error;
	//    }
	//    
	//    // cudaDeviceSynchronize waits for the kernel to finish, and returns
	//    // any errors encountered during the launch.
	//    cudaStatus = cudaDeviceSynchronize();
	//    if (cudaStatus != cudaSuccess) {
	//        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\number_of_particles", cudaStatus);
	//        goto Error;
	//    }
	//
	//    // Copy output vector from GPU buffer to host memory.
	//    cudaStatus = cudaMemcpy(c, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);
	//    if (cudaStatus != cudaSuccess) {
	//        fprintf(stderr, "cudaMemcpy failed!");
	//        goto Error;
	//    }
	//
	//Error:
	//    cudaFree(dev_c);
	//    cudaFree(dev_a);
	//    cudaFree(dev_b);
	//    
	    return cudaStatus;
}
