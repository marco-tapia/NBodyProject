/*
  Implementation for a serial N-Body Simulation using a brute force algorithm
*/

#include <stdio.h>

#include <math.h>
//gravitational constant
const double G = 6.67e-11;

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
	        
double calcForce(Body a, Body b){
    double distance = getDistance(a.location, b.location);
    return (a.mass*b.mass*G)/(distance*distance);
}
//need to add forces


int main(int argc,char *argv[]){
	double loc1[2] = {3.0,4.0};
	double loc2[2] = {10.0,0.0};
	double dist = getDistance(loc1,loc2);
	printf("%lf",dist);
//Need to initialize the bodies
//Add forces
//update velocities and positions

for (int i=0; i<bodies.length; i++) {
    for (int j=0; j<bodies.length; j++) {
      if (i!=j) {
        universe[i] += calcForce(bodies[i], bodies[j]);
      }
    }
  }
  

  return EXIT_SUCCESS;
}


