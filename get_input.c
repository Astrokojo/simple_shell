int get_input(char **buf)
{
	size_t n = 0;
	int read_input;

	read_input = getline(buffer, &n, stdin);

	if (read_input == -1)
	{
		perror("getline");
		exit(1);
	}

	if (read_input > 0 && (*buffer)[read_input -1] == '\n')
		(*buffer)[read_input -1] = '\0';

	return (read_lines == -1) ? -1 : 0;
}
