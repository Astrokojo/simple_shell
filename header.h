#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void shell_prompt(void);
int get_input(char **buf);
void cmd_token(char *buf, char *argv[]);

#endif /* MAIN_H*/
