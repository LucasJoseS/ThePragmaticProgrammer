#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BOOK_SIZE 256
#define DIRECT_SIZE 256

typedef enum {
  Node = 0,
  Up = 1,
  Right = 2,
  Down = 3,
  Left = 4,
} direction;

typedef struct {
  char name[256];
  char phone[15];
  direction direct[256];
} reg;

typedef struct {
  reg regs[BOOK_SIZE];
} book;

int main() {
  FILE *fp = fopen("address.book", "w");
  reg lucas = { "Lucas José da Silva", "19 1234-1234", {Right, Left, Up, Down}};
  reg jose  = { "José Lucas da Silva", "19 1234-1234", {Left, Right, Down, Up}};
  book address = { lucas, jose };

  fwrite(&address, sizeof(book), 1, fp);

  fp = fopen("address.book", "r");
  fread(&address, sizeof(book), 1, fp);

  for(int index = 0; index < BOOK_SIZE; ++index) {
    bool newline = false;
    
    if(strcmp(address.regs[index].name, "")) {
      printf("%s, %s", address.regs[index].name, address.regs[index].phone);
      newline = true;
    }

    for(int i = 0; i < DIRECT_SIZE; ++i) {
      switch(address.regs[index].direct[i]) {
      case Up: printf(" Up"); break;
      case Right: printf(" Right"); break;
      case Down: printf(" Down"); break;
      case Left: printf(" Left"); break;
      default: printf(""); break;
      };
    }

    if(newline)
      printf("\n");
  }
}
