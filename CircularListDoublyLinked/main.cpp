#include<iostream>
using namespace std;

template <class T>
class Node {
public:
	T data;
	Node<T> *next;
	Node<T> *prev;
	Node(T x) {
		data = x;
		next = NULL;
		prev = NULL;
	}
	Node(T x, Node<T> *_next) {
		data = x;
		next = _next;
	}
};

template <class T>
class CList {
public:
	Node<T> *head;
	Node<T> *tail;
	T Cantidad;
	CList() {
		head = NULL;
		tail = NULL;
	}

	int isEmpty() {
		return head == NULL && tail == NULL;
	}
	void Insert(int info) {
		Node<T> *tmp;
		tmp = head;
		if (Cantidad == 0) {
			head = NULL;
			tail = NULL;
			//cout << "La lista esta vacia " << endl;
			Node<T> *tmp2 = new Node<T>(info);
			head = tmp2;
			tail = tmp2;
			//cout << "Se inserto:head " << head->data << endl;
			Cantidad++;
		}
		else {
			//cout << "No esta vacio y pasa a evaluar" << endl;
			if (info < tmp->data && info != tmp->data) {
				//cout << "info es menor a la cabeza:inserta antes del head" << endl;
				Node<T> *tmp2 = new Node<T>(head->data, head->next);
				Node<T> *tmp3 = new Node<T>(info);
				head = tmp3;
				head->next = tmp2;
				tmp2->prev = head;
				tail = tmp2;
				Cantidad++;
			}
			else {
				//cout << "info es mayor a la cabeza:" << endl;
				Node<T> *truco;
				truco = tmp;
				//cout << "info tiene que ser menor diferente a la cabeza" << endl;
				while (tmp != NULL && info != tmp->data) {
					if (info < tmp->data) {
						//cout<<"Inserta entre 2 nodos"<<endl;
						Node<T> *tmp2 = new Node<T>(info);
						truco->next = tmp2;
						tmp2->next = tmp;
						tmp2->prev = truco;
						tmp->prev = tmp2;
						Cantidad++;
						break;
					}
					else {
						truco = tmp;
						tmp = tmp->next;
					}
					if (tmp == NULL) {
						//cout << "Insert al final de la lista" << endl;
						Node<T> *tmp4 = new Node<T>(info);
						truco->next = tmp4;
						tmp4->prev = truco;
						tail = tmp4;
						Cantidad++;
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
				cout << "Borra la cabeza:" << endl;
				Node<T> *tmp2;
				tmp2 = head;
				head = tmp2->next;
				delete tmp2;
				Cantidad--;
			}
			else {
				Node<T> *truco;
				truco = tmp;
				tmp = tmp->next;
				while (tmp != NULL) {
					if (info == tmp->data) {
						//cout << "caso de borrar la cola" << endl;
						if (tmp==tail) {
							//cout << "caso de borrar la cola" << endl;
							truco->next = NULL;
							if (Cantidad == 0) {
								head = NULL;
								tail = NULL;
							}
						}
						//cout << "borrar entre nodos" << endl;
						truco->next = tmp->next;
						tmp->next->prev = truco;
						delete tmp;
						Cantidad--;
						if (Cantidad == 0) {
							head = NULL;
							tail = NULL;
						}
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
		T i = 0;
		for (int i = 0; i < Cantidad; i++) {
			cout << tmp->data;
			tmp = tmp->next;
			cout << " --> ";
		}
		cout << " // " << endl;
	}
	void ReversePrintList() {
		cout << "--> ";
		Node<T> *tmp;
		tmp = tail;
		T i = 0;
		for (int i = 0; i < Cantidad; i++) {
			cout << tmp->data;
			tmp = tmp->prev;
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
			cout << "Cantidad de elementos: " << Lista.Cantidad << endl;
			system("pause");
			system("cls");
		}
		if (hasta == 2) {
			cout << "Ingrese el numero que desea eliminar: ";
			cin >> tempo2;
			cout << "Numero a que quieres borrar es : " << tempo2 << endl;
			Lista.DeleteVal(tempo2);
			cout << "Cantidad de elementos: " << Lista.Cantidad << endl;
			system("pause");
			system("cls");
		}
		if (hasta == 0) {
			break;
		}
		Lista.printList();
		Lista.ReversePrintList();
	}
	system("pause");
	return 0;
}