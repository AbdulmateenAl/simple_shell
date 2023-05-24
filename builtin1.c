#include "shell.h"

/**
 * help_env - shows information on the system builtin command 'env'.
 */
void help_env(void)
{
char *msg;

msg = "env: env\n\tPrints the current environment.\n";
write(STDOUT_FILENO, msg, str_len(msg));
}

/**
 * help_setenv - shows information on the system builtin command 'setenv'.
 */
void help_setenv(void)
{
char *msg;

msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "environment variable, or modifies an existing one.\n\n";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "\tUpon failure, prints a message to stderr.\n";
write(STDOUT_FILENO, msg, str_len(msg));
}

/**
 * help_unsetenv - shows information on the system builtin command
 * 'unsetenv'.
 */
void help_unsetenv(void)
{
char *msg;

msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "environmental variable.\n\n\tUpon failure, prints a ";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "message to stderr.\n";
write(STDOUT_FILENO, msg, str_len(msg));
}
