#ifndef drawing_h
#define drawing_h

#include "struct.h"
#include "collision.h"

void drawRect(float length, float width)
{
	float l = length;
	float w = width;

	glBegin(GL_POLYGON);					 //use GL_POLYGON
	glVertex2f(0, 0);
	glVertex2f(l, 0);
	glVertex2f(l, w);
	glVertex2f(0, w);

	glEnd();
}

void drawCircle(float radius)
{
	int n = global.waveTesselation / 8;
	if (n < 4) {
		n = 4;
	}
	float theta;
	float x, y;
	float r = radius;

	glBegin(GL_TRIANGLE_FAN);                //use GL_TRIANGLE_FAN
	
	glVertex2f(0, 0);                       //draw middle of circle for easy use GL_TRIANGLE_FAN
	for (int i = 0; i <= n; i++) {
		theta = i / (float)n * 2.0 * M_PI;
		x = r * cosf(theta);
		y = r * sinf(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

void drawEllipse(float radiusA, float radiusB)
{
	int n = global.waveTesselation / 8;
	if (n < 4) {
		n = 4;
	}
	float theta;
	float x, y;
	float a = radiusA;
	float b = radiusB;

	glBegin(GL_TRIANGLE_FAN);                   //use GL_TRIANGLE_FAN
	glVertex2f(0, 0);
	for (int i = 0; i <= n; i++) {
		theta = i / (float)n * 2.0 * M_PI;

		x = a * cosf(theta);
		y = b * sinf(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

void drawWaves(float length, float width, float waves)
{
	float t;
	t = glutGet(GLUT_ELAPSED_TIME) / (float)milli;                                 //use t to let wave move

	const int n = global.waveTesselation;
	float x, y, y1;
	float L = length;
	float A = width;
	float k = 2 * M_PI / waves;

	y1 = -0.05;                               //-0.05 is the bottom of the river

	glBegin(GL_TRIANGLE_STRIP);               //use GL_TRIANGLE_STRIP
	
	for (int i = 0; i <= n; i++) {

		x = L / (float)n*i;
		y = A * sinf(k*x+ 0.5*t);
		logs.log1.y = A * sinf(k*logs.log1.x + 0.5*t) - 0.045;
		logs.log2.y = A * sinf(k*logs.log2.x + 0.5*t) - 0.045;
		logs.log3.y = A * sinf(k*logs.log3.x + 0.5*t) - 0.045;
		logs.log4.y = A * sinf(k*logs.log4.x + 0.5*t) - 0.045;
		logs.log5.y = A * sinf(k*logs.log5.x + 0.5*t) - 0.045;
		glVertex2f(x, y);
		glVertex2f(x, y1);                                 //draw x,y1 for easy use GL_TRIANGLE_STRIP	
	}

	glEnd();
}

void drawAxes(float length)
{
	float l = length;

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(l, 0);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex2f(0, 0);
	glVertex2f(0, l);
	glEnd();
}

void drawGround()
{
	glBegin(GL_LINE_STRIP);                          //use GL_LINE_STRIP
	glColor3f(1, 1, 1);
	glVertex2f(gd.x0, gd.y3);
	glVertex2f(gd.x1, gd.y3);
	glVertex2f(gd.x1, gd.y1);
	glVertex2f(gd.x2, gd.y1);
	glVertex2f(gd.x2, gd.y3);
	glVertex2f(gd.x3, gd.y3);
	glVertex2f(gd.x3, gd.y2);
	glVertex2f(gd.x4, gd.y2);
	glVertex2f(gd.x4, gd.y3);
	glVertex2f(gd.x5, gd.y3);
	glEnd();
}

void drawCars()                                      //draw cars from left to right
{
	glColor3f(1, 1, 0);
	glPushMatrix();                                  //car 1
	glTranslatef(-0.72, 0.03, 0.0);
	drawRect(0.07, 0.03);
	glPopMatrix();

	glPushMatrix();                                  //car 2
	glTranslatef(-0.6, 0.03, 0.0);
	drawRect(0.065, 0.065);
	glPopMatrix();

	glPushMatrix();                                  //car 3
	glTranslatef(-0.48, 0.03, 0.0);
	drawRect(0.1, 0.02);
	glPopMatrix();

	glPushMatrix();                                  //car 4
	glTranslatef(-0.33, 0.03, 0.0);
	drawRect(0.03, 0.06);
	glPopMatrix();
}

void drawLogs()                                      //draw logs from left to right
{
	glColor3f(1, 0, 0);
	glPushMatrix();                                  //log 1
	glTranslatef(logs.log1.x, logs.log1.y, 0.0);
	drawCircle(0.02);
	glPopMatrix();

	glPushMatrix();                                  //log 2
	glTranslatef(logs.log2.x, logs.log2.y, 0.0);
	drawCircle(0.02);
	glPopMatrix();

	glPushMatrix();                                  //log 3
	glTranslatef(logs.log3.x, logs.log3.y, 0.0);
	drawCircle(0.02);
	glPopMatrix();

	glPushMatrix();                                  //log 4
	glTranslatef(logs.log4.x, logs.log4.y, 0.0);
	drawCircle(0.02);
	glPopMatrix();

	glPushMatrix();                                  //log 5
	glTranslatef(logs.log5.x, logs.log5.y, 0.0);
	drawCircle(0.02);
	glPopMatrix();
}

void drawRiver()
{
	glColor3f(0, 1, 1);
	glPushMatrix();
	glTranslatef(0.0, -0.05, 0.0);
	drawWaves(0.75, 0.05, 0.5);
	glPopMatrix();
}



void drawFrog() {

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(projectile.r.x, projectile.r.y, 0.0);
	
	
	if (global.rightSide || !global.go) {                                 //draw frog if it face to right, use global.frog_theta
		glRotatef(global.frog_theta, 0.0, 0.0, 1.0);
	}
	else {
		glRotatef(-global.frog_theta, 0.0, 0.0, 1.0);                      //draw frog if it face to left, use -global.frog_theta
	}		
	drawEllipse(0.01, 0.02);
	glPopMatrix();

}

void drawDeadFrog() {
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	glTranslatef(projectile.rNow.x, projectile.rNow.y, 0.0);
	drawEllipse(0.01, 0.02);	
	glPopMatrix();
}

void draw_parabola(float r_x, float r_y) {
	if (r_x >= projectile.r.x && jumpVector.theta<90) {              // draw Parabola when frog move right side

		glVertex2f(r_x, r_y);
		global.rightSide = true;

		if (!global.go) {
			global.frog_theta = jumpVector.theta + 90.0;             //frog theta before frog move
		}
		else {
			global.frog_theta = asinf(projectile.v.y / jumpVector.m) * 180 / M_PI + 90.0;   //frog theta while frog moving
		}
	}
	if (r_x <= projectile.r.x && jumpVector.theta>90) {              // draw Parabola when frog move left side

		glVertex2f(r_x, r_y);
		global.rightSide = false;

		if (!global.go) {
			global.frog_theta = jumpVector.theta - 90.0;             //frog theta before frog move
		}
		else {
			global.frog_theta = asinf(projectile.v.y / jumpVector.m) * 180 / M_PI - 90.0;        //frog theta while frog moving
		}
	}
	if (r_y <= projectile.r.y && jumpVector.theta == 90) {             // draw Parabola when frog move straight up 

		glVertex2f(r_x, r_y);
	}
}


void drawParabola()
{
	
	
	//t = 0.08 * (v_y / 0.01);         // (v_y/(g*dt))/(1/2*t) = n/2           v_y/0.01=12.5*t       t=0.08*(v_y / 0.01)	
	const float t = 3.0;  //set a number large enough 
	const int n = 150;
	float r_x, r_y, v_x, v_y, dt;
	glBegin(GL_LINE_STRIP);

	r_x = projectile.rNow.x;
	r_y = projectile.rNow.y;
		
	v_x = jumpVector.m* cosf(jumpVector.theta / 180 * M_PI);
	v_y = jumpVector.m* sinf(jumpVector.theta / 180 * M_PI);

	dt = t / n;
	for (int i = 0; i <= n; i++)
	{
		r_x += v_x * dt;
		r_y += v_y * dt;
		
		v_y += g * dt;                   //v_y'-v_y = g * dt = 0.01		

		bool is_gd = parabolaIntersectGround(r_x, r_y + 0.02, gd.x1, gd.x2, gd.x3, gd.x4, gd.y1, gd.y2, gd.y3 );
		bool is_cars1 = parabolaIntersectCars(r_x, r_y + 0.02, -0.72, 0.03, -0.650, 0.060);
		bool is_cars2 = parabolaIntersectCars(r_x, r_y + 0.02, -0.60, 0.03, -0.535, 0.095);
		bool is_cars3 = parabolaIntersectCars(r_x, r_y + 0.02, -0.48, 0.03, -0.380, 0.050);
		bool is_cars4 = parabolaIntersectCars(r_x, r_y + 0.02, -0.33, 0.03, -0.300, 0.090);
		bool is_logs1 = parabolaIntersectLogs(r_x, r_y + 0.02, logs.log1.x, logs.log1.y, 0.0, 0.02);
		bool is_logs2 = parabolaIntersectLogs(r_x, r_y + 0.02, logs.log2.x, logs.log2.y, 0.0, 0.02);
		bool is_logs3 = parabolaIntersectLogs(r_x, r_y + 0.02, logs.log3.x, logs.log3.y, 0.0, 0.02);
		bool is_logs4 = parabolaIntersectLogs(r_x, r_y + 0.02, logs.log4.x, logs.log4.y, 0.0, 0.02);
		bool is_logs5 = parabolaIntersectLogs(r_x, r_y + 0.02, logs.log5.x, logs.log5.y, 0.0, 0.02);

		
		
		if (is_gd) {
			if (ground.isLowGround) {
				draw_parabola(r_x, r_y);
				ground.isLowGround = false;
			}
			if (ground.isHighGround) {
				
				if (is_cars1 || is_cars2 || is_cars3 || is_cars4) {                            //collision with cars, break for loop
					ground.isHighGround = false;
					break;
				}
				draw_parabola(r_x, r_y);
				ground.isHighGround = false;	
				
			}
			if (ground.isRiverBottom) {
				if (is_logs1 || is_logs2 || is_logs3 || is_logs4 || is_logs5) {               //collision with logs, break for loop
					ground.isRiverBottom = false;
					break;
				}
				
				draw_parabola(r_x, r_y);
				ground.isRiverBottom = false;
				
			}
		}
		
	}
	glEnd();

}

void drawVector() 
{
	float r_x, r_y, v_x, v_y;
	
	const int n = 50;

	glBegin(GL_LINES);


	r_x = projectile.r.x;                                               //vector's position = frog's position
	r_y = projectile.r.y;

	if (!global.go)
	{		
		v_x = jumpVector.m* cosf(jumpVector.theta / 180 * M_PI);          //vector before animation
		v_y = jumpVector.m* sinf(jumpVector.theta / 180 * M_PI);
	}
	else {
		v_x = projectile.v.x;                                            //vector while animation
		v_y = projectile.v.y;
	}
	

	glVertex2f(r_x, r_y);
	glVertex2f(r_x+0.5*v_x, r_y+0.5*v_y);                      //draw the vector line half length
	glEnd();

}

void drawFrogandParabola() {
	glPushMatrix();
	glTranslatef(0.0, 0.02, 0.0);                //move the frog and  parabola to correct position

	if (global.frogDie) {		                  //if frog die, not draw vector
		drawDeadFrog();
		
		
	}
	else {
		drawFrog();
		glColor3f(0.5, 0.0, 1.0);              //set blue color for parabola
		drawParabola();	
		glColor3f(1, 0, 1);                    //set purple color for vector
		drawVector();
	}
	
	glPopMatrix();
}


#endif 