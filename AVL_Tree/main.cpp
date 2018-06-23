#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<list>
using namespace std;

class Node
{
public:
	int key;
	struct Node *left;
	struct Node *right;
	int height;
};

int max(int a, int b);

int height(class Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

class Node* newNode(int key)
{
	class Node* node = (class Node*) malloc(sizeof(class Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return(node);
}

class Node *rightRotate(class Node *y)
{
	class Node *x = y->left;
	class Node *T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	return x;
}

class Node *leftRotate(class Node *x)
{
	class Node *y = x->right;
	class Node *T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return y;
}

int getBalance(class Node *N)
{
	if (N == NULL) return 0;
	return height(N->left) - height(N->right);
}

class Node* insert(class Node* node, int key)
{
	if (node == NULL) return(newNode(key));
	if (key < node->key) node->left = insert(node->left, key);
	else if (key > node->key) node->right = insert(node->right, key);
	else return node;

	node->height = 1 + max(height(node->left), height(node->right));

	int balance = getBalance(node);
	if (balance > 1 && key < node->left->key) return rightRotate(node);
	if (balance < -1 && key > node->right->key) return leftRotate(node);
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

class Node * minValueNode(class Node* node)
{
	class Node* current = node;
	while (current->left != NULL) current = current->left;
	return current;
}

class Node* deleteNode(class Node* root, int key)
{
	if (root == NULL) return root;
	if (key < root->key) root->left = deleteNode(root->left, key);
	else if (key > root->key) root->right = deleteNode(root->right, key);
	else
	{
		if ((root->left == NULL) || (root->right == NULL))
		{
			class Node *temp = root->left ? root->left : root->right;
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else *root = *temp;
			free(temp);
		}
		else
		{
			class Node* temp = minValueNode(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key);
		}
	}

	if (root == NULL) return root;

	root->height = 1 + max(height(root->left), height(root->right));
	int balance = getBalance(root);
	if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

void inOrder(class Node *root, int niv)
{
	if (!root) {
		cout << "_";
		return;
	}
	inOrder(root->left, niv);
	if (root->height == niv) {
		cout << root->key;
	}
	inOrder(root->right, niv);
}
void ImprimirArbol2D(class Node *root) {
	int temporalDeNivel = height(root);
	for (int i = height(root); i > 0; i--) {
		for (int j = 0; j < temporalDeNivel; j++) {
			cout << "_";
		}
		inOrder(root, i);
		cout << " " << endl;
		temporalDeNivel--;
	}
}

int main()
{
	class Node *root = NULL;
	int ejemploIns[] = { 1,8,3,7,2,9,5,6,4 };
	int ejemploDel[] = { 3,1,6 };
	cout << "inserciones....." << endl;
	for (int i = 0; i < 9; i++) {
		root = insert(root, ejemploIns[i]);
	}
	cout << "Altura del arbol: " << height(root) << endl;;
	cout << endl;
	cout << "Impresion 2D despues de las inserciones" << endl;
	ImprimirArbol2D(root);
	cout << "borrados....." << endl;
	for (int i = 0; i < 3; i++) {
		root = deleteNode(root, ejemploDel[i]);
	}
	cout << endl;
	cout << "Impresion 2D despues de los borrados" << endl;
	ImprimirArbol2D(root);
	system("pause");
	/*
	int tempo;
	int tempo2;
	int hasta = 1;
	cout << "Arbol AVL" << endl;
	while (hasta != 0) {
		cout << "Desea : " << endl;
		cout << "1) Insertar" << endl; //1,8,3,7,2,9,5,6,4
		cout << "2) Eliminar" << endl; //3,1
		cout << "0) Terminar" << endl;
		cout << "Ingrese el numero de opcion" << endl;
		cin >> hasta;
		if (hasta == 1) {
			cout << "Ingrese el numero que desea insertar: ";
			cin >> tempo;
			root = insert(root, tempo);
		}
		if (hasta == 2) {
			cout << "Ingrese el numero que desea eliminar: ";
			cin >> tempo2;
			cout << "Numero a que quieres borrar es : " << tempo2 << endl;
			root = deleteNode(root, tempo2);
		}
		if (hasta == 0) {
			break;
		}
		ImprimirArbol2D(root);
	}*/
	return 0;
}