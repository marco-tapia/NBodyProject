/*
  Implementation for a serial N-Body Simulation using a brute force algorithm
*/

#include <stdio.h>

#include <math.h>
//gravitational constant
const double G = 6.67e-11;

typedef struct Body {
	double xcoord;
	double ycoord; 
	double mass;
	double xVel;
	double yVel;
	double xForce;
	double yForce;
}Body;


	        
void calcForce(Body* a, Body* b){
    double x_dist = a->xcoord-b->xcoord;
    double y_dist = a->ycoord-b->ycoord;
    double distance = sqrt(x_dist*x_dist + y_dist*y_dist);		    

    double F = (a->mass*b->mass*G)/(distance*distance);
    a->xForce += F*x_dist/distance;
    a->yForce += F*y_dist/distance;
}

void moveBody(double o) {
	
}
//need to add forces


int main(int argc,char *argv[]){
	
	double loc1[2] = {3.0,4.0};
	double loc2[2] = {10.0,0.0};
	//double dist = getDistance(loc1,loc2);
//	printf("%lf",dist);
//Need to initialize the bodies
//Add forces
//update velocities and positions

/*for (int i=0; i<bodies.length; i++) {
    for (int j=0; j<bodies.length; j++) {
      if (i!=j) {
        //universe[i] += calcForce(bodies[i], bodies[j]);
      }
    }
  }
 */ 

  return 0;
}


