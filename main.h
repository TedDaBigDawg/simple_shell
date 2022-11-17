#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct data - struct containing all the relevant data
 *
 * @av: arguments
 * @input: input from user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: line counter
 * @_environ: environment variable
 * @pid: process ID
 */

typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - singly linked list
 *
 * @separator: ; | &
 * @next: next node in the linked list
 */

typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - singly linked list
 *
 * @line: command line
 * @next: next node in the linked list
 */

typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - singly linked list
 *
 * @len_var: length of variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node in linked list
 */

typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - built in struct for comman arguments
 *
 * @name: name of command built in
 * @f: data type of pointer
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* aux_lists.c func */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2.c func */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* aux_str func */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c func */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c func */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3.c func */
void rev_string(char *s);

/* check_syntax_error.c func */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *datash, char *input, int i, int bool);
int check_syntax_error(data_shell *datash, char *input);

/* shell_loop.c func  */
char *without_comment(char *in);
void shell_loop(data_shell *datash);

/* read_line.c func */
char *read_line(int *i_eof);

/* split.c func */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);

/* rep_var.c func */
void check_env(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *datash);

/* get_line.c func */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line func */
int exec_line(data_shell *datash);

/* cmd_exec.c func */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);
int cmd_exec(data_shell *datash);

/* env1.c func */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);

/* env2.c func */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);

/* cd.c func */
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);
void cd_previous(data_shell *datash);
void cd_to_home(data_shell *datash);

/* cd_shell.c func */
int cd_shell(data_shell *datash);

/* get_builtin */
int (*get_builtin(char *cmd))(data_shell *datash);

/* _exit.c func */
int exit_shell(data_shell *datash);

/* aux_stdlib.c func */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1.c func */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *datash);
char *error_not_found(data_shell *datash);
char *error_exit_shell(data_shell *datash);

/* aux_error2.c func */
char *error_get_alias(char **args);
char *error_env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_shell *datash);

/* get_error.c func */
int get_error(data_shell *datash, int eval);

/* get_sigint.c func */
void get_sigint(int sig);

/* aux_help.c func */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c func */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c func */
int get_help(data_shell *datash);

#endif