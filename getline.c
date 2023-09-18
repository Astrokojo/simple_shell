#include "header.h"

int main(void)
{
	size_t n = 10;
	char *buffer = malloc(sizeof(char) * n);

  printf("Enter name");
  getline(&buffer, &n, stdin);

  printf("Name is:  %sBuffer size is %ld\n", buffer, n);
  
  free (buffer);
  
  return 0;
  
}
