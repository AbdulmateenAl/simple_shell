#ifndef MAIN_H
#define MAIN_H

#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

extern char **environ;

/**
 * string.c - function in the file name
 * strtok_char - function returning a string token
 * @str: string in question
 * Return: a character
 */
char **strtok_char(char *str);
int str_cmp(char *str1, char *str2);
char *str_cat(const char *src, char *dest);
/**
 * exec.c - function in the file
 * @ar_str: pointer to array
 * @envp: environment variable
 * Return: integer character or void
 */
void fork_exe(char **ar_str, char *envp[]);
char *file_check(char *str);
int path_check(char *str);
int check_builtin(char *str);

#endif
