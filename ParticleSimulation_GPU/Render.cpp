#include "Render.h"

// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctime>

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif

#include "C:/ProgramData/NVIDIA Corporation/CUDA Samples/v8.0/common/inc/GL/freeglut.h"	

// includes, cuda
//#include <cuda_runtime.h>
//#include <cuda_gl_interop.h>
#include <ostream>
#include <iostream>

// Utilities and timing functions
//	#include <timer.h>               // timing functions

// CUDA helper functions

//#include <vector_types.h>
Render::Render()
{
}


Render::~Render()
{
}


const unsigned int mesh_width = 256;
const unsigned int mesh_height = 256;
const float M_PI = 3.14159265;


int g_iWindowWidth = 512;
int g_iWindowHeight = 512;
int g_iGLUTWindowHandle = 0;

int g_iErrorCode = 0;

float g_fRotate1 = 0.0f;
float g_fRotate2 = 0.0f;
float g_fRotate3 = 0.0f;

std::clock_t g_PreviousTicks;
std::clock_t g_CurrentTicks;

void drawParticle(float2_cus p1)
{
	glBegin(GL_POINTS);
	glVertex2f(p1.x, p1.y);
	glEnd();

}

void DrawRectangle(float width, float height)
{
	const float w = width / 2.0f;
	const float h = height / 2.0f;

	glBegin(GL_QUADS);
	glVertex2f(-w, h);   // Top-Left
	glVertex2f(w, h);   // Top-Right
	glVertex2f(w, -h);   // Bottom-Right
	glVertex2f(-w, -h);   // Bottom-Left
	glEnd();

}


void DrawCircle(float radius, int numSides /* = 8 */)
{
	const float step = M_PI / numSides;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for (float angle = 0.0f; angle < (2.0f * M_PI); angle += step)
	{
		glVertex2f(radius * sinf(angle), radius * cosf(angle));
	}
	glVertex2f(0.0f, radius); // One more vertex to close the circle
	glEnd();
}


void Cleanup(int errorCode, bool bExit)
{
	if (g_iGLUTWindowHandle != 0)
	{
		glutDestroyWindow(g_iGLUTWindowHandle);
		g_iGLUTWindowHandle = 0;
	}

	if (bExit)
	{
		exit(errorCode);
	}
}


void DisplayGL()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//load identity matrix

	glTranslatef(-1.5f, 1.0f, -6.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glPointSize(10.0f);
	glEnable(GL_POINT_SMOOTH);
	drawParticle(float2_cus(0.0, 0.0));

	glutSwapBuffers();
	glutPostRedisplay();
}

void IdleGL()
{
	// Update our simulation
	g_CurrentTicks = std::clock();
	float deltaTicks = (g_CurrentTicks - g_PreviousTicks);
	g_PreviousTicks = g_CurrentTicks;

	float fDeltaTime = deltaTicks / (float)CLOCKS_PER_SEC;

	// Rate of rotation in (degrees) per second
	const float fRotationRate = 50.0f;

	// Update our rotation parameters
	g_fRotate1 += (fRotationRate * fDeltaTime);
	g_fRotate1 = fmodf(g_fRotate1, 360.0f);

	g_fRotate2 += (fRotationRate * fDeltaTime);
	g_fRotate2 = fmodf(g_fRotate2, 360.0f);

	g_fRotate3 += (fRotationRate * fDeltaTime);
	g_fRotate3 = fmodf(g_fRotate3, 360.0f);

	glutPostRedisplay();
}

void KeyboardGL(unsigned char c, int x, int y)
{
	// Store the current scene so we can test if it has changed later.
	

	switch (c)
	{
	case 's':
	case 'S':
	{
		std::cout << "Shade Model: GL_SMOOTH" << std::endl;
		// Switch to smooth shading model
		glShadeModel(GL_SMOOTH);
	}
	break;
	case 'f':
	case 'F':
	{
		std::cout << "Shade Model: GL_FLAT" << std::endl;
		// Switch to flat shading model
		glShadeModel(GL_FLAT);
	}
	break;
	case 'r':
	case 'R':
	{
		std::cout << "Reset Parameters..." << std::endl;
		g_fRotate1 = g_fRotate2 = g_fRotate3 = 0.0f;
	}
	break;
	case '\033': // escape quits
	case '\015': // Enter quits
	case 'Q':    // Q quits
	case 'q':    // q (or escape) quits
	{
		// Cleanup up and quit
		Cleanup(0, false);
	}
	break;
	}


	glutPostRedisplay();
}

void MouseGL(int button, int state, int x, int y)
{

}

void MotionGL(int x, int y)
{

}

void ReshapeGL(int w, int h)
{
	std::cout << "ReshapGL( " << w << ", " << h << " );" << std::endl;

	if (h == 0)                                        // Prevent a divide-by-zero error
	{
		h = 1;                                      // Making Height Equal One
	}

	g_iWindowWidth = w;
	g_iWindowHeight = h;

	glViewport(0, 0, g_iWindowWidth, g_iWindowHeight);

	// Setup the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)g_iWindowWidth / (GLdouble)g_iWindowHeight, 0.1, 100.0);

	glutPostRedisplay();
}


void Render::InitGL(int argc, char* argv[])
{
	std::cout << "Initialise OpenGL..." << std::endl;

	glutInit(&argc, argv);
	int iScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int iScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition((iScreenWidth - g_iWindowWidth) / 2,
		(iScreenHeight - g_iWindowHeight) / 2);
	glutInitWindowSize(g_iWindowWidth, g_iWindowHeight);

	g_iGLUTWindowHandle = glutCreateWindow("OpenGL");

	// Register GLUT callbacks
	glutDisplayFunc(DisplayGL);
	glutIdleFunc(IdleGL);
	glutMouseFunc(MouseGL);
	glutMotionFunc(MotionGL);
	glutKeyboardFunc(KeyboardGL);
	glutReshapeFunc(ReshapeGL);

	// Setup initial GL State
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);

	glShadeModel(GL_SMOOTH);
	std::cout << "Initialise OpenGL: Success!" << std::endl;
}