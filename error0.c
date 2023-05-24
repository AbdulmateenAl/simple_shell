#include "shell.h"
/**
 * denied_per_error - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *denied_per_error(char **args)
{
char *error, *hist_str;
int len;

hist_str = to_string(hist);
if (!hist_str)
return (NULL);

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
str_cat(error, ": ");
str_cat(error, args[0]);
str_cat(error, ": Permission denied\n");
free(hist_str);
return (error);
}

/**
 * not_found_error - creates error message.
 * @args: arguments passed to the command.
 * Return: The error string.
 */
char *not_found_error(char **args)
{
char *error, *hist_str;
int len;

hist_str = to_string(hist);
if (!hist_str)
return (NULL);

len = str_len(name) + str_len(hist_str) + str_len(args[0]) + 16;
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
str_cat(error, ": not found\n");

free(hist_str);
return (error);
}
