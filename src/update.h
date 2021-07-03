#ifndef update_h
#define update_h

#include "struct.h"
#include "collision.h"

void updateProjectileStateNumerical(float dt)
{
	// Euler integration
	// Position
	
	projectile.r.x += projectile.v.x * dt;	
	projectile.r.y += projectile.v.y * dt;

	// Velocity
	projectile.v.y += g * dt;	
	
}

void updateresetFrogPosOnLogs() {
	
	projectile.r.y = logs.log1.y;
}


// Idle callback for animation
void update(void)
{
	static float lastT = -1.0;
	float t, dt;
	
	if (!global.go) {
		if (global.onLogs) {
			if (logNum.onLogs1) {
				projectile.r.y = logs.log1.y + 0.015;                 //+0.015 means give frog enough height to avoid collision with logs
			}
			if (logNum.onLogs2) {
				projectile.r.y = logs.log2.y + 0.015;
			}
			if (logNum.onLogs3) {
				projectile.r.y = logs.log3.y + 0.015;
			}
			if (logNum.onLogs4) {
				projectile.r.y = logs.log4.y + 0.015;
			}
			if (logNum.onLogs5) {
				projectile.r.y = logs.log5.y + 0.015;
			}

		}
		//projectile.rNow.x = projectile.r.x;              //r.x will not change cause the logs only move up and down
		projectile.rNow.y = projectile.r.y;
		return;
	}
		
	
	t = glutGet(GLUT_ELAPSED_TIME) / (float)milli - global.startTime;

	if (lastT < 0.0) {
		lastT = t;
		return;
	}

	dt = t - lastT;

	//check collision that is ground
	bool is_gd = intersectGround(projectile.r.x, projectile.r.y + 0.02, gd.x1, gd.x2, gd.x3, gd.x4, gd.y1, gd.y2, gd.y3 );   
	//check collision that is a car
	bool is_cars1 = intersectCars(projectile.r.x, projectile.r.y + 0.02, -0.72, 0.03, -0.650, 0.060);
	bool is_cars2 = intersectCars(projectile.r.x, projectile.r.y + 0.02, -0.60, 0.03, -0.535, 0.095);
	bool is_cars3 = intersectCars(projectile.r.x, projectile.r.y + 0.02, -0.48, 0.03, -0.380, 0.050);
	bool is_cars4 = intersectCars(projectile.r.x, projectile.r.y + 0.02, -0.33, 0.03, -0.300, 0.090);
	bool is_logs1 = intersectLogs(projectile.r.x, projectile.r.y + 0.02, logs.log1.x, logs.log1.y, 0.01, 0.02);
	bool is_logs2 = intersectLogs(projectile.r.x, projectile.r.y + 0.02, logs.log2.x, logs.log2.y, 0.01, 0.02);
	bool is_logs3 = intersectLogs(projectile.r.x, projectile.r.y + 0.02, logs.log3.x, logs.log3.y, 0.01, 0.02);
	bool is_logs4 = intersectLogs(projectile.r.x, projectile.r.y + 0.02, logs.log4.x, logs.log4.y, 0.01, 0.02);
	bool is_logs5 = intersectLogs(projectile.r.x, projectile.r.y + 0.02, logs.log5.x, logs.log5.y, 0.01, 0.02);
	
	if (global.isIntersect) {
		if (is_gd) {                                                            //stop frog and reset the frog's start position when cllision with ground
			if (ground.isLowGround) {											//low ground                                                        
				resetFrogPos(projectile.r.x, projectile.r.y + 0.021);						    //reset frog's start position
				ground.isLowGround = false;
				
			}
			if (ground.isHighGround) {											//high ground
				resetFrogPos(projectile.r.x, projectile.r.y + 0.021);
				ground.isHighGround = false;
			}
			if (ground.isRiverBottom) {											//river bottom
				resetFrogPos(projectile.r.x, projectile.r.y + 0.021);                  //if frog arrive bottom, block frog, frog die
				global.frogDie = true;
				ground.isRiverBottom = false;
				
			}

			projectile.rNow.x = projectile.r.x;
			projectile.rNow.y = projectile.r.y;
			projectile.v.x = 0.0;
			projectile.v.y = 0.0;
			lastT = -1.0;                              //reset the lastT
			
			global.isIntersect = false;
			return;
		}

		if (is_cars1 || is_cars2 || is_cars3 || is_cars4) {               //stop frog and reset the frog's start position when cllision with car
			resetFrogPos(projectile.r.x, projectile.r.y + 0.021);

			global.isIntersect = false;
			projectile.rNow.x = projectile.r.x;
			projectile.rNow.y = projectile.r.y;
			projectile.v.x = 0.0;
			projectile.v.y = 0.0;
			lastT = -1.0;                              //reset the lastT
			return;
			
		}
		if (is_logs1 || is_logs2 || is_logs3 || is_logs4 || is_logs5) {               //stop frog and reset the frog's start position when cllision with car
			if (is_logs1) {
				logNum.onLogs1 = true;
			}
			if (is_logs2) {
				logNum.onLogs2 = true;
			}
			if (is_logs3) {
				logNum.onLogs3 = true;
			}
			if (is_logs4) {
				logNum.onLogs4 = true;
			}
			if (is_logs5) {
				logNum.onLogs5 = true;
			}
			resetFrogPos(projectile.r.x, projectile.r.y + 0.021);            //the frog position will not be static, it will change by logs move up and down
			global.onLogs = true;
			global.isIntersect = false;
			projectile.rNow.x = projectile.r.x;
			//projectile.rNow.y = projectile.r.y;          //when frog on logs, rNow y will alywas change 
			projectile.v.x = 0.0;
			projectile.v.y = 0.0;
			lastT = -1.0;                              //reset the lastT
			return;
		}
	
		
	}
	else {
		
		updateProjectileStateNumerical(dt);            //if no collisions, the frog will not stop 
	}

	lastT = t;




	/* Frame rate */
	dt = t - global.lastFrameRateT;


	if (dt > global.frameRateInterval) {
		global.frameRate = global.frames / dt;
		global.lastFrameRateT = t;
		global.frames = 0;
	}

	if (global.runAnimation) {
		glutPostRedisplay();
	}
}

#endif