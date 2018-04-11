#include<iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

void LlenarArray(int *arr, int tam) {
	srand(time(NULL));
	for (int i = 0; i<tam; i++) {
		int temporal = rand() % 999999;
		*(arr + i) = temporal;
	}
}

void printArr(int *arr, int tam) {
	for (int i = 0; i<tam; i++) {
		if (i<tam - 1) {
			cout << *(arr + i) << ", ";
		}
		else {
			cout << *(arr + i) << ".";
		}
	}
}

void Merge(int *arr, int inicio, int medio, int fin) {
	int i, j, k;
	int tamDeArrTemp1 = medio - inicio + 1;
	int tamDeArrTemp2 = fin - medio;
	int *tmpArr1;
	int *tmpArr2;
	tmpArr1 = new int[tamDeArrTemp1];
	tmpArr2 = new int[tamDeArrTemp2];
	for (i = 0; i < tamDeArrTemp1; i++) {
		*(tmpArr1 + i) = *(arr + (inicio + i));
	}
	for (j = 0; j < tamDeArrTemp2; j++) {
		*(tmpArr2 + j) = *(arr + (medio + 1 + j));
	}
	i = 0; j = 0; k = inicio;
	while (i < tamDeArrTemp1 && j < tamDeArrTemp2) {
		if (*(tmpArr1 + i) <= *(tmpArr2 + j)) {
			*(arr + k) = *(tmpArr1 + i);
			i++;
		}
		else {
			*(arr + k) = *(tmpArr2 + j);
			j++;
		}
		k++;
	}
	while (i < tamDeArrTemp1) {
		*(arr + k) = *(tmpArr1 + i);
		i++;
		k++;
	}
	while (j < tamDeArrTemp2) {
		*(arr + k) = *(tmpArr2 + j);
		j++;
		k++;
	}
	delete[]tmpArr1;
	delete[]tmpArr2;
}

void MergeSort(int *arr, int inicio, int fin) {
	if (inicio < fin) {
		int medio = inicio + (fin - inicio) / 2;
		MergeSort(arr, inicio, medio);
		MergeSort(arr, medio + 1, fin);

		Merge(arr, inicio, medio, fin);
	}
}


int main() {
	int tam;
	int *arr;
	float inicio, fin, t;
	int tamanios[4] = { 6,50000,75000,100000 };
	for (int i = 0; i < 1; i++) {
		tam = tamanios[i];
		arr = new int[tam];
		LlenarArray(arr, tam);
		cout << "Array inicial: " << endl;
		printArr(arr, tam);
		cout << " " << endl;
		inicio = clock();
		MergeSort(arr, 0, tam - 1);
		fin = clock();
		t = fin - inicio;
		printf("\nEl tiempo de proseso es: %f", t / CLOCKS_PER_SEC);
		printf("\n");
		cout << "Array final: " << endl;
		printArr(arr, tam);
	}
	printf("\n");
	system("PAUSE");
	return 0;
}