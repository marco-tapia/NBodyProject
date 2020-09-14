/*
Implementation for a serial N-Body Simulation using a brute force algorithm
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <omp.h>
#include <pthread.h>

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
    //printf("x_dist: %lf -- ", x_dist);
    double y_dist = a->ycoord-b->ycoord;
    //printf("y_dist: %lf -- ", y_dist);
    double distance = sqrt(x_dist*x_dist + y_dist*y_dist);
    //printf("distance: %lf -- ", distance);
    //SOFTENING used to avoid infinity
    //double grav = 0.0000000000667;
    //printf("G: %lf -- ", grav);
    //printf("G-:%.17g ", grav);
    double F = (a->mass*b->mass*G)/(distance*distance);// + SOFTENING*SOFTENING);
    //printf("F: %.17g -- ", F);
    a->xForce += F*x_dist/distance;
    a->yForce += F*y_dist/distance;
    //printf("a->XForce: %.17g -- ", a->xForce);
    //printf("a->YForce: %.17g -- ", a->yForce);

}

void resetForce(Body* b) {
  b->xForce = 0.0;
  b->yForce = 0.0;
}
//updates a single body's velocity and position with a passed in time step
void updateBody(Body* b,double timeStep) {
 b->xVel += timeStep * b->xForce / b->mass;
 b->yVel += timeStep * b->yForce / b->mass;
 b->xcoord += timeStep * b->xVel;
 b->ycoord += timeStep * b->yVel;
}
//need to add forces
void writeFile(Body* bodies, FILE *file, int arr_length){


    fwrite(bodies, sizeof(Body)*arr_length,1, file);    
 //   fprintf(file,"File writing\n");
   // printf("File write function is happening"); 
    //fopen to make file

    
}

int main(int argc,char *argv[]){
  //long n = strtol(argv[1],NULL,10);
 // pthread_t thread[1];
  FILE *file;
  file = fopen("output.bin","ab");
  long n = 10000;
  int timeStep=1;
  int time=2;

  //timer variables
  struct timespec start_time;
  struct timespec end_time;
  long msec;	
  //initialize the bodies
  Body* bodies = (Body*)malloc(sizeof(Body)*n);
  //set the srand
  srand(6);
  #pragma omp parallel for 
  for (int i = 0; i < n; i++) {
    double xc = (rand() % 6000) -3000 + (double)rand()/(double)(RAND_MAX); //Rand from -3000 to 3000
    double yc = (rand() % 6000) -3000 + (double)rand()/(double)(RAND_MAX); //Second rand add decimal points
    double m =  (rand() % 200) + 5;
    double xv = (rand() % 100) -50 + (double)rand()/(double)(RAND_MAX);
    double yv = (rand() % 100) -50 + (double)rand()/(double)(RAND_MAX);
    initBody(&bodies[i], xc, yc, m, xv, yv);
  }
clock_gettime(CLOCK_MONOTONIC,&start_time);
for (int i = 0; i<time; i++) {
  //printf("time %d \n", i); 
  //for (int i = 0; i < n; i++) {
  /*  printf("Body %d :\n", i);
    printf("XCoord: %.17g -- ", bodies[i].xcoord);
    printf("YCoord: %.17g -- ", bodies[i].ycoord);
    printf("Mass: %.17g -- ", bodies[i].mass);
    printf("XVel: %.17g -- ", bodies[i].xVel);
    printf("YVel: %.17g \n-- ", bodies[i].yVel);
    *///printf("XForce: %.17g -- ", bodies[i].xForce);
    //printf("YForce: %.17g -- \n", bodies[i].yForce); 
 //}

  #pragma omp parallel for collapse(2)
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (i!=j) {
	calcForce(&bodies[i], &bodies[j]);
      }
    }
  }
  #pragma omp parallel for
  for (int i=0; i<n; i++) {
    updateBody(&bodies[i], timeStep);
    
    

    
    //printf("XForce Before Reset: %.17g -- ", bodies[i].xForce);
    //printf("YForce: %.17g -- \n", bodies[i].yForce);
    resetForce(&bodies[i]);
    //printf("XForce After Reset: %.17g -- ", bodies[i].xForce);
    //printf("YForce: %.17g -- \n", bodies[i].yForce);
  }
  //time++;
//  printf("-------------------------------------------------------------------- \n");

//write file

  writeFile(bodies,file,n);
    
}
  clock_gettime(CLOCK_MONOTONIC,&end_time);
   msec = (end_time.tv_sec - start_time.tv_sec)*1000 + (end_time.tv_nsec - start_time.tv_nsec)/1000000;
  printf("Parallel Simulation with time_step %d completed in %dms",timeStep,msec);
  free(bodies);
//  FILE *read;
  //int c;
 // read = fopen("output.txt","r");
 // while(1){
   // c = fgetc(read);
   // if(feof(read)){
     // break;
  //  }
  //  printf("%c",c);
 // }
 // fclose(read);
  return 0;
}

