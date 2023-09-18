#include "header.h"

int main(void)
{
  pid_t pid;

  pid = fork();

  if (pid == -1)
  {
    perror("Failed");
    return 1;
  }

  if (pid == 0)
  {
    printf("Child process\n");
  }

  else
  {
    wait(NULL);
    sleep(5);
    printf("Parent process\n")  ;
  }

  return 0;
}