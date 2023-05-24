#include "shell.h"
/**
 * copy_env - Creates a copy of the environment.
 * Return: NULL or pointer to the new copy.
 */
char **copy_env(void)
{
char **new_environ;
size_t size;
int index;
for (size = 0; environ[size]; size++)
;

new_environ = malloc(sizeof(char *) * (size + 1));
if (!new_environ)
return (NULL);
for (index = 0; environ[index]; index++)
{
new_environ[index] = malloc(str_len(environ[index]) + 1);
if (!new_environ[index])
{
for (index--; index >= 0; index--)
free(new_environ[index]);
free(new_environ);
return (NULL);
}
str_cpy(new_environ[index], environ[index]);
}
new_environ[index] = NULL;
return (new_environ);
}

/**
 * free_env - Frees the the environment copy memory.
 */
void free_env(void)
{
int index;
for (index = 0; environ[index]; index++)
free(environ[index]);
free(environ);
}

/**
 * get_env - Gets an environmental variable from the PATH.
 * @var: name of the environmental variable to get.
 * Return: NULL or a pointer to var.
 */
char **get_env(const char *var)
{
int index, len;

len = str_len(var);
for (index = 0; environ[index]; index++)
{
if (str_cmp_n(var, environ[index], len) == 0)
return (&environ[index]);
}
return (NULL);
}

