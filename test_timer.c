#include <stdio.h>
#include <unistd.h>

#include "time_functions_19.h"

int main(void) {
  double n;

  // test timer
  start_timing();

  // Do work here 
  sleep(1);

  // Stop timer
  stop_timing();

  // Report
  n = get_wall_clock_diff();
  printf("wall_clock: %f\n", n);
  n = get_nanodiff();
  printf("nanodiff: %f\n", n);
}
