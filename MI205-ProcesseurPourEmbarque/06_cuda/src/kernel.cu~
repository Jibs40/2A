#include "cuda.h"
#include "kernel.cuh"


__global__ void Modeling (int n, float *ParticulesTrieesGPUMass, float *ParticulesTrieesGPUPosX, float *ParticulesTrieesGPUPosY, float *ParticulesTrieesGPUPosZ,float *ParticulesTrieesGPUVelX,float *ParticulesTrieesGPUVelY, float *ParticulesTrieesGPUVelZ){

int part_i = blockIdx.x * blockDim.x + threadIdx.x; // Repartition des calculs
	
	if (part_i<n)
	{
		float accelx = 0;
		float accely = 0;
		float accelz = 0;

		int part_j;
		float px = ParticulesTrieesGPUPosX[part_i];
		float py = ParticulesTrieesGPUPosY[part_i];
		float pz = ParticulesTrieesGPUPosZ[part_i];
		for (part_j = 0; part_j<n ;part_j++){

			float deltax = ParticulesTrieesGPUPosX[part_j]-px;
			float deltay = ParticulesTrieesGPUPosY[part_j]-py;
			float deltaz = ParticulesTrieesGPUPosZ[part_j]-pz;

			float dist = sqrtf((deltax * deltax)+ (deltay * deltay) + (deltaz * deltaz));
			if ( dist < 1.0 ) dist = 1.0;
			float d3 = dist * dist * dist;


			float m = MassFactor * PartDampingFactor * (1/d3) * ParticulesTrieesGPUMass[part_j];

			accelx += deltax * m;
			accely += deltay * m;
			accelz += deltaz * m;	

		}

 		ParticulesTrieesGPUVelX[part_i] += accelx;
		ParticulesTrieesGPUVelY[part_i] += accely;
		ParticulesTrieesGPUVelZ[part_i] += accelz;
	}
}

__global__ void accel_funct2(int n, float *ParticulesTrieesGPUVelX, float *ParticulesTrieesGPUVelY, float *ParticulesTrieesGPUVelZ, float *ParticulesTrieesGPUPosX,float *ParticulesTrieesGPUPosY, float *ParticulesTrieesGPUPosZ){

int k = blockIdx.x * blockDim.x + threadIdx.x;
	if(k<n){



		ParticulesTrieesGPUPosX[k] += ParticulesTrieesGPUVelX[k] * TIME ;
		ParticulesTrieesGPUPosY[k] += ParticulesTrieesGPUVelY[k] * TIME ;
		ParticulesTrieesGPUPosZ[k] += ParticulesTrieesGPUVelZ[k] * TIME ;
		}


}

void accel1( int nblocks, int nthreads, int n, float *ParticulesTrieesGPUMass, float *ParticulesTrieesGPUPosX, float *ParticulesTrieesGPUPosY, float *ParticulesTrieesGPUPosZ,float *ParticulesTrieesGPUVelX,float *ParticulesTrieesGPUVelY, float *ParticulesTrieesGPUVelZ) {
	Modeling<<<nblocks, nthreads>>>( n,  ParticulesTrieesGPUMass,  ParticulesTrieesGPUPosX, ParticulesTrieesGPUPosY, ParticulesTrieesGPUPosZ, ParticulesTrieesGPUVelX, ParticulesTrieesGPUVelY, ParticulesTrieesGPUVelZ);

}

void accel2( int nblocks, int nthreads,int n, float *ParticulesTrieesGPUVelX, float *ParticulesTrieesGPUVelY, float *ParticulesTrieesGPUVelZ, float *ParticulesTrieesGPUPosX,float *ParticulesTrieesGPUPosY, float *ParticulesTrieesGPUPosZ) {
	accel_funct2<<<nblocks, nthreads>>>(  n, ParticulesTrieesGPUVelX, ParticulesTrieesGPUVelY, ParticulesTrieesGPUVelZ, ParticulesTrieesGPUPosX, ParticulesTrieesGPUPosY, ParticulesTrieesGPUPosZ);
}








