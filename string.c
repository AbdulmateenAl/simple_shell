#include "main.h"
/**
 * strtok_char - a function that returns a string
 * @str: an array of strings
 * Return: string
 */
char **strtok_char(char *str)
{
	char **ar_st, *pars;
	int i = 0, j = 0;

	ar_st = malloc(8 * sizeof(char *));
	if (ar_st == NULL)
	{
		perror("space allocation failure");
		exit(1);
	}
	pars = strtok(str, " ");
	while (pars != NULL)
	{
		while (pars[j])
		{
			if (pars[j] == '\n')
				pars[j] = '\0';
			j++;
		}
		ar_st[i] = pars;
		i++;
		j = 0;
		pars = strtok(NULL, " ");
	}
	ar_st[i] = NULL;
	return (ar_st);
}
/**
 * str_cmp - used to compare two strings
 * @str1: pointer to first string
 * @str2: pointer to second string
 * Return: 0 if match, 1-- if 1 is shorter else 1++
*/
int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 != *str2)
		return (*str1 - *str2);
	return (0);
}
/**
 * str_cat - adds two strings
 * @src: pointer to string to be added
 * @dest: pointer to a string to be added to
 * Return: new string which is src and dest
*/
char *str_cat(const char *src, char *dest)
{
	const char *tempSrc;
	char *tempDest;

	tempDest = dest;
	tempSrc = src;

	while (*tempDest != '\0')
		tempDest++;
	while (*tempSrc != '\0')
		*tempDest++ = *tempSrc++;
	*tempDest = '\0';
	return (dest);
}
