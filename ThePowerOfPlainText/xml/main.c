#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void help() {
  printf("Use: main [ g | s ]\n");
}

typedef struct {
  char name[256];
  char phone[20];
} record;

void record_print(FILE *fp, char* name, char* phone) {
  fprintf(fp, "<record>\n");
  fprintf(fp, "\t<name> %s <\\name>\n", name);
  fprintf(fp, "\t<phone> %s <\\phone>\n", phone);
  fprintf(fp, "<\\record>\n");  
}

void record_show(char* name, char* phone, char* directions) {
  printf("%s %s %s\n", name, phone, directions);
}

void generate() {
  FILE *fp = fopen("address.book", "w");
  record lucas = {"Lucas José da Silva", "11 1234-1234"};
  record jose = {"José Lucas da Silva", "11 1234-1234"};

  fprintf(fp, "<?xml version=\"1.0\" enconding=\"UTF-8\"?>\n");
  fprintf(fp, "<address-book>\n");
  record_print(fp, lucas.name, lucas.phone);
  record_print(fp, jose.name, jose.phone);
  fprintf(fp, "<\\address-book>\n");
}

char *get_value(FILE *fp) {
  char *buffer = malloc(256);
  char c;
  
  while(getc(fp) != '>');

  int i = 0;
  while((c = getc(fp)) != '<') {
      buffer[i] = c;
      ++i;
  }
  return buffer;
}

void show() {
  FILE *fp = fopen("address.book", "r");
  char *name;
  char *phone;
  char *direction; 
  char c;

  while((c = getc(fp)) != EOF) {
    if(c == '<') {
      c = getc(fp);

      switch(c) {
      case 'n': name = get_value(fp); break;
      case 'p': phone = get_value(fp); break;
      case 'd': direction = get_value(fp); break;
      }
    }

    if(c == '\\' && getc(fp) == 'r') record_show(name, phone, direction);
  }
}

int main(int argc, char **argv) {
  if(argc <= 1) { help(); exit(1); }

  switch(argv[1][0]) {
  case 'g': generate(); break;
  case 's': show(); break;
  }
}
