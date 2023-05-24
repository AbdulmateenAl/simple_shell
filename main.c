#include "main.h"
​
/**
 * main - entry point for the shell
 * @argc: argument count
 * @argv: argument vectors array
 * @envp: environment pointer array
 * Return: 0 when successful
 */
int main(int argc, char *argv[], char *envp[])
{
    char **string;
    size_t n = 20, i = 0, pt = 4;
    ssize_t char_num;
    char *ptr, *n_str;
​
    if (argc > 1)
        argv[1] = NULL;
    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("£ ");
        ptr = malloc(sizeof(char) * n);
        char_num = getline(&ptr, &n, stdin);
        if (char_num == -1)
        {
            free(ptr);
            exit(EXIT_FAILURE);
        }
        if (*ptr != '\n')
        {
            string = strtok_char(ptr);
            if (str_cmp("exit", string[0]) == 0)
                break;
            i = check_builtin(string[0]);
            n_str = file_check(string[0]);
            if (i == 0 && n_str != NULL)
                string[0] = n_str;
            pt = path_check(string[0]);
            if (pt == 1)
                fork_exe(string, envp);
            if (n_str == NULL && pt == 0 && i == 0)
                printf("./Error: Does not exist\n");
        }
    }
    free(n_str);
    free(ptr);
    free(string);
    exit(0);
}
