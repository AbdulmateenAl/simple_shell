#include "shell.h"
/**
 * str_len - returns the length of a string
 * @s: pointer to the string in question
 * Return: length of the string
 */
int str_len(const char *s)
{
int length = 0;

if (!s)
return (length);
for (length = 0; s[length]; length++)
;
return (length);
}

/**
 * str_cpy - copies the string pointed to by src
 * @dest: Pointer to the destination of copied string
 * @src: Pointer to the src of the source string
 * Return: Pointer to dest
 */
char *str_cpy(char *dest, const char *src)
{
size_t i;

for (i = 0; src[i] != '\0'; i++)
dest[i] = src[i];
dest[i] = '\0';
return (dest);
}

/**
 * str_cat - combines two strings
 * @dest: Pointer to destination string
 * @src: Pointer to source string
 * Return: Pointer to destination string
 */
char *str_cat(char *dest, const char *src)
{
char *destTemp;
const char *srcTemp;

destTemp = dest;
srcTemp = src;

while (*destTemp != '\0')
destTemp++;

while (*srcTemp != '\0')
*destTemp++ = *srcTemp++;
*destTemp = '\0';
return (dest);
}

/**
 * str_cat_n - combines two strings where given number of bytes are copied from source
 * @dest: Pointer to destination string
 * @src: Pointer to source string
 * @n: given number of bytes to copy from src
 * Return: Pointer to destination string
 */
char *str_cat_n(char *dest, const char *src, size_t n)
{
size_t dest_len = str_len(dest);
size_t i;

for (i = 0; i < n && src[i] != '\0'; i++)
dest[dest_len + i] = src[i];
dest[dest_len + i] = '\0';

return (dest);
}

