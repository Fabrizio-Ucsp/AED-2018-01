#include<iostream>
using namespace std;

template <class T>
struct CNode{
	T data;
	CNode<T> *m_next;
	CNode(T x) {
		data = x;
		m_next = 0;
	}
};

template <class T>
class CList {
	public:
		CNode<T> *m_head;
		CList( T x) { 
			m_head = new CNode<T>(x); 
		}
		bool find(T x, CNode<T>**& p) {
			//cout << "&m_head: " << &m_head << endl;

			p = &m_head;
			// << "*p: " << *p << endl;
			//cout << "(*p)->data: " << (*p)->data << endl;
			//cout << "x: " << x << endl;
			while (*p != NULL && (*p)->data < x)
			{
				p = &(*p)->m_next;
			}
			//cout << "(*p)->data: " << (*p)->data << endl;
			//cout << "x: " << x << endl;
			return (*p) != NULL && (*p)->data == x;
		}
		bool Insert(T x) {
			CNode<T>**p;
			if (find(x, p))return false;
			CNode<T>*t = new CNode<T>(x);
			t->m_next = *p;
			*p = t;
			return true;
		}
		bool Remove(T x) {
			CNode<T>**p;
			cout << "remover" << endl;
			if (find(x, p))return false;
			cout << "pasa el if" << endl;
			CNode<T>*temp = *p;
			*p = temp->m_next;
			delete temp;
			return true;
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
	
};

int main() {
	cout << "Ingrse un valor para inicializar la lista: ";
	int tempo; cin >> tempo;
	CList<int>test(tempo);
	test.Print();
	test.Insert(tempo);
	test.Print();
	test.Remove(tempo);
	test.Print();
	/*int hasta = 1;
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
			test->Insert(tempo);
		}
		if (hasta == 2) {
			cout << "Ingrese el numero que desea eliminar: ";
			cin >> tempo;
			test->Remove(tempo);
		}
		test->Print();
	}*/
	system("pause");
}