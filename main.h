#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
​
extern char **environ;
​
/**
 * string.c
 */
char **strtok_char(char *str);
int str_cmp(char *str1, char *str2);
char *str_cat(const char *src, char *dest);
void printEnvironment();
/**
 * exec.c
 */
void fork_exe(char **ar_str, char *envp[]);
char *file_check(char *str);
int path_check(char *str);
int check_builtin(char *str);

