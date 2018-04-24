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
};

int main() {
	CBinTree<int, CLess<int>> Arbol;
	Arbol.Insert(9);
}