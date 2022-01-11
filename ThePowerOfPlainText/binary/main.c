#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
  printf("Use: main [ g | s ]\n");
}

typedef enum {
  None = 0,
  North = 1,
  South = 2,
  West = 3,
  East = 4,
} direct;

typedef struct {
  char name[256];
  char phone[20];
} record_v1;

typedef struct {
  char name[256];
  char phone[20];
  direct direction[10];
} record_v2;

void generate() {
  FILE *fp = fopen("address.book", "w");
  record_v1 lucas = {"Lucas José da Silva", "11 1234-1234"};
  record_v1 jose = {"José Lucas da Silva", "11 1234-1234"};
  int version = 1;

  fwrite(&version, sizeof(int), 1, fp);
  fwrite(&lucas, sizeof(record_v1), 1, fp);
  fwrite(&jose, sizeof(record_v1), 1, fp);
}

void show() {
  FILE *fp = fopen("address.book", "r");

  int version;
  fread(&version, sizeof(int), 1, fp);
  printf("Version: %d\n", version);

  if(version == 1) {
    record_v1 rec;
    while(fread(&rec, sizeof(record_v1), 1, fp)) {
      printf("%s: %s\n",  rec.name, rec.phone);
    }
  }

  if(version == 2) {
    record_v2 rec;
   
    while(fread(&rec, sizeof(record_v2), 1, fp)) {
      printf("%s: %s ",  rec.name, rec.phone);

      for(int i = 0; i < 10; ++i) {
        if(rec.direction[i] != None) {
          switch(rec.direction[i]) {
          case North: printf("North "); break;
          case South: printf("South "); break;
          case East: printf("East "); break;
          case West: printf("West "); break;
          }
        }
      }

      printf("\n");
    }  
  }
}

void update() {
  FILE *fp = fopen("address.book", "r");
  record_v2 recs[2];
  direct sample_directions[10] = {North, West, South, East};

  int version;
  fread(&version, sizeof(int), 1, fp);

  int i = 0;
  if(version == 1) {
    record_v1 rec;
    while(fread(&rec, sizeof(record_v1), 1, fp)) {
      strcpy(recs[i].name, rec.name);
      strcpy(recs[i].phone, rec.phone);
      memcpy(recs[i].direction, sample_directions, sizeof(direct) * 10);
      ++i;
    }
  }

  fp = fopen("address.book", "w");

  version = 2;
  fwrite(&version, sizeof(int), 1, fp);
  fwrite(&recs, sizeof(record_v2), i, fp);
}

int main(int argc, char **argv) {
  if(argc <= 1) { help(); exit(1); }

  switch(argv[1][0]) {
  case 'g': generate(); break;
  case 's': show(); break;
  case 'u': update(); break;
  }
}
