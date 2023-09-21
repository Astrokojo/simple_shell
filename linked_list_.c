#include "header.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	if (h == NULL)
		return (0);

	return (1 + list_len(h->next));
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	if (!h)
		return (0);

	_puts(convert_number(h->i, 10, 0));
	_putchar(':');
	_putchar(' ');
	_puts(h->str ? h->str : "(nil)");
	_puts("\n");

	return (1 + print_list(h->next));
}

/**
 *free_list - frees all nodes of a list
 *@head_ptr: ...
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 *print_list_str - prints only the string element in a linked list
 * @h: pointer to first node
 *
 *Return: list size
 */
size_t print_list_str(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
		return (n);
}
