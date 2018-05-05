#include<iostream>
using namespace std;

class Carta{
public:
	char palo;
	int id;
	char numero;
	Carta(char _palo, char _numero, int _id) {
		palo = _palo;
		id = _id;
		numero = _numero;
	};
};
class Jugado{
public:
	int score;

};


int main() {
	cout << "Ingrese el Numero de Jugadores: ";
	int NumeroDeJugadores;
	cin >> NumeroDeJugadores;
	while (NumeroDeJugadores<2) {
		cout << "El numero de jugadores tiene que ser minimo de 2 jugadores" << endl;
		cout << "Ingrese el Numero de Jugadores: ";
		cin >> NumeroDeJugadores;
	}
	system("pause");
	return 0;
}