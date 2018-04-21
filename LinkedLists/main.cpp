#include<iostream>
using namespace std;

template <class T>
class Node {
public:
	T data;
	Node<T> *next;
	Node(T x) {
		data = x;
		next =	NULL;
	}
	Node(T x,Node<T> *_next) {
		data = x;
		next = _next;
	}
};

template <class T>
class CList {
public:
	Node<T> *head;
	CList() {
		head = NULL;
	}
	
	int isEmpty() {
		return head == NULL;
	}

	void Insert(int info) {
		Node<T> *tmp;
		tmp = head;
		if (isEmpty()) {
			Node<T> *tmp2 = new Node<T>(info);
			head = tmp2;
		}
		else {
			if (info < tmp->data) {
				Node<T> *tmp2 = new Node<T>(head->data, head->next);
				Node<T> *tmp3 = new Node<T>(info);
				head = tmp3;
				head->next = tmp2;
			}
			else {
				Node<T> *truco;
				truco = tmp;
				while (tmp != NULL) {
					if (info < tmp->data){
						Node<T> *tmp2 = new Node<T>(info);
						truco->next = tmp2;
						tmp2->next = tmp;
						break;
					}else{
						truco = tmp;
						tmp = tmp->next;
					}
					if (tmp == NULL) {
						Node<T> *tmp4 = new Node<T>(info);
						truco->next = tmp4;
						break;
					}
				}
			}
		}
	}

	void DeleteVal(int info) {
		Node<T> *tmp;
		tmp = head;
		if (isEmpty()) {
			cout << "La lista esta vacia no puedes borrar nada" << endl;
		}
		else {
			if (info == tmp->data) {
				Node<T> *tmp2 ;
				tmp2 = head;
				head = tmp2->next;
				delete tmp2;
			}
			else {
				Node<T> *truco;
				truco = tmp;
				tmp = tmp->next;
				while (tmp != NULL) {
					if (info == tmp->data) {
						truco->next = tmp->next;
						delete tmp;
						break;
					}
					else {
						truco = tmp;
						tmp = tmp->next;
					}
					if (tmp == NULL) {
						cout << "No se encontro el numero en la lista" << endl;
						break;
					}
				}
			}
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
	
};

int main() {
	CList<int> Lista;
	int tempo;
	int tempo2;
	int hasta = 1;
	while (hasta != 0) {
		cout << "Desea : " << endl;
		cout << "1) Insertar" << endl;
		cout << "2) Eliminar" << endl;
		cout << "0) Terminar" << endl;
		cout << "Ingrese el numero de opcion" << endl;
		cin >> hasta;
		if (hasta == 1) {
			cout << "Ingrese el numero que desea insertar: ";
			cin >> tempo;
			Lista.Insert(tempo);
		}
		if (hasta == 2) {
			cout << "Ingrese el numero que desea eliminar: ";
			cin >> tempo2;
			cout << "Numero a que quieres borrar es : " << tempo2 << endl;
			Lista.DeleteVal(tempo2);
		}
		if (hasta == 0) {
			break;
		}
		Lista.printList();
	}
	system("pause");
	return 0;
}