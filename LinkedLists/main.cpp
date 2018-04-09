#include<iostream>
using namespace std;

class IntNode {
public:
	int info;
	IntNode *next;
	IntNode() {
		next = 0;
	}

	IntNode(int i, IntNode *in = 0) {
		info = i;
		next = in;
	}
};

int main() {
	IntNode *p = new IntNode(10);
	system("pause");
	return 0;
}