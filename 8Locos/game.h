#pragma once
#include "cartas.h"
#include "circular_jugador.h"
template <class T>
class Game {
public:
	Player_List<T> *Jugadores;
	Cards_List<T> mazo;
	Cards_List<T> pila_descarte;
	Game();
	void init_game();
	void init_players();
	void repartir_cartas(int cantidad, int num_players);
};

template<class T>
inline Game<T>::Game() {

}

template<class T>
inline void Game<T>::init_game() {
	mazo.CrearCartas();
	mazo.Barajear();
	init_players();
	Jugadores->get_player(1)->mazo_mano.Print();
}

template<class T>
void Game<T>::init_players() {
	int num_players;
	string _nombre;
	cout << "Ingrese el numero de jugadores(Minimo 2 y Maximo 4):" << endl;
	cin >> num_players;
	cout << endl;
	cout << "Ingrese el nombre del primer jugador: "; cin >> _nombre;
	Jugadores = new Player_List<T>(1, _nombre);
	if (num_players == 2) {
		cout << "Ingrese el nombre del segundo jugador: "; cin >> _nombre;
		Jugadores->Insert_Player(2, _nombre);
		repartir_cartas(7,num_players);
	}
	if (num_players > 2) {
		for (int i = 2; i <= num_players; i++) {
			cout << "Ingrese el nombre del siguiente jugador: "; cin >> _nombre;
			Jugadores->Insert_Player(i, _nombre);
			
		}
		repartir_cartas(8,num_players);
	}
}

template<class T>
inline void Game<T>::repartir_cartas(int cantidad,int num_players) {
	Player_Node<T> *temp;
	for (int j = 0; j < cantidad; j++) {
		for (int i = 1; i <= num_players; i++) {
			temp = Jugadores->get_player(i);
			temp->mazo_mano.Insert(mazo.m_head->id, mazo.m_head->numero, mazo.m_head->palo);
			mazo.Remove(mazo.m_head->id);
		}
	}
}
