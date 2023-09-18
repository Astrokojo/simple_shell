#include "header.h"

int main(void)
{
  pid_t pid;
  
  printf("Before fork I was one\n");

  pid = fork();

  if (pid == -1)
  {
    perror("Unsuccessful");
    return 1;
  }

  printf("After fork I became two\n");

  return 0;
}