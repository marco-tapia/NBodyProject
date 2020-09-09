/*
Implementation for a serial N-Body Simulation using a brute force algorithm
*/

#include <stdio.h>
#include <stdlib.h>
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

void initBody(Body* b, double xc, double yc, double m, double xv, double yv) {
  b->xcoord = xc;
  b->ycoord = yc;
  b->mass = m;
  b->xVel = xv;
  b->yVel = yv;
}
///
void calcForce(Body* a, Body* b) {
    double SOFTENING = 3e4;


    double x_dist = a->xcoord-b->xcoord;
    double y_dist = a->ycoord-b->ycoord;
    double distance = sqrt(x_dist*x_dist + y_dist*y_dist);
    //SOFTENING used to avoid infinity
    double F = (a->mass*b->mass*G)/(distance*distance + SOFTENING*SOFTENING);
    a->xForce += F*x_dist/distance;
    a->yForce += F*y_dist/distance;


}

void resetForce(Body* b) {
  b->xForce = 0;
  b->yForce = 0;
}
//updates a single body's velocity and position with a passed in time step
void updateBody(Body* b,double timeStep) {
 b->xVel += timeStep * b->xForce / b->mass;
 b->yVel += timeStep * b->yForce / b->mass;
 b->xcoord += timeStep * b->xVel;
 b->ycoord += timeStep * b->yVel;
}
//need to add forces


int main(int argc,char *argv[]){
  //long n = strtol(argv[1],NULL,10);
  int n = 10;
  int timeStep=1;
  //Need to initialize the bodies
  //Body* bodies[10];
  Body* bodies = (Body*)malloc(sizeof(Body)*n);
  //Body* nextStage[10];
  for (int i = 0; i < n; i++) {
    //set to srand so numbers change everytime
    double xc = (rand() % 400) -200; //Rand from -200 to 200
    double yc = (rand() % 400) -200;
    double m =  (rand() % 100);
    double xv = (rand() % 100) -50;
    double yv = (rand() % 100) -50;


    initBody(&bodies[i], xc, yc, m, xv, yv);
/*    initBody(nextStage[i], xc, yc, m, xv, yv);
 */ }
  //Add forces
  //update velocities and positions

  for (int i = 0; i < n; i++) {
    printf("Body %d :\n", i);
    printf("XCoord: %lf -- ", bodies[i].xcoord);
    printf("YCoord: %lf -- ", bodies[i].ycoord);
    printf("Mass: %lf -- ", bodies[i].mass);
    printf("XVel: %lf -- ", bodies[i].xVel);
    printf("YVel: %lf -- \n", bodies[i].yVel);


  }

  // for (int i=0; i<bodies.length; i++) {
  //     for (int j=0; j<bodies.length; j++) {
  //       if (i!=j & j>i) {
  //         nextStage[i] =
  //         calcForce(bodies[i], bodies[j]);
  //       }
  //     }
  //   }


  return 0;
}

