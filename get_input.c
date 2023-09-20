#include "header.h"
int get_input(char **buf)
{
	size_t n = 0;
	ssize_t read_input;

	read_input = getline(buf, &n, stdin);

	if (read_input == -1)
	{
		perror("getline");
		exit(1);
	}

	if (read_input > 0 && (*buf)[read_input -1] == '\n')
		(*buf)[read_input -1] = '\0';

	return (read_input == -1) ? -1 : 0;
}
