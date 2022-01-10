#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
  printf("Use: main [ g | s ]\n");
}

typedef struct {
  char name[256];
  char phone[20];
} record;

void generate() {
  FILE *fp = fopen("address.book", "w");
  record lucas = {"Lucas José da Silva", "11 1234-1234"};
  record jose = {"José Lucas da Silva", "11 1234-1234"};

  fwrite(&lucas, sizeof(record), 1, fp);
  fwrite(&jose, sizeof(record), 1, fp);
}

void show() {
  FILE *fp = fopen("address.book", "r");

  record rec;
  while(fread(&rec, sizeof(record), 1, fp)) {
    printf("%s: %s\n",  rec.name, rec.phone);
  }
}

int main(int argc, char **argv) {
  if(argc <= 1) { help(); exit(1); }

  switch(argv[1][0]) {
  case 'g': generate(); break;
  case 's': show(); break;
  }
}
