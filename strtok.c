#include "header.h"

int main(void)
{
	char *src = "Hello baby";
	char *str = malloc(sizeof(char) * strlen(src));
	char *delim = " ";
	char *token;
	strcpy(str, src);

	token = strtok(str, delim);
	
	while(token)
	{
		printf("%s\n", token);
		token = strtok(NULL, delim);
	}

	return 0;	
}
