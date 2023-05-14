#include "shell.h"
/**
*printMessage - outputs the message
*@message: prompt variable
*/
void printMessage(const char *message)
{
fputs(message, stdout);
}
/**
*printFatalError - used to show when there is an error in the code
*@errorMessage: the error message
*/
void printFatalError(const char *errorMessage)
{
fprintf(stderr, "%s: Fatal error\n", errorMessage);
}
/**
*executeCommand - prompt helper function
*@env: environment variable
*@argv: pointer variable
*@av: argument variable
*/
void executeCommand(char **env, char **argv, char *av)
{
pid_t pid_c;
int status;

pid_c = fork();
if (pid_c == -1)
{
free(argv[0]);
exit(EXIT_FAILURE);
}

if (pid_c == 0)
{
if (execve(argv[0], argv, env) == -1)
{
printFatalError(av);
}
}
else
{
waitpid(pid_c, &status, 0);
}
free(argv[0]);
}
/**
*prompt - used to output prompt to the screen
*@env: environment variable
*@av: argument variable
*/
void prompt(char **env, char *av)
{
char *line = NULL, *argv[MAX_COMMAND];
ssize_t c_num;
size_t num = 0;
int i, j;

while (1)
{
if (isatty(STDIN_FILENO))
printMessage("$helly☺🤖 ");
line = malloc(sizeof(char) * num);
c_num = getline(&line, &num, stdin);
if (c_num == -1)
{
free(line);
exit(EXIT_FAILURE);
}
i = 0;
while (line[i])
{
if (line[i] == '\n')
line[i] = 0;
i++;
}
j = 0;
argv[j] = strtok(line, " ");
while (argv[j])
{
argv[++j] = strtok(NULL, " ");
}
executeCommand(env, argv, av);
}
}
