#include "shell.h"
/**
*main - entry point to our shell
*@ac: argument count
*@env: environment variable
*@av: argument vector
*Return: 0 always on success
*/
int main(int ac, char **env, char **av)
{
if (ac == 1)
{
prompt(env, *av);
return (0);
}
return (0);
}
