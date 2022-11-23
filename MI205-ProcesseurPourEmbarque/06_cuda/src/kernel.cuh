#ifndef __KERNEL_CUH__
#define __KERNEL_CUH__


#define G_INERTIA 0.5f

#define Nb_Samples 1024
#define Nb_Particules 81920
#define Length_Modeling 3000
#define TIME  0.1
#define  MassFactor 10
#define  PartDampingFactor 1


void accel1( int nblocks, int nthreads, int n, float *ParticulesTrieesGPUMass, float *ParticulesTrieesGPUPosX, float *ParticulesTrieesGPUPosY, float *ParticulesTrieesGPUPosZ,float *ParticulesTrieesGPUVelX,float *ParticulesTrieesGPUVelY, float *ParticulesTrieesGPUVelZ);
	
void accel2( int nblocks, int nthreads,int n, float *ParticulesTrieesGPUVelX, float *ParticulesTrieesGPUVelY, float *ParticulesTrieesGPUVelZ, float *ParticulesTrieesGPUPosX,float *ParticulesTrieesGPUPosY, float *ParticulesTrieesGPUPosZ);

#endif
