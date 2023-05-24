#include "shell.h"
/**
 * system_env - Prints the current environment.
 * @args: arguments passed to the shell.
 * @front:  pointer to the beginning of args.
 * Return: If an error occurs -1. 0always
 */
int system_env(char **args, char __attribute__((__unused__)) **front)
{
int index;
char nc = '\n';

if (!environ)
return (-1);
for (index = 0; environ[index]; index++)
{
write(STDOUT_FILENO, environ[index], str_len(environ[index]));
write(STDOUT_FILENO, &nc, 1);
}
(void)args;
return (0);
}

/**
 * system_setenv - add or changes an environmental variable to the PATH.
 * @args: array of arguments to be passed to the shell.
 * @front: pointer to the beginning of args.
 * Return: If an error occurs -1.when successful 0.
 */
int system_setenv(char **args, char __attribute__((__unused__)) **front)
{
char **env_var = NULL, **new_environ, *new_value;
size_t size;
int index;

if (!args[0] || !args[1])
return (define_error(args, -1));

new_value = malloc(str_len(args[0]) + 1 + str_len(args[1]) + 1);
if (!new_value)
return (define_error(args, -1));
str_cpy(new_value, args[0]);
str_cat(new_value, "=");
str_cat(new_value, args[1]);

env_var = get_env(args[0]);
if (env_var)
{
free(*env_var);
*env_var = new_value;
return (0);
}
for (size = 0; environ[size]; size++)
;
new_environ = malloc(sizeof(char *) * (size + 2));
if (!new_environ)
{
free(new_value);
return (define_error(args, -1));
}
for (index = 0; environ[index]; index++)
new_environ[index] = environ[index];
free(environ);
environ = new_environ;
environ[index] = new_value;
environ[index + 1] = NULL;
return (0);
}

/**
 * system_unsetenv - removes an environmental variable from the PATH.
 * @args: arguments passed to the shell.
 * @front: pointer to the beginning of args.
 * Return: 0 always else -1
 */
int system_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
char **env_var, **new_environ;
size_t size;
int index, index2;

if (!args[0])
return (define_error(args, -1));
env_var = get_env(args[0]);
if (!env_var)
return (0);

for (size = 0; environ[size]; size++)
;

new_environ = malloc(sizeof(char *) * size);
if (!new_environ)
return (define_error(args, -1));
for (index = 0, index2 = 0; environ[index]; index++)
{
if (*env_var == environ[index])
{
free(*env_var);
continue;
}
new_environ[index2] = environ[index];
index2++;
}
free(environ);
environ = new_environ;
environ[size - 1] = NULL;
return (0);
}

