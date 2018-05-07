#pragma once
#include "cartas.h"
#include "circular_jugador.h"
template <class T>
class Game {
public:
	Player_List<T> *Jugadores;
	Cards_List<T> mazo;
	Cards_List<T> pila_descarte;
	bool direccion_juego = 1;
	Game();
	void init_game();
	void init_players();
	void repartir_cartas(int cantidad, int num_players);
	bool verificar_cartas(int _id,int _numero, string _palo);
	void iniciar_ronda();
};

template<class T>
inline Game<T>::Game() {

}

template<class T>
inline void Game<T>::init_game() {
	mazo.CrearCartas();
	mazo.Barajear();
	init_players();
	iniciar_ronda();
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

template<class T>
inline bool Game<T>::verificar_cartas(int _id,int _numero, string _palo) {
	Player_Node<T> *p = Jugadores->get_player(_id);
	Card_Node<T>*temp;
	for (temp = p->mazo_mano.m_head; temp; temp = temp->m_next) {
		if (temp->numero == _numero || temp->numero == 8)
			return false;
		if (temp->palo == _palo)
			return false;
	}
	return true;


}
template<class T>
inline void Game<T>::iniciar_ronda(){
	int id_temp = 52;
	
	Player_Node<T> *iterador_ronda=Jugadores->player_init;
	//si la primera carta es 8
	while (mazo.m_head->numero== 8) mazo.Barajear();
	pila_descarte.Insert(id_temp, mazo.m_head->numero, mazo.m_head->palo); id_temp--;
	mazo.Remove(mazo.m_head->id);
	bool condicion_ganar = false;
	bool pasar_ronda = false;
	int condicion_ronda = 1;
	int condicion_seguir = 0;
	bool condicion_dar = 0;	
	while (condicion_ganar != true) {
	
		while (pasar_ronda != true) {
			if (iterador_ronda->mazo_mano.m_head == nullptr) {
				cout << "¡¡¡¡¡USTED GANOO :D !!!! " << endl;
				condicion_ronda = true;
				pasar_ronda = true;
				continue;
			}
			cout << endl << "------Mazo de: " << iterador_ronda->nombre << "-------" << endl;
			iterador_ronda->mazo_mano.Print();


			cout << endl << "<------Pila de descarte----->";
			cout << " --> " << pila_descarte.m_head->numero << " --> " << pila_descarte.m_head->palo << endl;
			cout << "<------------------------------------------------------->" << endl;

			cout << "1. Dar Carta" << endl;
			cout << "2. Sacar Carta del mazo" << endl<<"Ingrese su opcion: ";
			cin >> condicion_ronda;
			cout << endl;
			if (condicion_ronda == 1) {
				if (verificar_cartas(iterador_ronda->id, pila_descarte.m_head->numero, pila_descarte.m_head->palo)) {
					cout << "Usted no tiene ninguna carta para dar" << endl;
				}
				else {
					while (condicion_dar != true) {
						int id_a_dar = 0;
						cout << "Ingrese la id de la carta a dar:";
						cin >> id_a_dar; cout << endl;
						Card_Node<T> **temp;
						if (!iterador_ronda->mazo_mano.find(id_a_dar, temp)) {
							cout << endl << "ID invalida" << endl;
							continue;
						}
						if ((*temp)->numero == 8) {
							cout << endl << "¡Tienes un comodin!" << endl;
							pila_descarte.Insert(id_temp, (*temp)->numero, (*temp)->palo); id_temp--;
							iterador_ronda->mazo_mano.Remove(id_a_dar);

							cout << endl << "------Mazo de: " << iterador_ronda->nombre << "-------" << endl;
							iterador_ronda->mazo_mano.Print();
							cout << endl;

							cout << "Ingresa la id de cualquier carta: "; cin >> id_a_dar;
							iterador_ronda->mazo_mano.find(id_a_dar, temp);	
							pila_descarte.Insert(id_temp, (*temp)->numero, (*temp)->palo); id_temp--;
							iterador_ronda->mazo_mano.Remove(id_a_dar);
							condicion_dar = true;
							pasar_ronda = true;
							continue;
						}

						if ((*temp)->numero == pila_descarte.m_head->numero || (*temp)->palo == pila_descarte.m_head->palo) {
								pila_descarte.Insert(id_temp, (*temp)->numero, (*temp)->palo); id_temp--;
								iterador_ronda->mazo_mano.Remove(id_a_dar);
								condicion_dar = true;
								pasar_ronda = true;
					
						}
						
					}
				}
			}
			condicion_dar=false;

			if (condicion_ronda == 2) {
				if (!verificar_cartas(iterador_ronda->id, pila_descarte.m_head->numero, pila_descarte.m_head->palo))
					cout << "Usted tiene cartas que puede jugar, ¡no sea tramposo!" << endl;
				else {
					iterador_ronda->mazo_mano.Insert(mazo.m_head->id, mazo.m_head->numero, mazo.m_head->palo);
					mazo.Remove(mazo.m_head->id);
				}
			}
		
		}
		iterador_ronda = iterador_ronda->nodes[direccion_juego];
		pasar_ronda = false;
		cout << endl << "seguir?" << endl;
		cin >> condicion_seguir;
	}
	
	
}
