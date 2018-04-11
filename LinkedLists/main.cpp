#include<iostream>
using namespace std;

class IntNode {
public:
	int info;
	IntNode *next;
	IntNode() {
		next = 0;
	}

	IntNode(int _info, IntNode *ptr = 0) {
		info = _info;
		next = ptr;
	}
};

class IntList {
public:
	IntNode * head, *tail;
	IntList() {
		head = tail = 0;
	}
	int isEmpty() {
		return head == 0;
	}
	~IntList() {
		for (IntNode *p; !isEmpty(); ) {
			p = head->next;
			delete head;
			head = p;
		}
	}
	void addtoHead(int info) {
		head = new IntNode(info, head);
		if (tail == 0) {
			tail = head;
		}
	}
	void addtoTail(int info) {
		if (tail != 0) {
			tail->next = new IntNode(info);
			tail = tail->next;
		}
		else head = tail = new IntNode(info);
	}
	int deleteFromHead() {
		int infoHead = head->info;
		IntNode *tmp = head;
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
			IntNode *tmp;
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
				IntNode *tmp = head->next;
				head = head->next;
				delete tmp;
			}
			else {
				IntNode *pred, *tmp;
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
		IntNode *tmp;
		for (tmp = head; tmp != 0 && !(tmp->info == num); tmp = tmp->next);
		return tmp != 0;
	}
};

int main() {
	IntNode *p = new IntNode(10);
	cout << "IntNode info: " << p->info;
	p->next = new IntNode(8);
	p->next->next = new IntNode(50);

	system("pause");
	return 0;
}
