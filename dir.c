#include "shell.h"
/**
 * get_location - returns the location of command
 * @command: The command in question
 * Return:  NULL or the full pathname of the command.
 */
char *get_location(char *command)
{
char **path, *temp;
list_t *dirs, *head;
struct stat st;

path = get_env("PATH");
if (!path || !(*path))
return (NULL);
dirs = get_path_dir(*path + 5);
head = dirs;
while (dirs)
{
temp = malloc(str_len(dirs->dir) + str_len(command) + 2);
if (!temp)
return (NULL);
str_cpy(temp, dirs->dir);
str_cat(temp, "/");
str_cat(temp, command);

if (stat(temp, &st) == 0)
{
free_list(head);
return (temp);
}
dirs = dirs->next;
free(temp);
}
free_list(head);
return (NULL);
}

/**
 * fill_path_dir - copies path and replaces with current working directory.
 * @path: list of directories.
 * Return: copy of path.
 */
char *fill_path_dir(char *path)
{
int i, length = 0;
char *path_copy, *pwd;

pwd = *(get_env("PWD")) + 4;
for (i = 0; path[i]; i++)
{
if (path[i] == ':')
{
if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
length += str_len(pwd) + 1;
else
length++;
}
else
length++;
}
path_copy = malloc(sizeof(char) * (length + 1));
if (!path_copy)
return (NULL);
path_copy[0] = '\0';
for (i = 0; path[i]; i++)
{
if (path[i] == ':')
{
if (i == 0)
{
str_cat(path_copy, pwd);
str_cat(path_copy, ":");
}
else if (path[i + 1] == ':' || path[i + 1] == '\0')
{
str_cat(path_copy, ":");
str_cat(path_copy, pwd);
}
else
str_cat(path_copy, ":");
}
else
{
str_cat_n(path_copy, &path[i], 1);
}
}
return (path_copy);
}

/**
 * get_path_dir - prepares a path list into token
 * @path: list of directories.
 * Return: pointer to the initialized list.
 */
list_t *get_path_dir(char *path)
{
int index;
char **dirs, *path_copy;
list_t *head = NULL;

path_copy = fill_path_dir(path);
if (!path_copy)
return (NULL);
dirs = str_tok(path_copy, ":");
free(path_copy);
if (!dirs)
return (NULL);

for (index = 0; dirs[index]; index++)
{
if (add_node_end(&head, dirs[index]) == NULL)
{
free_list(head);
free(dirs);
return (NULL);
}
}
free(dirs);
return (head);
}
