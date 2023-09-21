#include "header.h"

/**
 *at_index - gets the index of a node
 *@head: points to head of the node
 *@node: nodes:wq
 *
 *
 *Return: index of node or -1
 */
ssize_t at_index(list_t *head, list_t *node)
{
	size_t node_size = 0;

	while (head)
	{
		if (head == node)
			return (node_size);
		
		head = head->next;
		node_size++;
	}
	return (-1);
}
/**
 * add_node - adds a node to the start of a list
 * @head: points to head of the node
 * @str: string
 * @num: number
 *
 *
 * Return: new lissst
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->i = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: ditto
 * @str: ditto
 * @num: ditto
 *
 *
 * Return: new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->i = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


/**
 * del_at_index - deletes node at given index
 * @head: ditto
 * @index: the node to delete
 *
 *
 * Return: 1 on success, 0 on failure
 */
int del_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		list_t *node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	return (del_at_index(&((*head)->next), (index - 1)));
}

/**
 *node_starts_with - entry point
 *@node: node
 *@substr: string to match
 *@c: char value
 *
 *
 *Return: output
 */
list_t *node_starts_with(list_t *node, char *substr, char c)
{
	char *ptr = NULL;

	while(node)
	{
		ptr = _strstr(node->str, substr);
		
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);

		node = node->next;
	}
	return NULL;
}
