#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#include "GL/glew.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "cuda_runtime.h"
#include "kernel.cuh"
#include "text.h"
#define VERBOSE
#define Nb_Particules 81920
#define Nb_Samples 1024

static float g_inertia = 0.5f;

static float oldCamPos[] = { 0.0f, 0.0f, -45.0f };
static float oldCamRot[] = { 0.0f, 0.0f, 0.0f };
static float newCamPos[] = { 0.0f, 0.0f, -45.0f };
static float newCamRot[] = { 0.0f, 0.0f, 0.0f };

static bool g_showGrid = true;
static bool g_showAxes = true;
static bool g_ShowParticles = true;

inline bool CUDA_MALLOC( void ** devPtr, size_t size ) {
	cudaError_t cudaStatus;
	cudaStatus = cudaMalloc( devPtr, size );
	if ( cudaStatus != cudaSuccess ) {
		printf( "error: unable to allocate buffer\n");
		return false;
	}
	return true;
}

inline bool CUDA_MEMCPY( void * dst, const void * src, size_t count, enum cudaMemcpyKind kind ) {
	cudaError_t cudaStatus;
	cudaStatus = cudaMemcpy( dst, src, count, kind );
	if ( cudaStatus != cudaSuccess ) {
		printf( "error: unable to copy buffer\n");
		return false;
	}
	return true;
}

void RandomizeFloatArray( int n, float * arr ) {
	for ( int i = 0; i < n; i++ ) {
		arr[i] = (float)rand() / ( (float)RAND_MAX / 2.0f ) - 1.0f;
	}
}
void ShowParticles(float PosX[], float PosY[], float PosZ[]){
	int i = 0;
	

	for (i=0; i<Nb_Samples;i++){
		if ((i>=0 && i<(16384/80)) || (i>=(32768/80) && i<(40960/80)) || (i>=(49152/80) && (i<65536/80))) {		// Milkyway
			glBegin( GL_POINTS );
			glColor3f( 1.0f, 1.0f, 0.0f );
			glVertex3f(PosX[i],PosY[i],PosZ[i]);	
			glEnd(); 
			}
		else if ((i>=(16384/80) && i<(32768/80)) || (i>=(40690/80) && i< (49152/80)) ||(i>=(65536/80) && i< (81920/80)))  { 	// Andromeda
			glBegin( GL_POINTS );
			glColor3f( 1.0f, 0.0f, 0.0f );
			glVertex3f(PosX[i], PosY[i], PosZ[i]);	
			glEnd();
		}
	}	
}

void DrawGridXZ( float ox, float oy, float oz, int w, int h, float sz ) {
	
	int i;

	glLineWidth( 1.0f );

	glBegin( GL_LINES );

	glColor3f( 0.48f, 0.48f, 0.48f );

	for ( i = 0; i <= h; ++i ) {
		glVertex3f( ox, oy, oz + i * sz );
		glVertex3f( ox + w * sz, oy, oz + i * sz );
	}

	for ( i = 0; i <= h; ++i ) {
		glVertex3f( ox + i * sz, oy, oz );
		glVertex3f( ox + i * sz, oy, oz + h * sz );
	}

	glEnd();

}

void ShowAxes() {

	glLineWidth( 2.0f );

	glBegin( GL_LINES );
	
	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex3f( 0.0f, 0.0f, 0.0f );
	glVertex3f( 2.0f, 0.0f, 0.0f );

	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex3f( 0.0f, 0.0f, 0.0f );
	glVertex3f( 0.0f, 2.0f, 0.0f );

	glColor3f( 0.0f, 0.0f, 1.0f );
	glVertex3f( 0.0f, 0.0f, 0.0f );
	glVertex3f( 0.0f, 0.0f, 2.0f );
	
	glEnd();

}


int main( int argc, char ** argv ) {

float AllParticulesMass[Nb_Particules];
float AllParticulesPosX[Nb_Particules];
float AllParticulesPosY[Nb_Particules];
float AllParticulesPosZ[Nb_Particules];
float AllParticulesVelX[Nb_Particules];
float AllParticulesVelY[Nb_Particules];
float AllParticulesVelZ[Nb_Particules];


float *ParticulesTrieesCPUMass = NULL;
float *ParticulesTrieesCPUPosX = NULL;
float *ParticulesTrieesCPUPosY = NULL;
float *ParticulesTrieesCPUPosZ = NULL;
float *ParticulesTrieesCPUVelX = NULL;
float *ParticulesTrieesCPUVelY = NULL;
float *ParticulesTrieesCPUVelZ = NULL;

float *ParticulesTrieesGPUMass = NULL;
float *ParticulesTrieesGPUPosX = NULL;
float *ParticulesTrieesGPUPosY = NULL;
float *ParticulesTrieesGPUPosZ = NULL;
float *ParticulesTrieesGPUVelX = NULL;
float *ParticulesTrieesGPUVelY = NULL;
float *ParticulesTrieesGPUVelZ = NULL;



// Allocation mémoire CPU

	ParticulesTrieesCPUMass = (float * )malloc( sizeof( float ) * Nb_Samples );
	ParticulesTrieesCPUPosX = (float * )malloc( sizeof( float ) * Nb_Samples );
	ParticulesTrieesCPUPosY = (float * )malloc( sizeof( float ) * Nb_Samples );
	ParticulesTrieesCPUPosZ = (float * )malloc( sizeof( float ) * Nb_Samples );
	ParticulesTrieesCPUVelX = (float * )malloc( sizeof( float ) * Nb_Samples );
	ParticulesTrieesCPUVelY = (float * )malloc( sizeof( float ) * Nb_Samples );
	ParticulesTrieesCPUVelZ = (float * )malloc( sizeof( float ) * Nb_Samples );


	int i,count = 0;

	FILE *fd =  fopen("./bin/dubinski.tab","r"); 

	if (fd == NULL) printf("impossible d'ouvrir le fichier\n");
	else printf("Fichier ouvert\n");

	/*if(argc>2) int numthreads = atoi(argv[1]);
	else {
	printf("ERROR : Syntaxe : <Nom programme> <Nombre threads>\n");
	exit(0);
	}*/

	int numthreads = 192;
	int numblocks = (Nb_Samples  + ( numthreads - 1) ) / numthreads;



	for (i = 0; i<Nb_Particules;i++){

	fscanf(fd, "%f %f %f %f %f %f %f",&AllParticulesMass[i], &AllParticulesPosX[i], &AllParticulesPosY[i],&AllParticulesPosZ[i], &AllParticulesVelX[i], 		&AllParticulesVelY[i], &AllParticulesVelZ[i]);

		if (i%80 == 0 ){
		ParticulesTrieesCPUMass[count] = AllParticulesMass[i];
		ParticulesTrieesCPUPosX[count] = AllParticulesPosX[i];
		ParticulesTrieesCPUPosY[count] = AllParticulesPosY[i];
		ParticulesTrieesCPUPosZ[count] = AllParticulesPosZ[i];
		ParticulesTrieesCPUVelX[count] = AllParticulesVelX[i];
		ParticulesTrieesCPUVelY[count] = AllParticulesVelY[i];
		ParticulesTrieesCPUVelZ[count] = AllParticulesVelZ[i];
		count=count+1;

		}	
	}

	fclose(fd);


	//Allocation mémoire GPU
	CUDA_MALLOC( (void**)&ParticulesTrieesGPUMass		, Nb_Samples * sizeof(float ) );
	CUDA_MALLOC( (void**)&ParticulesTrieesGPUPosX		, Nb_Samples * sizeof(float ) );
	CUDA_MALLOC( (void**)&ParticulesTrieesGPUPosY		, Nb_Samples * sizeof(float ) );
	CUDA_MALLOC( (void**)&ParticulesTrieesGPUPosZ		, Nb_Samples * sizeof(float ) );
	CUDA_MALLOC( (void**)&ParticulesTrieesGPUVelX		, Nb_Samples * sizeof(float ) );
	CUDA_MALLOC( (void**)&ParticulesTrieesGPUVelY		, Nb_Samples * sizeof(float ) );
	CUDA_MALLOC( (void**)&ParticulesTrieesGPUVelZ		, Nb_Samples * sizeof(float ) );


	CUDA_MEMCPY( ParticulesTrieesGPUMass, ParticulesTrieesCPUMass	, Nb_Samples * sizeof( float  ), cudaMemcpyHostToDevice );
	CUDA_MEMCPY( ParticulesTrieesGPUPosX, ParticulesTrieesCPUPosX	, Nb_Samples * sizeof( float  ), cudaMemcpyHostToDevice );
	CUDA_MEMCPY( ParticulesTrieesGPUPosY, ParticulesTrieesCPUPosY	, Nb_Samples * sizeof( float ), cudaMemcpyHostToDevice );
	CUDA_MEMCPY( ParticulesTrieesGPUPosZ, ParticulesTrieesCPUPosZ	, Nb_Samples * sizeof( float  ), cudaMemcpyHostToDevice );
	CUDA_MEMCPY( ParticulesTrieesGPUVelX, ParticulesTrieesCPUVelX	, Nb_Samples * sizeof( float  ), cudaMemcpyHostToDevice );
	CUDA_MEMCPY( ParticulesTrieesGPUVelY, ParticulesTrieesCPUVelY	, Nb_Samples * sizeof( float  ), cudaMemcpyHostToDevice );
	CUDA_MEMCPY( ParticulesTrieesGPUVelZ, ParticulesTrieesCPUVelZ	, Nb_Samples * sizeof( float  ), cudaMemcpyHostToDevice );

	SDL_Event event;
	SDL_Window * window;
	SDL_DisplayMode current;
  	
	int width = 640;
	int height = 480;

	bool done = false;

	float mouseOriginX = 0.0f;
	float mouseOriginY = 0.0f;

	float mouseMoveX = 0.0f;
	float mouseMoveY = 0.0f;

	float mouseDeltaX = 0.0f;
	float mouseDeltaY = 0.0f;

	struct timeval begin, end;
	float fps = 0.0;
	char sfps[40] = "FPS: ";

	if ( SDL_Init ( SDL_INIT_EVERYTHING ) < 0 ) {
		printf( "error: unable to init sdl\n" );
		return -1;
	}

	if ( SDL_GetDesktopDisplayMode( 0, &current ) ) {
		printf( "error: unable to get current display mode\n" );
		return -1;
	}

	window = SDL_CreateWindow( "SDL", 	SDL_WINDOWPOS_CENTERED, 
										SDL_WINDOWPOS_CENTERED, 
										width, height, 
										SDL_WINDOW_OPENGL );
  
	SDL_GLContext glWindow = SDL_GL_CreateContext( window );

	GLenum status = glewInit();

	if ( status != GLEW_OK ) {
		printf( "error: unable to init glew\n" );
		return -1;
	}

	if ( ! InitTextRes( "./bin/DroidSans.ttf" ) ) {
		printf( "error: unable to init text resources\n" );
		return -1;
	}

	SDL_GL_SetSwapInterval( 1 );

	freopen("/dev/tty","w",stdout);

	// Init
	cudaError_t cudaStatus;
	cudaStatus = cudaSetDevice( 0 );	// Une fois en début de programme pour init

	if ( cudaStatus != cudaSuccess ) {
	printf( "error: unable to setup cuda device\n");
	}

		


	while ( !done ) {
  		
		int i ;


		while ( SDL_PollEvent( &event ) ) {
      
			unsigned int e = event.type;
			
			if ( e == SDL_MOUSEMOTION ) {
				mouseMoveX = event.motion.x;
				mouseMoveY = height - event.motion.y - 1;
			} else if ( e == SDL_KEYDOWN ) {
				if ( event.key.keysym.sym == SDLK_F1 ) {
					g_showGrid = !g_showGrid;
				} else if ( event.key.keysym.sym == SDLK_F2 ) {
					g_showAxes = !g_showAxes;
				} else if ( event.key.keysym.sym == SDLK_ESCAPE ) {
 					done = true;
				}
			}

			if ( e == SDL_QUIT ) {
				printf( "quit\n" );
				done = true;
			}

		}

		mouseDeltaX = mouseMoveX - mouseOriginX;
		mouseDeltaY = mouseMoveY - mouseOriginY;

		if ( SDL_GetMouseState( 0, 0 ) & SDL_BUTTON_LMASK ) {
			oldCamRot[ 0 ] += -mouseDeltaY / 5.0f;
			oldCamRot[ 1 ] += mouseDeltaX / 5.0f;
		}else if ( SDL_GetMouseState( 0, 0 ) & SDL_BUTTON_RMASK ) {
			oldCamPos[ 2 ] += ( mouseDeltaY / 100.0f ) * 0.5 * fabs( oldCamPos[ 2 ] );
			oldCamPos[ 2 ]  = oldCamPos[ 2 ] > -5.0f ? -5.0f : oldCamPos[ 2 ];
		}

		mouseOriginX = mouseMoveX;
		mouseOriginY = mouseMoveY;

		glViewport( 0, 0, width, height );
		glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glEnable( GL_BLEND );
		glBlendEquation( GL_FUNC_ADD );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glDisable( GL_TEXTURE_2D );
		glEnable( GL_DEPTH_TEST );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( 50.0f, (float)width / (float)height, 0.1f, 100000.0f );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		for ( i = 0; i < 3; ++i ) {
			newCamPos[ i ] += ( oldCamPos[ i ] - newCamPos[ i ] ) * g_inertia;
			newCamRot[ i ] += ( oldCamRot[ i ] - newCamRot[ i ] ) * g_inertia;
		}

		glTranslatef( newCamPos[0], newCamPos[1], newCamPos[2] );
		glRotatef( newCamRot[0], 1.0f, 0.0f, 0.0f );
		glRotatef( newCamRot[1], 0.0f, 1.0f, 0.0f );
		
		if ( g_showGrid ) {
			DrawGridXZ( -100.0f, 0.0f, -100.0f, 20, 20, 10.0 );
		}

		if ( g_showAxes ) {
			ShowAxes();
		}
		
		if (g_ShowParticles){
		ShowParticles(ParticulesTrieesCPUPosX,ParticulesTrieesCPUPosY,ParticulesTrieesCPUPosZ);
		}

		gettimeofday( &begin, NULL );
		
		// Appels Kernels

		accel1( numblocks, numthreads,  Nb_Samples, ParticulesTrieesGPUMass, ParticulesTrieesGPUPosX, ParticulesTrieesGPUPosY,ParticulesTrieesGPUPosZ, ParticulesTrieesGPUVelX, ParticulesTrieesGPUVelY, ParticulesTrieesGPUVelZ);

		 accel2( numblocks, numthreads,  Nb_Samples, ParticulesTrieesGPUVelX,  ParticulesTrieesGPUVelY,  ParticulesTrieesGPUVelZ, ParticulesTrieesGPUPosX, ParticulesTrieesGPUPosY,  ParticulesTrieesGPUPosZ) ;
		
		// Synchro des Threads
		
		cudaStatus = cudaDeviceSynchronize();
		if (cudaStatus != cudaSuccess){
			printf("error synchronize Threads\n");
		}

 		//Copie retour

		CUDA_MEMCPY( ParticulesTrieesCPUPosX, ParticulesTrieesGPUPosX 	, Nb_Samples * sizeof( float  ), cudaMemcpyDeviceToHost );
		CUDA_MEMCPY( ParticulesTrieesCPUPosY, ParticulesTrieesGPUPosY 	, Nb_Samples * sizeof( float  ), cudaMemcpyDeviceToHost );
		CUDA_MEMCPY( ParticulesTrieesCPUPosZ, ParticulesTrieesGPUPosZ	, Nb_Samples * sizeof( float  ), cudaMemcpyDeviceToHost );
	
		gettimeofday( &end, NULL );

		fps = (float)1.0f / ( ( end.tv_sec - begin.tv_sec ) * 1000000.0f + end.tv_usec - begin.tv_usec) * 1000000.0f;
		sprintf( sfps, "FPS : %.4f", fps );

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, width, 0, height);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		DrawText( 10, height - 20, sfps, TEXT_ALIGN_LEFT, RGBA(255, 255, 255, 255) );
		DrawText( 10, 30, "'F1' : show/hide grid", TEXT_ALIGN_LEFT, RGBA(255, 255, 255, 255) );
		DrawText( 10, 10, "'F2' : show/hide axes", TEXT_ALIGN_LEFT, RGBA(255, 255, 255, 255) );

		SDL_GL_SwapWindow( window );
		SDL_UpdateWindowSurface( window );
	

		}

	SDL_GL_DeleteContext( glWindow );
	DestroyTextRes();
	SDL_DestroyWindow( window );
	SDL_Quit();


	return 1;

}

