#include "shell.h"

/**
 * free_args - frees args memory
 * @args: pointer containing commands/arguments.
 * @front: pointer to the beginning of args.
 */
void free_args(char **args, char **front)
{
size_t i;

for (i = 0; args[i] || args[i + 1]; i++)
free(args[i]);

free(front);
}

/**
 * get_pid - gets the current child process ID
 * Return: current process ID or NULL on failure
 */
char *get_pid(void)
{
size_t i = 0;
char *buffer;
ssize_t file;

file = open("/proc/self/stat", O_RDONLY);
if (file == -1)
{
perror("Cant read file");
return (NULL);
}
buffer = malloc(120);
if (!buffer)
{
close(file);
return (NULL);
}
read(file, buffer, 120);
while (buffer[i] != ' ')
i++;
buffer[i] = '\0';
close(file);
return (buffer);
}

/**
 * get_env_value - gets the value to the environmental variable
 * @beginning: environmental variable in question
 * @len: The length of the environmental variable
 * Return: an empty string or the value of the environmental variable
 */
char *get_env_value(char *beginning, int len)
{
char **var_addr;
char *replacement = NULL, *temp, *var;

var = malloc(len + 1);
if (!var)
return (NULL);
var[0] = '\0';
str_cat_n(var, beginning, len);

var_addr = get_env(var);
free(var);
if (var_addr)
{
temp = *var_addr;
while (*temp != '=')
temp++;
temp++;
replacement = malloc(str_len(temp) + 1);
if (replacement)
str_cpy(replacement, temp);
}

return (replacement);
}

/**
 * rep_var - replaces variable
 * @line: A double pointer containing the command and arguments
 * @exe_ret: pointer to the return value of the last executed command
 */
void rep_var(char **line, int *exe_ret)
{
int j, k = 0, len;
char *replacement = NULL, *old_line = NULL, *new_line;

old_line = *line;
for (j = 0; old_line[j]; j++)
{
if (old_line[j] == '$' && old_line[j + 1] &&
old_line[j + 1] != ' ')
{
if (old_line[j + 1] == '$')
{
replacement = get_pid();
k = j + 2;
}
else if (old_line[j + 1] == '?')
{
replacement = to_string(*exe_ret);
k = j + 2;
}
else if (old_line[j + 1])
{
for (k = j + 1; old_line[k] &&
old_line[k] != '$' &&
old_line[k] != ' ';
k++)
;
len = k - (j + 1);
replacement = get_env_value(&old_line[j + 1], len);
}
new_line = malloc(j + str_len(replacement) + str_len(&old_line[k]) + 1);
if (!line)
return;
new_line[0] = '\0';
str_cat_n(new_line, old_line, j);
if (replacement)
{
str_cat(new_line, replacement);
free(replacement);
replacement = NULL;
}
str_cat(new_line, &old_line[k]);
free(old_line);
*line = new_line;
old_line = new_line;
j = -1;
}
}
}

