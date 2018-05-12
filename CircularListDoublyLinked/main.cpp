#include<stdio.h>
#include<conio.h>
#include<iostream>
using namespace std;
struct node
{
	int data;
	node *next, *prev;
}*p = NULL, *head = NULL, *r = NULL, *np = NULL, *tail = NULL;
int c = 0;
void create(int x)
{
	np = new node;
	np->data = x;
	np->next = NULL;
	np->prev = NULL;
	if (c == 0)
	{
		tail = np;
		head = np;
		p = head;
		p->next = head;
		p->prev = head;
		c++;
	}
	else if (c == 1)
	{
		p = head;
		r = p;
		if (np->data < p->data)
		{
			np->next = p;
			p->prev = np;
			head = np;
			p->next = np;
			np->prev = p;
			tail = p;
		}
		else if (np->data > p->data)
		{
			p->next = np;
			np->prev = p;
			np->next = head;
			p->prev = np;
		}
		c++;
	}
	else {
		p = head;
		r = p;
		if (np->data < p->data)
		{
			np->next = p;
			p->prev = np;
			head = np;
			do
			{
				p = p->next;
			} while (p->next != r);
			tail = p;
			p->next = np;
			np->prev = p;
		}
		else if (np->data > p->data)
		{
			while (p->next != head && np->data > p->data)
			{
				r = p;
				p = p->next;
				if (p->next == head && (p->data < np->data))
				{
					p->next = np;
					np->prev = p;
					np->next = head;
					tail = np;
					head->prev = np;
					break;
				}
				else if (np->data < p->data)
				{
					r->next = np;
					np->prev = r;
					np->next = p;
					p->prev = np;
					if (p->next != head)
					{
						do
						{
							p = p->next;
						} while (p->next != head);
					}
					tail = p;
					break;
				}
			}
		}
	}
}
void traverse_tail(int i)
{
	node *t = tail;
	int x = 0;
	while (x <= i)
	{
		cout << t->data << "\t";
		t = t->prev;
		x++;
	}
	cout << endl;
}
void traverse_head(int i)
{
	node *t = head;
	int c = 0;
	while (c <= i)
	{
		cout << t->data << "\t";
		t = t->next;
		c++;
	}
	cout << endl;
}
int main()
{
	int i = 0, n, x, ch;
	cout << "enter the no of nodes\n";
	cin >> n;
	while (i < n)
	{
		cout << "\nenter value of node\n";
		cin >> x;
		create(x);
		i++;
	}
	cout << "\nTraversing Doubly Linked List head first\n";
	traverse_head(n);
	cout << "\nTraversing Doubly Linked List tail first\n";
	traverse_tail(n);
	system("pause");
}