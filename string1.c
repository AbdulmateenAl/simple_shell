#include "shell.h"
/**
 * re_alloc - Reallocates a memory block using malloc
 * @ptr: pointer to the original memory
 * @old_size: size in bytes of the allocated space for ptr
 * @new_size: size in bytes for the new memory block
 * Return: pointer to the reallocated memory block 0 or -
 */
void *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *mem;
char *ptr_copy, *filler;
unsigned int index;

if (new_size == old_size)
return (ptr);

if (ptr == NULL)
{
mem = malloc(new_size);
if (mem == NULL)
return (NULL);
return (mem);
}

if (new_size == 0 && ptr != NULL)
{
free(ptr);
return (NULL);
}

ptr_copy = ptr;
mem = malloc(sizeof(*ptr_copy) * new_size);
if (mem == NULL)
{
free(ptr);
return (NULL);
}

filler = mem;

for (index = 0; index < old_size && index < new_size; index++)
filler[index] = *ptr_copy++;

free(ptr);
return (mem);
}

/**
 * assign_line_ptr - assigns the line_ptr variable for get_line
 * @line_ptr: buffer to store the input string
 * @n: size of line_ptr
 * @buffer: string to assign to line_ptr
 * @b: buffer size
 */
void assign_line_ptr(char **line_ptr, size_t *n, char *buffer, size_t b)
{
if (*line_ptr == NULL)
{
if (b > 120)
*n = b;
else
*n = 120;
*line_ptr = buffer;
}
else if (*n < b)
{
if (b > 120)
*n = b;
else
*n = 120;
*line_ptr = buffer;
}
else
{
str_cpy(*line_ptr, buffer);
free(buffer);
}
}

/**
 * get_line - Reads input from user
 * @line_ptr: buffer to store the input
 * @n: size of line_ptr
 * @stream: user in question
 * Return: size read in bytes
 */
ssize_t get_line(char **line_ptr, size_t *n, FILE *stream)
{
static ssize_t input;
ssize_t ret;
char c = 'x', *buffer;
int r;

if (input == 0)
fflush(stream);
else
return (-1);
input = 0;

buffer = malloc(sizeof(char) * 120);
if (!buffer)
return (-1);
while (c != '\n')
{
r = read(STDIN_FILENO, &c, 1);
if (r == -1 || (r == 0 && input == 0))
{
free(buffer);
return (-1);
}
if (r == 0 && input != 0)
{
input++;
break;
}
if (input >= 120)
buffer = re_alloc(buffer, input, input + 1);

buffer[input] = c;
input++;
}
buffer[input] = '\0';

assign_line_ptr(line_ptr, n, buffer, input);

ret = input;
if (r != 0)
input = 0;
return (ret);
}

