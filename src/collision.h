#ifndef collision_h
#define collision_h

#include "struct.h"
#include <math.h>


bool intersectGround(float r_x, float r_y, float g_x1, float g_x2, float g_x3, float g_x4, float g_y1, float g_y2, float g_y3) {
	
		
		if (r_x > g_x1 && r_x < g_x2  ) {          //intersect at high ground
			if (r_y < g_y1) {
				global.go = false;
				ground.isHighGround = true;
				global.isIntersect = true;
				return true;
			}
			
		}
		else if (r_x > g_x3 && r_x < g_x4 ) {        //intersect at river bottom
			if ( r_y < g_y2) {			
				global.go = false;
				ground.isRiverBottom = true;
				global.isIntersect = true;
				return true;
			}
			
		}
		else if ( r_y < g_y3) {                                  //intersect at low ground
			
			global.go = false;
			ground.isLowGround = true;
			global.isIntersect = true;
			return true;
		}

		return false;
}

bool parabolaIntersectGround(float r_x, float r_y, float g_x1, float g_x2, float g_x3, float g_x4, float g_y1, float g_y2, float g_y3) {


	if (r_x > g_x1 && r_x < g_x2) {          //intersect at high ground
		if (r_y > g_y1) {
			ground.isHighGround = true;
			return true;
		}

	}
	else if (r_x > g_x3 && r_x < g_x4) {        //intersect at river bottom
		if (r_y > g_y2) {
			ground.isRiverBottom = true;
			return true;
		}

	}
	else if (r_y > g_y3) {                                  //intersect at low ground

		ground.isLowGround = true;
		return true;
	}

	return false;
}

bool intersectLogs(float r_x, float r_y, float x, float y, float r_f, float r) {            ////use circle collision
	if ( sqrt(pow(r_x - x, 2) + pow(r_y - y, 2)) < r_f + r) {
		global.go = false;
		global.isIntersect = true;		
		return true;
	}
	

	return false;
}

bool parabolaIntersectLogs(float r_x, float r_y, float x, float y, float r_f, float r) {
	if (sqrt(pow(r_x - x, 2) + pow(r_y - y, 2)) < r_f + r) {

		return true;
	}


	return false;
}

bool intersectCars(float r_x, float r_y, float x1, float y1, float x2, float y2) {            //use box collision
	if (r_x > x1 && r_x < x2 ) {
		if (r_y < y2 ) {
			global.go = false;
			global.isIntersect = true;
			return true;
		}		
	}

	return false;
}

bool parabolaIntersectCars(float r_x, float r_y, float x1, float y1, float x2, float y2) {
	if (r_x > x1 && r_x < x2) {
		if (r_y < y2) {
			
			return true;
		}

	}
	
	return false;
}

void resetFrogPos(float r_x, float r_y) {
	projectile.r.x = r_x;
	projectile.r.y = r_y;

}

#endif