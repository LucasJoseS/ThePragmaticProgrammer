#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Use: ./interpreter [filename]\n");
    exit(1);
  }

  FILE *fp = fopen(argv[1], "r");
  if(fp == NULL) {
    printf("File not found.\n");
    exit(1);
  }

  for(char c = fgetc(fp); c != EOF; c = fgetc(fp)) {
    switch(c) {
    case 'P':
      fgetc(fp);
      printf("Select pen %c\n", fgetc(fp));
      break;

    case 'D':
      printf("Putting down the pen\n");
      break;

    case 'W':
      fgetc(fp);
      printf("Going to the west %c units\n", fgetc(fp));
      break;

    case 'N':
      fgetc(fp);
      printf("Going to the north %c units\n", fgetc(fp));
      break;

    case 'E':
      fgetc(fp);
      printf("Going to the east %c units\n", fgetc(fp));
      break;

    case 'S':
      fgetc(fp);
      printf("Going to the south %c units\n", fgetc(fp));
      break;

    case 'U':
      printf("Putting up the pen\n");
      break;
    }
  }
}
