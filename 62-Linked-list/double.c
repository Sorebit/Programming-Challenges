// gcc -std=c99 double.c -o double.app
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	char data;
	struct node *next;	
	struct node *prev;	
} node;

typedef struct dlist
{
	node *head;
	node *tail;
	int size;
} dlist;

dlist dlist_init();
void dlist_print_node(node *n);
void dlist_print(dlist *list);
node * dlist_find(node *p, char data);
int dlist_push_front(dlist *list, char data);
int dlist_pop_front(dlist *list);
int dlist_push_back(dlist *list, char data);
int dlist_pop_back(dlist *list);
int dlist_insert_before(dlist *list, node *before, char data);
int dlist_insert_after(dlist *list, node *after, char data);
int dlist_pop(dlist *list, node *n);

int main(int argc, char const *argv[])
{
	dlist list = dlist_init();
	dlist_push_front(&list, '@'); // @
	dlist_push_front(&list, 'K'); // K @
	dlist_push_front(&list, '+'); // + K @
	dlist_push_front(&list, '#'); // # + K @
	dlist_pop_front(&list);       // + K @
	dlist_pop_front(&list);       // K @
	dlist_pop_back(&list);        // K
	dlist_push_back(&list, '$');  // K $
	dlist_push_back(&list, '^');  // K $ ^
	dlist_push_back(&list, '&');  // K $ ^ &
	dlist_pop_back(&list);        // K $ ^
	dlist_insert_before(&list, dlist_find(list.head, '^'), '"'); // K $ " ^
	dlist_insert_after(&list, dlist_find(list.head, 'K'), '*');  // K * $ " ^
	dlist_pop(&list, dlist_find(list.head, '"')); // K * $ ^
	dlist_pop(&list, dlist_find(list.head, 'K')); // * $ ^
	dlist_print(&list);
	return 0;
}

dlist dlist_init()
{
	dlist list;
	list.size = 0;
	list.head = NULL;
	list.tail = NULL;
	return list;
}

void dlist_print_node(node *n)
{
	printf("%10d | [%10d] | %10d | %c\n", n->prev, n, n->next, n->data);
}

void dlist_print(dlist *list)
{
	node *n = list->head;
	int i = 0;
	printf("HEAD: %10d | TAIL: %10d | SIZE: (%d)\n\n", list->head, list->tail, list->size);
	printf("(i) | %10s | [%10s] | %10s | DATA\n", "PREV", "THIS", "NEXT");
	printf("----+------------+--------------+------------+------\n");
	while(n)
	{
		printf("(%d) | ", i++);
		dlist_print_node(n);
		n = n->next;
	}
}

node * dlist_find(node *p, char data)
{
	node *tmp = p;
	while(tmp)
	{
		if (tmp->data == data)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

int dlist_push_front(dlist *list, char data)
{
	node *n = (node *)malloc(sizeof(node));
	if (!n) return 1;
	n->data = data;
	n->prev = NULL;
	if (list->size == 0)
	{
		n->next = NULL;
		list->head = list->tail = n;
	}
	else
	{
		n->next = list->head;
		list->head->prev = n;
		list->head = n;
	}
	list->size++;
	return 0;
}

int dlist_pop_front(dlist *list)
{
	node *tmp;
	if (!list->size) return 1;
	tmp = list->head;
	if (list->size == 1)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		list->head = tmp->next;
		list->head->prev = NULL;
	}
	list->size--;
	return 0;
}

int dlist_push_back(dlist *list, char data)
{
	node *n = (node *)malloc(sizeof(node));
	if (!n) return 1;
	n->data = data;
	n->next = NULL;
	if (list->size == 0)
	{
		n->prev = NULL;
		list->head = list->tail = n;
	}
	else
	{
		n->prev = list->tail;
		list->tail->next = n;
		list->tail = n;
	}
	list->size++;
	return 0;
}

int dlist_pop_back(dlist *list)
{
	node *tmp;
	if (!list->size) return 1;
	tmp = list->tail;
	if (list->size == 1)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		list->tail = tmp->prev;
		list->tail->next = NULL;
	}
	list->size--;
	return 0;
}

int dlist_insert_before(dlist *list, node *before, char data)
{
	node *n = (node *)malloc(sizeof(node));
	if (!n) return 1;
	if (before == list->head)
	{
		dlist_push_front(list, data);
		return 0;
	}
	n->data = data;
	n->next = before;
	n->prev = before->prev;
	before->prev->next = n;
	before->prev = n;
	list->size++;
	return 0;
}


int dlist_insert_after(dlist *list, node *after, char data)
{
	node *n = (node *)malloc(sizeof(node));
	if (!n) return 1;
	if (after == list->tail)
	{
		dlist_push_back(list, data);
		return 0;
	}
	n->data = data;
	n->next = after->next;
	n->prev = after;
	n->next->prev = n;
	n->prev->next = n;
	list->size++;
	return 0;
}

int dlist_pop(dlist *list, node *n)
{
	if (list->size == 0) return 1;
	if (list->size == 1 || n == list->head)
	{
		dlist_pop_front(list);
		return 0;
	}
	if (n == list->tail)
	{
		dlist_pop_back(list);
		return 0;
	}

	n->prev->next = n->next;
	n->next->prev = n->prev;
	free(n);
	list->size--;
	return 0;
}