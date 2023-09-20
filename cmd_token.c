#include "header.h"
/**
 * cmd_token - tokenize the user inputs
 * @buf: buffer from getline
 * @argv: argument
 */
void cmd_token(char *buf, char *argv[])
{
	char *token;
	int argc = 0;

	token = strtok(buf, " \n");
	while (token)
	{
		argv[argc] = strdup(token);
		token = strtok(NULL, " \n");
		argc++;
	}
	argv[argc] = NULL;
}
