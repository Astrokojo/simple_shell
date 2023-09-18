#include "header.h"

int main() 
{
    pid_t pid = getpid();
  
    printf("Parent PID: %d\n", pid);
  
    return 0;
}
