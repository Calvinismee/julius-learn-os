#include <stdlib.h>
#include <stdio.h>

int main() {
  char command[50];
  int month, year;
  printf("Month: ");
  scanf("%d", &month);
  printf("Year: ");
  scanf("%d", &year);

  sprintf(command, "cal %d %d", month, year);
  system(command);
  return 0;
}
