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

template <class T, class Op>
class CList {
	public:
		CNode<T> *m_head;
		CList() { 
			m_head = 0; 
		}
		Op m_op;
		bool find(T x, CNode<T>**& p) {
			cout << "&m_head: " << &m_head << endl;

			p = &m_head;
			cout << "*p: " << *p << endl;
			cout << "(*p): " << (*p) << endl;
			while (*p != NULL && (*p)->data < x)
			{
				p = &(*p)->m_next;
			}
			return (*p) != NULL && (*p)->data == x;
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
			if (find(x, p))return 0;
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
	
};

int main() {
	CList<int>*test = new CList<int>();
	test->Insert(10);
	test->Insert(11);
	test->Print();
	system("pause");
}