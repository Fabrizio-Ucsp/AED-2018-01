#pragma once
#include <iostream>
#include <string>
#include "cartas.h"
using namespace std;

template <class T>
class Player_Node{
public:
	T id;
	string nombre; 
	Cards_List<T> mazo_mano;
	int Puntuacion=0;
	Player_Node<T> *nodes[2];
	Player_Node(T _id,string _nombre) {
		id = _id;
		nombre = _nombre;
		nodes[0] = nodes[1] = nullptr;
	}
	void CalcularPuntaje() {
		Card_Node<T>**p;
		p = &mazo_mano.m_head;
		while (*p != nullptr) {
			if ((*p)->numero>10) {
				Puntuacion = Puntuacion + 10;
			}
			else {
				if ((*p)->numero==8) {
					Puntuacion = Puntuacion + 50;
				}
				else {
					Puntuacion = Puntuacion + (*p)->numero;
				}
			}
			p = &(*p)->m_next;
		}
		cout << " Puntuacion de la mano actual : " << Puntuacion << endl;
	}
};

template <class T>
class Player_List{
public:
	Player_Node<T> *player_init;
	Player_Node<T> *player_end;
	Player_List() {
		player_init = player_end = nullptr;
	}
	Player_List(int _id , string _nombre) {
		player_init = new Player_Node<T>(_id, _nombre);
		player_init->nodes[1] = player_init->nodes[0] = player_init;
		player_end = player_init;
		
	}

	void Insert_Player(int _id,string _nombre){
		Player_Node<T>*temp;
		Player_Node<T>*p;
		for (p = player_init; p && p->id != player_end->id; p = p->nodes[1]);
		p->nodes[1] = new Player_Node<T>(_id, _nombre);
		player_end = p->nodes[1];
		player_end->nodes[0] = p;
		player_init->nodes[0] = player_end;
		player_end->nodes[1] = player_init;	
	}
	Player_Node<T>* get_player(int _id){
		Player_Node<T>*p;
		for (p = player_init; p && p->id != _id; p = p->nodes[1]);
		return p;
	}
	void Print_Player() {
		
		for (Player_Node<T>*p = player_init; p->id!=player_end->id; p = p->nodes[1]) {
			cout << p->id << endl;;
		}
		cout << player_end->id << endl;
	}

};
