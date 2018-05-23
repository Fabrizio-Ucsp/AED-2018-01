#include<iostream>
using namespace std;

template <class T>
struct CLess{
	bool operator ()(T a, T b) { return a < b; }
};


template <class T>
struct CGreater {
	bool operator ()(T a, T b) { return a > b; }
};

template <class T>
class CBinNode {
public: 
	T data=0;
	T nivel=0;
	CBinNode<T>* nodes[2];
	CBinNode(T _data) {
		nodes[0] = NULL;
		nodes[1] = NULL;
		data = _data;
	}
};

template <class T,class C>
class CBinTree {
public:
	T tam=0;
	T nivel_arbol=0;
	T nivel_temporal=0;
	CBinNode<T> *root;
	C m_cmp;
	CBinTree() {
		root = 0;
	};
	//~CBinTree();
	bool Find(T x,CBinNode<T>**&p) {
		T tenporal=0;
		for (
			p = &root;
			*p != NULL && (*p)->data != x;
			p = &( (*p) -> nodes[ m_cmp((*p)->data, x) ] )
		)
		{
			tenporal++;//??????????????????????????????????????????????
		}
		nivel_temporal = tenporal;
		if (tenporal>nivel_arbol) {
			nivel_arbol = tenporal;
		}
		return *p != 0;
	}
	bool Insert(T x) {
		CBinNode<T> **p;
		if (Find(x, p))return 0;
		*p = new CBinNode<T>(x);
		(*p)->nivel = nivel_temporal;
		tam++;
		nivel_temporal = 0;
		return 1;
	}
	CBinNode<T> ** HallaReemplazo(CBinNode<T>**&p) {
		CBinNode<T>**tmp;
		for ( tmp = &(*p)->nodes[0]; (*tmp)->nodes[1] != NULL; tmp = &(*tmp)->nodes[1] );
		return tmp;
	}
	bool Remove(T x) {
		CBinNode<T> **p;
		if (!Find(x, p))return 0;
		if ((*p)->nodes[0] && (*p)->nodes[1]) {
			CBinNode<T> **q = HallaReemplazo(p);
			(*p)->data = (*q)->data;
			p = q;
		}
		CBinNode<T> *t = *p;
		*p = ((*p)->nodes[!((*p)->nodes[0])]);
		delete t;
	}
	
	void InOrder(CBinNode<T>*p,int var) {	
		if (!p)return;
		InOrder(p->nodes[0],var);
		if (p->nivel == var) {
			cout << p->data << " ";
		}
		InOrder(p->nodes[1],var);
	}

	void PrintTree() {
		for (int i = 0; i < nivel_arbol+1; i++) {
			CBinNode<T>*p;
			p = root;
			InOrder(p,i);
			cout << " " << endl;
		}
		cout << "Numero de valores en el arbol: " << tam << endl;
		cout << "Niveles que posee el arbol: " << nivel_arbol+1 << endl;
	}
};

int main() {
	CBinTree<int, CLess<int>> Arbol;
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
			Arbol.Insert(tempo);
		}
		if (hasta == 2) {
			cout << "Ingrese el numero que desea eliminar: ";
			cin >> tempo2;
			cout << "Numero a que quieres borrar es : " << tempo2 << endl;
			Arbol.Remove(tempo2);
		}
		if (hasta == 0) {
			break;
		}
		Arbol.PrintTree();
	}
	cout << " " << endl;
	getchar();
}