#pragma once
#include "ParticleSystem.h"

class Simulation
{
public:

	int particleDims(ParticleSystem particle_system);
	int particleGetState(ParticleSystem particle_system, float *dst);
	int particleSetState(ParticleSystem particle_system, float *src);
	int particleDerivative(ParticleSystem particle_system, float *dst);
	void clearForces(ParticleSystem particle_system);
	void computeForces(ParticleSystem particle_system);
	void scaleVector(float* temp1, float delta_t);
	void addVectors(float* vector1, float* vector2, float* result);
	void eulerStep(ParticleSystem particle_system, float DeltaT);

};
