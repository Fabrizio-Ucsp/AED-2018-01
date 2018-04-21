#include<iostream>
using namespace std;

template <class T>
class Node {
public:
	T data;
	Node<T> *next;
	Node(T x) {
		data = x;
		next =	0;
	}
};

template <class T>
class CList {
public:
	Node<T> *head, *tail;
	CList( T x ) {
		head = new Node<T>(x);
	}
	
	void addToList(int info) {
		Node<T> *tmp;
		tmp = head;
		cout << "AddToList:" << endl;
		cout << "info: " << info << endl;
		cout << "tmp -> data: " << tmp->data << endl;
		cout << "tmp: " << tmp << endl;
		cout << "head: " << head << endl;
		if (info<tmp->data) {
			Node<T> *tmp2 = new Node<T>(head->data);
			Node<T> *tmp3 = new Node<T>(info);
			head = tmp3;
			head->next = tmp2;
		}
		while( tmp != NULL && tmp->data<info) {
			cout << "Cuando el numero es mayor al head: " << endl;
			Node<T> *tmp2 = new Node<T>(info);
			tmp2 = tmp->next->next;
			tmp = tmp2;
			tmp = tmp->next;
		}
	}
	void printList() {
		cout << "--> ";
		Node<T> *tmp;
		tmp = head;
		while (tmp != NULL) {
			cout << tmp->data;
			tmp = tmp->next;
			cout << " --> ";
		}
		cout << " // " << endl;
	}
	/*
	void addtoTail(int info) {
		if (tail != 0) {
			tail->next = new Node<T>(info);
			tail = tail->next;
		}
		else head = tail = new Node<T>(info);
	}
	int deleteFromHead() {
		int infoHead = head->info;
		Node<T> *tmp = head;
		if (head == tail) {
			head = tail = 0;
		}
		else {
			head = head->next;
		}
		delete tmp;
		return infoHead;
	}
	int deleteFromTail() {
		int infoTail = tail->info;
		if (head == tail) {
			delete head;
			head = tail = 0;
		}
		else {
			Node<T> *tmp;
			for (tmp = head; tmp->next != tail; tmp = tmp->next);
			delete tail;
			tail = tmp;
			tail->next = 0;
		}
		return infoTail;
	}
	void deleteNode(int infoNodo) {
		if (head != 0) {
			if (head == tail && infoNodo == head->info) {
				delete head;
				head = tail = 0;
			}
			else if (infoNodo == head->info) {
				Node<T> *tmp = head->next;
				head = head->next;
				delete tmp;
			}
			else {
				Node<T> *pred, *tmp;
				for (pred = head, tmp = head->next; tmp != 0 && !(tmp->info == infoNodo); pred = pred->next, tmp = tmp->next);
				if (tmp != 0) {
					pred->next = tmp->next;
					if (tmp == tail) {
						tail = pred;
					}
					delete tmp;
				}
			}
		}
	}
	bool inInList(int num) const {
		Node<T> *tmp;
		for (tmp = head; tmp != 0 && !(tmp->info == num); tmp = tmp->next);
		return tmp != 0;
	}*/
};

int main() {
	CList<int> p(11) ;
	cout << "Head info: " << p.head->data<<endl;
	p.addToList(9);
	p.printList();

	p.addToList(10);
	p.printList();
	system("pause");
	return 0;
}
