 
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h> 
#include <sstream>
#include <iostream>

#pragma comment(lib, "glew32.lib")
 
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
 
LARGE_INTEGER frequency;        // ticks per second
LARGE_INTEGER t1, t2;           // ticks
double frameTimeQP=0;
float frameTime=0 ;

float startTime=0, currentTime=0, fps=0;
int totalFrames=0; 
  
void InitGL() {

	//timing related stuff
	startTime = (float)glutGet(GLUT_ELAPSED_TIME);
	currentTime = startTime;

	// get ticks per second
	QueryPerformanceFrequency(&frequency);

	//disable vsync so that the frame rate are not stuck at 60 Hz
	wglSwapIntervalEXT(0); 	  

	//set the clear color to red
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}

void OnReshape(int new_width, int new_height) {
	glViewport(0, 0, new_width, new_height); 
}
 
void OnRender() { 
	//use glut to get the elapsed time
	float newTime = (float) glutGet(GLUT_ELAPSED_TIME);
	frameTime = newTime-currentTime;
	currentTime = newTime;
	 
	//Using high res. counter to get elapsed time in msecs
	QueryPerformanceCounter(&t2);	
	frameTimeQP = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	t1=t2;
	 
	//calculate FPS
	++totalFrames;
	if((newTime-startTime)>1000)
	{
		float elapsedTime = (newTime-startTime);
		fps = (totalFrames/ elapsedTime)*1000 ;
		startTime = newTime;
		totalFrames=0;

		//set the window title
		std::stringstream str;
		str<<"FPS: "<<fps<<", Frame time (GLUT): "<<frameTime<<" msecs, Frame time (QP): "<<frameTimeQP<<" msecs."<<std::endl;			
		glutSetWindowTitle(str.str().c_str());
	}

	//clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//swap back and front buffers
	glutSwapBuffers();
}

void OnShutdown() { 

}
 

void OnIdle() {
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	//initialize freeglut library
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA ); 
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); 
	glutCreateWindow("Getting started with Legacy OpenGL");

	//attach callbacks
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape); 
	glutCloseFunc(OnShutdown); 
	glutIdleFunc(OnIdle);
	
	//initialize glew library
	glewInit(); 

	//output OpenGL and GLSL version information
	std::cout<<"Using GLEW: "<<glewGetString(GLEW_VERSION)<<std::endl;
	std::cout<<"Hardware Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
	std::cout<<"OpenGL Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
	std::cout<<"OpenGL  Version: "<<glGetString (GL_VERSION)<<std::endl;
	std::cout<<"  GLSL  Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;
		 
	//setup initial OpenGL states
	InitGL();
	
	//run main loop
	glutMainLoop();

	return EXIT_SUCCESS;
}
