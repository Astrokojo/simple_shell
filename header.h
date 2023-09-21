#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 1024
#define BUF_FLUSH -1
#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define TO_LWRCASE 1
#define TO_UNSIGNED  2

#define GET_LINE 0
#define STRTOK_ 0

#define HISTORY_FILE ".simple_shell_history"
#define MAX_HISTORY 4096

extern char **environ;

/* Structs */
typedef struct list_str
{
	int i;
	char *str;
	struct list_str *next;
}list_t;
/**
 *struct shell_info - contains pseudo-argu to pass into the shell,.
 *@alias: the alias node
 *@arg: a string generated from getline containing arguements
 *@argc: the argument count
 *@argv: an array of strings generated from arg
 *@counter: the error count
 *@errors: the error code for exit()s
 *@env: linked_list copy of environ in the shell
 *@environ:  of environ from LL env
 *@env_changed: on if environ was changed
 *@fname: the program filename
 *@history: the history node
 *@path: a string path for the current command
 *@linecount_flag: if on count this line of input
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type `||, &&, ;`
 *@readfd:fd from which to read input
 *@histcount: the history line number count
 */
typedef struct shell_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int counter;
	int errors;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} shell_info_t;

typedef struct shell_cmd
{
	char *type;
	int (*func)(shell_info_t *);
} cmd_tab;

/* Standard Library Prototypes */
int _strcmp(char *, char *);
int _strlen(char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *str);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **_strtok(char *,char *);
void _puts(char *);
int _putchar(char );
int _puttchar(char);
int _putfd(char, int);
int _putsfd(char *, int);
int _erratoi(char *);
int _atoi(char *);
int _isalpha(int);
int print_d(int, int);
char *convert_number(long int, int, int);
void _putts(char *);

/* Memory-utility Prototypes */
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
int freeptr(void **ptr);
void free_str_arr(char **str_arr);

/* Shell Utility prototypes */
void remove_comments(char *);
char *_strstr(const char *,const char *);
int chk_delim(char, char *);
void print_error(shell_info_t *shell_info, char *errtype);

/* Shell Initialization and Cleanup Prototypes */
int shell_loop(shell_info_t *shell_info, char **av);
int interactive(shell_info_t *);
void clear_shell_info(shell_info_t *);
void set_shell_info(shell_info_t *, char **);
void free_shell_info(shell_info_t *, int);

/* Input and Parsing Prototypes */
ssize_t get_input(shell_info_t *);
int _getline(shell_info_t *, char **, size_t *);
void parse_cmd(shell_info_t *);
int is_chain(shell_info_t *, char *, size_t *);
void check_chain(shell_info_t *, char *, size_t *, size_t, size_t);

/* alias prototypes */
int _alias(shell_info_t *);
int set_alias(shell_info_t *shell_info, char *str);
int unset_alias(shell_info_t *shell_info, char *str);
int replace_alias(shell_info_t *shell_info);
int replace_vars(shell_info_t *);
int replace_string(char **, char *);

/* Execution and Builtin Prototypes */
int find_cmd(shell_info_t *);
void child_pid(shell_info_t *);
int prints_cmd(shell_info_t *, char *);
char *char_double(char *, int, int);
char *find_path(shell_info_t *, char *, char *);

/* Command Prototypes */
int _chdir(shell_info_t *shell_info);
int _help_(shell_info_t *shell_info);
int _exit_sh(shell_info_t *shell_info);

/* Env wrapper Prototypes */
char **get_environ(shell_info_t *shell_info);
int _setenv_struct (shell_info_t *shell_info);
int _unsetenv_struct (shell_info_t *shell_info);

/* Env prototypes */
int current_env(shell_info_t *shell_info);
char *_getenv(shell_info_t *, char *name);
int env_list(shell_info_t *);
int _unsetenv(shell_info_t *, char *);
int _setenv(shell_info_t *, char *, char *);

/* History Prototypes */
int shell_hist(shell_info_t *shell_info);
char *get_hist(shell_info_t *shell_info);
int write_hist(shell_info_t *shell_info);
int read_hist(shell_info_t *shell_info);
int compile_hist(shell_info_t *shell_info, char *buf, int linecount);
int update_hist(shell_info_t *shell_info);

/* Linked List_Node Prototypes */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
int del_at_index(list_t **, unsigned int);
list_t *node_starts_with(list_t *, char *, char);
ssize_t at_index(list_t *, list_t *);

/* Link List Prototypes */
void free_list(list_t **);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
size_t print_list_str(const list_t *);

/* Signal Handling Prototypes */
void sigintHandler(int);

 #endif /*HELL_H */

