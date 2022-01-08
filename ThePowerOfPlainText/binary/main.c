#include <stdio.h>

typedef struct {
  char name[256];
  char phone[15];
} reg;

typedef struct {
  reg regs[256];
} book;

int main() {
  reg lucas = { "Lucas José da Silva", "19 1234-1234" };
  reg jose  = { "José Lucas da Silva", "19 1234-1234" };
  book address = { lucas, jose };
  FILE *fp = fopen("address.book", "w");

  fwrite(&address, sizeof(book), 1, fp);
}
