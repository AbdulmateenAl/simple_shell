#include "shell.h"
int system_alias(char **args, char __attribute__((__unused__)) * *front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
/**
 * system_alias - system command that prints aliases
 * @args:  arguments.
 * @front: double pointer to the args.
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int system_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		value = str_chr(args[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (str_cmp(args[i], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = define_error(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (ret);
}
/**
 * set_alias - set an existing alias or create new alias'name' with a new value
 * @var_name: Name of the alias.
 * @value: Value of the alias. starts with a '='.
 */
void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = str_len(value) - str_spn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (str_cmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}
/**
 * print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = str_len(alias->name) + str_len(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	str_cpy(alias_string, alias->name);
	str_cat(alias_string, "='");
	str_cat(alias_string, alias->value);
	str_cat(alias_string, "'\n");
	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * replace_aliases - replace any matching alias with their value.
 * @args: pointer to the arguments
 * Return: args.
 */
char **replace_aliases(char **args)
{
	alias_t *temp;
	int i;
	char *new_value;

	if (str_cmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (str_cmp(args[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (str_len(temp->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				str_cpy(new_value, temp->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}
	return (args);
}
