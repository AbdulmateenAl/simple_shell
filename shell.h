#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt setter*/
extern char **environ;
/* Global shell name */
char *name;
/* shell history counter */
int hist;
/**
 * struct list_l - A struct type that defines list.
 * @dir: path to a directory .
 * @next: pointer to another struct list_l.
 */
typedef struct list_l
{
char *dir;
struct list_l *next;
} list_t;

/**
 * struct builtin_f - struct type that defines builtin commands.
 * @name: The name of the builtin command.
 * @f: pointer to the builtin command's function.
 */
typedef struct builtin_f
{
char *name;
int (*f)(char **argv, char **front);
} inbuilt_t;

/**
 * struct alias_s - struct defining aliases.
 * @name: The alias.
 * @value: value of alias.
 * @next: pointer to another struct alias_s.
 */
typedef struct alias_s
{
char *name;
char *value;
struct alias_s *next;
} alias_t;

/* aliases list list */
alias_t *aliases;

/* utility protos */
ssize_t get_line(char **line_ptr, size_t *n, FILE *stream);
void *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **str_tok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *to_string(int num);

/* Input Helpers protos */
void handle_line(char **line, ssize_t read);
void rep_var(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);

/* String functions protos */
int str_len(const char *s);
char *str_cat(char *dest, const char *src);
char *str_cat_n(char *dest, const char *src, size_t n);
char *str_cpy(char *dest, const char *src);
char *str_chr(char *s, char c);
int str_spn(char *s, char *accept);
int str_cmp(char *s1, char *s2);
int str_cmp_n(const char *s1, const char *s2, size_t n);

/* Builtins protos */
int (*get_builtin(char *command))(char **args, char **front);
int system_exit(char **args, char **front);
int system_env(char **args, char __attribute__((__unused__)) **front);
int system_setenv(char **args, char __attribute__((__unused__)) **front);
int system_unsetenv(char **args, char __attribute__((__unused__)) **front);
int system_cd(char **args, char __attribute__((__unused__)) **front);
int system_alias(char **args, char __attribute__((__unused__)) **front);
int system_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers protos */
char **copy_env(void);
void free_env(void);
char **get_env(const char *var);

/* Error Handling protos */
int define_error(char **args, int err);
char *env_error(char **args);
char *_error(char **args);
char *exit_error(char **args);
char *cd_error(char **args);
char *syntax_error(char **args);
char *denied_per_error(char **args);
char *not_found_error(char **args);

/* list protos */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);

int proc_file_commands(char *file_path, int *exe_ret);
#endif
