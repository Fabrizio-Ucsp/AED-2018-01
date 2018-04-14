#include<iostream>
using namespace std;

template <class T>
class Node {
public:
	T info;
	Node<T> *next; 
	Node() {
		next = 0;
	}

	Node(T _info, Node *ptr = 0) {
		info = _info;
		next = ptr;
	}
};
template <class T>
class IntList {
public:
	Node<T> *head, *tail;
	IntList() {
		head = tail = 0;
	}
	int isEmpty() {
		return head == 0;
	}
	~IntList() {
		for (Node<T> *p; !isEmpty(); ) {
			p = head->next;
			delete head;
			head = p;
		}
	}
	void addtoHead(int info) {
		head = new Node<T>(info, head);
		if (tail == 0) {
			tail = head;
		}
	}
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
	}
};

int main() {
	Node<int> *p = new Node<int>(10);
	cout << "Node info: " << p->info;
	p->next = new Node<int>(8);
	p->next->next = new Node<int>(50);

	system("pause");
	return 0;
}
