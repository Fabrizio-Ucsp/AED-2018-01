#pragma once
#include "cartas.h"
#include "circular_jugador.h"
template <class T>
class Game {
public:
	int NumeroDeJugadores;
	Player_List<T> *Jugadores;
	Cards_List<T> mazo;
	Cards_List<T> pila_descarte;
	bool direccion_juego = 1;
	Game();
	void init_game();
	void init_players();
	void repartir_cartas(int cantidad, int num_players);
	bool verificar_cartas(int _id,int _numero, string _palo);
	bool dar_puntajes();
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
	NumeroDeJugadores = num_players;
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
	system("cls");
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
inline bool Game<T>::dar_puntajes(){

	int meta;
	if (NumeroDeJugadores == 2) {
		meta = 100;
	}
	if (NumeroDeJugadores == 3) {
		meta = 150;
	}
	if (NumeroDeJugadores == 4) {
		meta = 200;
	}

	cout << endl << "Se terminaron las cartas D:" << endl;
	cout << "Calcular Los Puntajes de los jugadores" << endl;
	cout << "NumeroDeJugadores: " << NumeroDeJugadores << endl;
	Player_Node<T> *iter = Jugadores->player_init;
	for (int i = 0; i < NumeroDeJugadores; i++) {
		cout << "NombreDelJugador: " << iter->nombre << endl;
		iter->CalcularPuntaje();
		if (iter->Puntuacion >= meta) {
			cout << "Gano el jugador : " << iter->nombre << " por llegar o pasar la meta: " << meta << endl;
			return true ;
		}
		iter = iter->nodes[direccion_juego];
	}

	cout << "Nadie alcanzo la meta : " << meta << endl;
	cout << "Se Vuelve a crear la baraja y repartir las manos" << endl;
	mazo.CrearCartas();
	pila_descarte.~Cards_List();
	while (mazo.m_head->numero == 8) mazo.Barajear();
	for (int i = 0; i < NumeroDeJugadores; i++) {
		iter->mazo_mano.~Cards_List();
		iter = iter->nodes[direccion_juego];
	}
	if (NumeroDeJugadores == 2) repartir_cartas(7, NumeroDeJugadores);
	if (NumeroDeJugadores > 2) repartir_cartas(8, NumeroDeJugadores);

	cout << "A empezar denuevo :D pero eso si se mantienen los puntajes ;)" << endl;
	return false;

}

template<class T>
inline void Game<T>::iniciar_ronda(){
	int id_temp = 52;
	Player_Node<T> *iterador_ronda=Jugadores->player_init;
	//si la primera carta es 8
	while (mazo.m_head->numero== 8) mazo.Barajear();
	pila_descarte.Insert(id_temp, mazo.m_head->numero, mazo.m_head->palo); id_temp--;
	mazo.Remove(mazo.m_head->id);
	mazo.PrintNumeroDeCartas();
	bool condicion_ganar = false;
	bool pasar_ronda = false;
	int condicion_ronda = 1;
	string condicion_seguir ;
	bool condicion_dar = 0;	
	
	while (condicion_ganar != true) {
		while (pasar_ronda != true) {

			
			cout << endl << "____________________________8LOCOS_________________________________" << endl;
			
			cout << " NumeroDeJugadores: " << NumeroDeJugadores << endl;
			mazo.PrintNumeroDeCartas();
			cout << endl << "------Mazo de: " << iterador_ronda->nombre << "-------" << endl;
			iterador_ronda->mazo_mano.Print();
			cout << "Puntuacion: " << iterador_ronda->Puntuacion << endl;
			cout << endl << "<------Pila de Juego----->";
			cout << " --> " << pila_descarte.m_head->numero << " --> " << pila_descarte.m_head->palo << endl;
			cout << "<------------------------------------------------------->" << endl;

			cout << "1. Dar Carta" << endl;
			cout << "2. Sacar Carta del mazo" << endl<<"Ingrese su opcion: ";
			cin >> condicion_ronda;
			cout << endl;
			if (condicion_ronda == 1) {
				if (verificar_cartas(iterador_ronda->id, pila_descarte.m_head->numero, pila_descarte.m_head->palo)) {
					cout << "Usted no tiene ninguna carta para dar" << endl;
					system("pause");
					system("cls");
				}
				else {
					Card_Node<T> **temp;
					int id_a_dar;
					while (condicion_dar != true) {
						cout << "Ingrese la ID de la carta a dar:";
						cin >> id_a_dar; cout << endl;
						if (!iterador_ronda->mazo_mano.find(id_a_dar, temp)) {
							cout << endl << "ID invalida!, intentelo de nuevo..." << endl;
						}
						else{ condicion_dar = true; }
					}
					iterador_ronda->mazo_mano.find(id_a_dar, temp);
					if ((*temp)->numero == 8) {
						cout << endl << "Tienes un comodin!Puedes colocar una carta otravez" << endl;
						//system("pause");
						//system("cls");
						pila_descarte.Insert(id_temp, (*temp)->numero, (*temp)->palo); id_temp--;
						iterador_ronda->mazo_mano.Remove(id_a_dar);

						cout << endl << "------Mazo de: " << iterador_ronda->nombre << "-------" << endl;
						iterador_ronda->mazo_mano.Print();
						cout << endl;
						condicion_dar = false;
						while (condicion_dar != true) {
							cout << "Ingresa la id de cualquier carta: "; cin >> id_a_dar;
							if (iterador_ronda->mazo_mano.find(id_a_dar, temp)) {
								//iterador_ronda->mazo_mano.find(id_a_dar, temp);
								pila_descarte.Insert(id_temp, (*temp)->numero, (*temp)->palo); id_temp--;
								iterador_ronda->mazo_mano.Remove(id_a_dar);
								condicion_dar = true;
								pasar_ronda = true;
								//continue
							}
							else { cout << "Ingrese una ID valida, intentelo otra vez..." << endl; }
						}
					}
					
					if ((*temp)->numero == pila_descarte.m_head->numero || (*temp)->palo == pila_descarte.m_head->palo) {
						if ((*temp)->numero == 11) {
							cout << "---!!! A TODO GAAAAS!!!!, cambiasta la direccion del juego---" << endl;
							direccion_juego = 0;
						}
						pila_descarte.Insert(id_temp, (*temp)->numero, (*temp)->palo); id_temp--;
						iterador_ronda->mazo_mano.Remove(id_a_dar);
						condicion_dar = true;
						pasar_ronda = true;
					}
				}
			}
			condicion_dar=false;

			if (condicion_ronda == 2) {
				if (verificar_cartas(iterador_ronda->id, pila_descarte.m_head->numero, pila_descarte.m_head->palo)) { //cambiar aca para que puedas sacar con o sin restriccion
					cout << "Usted tiene cartas que puede jugar, ¡no sea tramposo!" << endl;
					system("pause");
					system("cls");
				}
				else {
					iterador_ronda->mazo_mano.Insert(mazo.m_head->id, mazo.m_head->numero, mazo.m_head->palo);
					mazo.Remove(mazo.m_head->id);
					cout << "Usted ha cojido una carta de la baraja" << endl;
					system("pause");
					system("cls");
				}
			}
			if (iterador_ronda->mazo_mano.m_head == nullptr) {
				cout << "¡¡¡¡¡USTED GANOO :D !!!! " << endl;
				condicion_ronda = true;
				pasar_ronda = true;
				condicion_ganar = true;
				break; break;
			}
			if (mazo.m_head == nullptr) { //si se termina el mazo de cartas
				if (!dar_puntajes()) {
					id_temp = 52;
					iterador_ronda = Jugadores->player_init;
					//si la primera carta es 8
					pila_descarte.Insert(id_temp, mazo.m_head->numero, mazo.m_head->palo); id_temp--;
					mazo.Remove(mazo.m_head->id);
					mazo.PrintNumeroDeCartas();
					condicion_ganar = false;
					condicion_ronda = 1;
					condicion_dar = 0;
				}
				else {
					condicion_ganar = true;
					condicion_ronda = true;
					continue;
				}
			}
			
		}
		cout << endl << "____________________________Fin Del Turno_________________________________" << endl;
		system("pause");
		system("cls");
		iterador_ronda = iterador_ronda->nodes[direccion_juego];
		pasar_ronda = false;
		cout << endl << "----Seguir?(Que su compañero no vea sus cartas) ingrese 1 porfavor" << endl;
		cin >> condicion_seguir;
		system("cls");
	}
	cout << "EL jugador " << iterador_ronda->nombre << " gano!!!" << endl;
	cout << endl << "---------------FIN DEL JUEGO----------------------------" << endl;
	
}
