/* O/S Project 2 

 A multi-threaded Producer/Consumer program using a circular buffer
 with semaphores.

 compile with -lpthread

 gcc -o proj2 proj2.c -lpthread && ./proj2

 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "time_functions_19.h"
#include "setpath_defs.h"

#define BUFFER_LENGTH 10
#define LINE_LENGTH 1024
#define END -1

//#define in_path "/home/student/tmp/coursein/p1-in.txt"
//#define in_path "/home/student/tmp/courseout/p1-out.txt"

#define DEBUG 0

char buffer[BUFFER_LENGTH][LINE_LENGTH];
int in, out;
sem_t full, empty,lock; //Added lock

FILE* infile, * outfile;

void *producer(void *args);
void *consumer(void *args);


int main() {

  setpath311('1');
  double wall_clock, nano_diff; 
  
  in = out = 0;
  sem_init(&full, 0, BUFFER_LENGTH);
  sem_init(&lock,0,1); //Added
  sem_init(&empty, 0, 0);
  
  start_timing();

  // start processing:
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, producer, NULL);
  pthread_create(&tid2, NULL, consumer, NULL);
  
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  stop_timing();

  // shutdown
  sem_destroy(&full);
  sem_destroy(&empty);
  
 

  // report timings
  wall_clock = get_wall_clock_diff();
  printf("Wall Clock: %f\n", wall_clock);
  nano_diff = get_nanodiff();
  printf("Nano Difference: %f\n", nano_diff);
}

void *producer(void *args) {
  char line[LINE_LENGTH+1];
  int i = 0;

  //setpath311('1');
  printf("producer start - Reading from %s\n", in_path);
  infile = fopen(in_path, "r"); 
  while (fread(line, LINE_LENGTH, 1, infile) == 1) {
    
    sem_wait(&empty);
    sem_wait(&lock);

    if (DEBUG) {
      printf("producer line no: %i, buffer index %i: ", ++i, in);
    }

    strncpy(buffer[in++], line, LINE_LENGTH);
    if (in == BUFFER_LENGTH) {
      in = 0;
    }
    
    if (DEBUG) {
      // display 20 chars
      line[20] = '\0';
      puts(line);
    }
    sem_post(&lock);
    sem_post(&full);
  }

  // indicate end of transfer
  buffer[in][0] = END;
  fclose(infile);
  printf("producer end\n");
}

void *consumer(void *args) {
  char line[LINE_LENGTH+1];
  int i = 0;

  //setpath311('1');
  printf("consumer start - writing to %s\n", out_path);
  outfile = fopen(out_path, "w"); 
  while (buffer[out][0] != END) {
    
    sem_wait(&full);
    sem_wait(&lock);

    if (DEBUG) {
      printf("consumer line no: %i, buffer index %i: ", ++i, out);
    }
    
    strncpy(line, buffer[out++], LINE_LENGTH);
    if (out == BUFFER_LENGTH) {
      out = 0;
    }
    fwrite(line, LINE_LENGTH, 1, outfile);

    if (DEBUG) {
      // display 20 chars
      line[20] = '\0';
      puts(line);
    }
      
    sem_post(&lock);
    sem_post(&empty);
  }
  fclose(outfile);
  printf("consumer end\n");
}


//#include "no-setpath_fn.h"
// #include "turbine_setpath_fn.h"

