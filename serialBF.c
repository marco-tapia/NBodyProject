/*
  Implementation for a serial N-Body Simulation using a brute force algorithm
*/

#include <stdio.h>

#include <math.h>

typedef struct Body {
	double location[2]; 
	double mass;
	double velocity[2];
	double force[2];
}Body;


double getDistance(double loc1[2], double loc2[2]){
	double x_dist =pow(loc1[0]-loc2[0],2);
	double y_dist = pow(loc1[1]-loc2[1],2);
	return sqrt(x_dist+y_dist);
}
	        

int main(int argc,char *argv[]){
	double loc1[2] = {3.0,4.0};
	double loc2[2] = {10.0,0.0};
	double dist = getDistance(loc1,loc2);
	printf("%lf",dist);
}


