#include "shell.h"
/**
 * env_error - Creates an error message for system_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *env_error(char **args)
{
char *error, *hist_str;
int len;

hist_str = to_string(hist);
if (!hist_str)
return (NULL);

args--;
len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 45;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(hist_str);
return (NULL);
}

str_cpy(error, name);
str_cat(error, ": ");
str_cat(error, hist_str);
str_cat(error, ": ");
str_cat(error, args[0]);
str_cat(error, ": Unable to add/remove from environment\n");

free(hist_str);
return (error);
}

/**
 * _error - Creates an error message for system_alias errors.
 * @args: arguments passed to the command.
 * Return: error string.
 */
char *_error(char **args)
{
char *error;
int len;

len = str_len(name) + str_len(args[0]) + 13;
error = malloc(sizeof(char) * (len + 1));
if (!error)
return (NULL);

str_cpy(error, "alias: ");
str_cat(error, args[0]);
str_cat(error, " not found\n");

return (error);
}

/**
 * exit_error - a function that creates message for system_exit errors.
 * @args: arguments passed to the command.
 * Return: The error string.
 */
char *exit_error(char **args)
{
char *error, *hist_str;
int len;

hist_str = to_string(hist);
if (!hist_str)
return (NULL);

len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 27;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(hist_str);
return (NULL);
}

str_cpy(error, name);
str_cat(error, ": ");
str_cat(error, hist_str);
str_cat(error, ": exit: Illegal number: ");
str_cat(error, args[0]);
str_cat(error, "\n");

free(hist_str);
return (error);
}

/**
 * cd_error - Creates an error message for cd errors.
 * @args: arguments passed to the command.
 *
 * Return:error string.
 */
char *cd_error(char **args)
{
char *error, *hist_str;
int len;

hist_str = to_string(hist);
if (!hist_str)
return (NULL);

if (args[0][0] == '-')
args[0][2] = '\0';
len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 24;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(hist_str);
return (NULL);
}

str_cpy(error, name);
str_cat(error, ": ");
str_cat(error, hist_str);
if (args[0][0] == '-')
str_cat(error, ": cd: Illegal option ");
else
str_cat(error, ": cd: can't cd to ");
str_cat(error, args[0]);
str_cat(error, "\n");

free(hist_str);
return (error);
}

/**
 * syntax_error - Creates an error message for syntax errors.
 * @args: arguments passed to the command.
 * Return: error string.
 */
char *syntax_error(char **args)
{
char *error, *hist_str;
int len;

hist_str = to_string(hist);
if (!hist_str)
return (NULL);

len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 33;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(hist_str);
return (NULL);
}

str_cpy(error, name);
str_cat(error, ": ");
str_cat(error, hist_str);
str_cat(error, ": Syntax error: \"");
str_cat(error, args[0]);
str_cat(error, "\" unexpected\n");

free(hist_str);
return (error);
}

