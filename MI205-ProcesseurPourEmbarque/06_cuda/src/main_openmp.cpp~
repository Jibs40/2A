#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

#include "GL/glew.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "text.h"

#define Nb_Samples 1024
#define Nb_Particules 81920
#define Length_Modeling 3000
#define TIME  0.1
#define  MassFactor 10
#define  PartDampingFactor 1





static float g_inertia = 0.5f;

static float oldCamPos[] = { 0.0f, 0.0f, -45.0f };
static float oldCamRot[] = { 0.0f, 0.0f, 0.0f };
static float newCamPos[] = { 0.0f, 0.0f, -45.0f };
static float newCamRot[] = { 0.0f, 0.0f, 0.0f };

static bool g_showGrid = true;
static bool g_showAxes = true;

struct particule {
	float mass;
	float posx;
	float posy;
	float posz;
	float velx;
	float vely;
	float velz;
} particule;


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

void ShowParticles(struct particule * particules){

	int i = 0;
	

	for (i=0; i<Nb_Samples;i++){
		if ((i>=0 && i<(16384/80)) || (i>=(32768/80) && i<(40960/80)) || (i>=(49152/80) && (i<65536/80))) {		// Milkyway
			glBegin( GL_POINTS );
			glColor3f( 1.0f, 1.0f, 0.0f );
			glVertex3f(particules[i].posx, particules[i].posy, particules[i].posz);	
			glEnd(); 
			}
		else if ((i>=(16384/80) && i<(32768/80)) || (i>=(40690/80) && i< (49152/80)) ||(i>=(65536/80) && i< (81920/80)))  { 	// Andromeda
			glBegin( GL_POINTS );
			glColor3f( 1.0f, 0.0f, 0.0f );
			glVertex3f(particules[i].posx, particules[i].posy, particules[i].posz);	
			glEnd();
		}
	}	
}

void Modeling (struct particule * SamplesParticules){


int i,j,k =0;

	float accelx[Nb_Samples];
	float accely[Nb_Samples];
	float accelz[Nb_Samples];

#pragma omp parallel for

for (i = 0; i<Nb_Samples ;i++){
	
	accelx[i] = 0;
	accely[i] = 0;
	accelz[i] = 0;

	#pragma omp parallel for 

		for (j = 0; j<Nb_Samples ;j++){

		float deltax = SamplesParticules[j].posx-SamplesParticules[i].posx;
		float deltay = SamplesParticules[j].posy-SamplesParticules[i].posy;
		float deltaz = SamplesParticules[j].posz-SamplesParticules[i].posz;
	
		float dist = sqrtf((deltax * deltax)+ (deltay * deltay) + (deltaz * deltaz));
		if ( dist < 1.0 ) dist = 1.0;
		float d3 = dist * dist * dist;


		float m = MassFactor * PartDampingFactor * (1/d3) * SamplesParticules[j].mass;

		accelx[i] += deltax * m;
		accely[i] += deltay * m;
		accelz[i] += deltaz * m;	

		}
}

	for (k=0;k<Nb_Samples;k++){
		SamplesParticules[k].velx += accelx[k];
		SamplesParticules[k].vely += accely[k];
		SamplesParticules[k].velz += accelz[k];

		SamplesParticules[k].posx += SamplesParticules[k].velx * TIME ;
		SamplesParticules[k].posy += SamplesParticules[k].vely * TIME ;
		SamplesParticules[k].posz += SamplesParticules[k].velz * TIME ;

	}

	ShowParticles(SamplesParticules);

}


int main( int argc, char ** argv ) {

struct particule particules[Nb_Particules];
struct particule SamplesParticules[Nb_Samples];

omp_set_num_threads( 4 );

	int i,count = 0;

	FILE *fd =  fopen("./bin/dubinski.tab","r"); 

	if (fd == NULL) printf("impossible d'ouvrir le fichier\n");
	else printf("Fichier ouvert\n");
	

	for (i = 0; i<Nb_Particules;i++){
	fscanf(fd, "%f %f %f %f %f %f %f",&particules[i].mass, &particules[i].posx, &particules[i].posy, &particules[i].posz, &particules[i].velx, &particules[i].vely, &particules[i].velz );

		if (i%80 == 0 ){
		SamplesParticules[count].posx = particules[i].posx;
		SamplesParticules[count].posy = particules[i].posy;
		SamplesParticules[count].posz = particules[i].posz;
		SamplesParticules[count].velx = particules[i].velx;
		SamplesParticules[count].vely = particules[i].vely;
		SamplesParticules[count].velz = particules[i].velz;
		SamplesParticules[count].mass = particules[i].mass;
		count=count+1;
		}	
	}

	fclose(fd);


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

		gettimeofday( &begin, NULL );

		// Simulation should be computed here

		Modeling(SamplesParticules);

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

