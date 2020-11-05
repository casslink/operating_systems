#include <stdio.h>
#include <string.h>

#define INPUT_FILE  "/Users/cassandralink/tmp/coursein/p1-in.txt"
#define OUTPUT_FILE "/Users/cassandralink/tmp/courseout/p1-out.txt"
#define LINE_LENGTH 80
#define DEBUG 1

void char_by_char(FILE *infile, FILE *outfile);
void line_by_line(FILE *infile, FILE *outfile);

int main(int argc, char **argv) {
  FILE *infile, *outfile;
  char mode_arg[80];
  int mode;
  
  //process input
  if(argc < 2) {
    printf("Please specify mode (0 or 1)\n");
    return 1;
  }
  
  //get mode
  strcpy(mode_arg, argv[1]);
  printf("mode: %s\n", mode_arg);
  if(strcmp(mode_arg, "0") == 0) {
    mode = 0;
  }
  else if(strcmp(mode_arg, "1") == 0) {
    mode = 1;
  }
  else {
    printf("Unrecognized mode, input must be 0 or 1\n");
    return 1;
  }

  infile = fopen(INPUT_FILE, "r");
  outfile = fopen(OUTPUT_FILE, "w");
  
  //turn off O/S buffering
  setvbuf(infile, NULL, _IONBF, 0);  
  setvbuf(outfile, NULL, _IONBF, 0);
  
  //start timer  
  //start_timing();

  if(mode == 0) {
    char_by_char(infile,outfile);
  }
  else {
    line_by_line(infile, outfile);
  }
  //end timer
  //stop_timing();

  fclose(infile);
  fclose(outfile);
  
  //report timings
  //printf("Program Time: %f\n", get_wall_clock_diff());
}

void char_by_char(FILE *infile, FILE *outfile) {
  char ch;

  if(DEBUG) {
    printf("Copying file character by character\n");
  }

  while((ch = getc(infile)) != EOF) {
    putc(ch, outfile);
  }
}

void line_by_line(FILE *infile, FILE *outfile) {
  char line[LINE_LENGTH];

  if(DEBUG) {
    printf("Copying file line by line\n");
  }

  while((fgets(line, LINE_LENGTH, infile)) != NULL) {
    fputs(line, outfile);
  }
}

