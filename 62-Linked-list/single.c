#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	char data;
	struct node *next;
} node;

int lls_size(node *head);
void lls_print(node *n);
void lls_print_all(node *head);
node * lls_find(node *p, char data);
int lls_push_front(node **head, char data);
int lls_pop_front(node **head);
int lls_push_back(node **head, char data);
int lls_pop_back(node **head);
int lls_insert_before(node **head, node *before, char data);
int lls_insert_after(node **head, node *after, char data);


int main(int argc, char const *argv[])
{
	node *head = NULL;
	lls_pop_front(&head);       // returns 1
	lls_pop_back(&head);       // returns 1
	lls_push_front(&head, 'x'); // x
	lls_push_front(&head, 'y'); // y x
	lls_push_front(&head, 'z'); // z y x
	lls_pop_back(&head);       // z y
	lls_pop_front(&head);       // y
	lls_pop_back(&head);       // 
	lls_push_front(&head, 'c'); // c
	lls_push_front(&head, 'i'); // i c 
	lls_push_front(&head, 'b'); // b i c
	lls_push_front(&head, 'a'); // a b i c
	lls_push_front(&head, 'z'); // z a b i c
	lls_pop_front(&head);       // a b i c
	lls_pop_front(&head);       // b i c
	lls_push_back(&head, 'h');  // b i c h
	lls_push_back(&head, 'a');  // b i c h a
	lls_push_back(&head, 'e');  // b i c h a e
	lls_push_back(&head, 'l');  // b i c h a e l
	lls_push_back(&head, 'l');  // b i c h a e l l
	lls_pop_back(&head);        // b i c h a e l

	node *p = lls_find(head, 'c');
	if(p)
	{
		lls_print(p);
		lls_insert_before(&head, p, 'a'); // b i a c h a e l
	}


	printf("size: %d\n", lls_size(head));
	lls_print_all(head);
	return 0;
}

int lls_size(node *head)
{
	int count = 0;
	node *n = head;
	while(n)
	{
		n = n->next;
		++count;
	}
	return count;
}

void lls_print(node *n)
{
	if(n == NULL)
	{
		printf("[NULL]\n");
		return;
	}
	printf("[%10d] -> data: %c | next: [", n, n->data, n->next);
	if(!n->next)
		printf("%10s", "NULL");
	else
		printf("%10d", n->next);
	printf("]\n");
}

void lls_print_all(node *head)
{
	node *n = head;
	while(n)
	{
		lls_print(n);
		n = n->next;
	}
}

node * lls_find(node *p, char data)
{
	while(p && p->data != data)
	{
		p = p->next;
	}
	return p;
}

int lls_push_front(node **head, char data)
{
	node *n = (node *)malloc(sizeof(node));
	if(!n) return 1;

	n->data = data;
	n->next = *head;

	*head = n;
	return 0;
}

int lls_pop_front(node **head)
{
	if(*head == NULL) return 1;
	node *p = *head;
	*head = p->next;
	free(p);
	p = NULL;
	return 0;
}

int lls_push_back(node **head, char data)
{
	node *n = (node *)malloc(sizeof(node));
	if(!n) return 1;
	n->data = data;
	n->next = NULL;

	if(!head)
		*head = n;

	node *p = *head;
	while(p->next)
	{
		p = p->next;
	}
	p->next = n;

	return 0;
}

int lls_pop_back(node **head)
{
	if(*head == NULL) return 1;
	node *p = *head;

	if(p->next == NULL)
	{
		free(p);
		p = NULL;
		*head = NULL;
		return 0;
	}

	while(p->next->next)
	{
		p = p->next;
	}
	free(p->next);
	p->next = NULL;

	return 0;
}

int lls_insert_before(node **head, node *before, char data)
{
	node *n = (node *)malloc(sizeof(node));
	if(!n) return 1;
	n->data = data;
	n->next = before;

	if(before == *head)
	{
		lls_push_front(head, data);
		return 0;
	}

	node *p = *head;
	while(p)
	{
		if(p->next == before)
		{
			p->next = n;
			break;
		}
		p = p->next;
	}
	if(!p) return 2;
	return 0;
}
int lls_insert_after(node **head, node *after, char data)
{
	node *n = (node *)malloc(sizeof(node));
	if(!n) return 1;
	n->data = data;
	n->next = after->next;
	after->next = n;
	return 0;
}