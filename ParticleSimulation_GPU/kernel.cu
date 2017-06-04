
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

#include "ParticleSystem.h"

__host__ cudaError_t simulateParticles(int);

__global__ void simulateParticles()
{
	

}

int main()
{

	// Add vectors in parallel.
	cudaError_t cudaStatus = simulateParticles(1);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "addWithCuda failed!");
		return 1;
	}

	// cudaDeviceReset must be called before exiting in order for profiling and
	// tracing tools such as Nsight and Visual Profiler to show complete traces.
	cudaStatus = cudaDeviceReset();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaDeviceReset failed!");
		return 1;
	}

	return 0;
}

int ParticleDims(ParticleSystem particle_system)
{
	return(6 * particle_system->number_of_particles);
};

int ParticleGetState(ParticleSystem particle_system, float *dst)
{
	for (int i = 0; i < particle_system->number_of_particles; i++)
	{
		*(dst++) = particle_system->particle[i]->p.x;
		*(dst++) = particle_system->particle[i]->p.y;
		*(dst++) = particle_system->particle[i]->p.z;
		*(dst++) = particle_system->particle[i]->v.x;
		*(dst++) = particle_system->particle[i]->v.y;
		*(dst++) = particle_system->particle[i]->v.z;
	}
}

int ParticleSetState(ParticleSystem particle_system, float *src)
{
	for (int i = 0; i < particle_system->number_of_particles; i++) {
		particle_system->particle[i]->p.x = *(src++);
		particle_system->particle[i]->p.y = *(src++);
		particle_system->particle[i]->p.z = *(src++);
		particle_system->particle[i]->v.x = *(src++);
		particle_system->particle[i]->v.y = *(src++);
		particle_system->particle[i]->v.z = *(src++);
	}
}

void Clear_Forces(ParticleSystem particle_system);

void Compute_Forces(ParticleSystem particle_system);

int ParticleDerivative(ParticleSystem particle_system, float *dst)
{
	
	Clear_Forces(particle_system);   /* zero the force accumulators */
	Compute_Forces(particle_system); /* magic force function */
	for (int i = 0; i < particle_system->number_of_particles; i++) {
		*(dst++) = particle_system->particle[i]->v.x;    /* xdot=v*/
		*(dst++) = particle_system->particle[i]->v.y;
		*(dst++) = particle_system->particle[i]->v.z;
		*(dst++) = particle_system->particle[i]->f.x / particle_system->particle[i]->m; /* vdot = f/m */
		*(dst++) = particle_system->particle[i]->f.y / particle_system->particle[i]->m;
		*(dst++) = particle_system->particle[i]->f.z / particle_system->particle[i]->m;
	}
}

void ScaleVector(float* temp1, float delta_t);

void AddVectors(float* vector1, float* vector2, float* result);

void EulerStep(ParticleSystem particle_system, float DeltaT)
{
	float *temp1, *temp2;
	ParticleDerivative(particle_system, temp1);   /* get deriv */
	ScaleVector(temp1, DeltaT);       /* scale it */
	ParticleGetState(particle_system, temp2);      /* get state */
	AddVectors(temp1, temp2, temp2);  /* add -> temp2 */
	ParticleSetState(particle_system, temp2);      /* update state */
	particle_system->t += DeltaT;                 /* update time */
}


__host__ cudaError_t simulateParticles(int)
{
	//    cudaError_t cudaStatus;
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
	//    return cudaStatus;
}
