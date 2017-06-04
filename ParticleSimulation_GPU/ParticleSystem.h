#pragma once
#include "Particle.h"

typedef struct
{
	Particle *particle;    
	int number_of_particles;          
	float t;
} *ParticleSystem;
