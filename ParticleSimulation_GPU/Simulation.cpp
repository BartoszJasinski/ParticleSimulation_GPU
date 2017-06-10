#include "Simulation.h"
#include "ParticleSystem.h"


int particleDims(ParticleSystem particle_system)
{
	return(6 * particle_system->number_of_particles);
}


void clearForces(ParticleSystem particle_system)
{
	
}

void computeForces(ParticleSystem particle_system)
{
	
}

int particleDerivative(ParticleSystem particle_system, float *dst)
{

	clearForces(particle_system);   /* zero the force accumulators */
	computeForces(particle_system); /* magic force function */
	for (int i = 0; i < particle_system->number_of_particles; i++)
	{
		*(dst++) = particle_system->particle[i]->v.x;    /* xdot=v*/
		*(dst++) = particle_system->particle[i]->v.y;
		*(dst++) = particle_system->particle[i]->v.z;
		*(dst++) = particle_system->particle[i]->f.x / particle_system->particle[i]->m; /* vdot = f/m */
		*(dst++) = particle_system->particle[i]->f.y / particle_system->particle[i]->m;
		*(dst++) = particle_system->particle[i]->f.z / particle_system->particle[i]->m;
	}

	return 0;
}

int particleGetState(ParticleSystem particle_system, float *dst)
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

	return 0;
}

int particleSetState(ParticleSystem particle_system, float *src)
{
	for (int i = 0; i < particle_system->number_of_particles; i++)
	{
		particle_system->particle[i]->p.x = *(src++);
		particle_system->particle[i]->p.y = *(src++);
		particle_system->particle[i]->p.z = *(src++);
		particle_system->particle[i]->v.x = *(src++);
		particle_system->particle[i]->v.y = *(src++);
		particle_system->particle[i]->v.z = *(src++);
	}

	return 0;
}

void scaleVector(float* temp1, float delta_t)
{
	
}

void addVectors(float* temp1, float* temp2, float* temp3)
{
	
}

void eulerStep(ParticleSystem particle_system, float DeltaT)
{
	float *temp1, *temp2;
	particleDerivative(particle_system, temp1);   /* get deriv */
	scaleVector(temp1, DeltaT);       /* scale it */
	particleGetState(particle_system, temp2);      /* get state */
	addVectors(temp1, temp2, temp2);  /* add -> temp2 */
	particleSetState(particle_system, temp2);      /* update state */
	particle_system->t += DeltaT;                 /* update time */
}
