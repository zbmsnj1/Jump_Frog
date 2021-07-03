
#ifndef keyControl_h
#define keyControl_h
#include"struct.h"

void frogRespawn() {
	global.frogDie = false;
	global.onLogs = false;
	global.isIntersect = false;
	global.go = false;
	global.rightSide = true;
	projectile.r.x = -1.0;
	projectile.r.y = 0.0;
	projectile.rNow.x = projectile.r.x;
	projectile.rNow.y = projectile.r.y;
	jumpVector.m = 0.25;
	jumpVector.theta = 60.0;
}

void keyboardCB(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	case 'g':
		global.runAnimation = !global.runAnimation;
		break;
	case 'o':
		global.OSD = !global.OSD;
		break;
	case 'f':
		global.wireframeOn = !global.wireframeOn;
		break;
	case 'r':
		if (!global.go) {
			frogRespawn();
		}		
		break;
	case ' ':
		if (!global.go && !global.frogDie) {
			global.startTime = glutGet(GLUT_ELAPSED_TIME) / (float)milli;
			
			global.onLogs = false;
			logNum.onLogs1 = false;
			logNum.onLogs2 = false;
			logNum.onLogs3 = false;
			logNum.onLogs4 = false;
			logNum.onLogs5 = false;
			global.go = true;
			projectile.v.x = jumpVector.m* cosf(jumpVector.theta / 180 * M_PI);
			projectile.v.y = jumpVector.m* sinf(jumpVector.theta / 180 * M_PI);


		}
		break;
	case'+':
	case'=':	
		global.waveTesselation *= 2 ;
		if (global.waveTesselation >= 128)
			global.waveTesselation = 128;
		printf("waveTesselation :%f\n", global.waveTesselation);
		break;
	case'-':
		global.waveTesselation /=  2;
		if (global.waveTesselation <= 2)
			global.waveTesselation = 2;
		printf("waveTesselation :%f\n", global.waveTesselation);
		break;
	default:
		break;
	}

		glutPostRedisplay();
	
}

void keyboardSP(unsigned char key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:

		if (!global.go && !global.frogDie) {
			jumpVector.theta += jumpVector.thetaVar;
			if (jumpVector.theta >= jumpVector.thetaMax)
				jumpVector.theta = jumpVector.thetaMax;
			    
			printf("theta :%f\n", jumpVector.theta);
		}
		break;
	case GLUT_KEY_RIGHT:
		if (!global.go && !global.frogDie) {
			jumpVector.theta -= jumpVector.thetaVar;
			if (jumpVector.theta <= jumpVector.thetaMin)
				jumpVector.theta = jumpVector.thetaMin;
			    
			printf("theta :%f\n", jumpVector.theta);
		}
		break;
	case GLUT_KEY_UP:
		if (!global.go && !global.frogDie) {
			jumpVector.m += jumpVector.mVar;
			if (jumpVector.m >= jumpVector.mMax)
				jumpVector.m = jumpVector.mMax;
			printf("m :%f\n", jumpVector.m);
		}
		break;
	case GLUT_KEY_DOWN:
		if (!global.go && !global.frogDie) {
			jumpVector.m -= jumpVector.mVar;
			if (jumpVector.m <= jumpVector.mMin)
				jumpVector.m = jumpVector.mMin;
			printf("m :%f\n", jumpVector.m);
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


#endif 
