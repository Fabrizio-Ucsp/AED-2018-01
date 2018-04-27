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
struct CBinNode{
	T data;
	CBinNode<T>*nodes[2];
	CBinNode(T x) {
		nodes[0] = nodes[1] = 0;
		data = x;
	}
};
template <class T,class C>
class CBinTree {
public:
	CBinNode<T> *root;
	C m_cmp;
	CBinTree() {
		root = 0;
	};
	//~CBinTree();
	bool Find(T x,CBinNode<T>**&p) {
		for (p = &root ; 
			*p && (*p)->data != x ; 
			p = &((*p)->nodes[ m_cmp( (*p)->data, x )])
			);
		return *p != 0;
	}
	bool Insert(T x) {
		CBinNode<T> **p;
		if (Find(x, p))return 0;
		*p = new CBinNode<T>(x);
		return 1;
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
		p = &((*p)->nodes[!((*p)->nodes[0])]);
		delete t;
	}
	/*
	void Print() {
		cout << "Raiz" << endl;
		CBinNode<T> **p;
		CBinNode<T> **trucaso;
		p = &root;
		trucaso = &root;
		if (*p == NULL) { cout << "Esta Vacio" << endl; }
		else {
			cout << (*p)->data << endl;
			while( (*trucaso)->nodes[0] != NULL && (*trucaso)->nodes[0] != NULL ){
				cout << "I  D" << endl;
				p = &((*trucaso)->nodes[0]);
				cout << (*p)->data << " ";

				p = &((*trucaso)->nodes[1]);
				cout << (*p)->data << endl;
				trucaso = 
			}
		}
	}*/
	void InOrder(CBinNode<T>*p) {
		if (!p)return;
		InOrder(p->nodes[0]);
		cout << p->data;
		InOrder(p->nodes[1]);
	}
};

int main() {
	CBinTree<int, CLess<int>> Arbol;
	Arbol.Print();
	Arbol.Insert(15);
	Arbol.Insert(10);
	Arbol.Insert(17);
	Arbol.Print();
	system("pause");
}