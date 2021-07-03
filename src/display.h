#ifndef display_h
#define display_h

#include "drawing.h"




void displayOSD()
{
	char buffer[30];
	char *bufp;
	int w, h;

	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	/* Set up orthographic coordinate system to match the
	window, i.e. (0,0)-(w,h) */
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	/* Frame rate */
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos2i(500, 700);
	snprintf(buffer, sizeof buffer, "fr (f/s): %6.0f", global.frameRate);
	for (bufp = buffer; *bufp; bufp++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);

	/* Time per frame */
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos2i(500, 680);
	snprintf(buffer, sizeof buffer, "ft (ms/f): %5.0f", 1.0 / global.frameRate * 1000.0);
	for (bufp = buffer; *bufp; bufp++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);

	/* Wave tesselation */
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos2i(500, 660);
	snprintf(buffer, sizeof buffer, "tess: %5.0f", global.waveTesselation);
	for (bufp = buffer; *bufp; bufp++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);

	/* Pop modelview */
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);

	/* Pop projection */
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	/* Pop attributes */
	glPopAttrib();
}



void display(void)
{
	GLenum err;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	// Display OSD
	if (global.OSD)
		displayOSD();
	glPopMatrix();
	if (!global.wireframeOn) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	
	drawAxes(1);
	drawGround();
	drawRiver();
	drawLogs();
	drawCars();
	drawFrogandParabola();

	glutSwapBuffers();

	global.frames++;
	
	// Check for errors
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("%s\n", gluErrorString(err));

	if (global.runAnimation) {
		glutPostRedisplay();
	}
	
}

#endif
