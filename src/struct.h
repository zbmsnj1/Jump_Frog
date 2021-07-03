#ifndef struct_h
#define struct_h



typedef struct {                                 //m = magnitude  from 0 to 0.25
	float m, theta,                              //jump theta from 0 to 180
		mMin, mMax,
		thetaMin, thetaMax,
		mVar, thetaVar;                          //variable of m = 0.01, variable of theta = 5 (different arrow keys press)
} initVel;

typedef struct {
	bool isHighGround;
	bool isLowGround;
	bool isRiverBottom;
	
} groundType;

typedef struct {
	bool onLogs1;
	bool onLogs2;
	bool onLogs3;
	bool onLogs4;
	bool onLogs5;
} logType;

typedef struct { float x0, x1, x2, x3, x4, x5, y1, y2, y3; } groundXY;

typedef struct { float x, y; } vec2f;

typedef struct { vec2f log1, log2, log3, log4, log5; } logPos;

typedef struct { vec2f  v0, r, v, rNow; } state;            //v0 is initial v,  r is position , v is speed, rNow is a record of r when frog static(not move)

typedef struct {
	bool wireframeOn;
	bool runAnimation;
	bool frogDie;
	bool onLogs;							      //check frog on logs or not
	bool isIntersect;							//check if any collisions happen
	bool go;                                     //check frog moves or not, controled by SPACE key
	bool rightSide;                               //check the direction of the frog
	float startTime;
	bool OSD;
	int frames;
	float frameRate;
	float frameRateInterval;
	float lastFrameRateT;
	float frog_theta;                             //a global variable to control frog's(ellipse) jump theta
	float waveTesselation;
} global_t;

/* Use a low gravity value, rather than true Earth gravity of 9.8,
* to slow down projectile acceleration, otherwise too fast for
* nice projectile motion aesthetics.
*/

const float g = -0.25;
const int milli = 1000;




initVel jumpVector = { 0.25, 60.0,                                    
0.0, 0.25,
0.0, 180.0,
0.01, 1.0 };

state projectile = {

	{ 0.25, 0.25 },
{ -1.0, 0.0 },
{ 0.0, 0.0 },
{ -1.0, 0.0 }
};

logPos logs = {
	{ 0.075, 0.03 },
{ 0.225, 0.03 },
{ 0.375, 0.03 },
{ 0.525, 0.03 },
{ 0.675, 0.03 }
};

global_t global = { false,  true, false, false, false, false, true,  0.0,  true, 0, 0.0, 0.2, 0.0, 60.0, 64 };

logType logNum ={ false, false, false, false, false };                                 //use to check which log is intersected

groundType ground = { false, false, false };										//use to check which area of ground is intersected

groundXY gd = { -1.0, -0.75, -0.25, 0.0, 0.75, 1.0, 0.03, -0.1, 0.0 };

#endif