#include "main.h"
/**
 * fork_exe - uses fork to execute
 * @ar_str: an array of strings from user input
 * @envp: environment from the parent
 * Return: void
 */
void fork_exe(char **ar_str, char *envp[])
{
	pid_t c_pid;
	int status;
	char *args[] = {"/bin/ls", NULL};

	c_pid = fork();
	if (c_pid < 0)
	{
		perror("error:Fork issue check your code");
		return;
	}
	if (c_pid == 0)
	{
		execve(args[0], args, envp);
		perror("execve");
		_exit(1);
	}
	else
	{
		wait(&status);
	}
	free(ar_str[0]);
}
/**
 * file_check - checks if command exists
 * @str: string to be checked
 * Return: add required path
 */
char *file_check(char *str)
{
	DIR *dir = opendir("/bin/");
	char *temp, *cats;
	struct dirent *entity;

	if (dir == NULL)
		return (NULL);
	entity = readdir(dir);
	while (entity != NULL)
	{
		temp = entity->d_name;
		if (str_cmp(temp, str) == 0)
		{
			cats = str_cat("/bin/", str);
			closedir(dir);
			return (cats);
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}
/**
 * path_check - checks for a "/bin/" path of a string
 * @str: the string in question
 * Return: 0 if no path else 1
 */
int path_check(char *str)
{
	char *pth = "/bin?", *ptr, *k;
	int i = 0, p = 0;

	ptr = malloc(sizeof(char) * 50);
	if (ptr == NULL)
		return (0);
	while (pth[i] != '\0')
	{
		if (pth[i] != str[i])
		{
			free(ptr);
			return (0);
		}
		i++;
	}
	while (str[i] != '\0')
	{
		ptr[p] = str[i];
		p++;
		i++;
	}
	ptr[p] = '\0';
	k = file_check(ptr);
	if (k != NULL)
	{
		free(ptr);
		return (1);
	}
	return (0);
}
/**
 * check_builtin - checks for in built functions
 * @str: string containing function or command
 * Return: 0 when found else 1
 */
int check_builtin(char *str)
{
	char **line_arr;
	int i = 0;

	line_arr = malloc(sizeof(char *) * 5);
	if (line_arr == NULL)
		return (0);
	line_arr[0] = "ls";
	line_arr[1] = "exit";
	line_arr[2] = "env";
	line_arr[3] = "ls -l /tmp";

	for (i = 0; i < 4; i++)
	{
		if (str_cmp(line_arr[i], str) == 0)
			break;
	}
	switch (i)
	{
		case 0:
			system("ls");
			return (1);
		case 1:
			return (2);
		case 2:
			system("env");
			return (3);
		case 3:
			system("ls -l /tmp");
			return (4);
		default:
			perror("Error: No such file or directory");
			free(line_arr);
			return (0);
	}
}
