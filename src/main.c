/*
* Interactive 3D Graphics and Animation Assignment 1: Frogger 2D (Frogger part 1)
* 
* Name: Yifan Wang 
* 
* ID: s3672150
* 
*
*/
#include <math.h>
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "drawing.h"
#include "struct.h"
#include "keyControl.h"
#include "display.h"
#include "update.h"
#include "collision.h"


void myinit(void)
{
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/*  Main Loop
*  Open window with initial window size, title bar,
*  RGBA display mode, and handle input events.
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(400, 0);
	glutInitWindowSize(750, 750);
	glutCreateWindow("Ass1/S3672150 Yifan Wang");
	glutSpecialFunc(keyboardSP);
	glutKeyboardFunc(keyboardCB);	
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(update);
	
	myinit();

	glutMainLoop();
}