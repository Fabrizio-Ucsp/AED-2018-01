#include<iostream>
using namespace std;

template <class T>
struct CNode{
	T data;
	CNode<T> *m_next;
	CNode(T x) {
		data = x;
		m_next = NULL;
	}
};

template <class T>
class CList {
	public:
		CNode<T> *m_head;
		CList() { 
			m_head = NULL;
		}

		bool find(T x, CNode<T>**& p) {
			for(p = &m_head; (*p) && (*p)->data < x ; p=&(*p)->m_next){}
			return (*p) && (*p)->data == x;
		}

		bool Insert(T x) {
			CNode<T>**p;
			if (find(x, p))return 0;
			CNode<T>*t = new CNode<T>(x);
			t->m_next = *p;
			*p = t;
			return 1;
		}

		bool Remove(T x) {
			CNode<T>**p;
			if (!find(x, p))return 0;
			CNode<T>*temp = *p;
			*p = temp->m_next;
			delete temp;
			return 1;
		}

		void Print(){
			cout << "--> ";
			CNode<T>**p;
			p = &m_head;
			while (*p != NULL) {
				cout << (*p)->data;
				p = &(*p)->m_next;
				cout << " --> ";
			}
			cout << " // "<<endl;
		}

		~CList() {
			CNode<T> **p = &m_head;
			CNode<T> *temp;
			while (*p){
				temp = *p;
				*p = (*p)->m_next;
				delete temp;
			}
		}
	
};

int main() {
	int tempo;
	int tempo2;
	CList<int> List;

	int hasta = 1;
	while (hasta != 0) {
		cout << "Desea : "<<endl;
		cout << "1) Insertar" << endl;
		cout << "2) Eliminar" << endl;
		cout << "0) Terminar" << endl;
		cout << "Ingrese el numero de opcion" << endl;
		cin >> hasta;
		if (hasta == 1) {
			cout << "Ingrese el numero que desea insertar: ";
			cin >> tempo;
			List.Insert(tempo);
		}
		if (hasta == 2) {
			cout << "Ingrese el numero que desea eliminar: ";
			cin >> tempo2;
			cout << "Numero a que quieres borrar es : " << tempo2 << endl;
			List.Remove(tempo2);
		}
		if (hasta == 0) {
			break;
		}
		List.Print();
	}
	system("pause");
}