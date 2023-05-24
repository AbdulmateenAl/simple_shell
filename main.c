#include "shell.h"
/**
 * sig_handler - detects when to print prompt on the screen.
 * @sig: The signal to be read.
 */
void sig_handler(int sig)
{
char *new_prompt = "\n£ ";

(void)sig;
signal(SIGINT, sig_handler);
write(STDIN_FILENO, new_prompt, 10);
}

/**
 * execute - calls a command in pid.
 * @args: arguments array.
 * @front: pointer to the beginning of args.
 *
 * Return: corresponding error code or exit value of the last executed command.
 */
int execute(char **args, char **front)
{
pid_t child_pid;
int status, flag = 0, ret = 0;
char *command = args[0];

if (command[0] != '/' && command[0] != '.')
{
flag = 1;
command = get_location(command);
}

if (!command || (access(command, F_OK) == -1))
{
if (errno == EACCES)
ret = (define_error(args, 126));
else
ret = (define_error(args, 127));
}
else
{
child_pid = fork();
if (child_pid == -1)
{
if (flag)
free(command);
perror("Error child:");
return (1);
}
if (child_pid == 0)
{
execve(command, args, environ);
if (errno == EACCES)
ret = (define_error(args, 126));
free_env();
free_args(args, front);
free_alias_list(aliases);
_exit(ret);
}
else
{
wait(&status);
ret = WEXITSTATUS(status);
}
}
if (flag)
free(command);
return (ret);
}

/**
 * main - entry to shell
 * @argc: number of arguments to shell
 * @argv: pointers to the argument values.
 * Return: value of the last executed command.
 */
int main(int argc, char *argv[])
{
int ret = 0, retn;
int *exe_ret = &retn;
char *prompt = "#cisfun$ ", *new_line = "\n";

name = argv[0];
hist = 1;
aliases = NULL;
signal(SIGINT, sig_handler);

*exe_ret = 0;
environ = copy_env();
if (!environ)
exit(-100);

if (argc != 1)
{
ret = proc_file_commands(argv[1], exe_ret);
free_env();
free_alias_list(aliases);
return (*exe_ret);
}

if (!isatty(STDIN_FILENO))
{
while (ret != END_OF_FILE && ret != EXIT)
ret = handle_args(exe_ret);
free_env();
free_alias_list(aliases);
return (*exe_ret);
}

while (1)
{
write(STDOUT_FILENO, prompt, 10);
ret = handle_args(exe_ret);
if (ret == END_OF_FILE || ret == EXIT)
{
if (ret == END_OF_FILE)
write(STDOUT_FILENO, new_line, 10);
free_env();
free_alias_list(aliases);
exit(*exe_ret);
}
}
free_env();
free_alias_list(aliases);
return (*exe_ret);
}

