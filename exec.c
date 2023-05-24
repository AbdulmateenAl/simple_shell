#include "shell.h"
/**
 * get_builtin - fetches for system builtin function.
 * @command: command to match.
 * Return: pointer to the corresponding builtin function.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
inbuilt_t funcs[] = {
{"exit", system_exit},
{"env", system_env},
{"setenv", system_setenv},
{"unsetenv", system_unsetenv},
{"cd", system_cd},
{"alias", system_alias},
{"help", system_help},
{NULL, NULL}};
int i;

for (i = 0; funcs[i].name; i++)
{
if (str_cmp(funcs[i].name, command) == 0)
break;
}
return (funcs[i].f);
}

/**
 * system_exit - process termination for the system shell.
 * @args: arguments containing the exit value.
 * @front: pointer to the beginning of args.
 * Return: 0 success 2 invalid args 3 no args
 */
int system_exit(char **args, char **front)
{
int i = 0, len_of_int = 10;
unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

if (args[0])
{
if (args[0][0] == '+')
{
i = 1;
len_of_int++;
}
for (; args[0][i]; i++)
{
if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
num = (num * 10) + (args[0][i] - '0');
else
return (define_error(--args, 2));
}
}
else
{
return (-3);
}
if (num > max - 1)
return (define_error(--args, 2));
args -= 1;
free_args(args, front);
free_env();
free_alias_list(aliases);
exit(num);
}

/**
 * system_cd - Changes the current directory of the system process.
 * @args: arguments.
 * @front: pointer to the beginning of args.
 * Return: 0 for success -1 when error occur -2 invalid directory
 */
int system_cd(char **args, char __attribute__((__unused__)) **front)
{
char **dir_info, *new_line = "\n";
char *old_pwd = NULL, *pwd = NULL;
struct stat dir;

old_pwd = getcwd(old_pwd, 0);
if (!old_pwd)
return (-1);

if (args[0])
{
if (*(args[0]) == '-' || str_cmp(args[0], "--") == 0)
{
if ((args[0][1] == '-' && args[0][2] == '\0') ||
args[0][1] == '\0')
{
if (get_env("OLDPWD") != NULL)
(chdir(*get_env("OLDPWD") + 7));
}
else
{
free(old_pwd);
return (define_error(args, 2));
}
}
else
{
if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode) && (
			(dir.st_mode & S_IXUSR) != 0))
chdir(args[0]);
else
{
free(old_pwd);
return (define_error(args, 2));
}
}
}
else
{
if (get_env("HOME") != NULL)
chdir(*(get_env("HOME")) + 5);
}

pwd = getcwd(pwd, 0);
if (!pwd)
return (-1);

dir_info = malloc(sizeof(char *) * 2);
if (!dir_info)
return (-1);

dir_info[0] = "OLDPWD";
dir_info[1] = old_pwd;
if (system_setenv(dir_info, dir_info) == -1)
return (-1);

dir_info[0] = "PWD";
dir_info[1] = pwd;
if (system_setenv(dir_info, dir_info) == -1)
return (-1);
if (args[0] && args[0][0] == '-' && args[0][1] != '-')
{
write(STDOUT_FILENO, pwd, str_len(pwd));
write(STDOUT_FILENO, new_line, 1);
}
free(old_pwd);
free(pwd);
free(dir_info);
return (0);
}

/**
 * system_help - shows info about system builtin commands.
 * @args: arguments.
 * @front: pointer to the beginning of args.
 * Return: 0 for success else -1
 */
int system_help(char **args, char __attribute__((__unused__)) **front)
{
if (!args[0])
help_all();
else if (str_cmp(args[0], "alias") == 0)
help_alias();
else if (str_cmp(args[0], "cd") == 0)
help_cd();
else if (str_cmp(args[0], "exit") == 0)
help_exit();
else if (str_cmp(args[0], "env") == 0)
help_env();
else if (str_cmp(args[0], "setenv") == 0)
help_setenv();
else if (str_cmp(args[0], "unsetenv") == 0)
help_unsetenv();
else if (str_cmp(args[0], "help") == 0)
help_help();
else
write(STDERR_FILENO, name, str_len(name));

return (0);
}

