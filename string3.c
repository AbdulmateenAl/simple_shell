#include "shell.h"
/**
 * str_chr - gets a character in a string
 * @s: string in question
 * @c: character in question
 * Return: pointer to the first instance or NULL.
 */
char *str_chr(char *s, char c)
{
int index;

for (index = 0; s[index]; index++)
{
if (s[index] == c)
return (s + index);
}
return (NULL);
}

/**
 * str_spn - gets the length of a prefix substring
 * @s: string in question
 * @accept: prefix in question
 * Return: length of prefix
 */
int str_spn(char *s, char *accept)
{
int bytes = 0;
int index;

while (*s)
{
for (index = 0; accept[index]; index++)
{
if (*s == accept[index])
{
bytes++;
break;
}
}
s++;
}
return (bytes);
}

/**
 * str_cmp - Compares two strings
 * @s1: first string in question
 * @s2: second string in question
 * Return: Positive if s1 > s2
 *         0 if s1 = s2
 *         Negative if s1 < s2
 */
int str_cmp(char *s1, char *s2)
{
while (*s1 && *s2 && *s1 == *s2)
{
s1++;
s2++;
}

if (*s1 != *s2)
return (*s1 - *s2);

return (0);
}

/**
 * str_cmp_n - Compare two strings
 * @s1: Pointer to a string one
 * @s2: Pointer to a string two
 * @n: first n bytes of the strings to compare.
 * Return: < 0 if s1 < s2.
 *         0 if s1 = s2
 *         > 0 if s1 > s2.
 */
int str_cmp_n(const char *s1, const char *s2, size_t n)
{
size_t i;

for (i = 0; s1[i] && s2[i] && i < n; i++)
{
if (s1[i] > s2[i])
return (s1[i] - s2[i]);
else if (s1[i] < s2[i])
return (s1[i] - s2[i]);
}
if (i == n)
return (0);
else
return (-15);
}

