#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct data - contains all data needed
 * @av: argument vector
 * @input: command line
 * @args: tokens of the command line
 * @status: status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
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
} info_shell;

/**
 * struct sep_list_l - single linked list
 * @separator: ; | &
 * @next: pointer to the next list
 * Decription: single linked list to store separator
 */

typedef struct sep_list_l
{
	char separator;
	struct sep_list_l *next;
} sep_list;

/**
 * struct command_line_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct command_line_s
{
	char *line;
	struct command_line_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of variable
 * @val: value of variable
 * @len_val: length of value
 * @next: next node
 * Decription: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/* lists.c*/
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* str3.c */
void rev_string(char *s);

/* read_line.c */
char *read_line(int *i);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(info_shell *datahsh);

/* env2.c */
char *new_env(char *name, char *value);
void set_env(char *name, char *value, info_shell *datahsh);
int _setenv(info_shell *datahsh);
int _unsetenv(info_shell *datahsh);

/* stdlib.c */
int get_len(int n);
char *_itoa(int n);
int _atoi(char *s);

/**
 * struct builtin_c -  builtin struc for command arguments
 * @name: name of the builtin command i.e cd, env, exit
 * @f: pointer function
 */
typedef struct builtin_c
{
	char *name;
	int (*f)(info_shell *datahsh);
} builtin_t;

/* check_syntax_error */
int repetition(char *input, int i);
int repeatition(char *input, int i);
int error_sep(char *input, int i, char last_read);
int char_first(char *input, int *i);
void print_error(info_shell *datahsh, char *input, int i, int bool);
int check_error(info_shell *datahsh, char *input);


/* loop_shell */
char *without_comment(char *in);
void shell_loop(info_shell *datahsh);

/* spliting*/
char *char_swap(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void next_command(sep_list **list_s, line_list **list_l, info_shell *datahsh);
int splits_command(info_shell *datahsh, char *input);
char **splits_line(char *input);

/* rep_var.c */
void env_check(r_var **h, char *in, info_shell *data);
int var_check(r_var **h, char *in, char *st, info_shell *data);
char *replace_input(r_var **head, char *input, char *new_input, int nlen);
char *replace_var(char *input, info_shell *datahsh);

/* get_line.c */
void sets_line(char **linep, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **linep, size_t *n, FILE *stream);

/* exec_line */
int exect_line(info_shell *datahsh);

/* cmd_exec.c */
int in_currdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(info_shell *datahsh);
int check_access(char *dir, info_shell *datahsh);
int cmd_exec(info_shell *datahsh);

/* cd.c */
void cd_dot(info_shell *datahsh);
void cd_to(info_shell *datahsh);
void cd_prev(info_shell *datahsh);
void cd_home(info_shell *datahsh);

/* cd_shell.c */
int cd_shell(info_shell *datahsh);
/* get_builtin */
int (*get_builtin(char *cmd))(info_shell *datahsh);
/* _exit.c */
int shell_exit(info_shell *datahsh);

/* aux_stdlib.c*/
int get_len(int n);
char *_itoa(int n);
int _atoi(char *s);

/* error1.c */
char *strcat_cd(info_shell *, char *, char *, char *);
char *error_get_cd(info_shell *datahsh);
char *error_not_found(info_shell *datahsh);
char *error_shell_exit(info_shell *datahsh);

/* error2.c */
char *error_get_alias(char **args);
char *error_env(info_shell *datahsh);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(info_shell *datahsh);

/* get_error.c */
int get_error(info_shell *datahsh, int eval);
/*get_sigint,c */
void get_sigint(int sig);

/* help.c */
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_general(void);
void help_exit(void);

/* help2.c */
void _help(void);
void help_alias(void);
void help_cd(void);

/* get_help.c */
int get_help(info_shell *datahsh);
int cmpenvname(const char *n_env, const char *name);
/* set and free data */
void free_data(info_shell *datahs);
void set_data(info_shell *datahsh, char **av);
#endif
