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
#include <string.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* This is the environmental variable called manually */
extern char **environ;

/**
 * struct data - struct containing data to be provided during runtime
 * @av: argument vector
 * @input: input string by user
 * @args: tokens used in the command line
 * @status: status of the shell at that point
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
 * struct sep_list_s - single linked list
 * @separator: they are: | &
 * @next: pointer to the next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line arguments
 * @next: pointer to the next node
 *
 * Description: single linked list to store command lines arguments
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the varaible
 * @len_val: length of the value
 * @next: next node
 * Description: single linked lilst to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - builtin struct for command args
 * @name: name of command builtin
 * @f: pointer function
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(info_shell *datahsh);
} builtin_t;

/* the_shell_loop.c */
char *remove_comment(char *input_str);
void loop_shell(info_shell *datahsh);

/* check_error.c (syntax error) */
int check_error(info_shell *datahsh, char *input);
int repetition(char *input_str, int i);
int error_sep(char *input, int i, char last);
int char_first(char *input, int *i);
void print_error(info_shell *datahsh, char *input, int i, int bool);

/* read_line.c */
char *read_line(int *i);

/* replace_var.c */
void env_check(r_var **head, char *input, info_shell *data);
int var_check(r_var **head, char *input, char *st, info_shell *data);
char *replace_input(r_var **head, char *input, char *new_input, int nlen);
char *replace_var(char *input, info_shell *datahsh);

/* split_commands.c */
char *char_swap(char *input, int bool);
void add_nodes(sep_list **h_s, line_list **h_l, char *input);
void next_command(sep_list **l_s, line_list **l_l, info_shell *datahsh);
int split_commands(info_shell *datahsh, char *input);
char **split_line(char *input);

/* error1.c */
char *strcat_cd(info_shell *, char *, char *, char * );
char *error_get_cd(info_shell *datahsh);
char *error_not_found(info_shell *datahsh);
char *error_shell_exit(info_shell *datahsh);
/* error2.c */
char *error_get_alias(char **args);
char *error_env(info_shell *datahsh);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(info_shell *datahsh);

/* help.c */
void help_exit(void);
void help_general(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);

/* help2.c */
void _help(void);
void help_alias(void);
void help_cd(void);

/* list.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* list2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* stdlib.c */
int get_len(int num);
char *_itoa(int num);
int _atoi(char *str);

/* str_function.c */
char *_strcat(char *str1, const char *str2);
char *_strcpy(char *str1, char *str2);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* str_function2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* str_function3.c */
void rev_string(char *s);

/* cd_sommands.c */
void cd_dot(info_shell *datahsh);
void cd_to(info_shell *datahsh);
void cd_prev(info_shell *datahsh);
void cd_home(info_shell *datahsh);
/* cd_shell.c */
int cd_shell(info_shell *datahsh);

/* command_exec. c */
int in_currdir(char *path, int *i);
char *_which(char *command, char **_environ);
int is_exec(info_shell *datahsh);
int check_error_cmd(char *dir, info_shell *datahsh);
int cmd_exec(info_shell *datahsh);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(info_shell *datahsh);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, info_shell *datahsh);
int _setenv(info_shell *datahsh);
int _unsetenv(info_shell *datahsh);

/* exect_line.c */
int exect_line(info_shell *datahsh);

/* shell_exit.c */
int shell_exit(info_shell *datahsh);

/* get_builtin */
int (*get_builtin(char *cmd))(info_shell *datahsh);

/* getting_error.c */
int get_error(info_shell *datahsh, int eval);

/* help_get.c */
int get_help(info_shell *datahsh);

/* getting_error.c */
int get_error(info_shell *datahsh, int eval);

/* line_get.c */
void sets_line(char **linep, size_t *n, char *buff, size_t j);
ssize_t get_line(char **linep, size_t *n, FILE *stream);

/* handle_ctrl_c.c */
void get_sigint(int sig);

#endif
