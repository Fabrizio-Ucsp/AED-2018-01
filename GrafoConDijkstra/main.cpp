﻿#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <functional>
#include <assert.h>
using namespace std;
template<typename G>
struct Nodo
{
	using N = typename G::Data;
	using Arista = typename G::Arista;
	N dato;
	list<Arista*> aristasApuntadas;
	list<Arista*> aristasRecibidas;
	bool existe = true;
	int distancia;

	Nodo(const N& dato) :dato(dato) {}
	~Nodo();

	void agregarAristaApuntada(Arista* arista);
	void agregarAristaRecibida(Arista* arista);
	void eliminarAristaApuntadayRecibida(Arista* arista);
};

template<typename G>
Nodo<G>::~Nodo() {
	this->existe = false;
	set<Arista*> ArApuntYRecibidas;// AA U AR - (AA ∩ AR): Para no eliminar 2 veces una misma arista
	for_each(aristasApuntadas.begin(), aristasApuntadas.end(), [&](Arista* arista) {ArApuntYRecibidas.insert(arista); });
	for_each(aristasRecibidas.begin(), aristasRecibidas.end(), [&](Arista* arista) {ArApuntYRecibidas.insert(arista); });

	for_each(ArApuntYRecibidas.begin(), ArApuntYRecibidas.end(), [](Arista* arista) {delete arista; });
	cout << "Se libero el nodo con valor " << dato << endl;
}

template<typename G>
inline void Nodo<G>::agregarAristaApuntada(Arista* arista) {
	aristasApuntadas.push_back(arista);
}

template<typename G>
inline void Nodo<G>::agregarAristaRecibida(Arista* arista) {
	aristasRecibidas.push_back(arista);
}

template<typename G>
inline void Nodo<G>::eliminarAristaApuntadayRecibida(Arista* arista) {
	auto kill = find(aristasApuntadas.begin(), aristasApuntadas.end(), arista);
	if (kill != aristasApuntadas.end()) aristasApuntadas.erase(kill);

	kill = find(aristasRecibidas.begin(), aristasRecibidas.end(), arista);
	if (kill != aristasRecibidas.end()) aristasRecibidas.erase(kill);
}
template<typename G>
struct Arista
{
	using Nodo = typename G::Nodo;
	using E = typename G::Weight;

	E peso;
	bool dir;                    //0 = bidir,1 = dir
	Nodo* nodos[2];

	Arista(Nodo*& n1, Nodo*& n2, E& peso, const bool& dir);
	~Arista();
};

template<typename G>
Arista<G>::Arista(Nodo*& n1, Nodo*& n2, E& peso, const bool& dir) :peso(peso), dir(dir) {
	nodos[0] = n1;
	nodos[1] = n2;
}

template<typename G>
Arista<G>::~Arista() {
	if (nodos[0]->existe && nodos[1]->existe) { ///Grafo.removerArista()
		nodos[0]->eliminarAristaApuntadayRecibida(this);
		nodos[1]->eliminarAristaApuntadayRecibida(this);
	}
	else {                                      ///Grafo.removerNodo()
		Nodo* nodoNoEliminado = nodos[nodos[1]->existe];
		nodoNoEliminado->eliminarAristaApuntadayRecibida(this);
	}
	cout << "Se elimino la arista con peso " << peso << " que unia los nodos con pesos " << nodos[0]->dato << " y " << nodos[1]->dato << endl;
}
template <typename G>
struct currentThreadNodo {
public:
	using Nodo = typename G::Nodo;
	using N = typename G::Data;
public:
	Nodo * currentNodo;
	int distanciaRecorrida;
	vector<N> camino;

	currentThreadNodo(Nodo* nodoActual, int distancia, vector<N> nuevoCamino) :currentNodo(nodoActual), distanciaRecorrida(distancia),
		camino(nuevoCamino) {
		;
	}
	void agregarPaso(N paso) {
		camino.push_back(paso);
	}
	string retornarCamino() const {
		string output;
		for (N dato : camino) {
			output += static_cast<char>(dato);
		}
		if (!output.length())
			output = "nada";
		return output;
	}
};
template<typename G>
ostream& operator<<(ostream& o, const currentThreadNodo<G>& ctr) {
	o << "Thread->( En " << ctr.currentNodo->dato << ", Dist= " << ctr.distanciaRecorrida;
	return o << ", Camino = " << ctr.retornarCamino() << " ) ";
}

template<typename N, typename E>
class Grafo
{
public:
	using self = Grafo<N, E>;
	using Nodo = Nodo<self>;
	using Arista = Arista<self>;
	using currentThreadNodo = currentThreadNodo<self>;
	using Data = N;
	using Weight = E;
private:
	list<Nodo*> universoNodos;
	Nodo* buscarNodo(const N& contenido, size_t& pos = basura) const;
public:
	Grafo() = default;
	~Grafo();

	bool insertarNodo(const N& n);
	template<typename... Args>
	bool insertarNodo(const N& n, Args... otrosParametros);
	bool removerNodo(const N& cont_arista);

	bool insertarEnlace(const N& contenido_a, const N& contenido_b, E peso, const bool& dir);
	bool removerEnlace(const N& contenido_a, const N& contenido_b);
	//Agregar un dixtra del tipo distancia entre dos nodos.
	//Funciones auxiliares
	void imprimir() const;
	bool Dijktra(const N & contenido_nodoA, const N & contenido_nodoB);
	bool noEsEsteNodo(Nodo*& nodo, Arista*& arista) const;
};



template<typename N, typename E>
Nodo<Grafo<N, E>>* Grafo<N, E>::buscarNodo(const N & contenido, size_t & pos) const {
	pos = 0;
	for (auto itr : universoNodos) {
		if (itr->dato == contenido) {
			return itr;
		}
		++pos;
	}
	return nullptr;
}

template<typename N, typename E>
Grafo<N, E>::~Grafo() {
	cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
	cout << "--------------DESTRUCTOR---------------" << endl;
	for_each(universoNodos.begin(), universoNodos.end(), [](Nodo* nodo) {delete nodo; });
	cout << "-----------------FIN-------------------" << endl;
}

template<typename N, typename E>
bool Grafo<N, E>::insertarNodo(const N& n) {///Caso base
	Nodo* new_Nodo = new Nodo(n);
	if (!new_Nodo) return false;
	universoNodos.push_back(new_Nodo);
	return true;
}
template<typename N, typename E>
template<typename ...Args>
bool Grafo<N, E>::insertarNodo(const N& n, Args ...otrosParametros) {
	Nodo* new_Nodo = new Nodo(n);
	if (!new_Nodo) return false;
	universoNodos.push_back(new_Nodo);
	return insertarNodo(otrosParametros...);
}

template<typename N, typename E>
bool Grafo<N, E>::removerNodo(const N& cont_arista) {//Elimina el nodo y su presencia en universoNodos.
	size_t pos = 0;
	delete buscarNodo(cont_arista, pos);

	auto kill = universoNodos.begin();
	advance(kill, pos);
	universoNodos.erase(kill);

	return true;
}

template<typename N, typename E>
bool Grafo<N, E>::insertarEnlace(const N& contenido_a, const N& contenido_b, E peso, const bool & dir) {
	Nodo* Nodo_A = buscarNodo(contenido_a);
	Nodo* Nodo_B = buscarNodo(contenido_b);
	if (!Nodo_A || !Nodo_B) return false; //Si no encuentra un nodo

	Arista* nuevaArista = new Arista(Nodo_A, Nodo_B, peso, dir);
	if (!nuevaArista) return false; //Si no hay espacio en la memoria para asignarle a la nueva arista

	Nodo_A->agregarAristaApuntada(nuevaArista);
	Nodo_B->agregarAristaRecibida(nuevaArista);
	if (dir == BiDir) {
		Nodo_B->agregarAristaApuntada(nuevaArista);
		Nodo_A->agregarAristaRecibida(nuevaArista);
	}
	return true;
}

template<typename N, typename E>
bool Grafo<N, E>::removerEnlace(const N& contenido_a, const N& contenido_b)
{
	Nodo* Nodo_A = buscarNodo(contenido_a);
	Nodo* Nodo_B = buscarNodo(contenido_b);
	if (!Nodo_A || !Nodo_B) return false; //Si no encuentra algun nodo
										  ///Certeza de que una arista apunta a la otra

	list<Arista*>& aristasA = Nodo_A->aristasApuntadas;
	for (auto arista : aristasA) {
		if (arista->nodos[1] == Nodo_B) {
			delete arista;
			return true;
		}
	}
	list<Arista*>& aristasB = Nodo_B->aristasApuntadas;
	for (auto arista : aristasB) {
		if (arista->nodos[1] == Nodo_A) {
			delete arista;
			return true;
		}
	}
	///No se encontro nada
	return false;
}

template<typename N, typename E>
void Grafo<N, E>::imprimir() const {
	for (Nodo* itrNodos : universoNodos) {
		cout << itrNodos->dato << "->";
		for (Arista* itrAristas : itrNodos->aristasApuntadas) {
			cout << itrAristas->peso << '(' << itrAristas->nodos[noEsEsteNodo(itrNodos, itrAristas)]->dato << "), ";
		}
		cout << "\b\b  \n";                  //Elimina de "A1, B9, ... ,Z100, " la parte final ", " sobrante.
	}
}

template<typename N, typename E>
bool Grafo<N, E>::Dijktra(const N& cont_nodoOrigen, const N& cont_nodoDestino)
{
	for_each(universoNodos.begin(), universoNodos.end(), [](Nodo* nodo) {nodo->distancia = INT_MAX; });
	Nodo* nodoOrigen = buscarNodo(cont_nodoOrigen);
	Nodo* nodoDestino = buscarNodo(cont_nodoDestino);
	if (!nodoOrigen || !nodoDestino) return false; //Si no encuentra algun nodo, detengo el algoritmo ahi mismo
	nodoOrigen->distancia = 0;
	if (nodoOrigen == nodoDestino) {
		cout << "La distancia minima es: " << 0 << " y el camino es nada" << endl;
		return true;
	}

	deque<currentThreadNodo> threadsVivos;
	auto imprimirThreads = [&]() {
		for (currentThreadNodo ctr : threadsVivos) {
			cout << ctr << endl;
		}
	};
	vector<N> valoresCamino;
	for (Arista* itr : nodoOrigen->aristasApuntadas) {
		valoresCamino.clear();
		valoresCamino.push_back(nodoOrigen->dato);
		threadsVivos.emplace_back(itr->nodos[1], itr->peso, valoresCamino);
		itr->nodos[1]->distancia = itr->peso;
	}
	//imprimirThreads();

	while (threadsVivos.size()) {
		for (currentThreadNodo& ctn : threadsVivos) {
			for (Arista*& arista : ctn.currentNodo->aristasApuntadas) {
				valoresCamino.clear();
				int nuevaDistancia = ctn.distanciaRecorrida + arista->peso;
				Nodo* nodoOpuesto = arista->nodos[noEsEsteNodo(ctn.currentNodo, arista)];
				if (nuevaDistancia < nodoOpuesto->distancia) {
					valoresCamino = ctn.camino;
					valoresCamino.push_back(ctn.currentNodo->dato);
					threadsVivos.emplace_back(nodoOpuesto, nuevaDistancia, valoresCamino);
					nodoOpuesto->distancia = nuevaDistancia;
				}
			}
			/*
			cout << endl;
			imprimirThreads();
			*/
			if (ctn.currentNodo == nodoDestino) {
				//cout << "Camino mas corto encontrado" << endl;
				cout << "La distancia es: " << ctn.distanciaRecorrida << " y el camino recorrido es: " << ctn.retornarCamino() << ctn.currentNodo->dato << endl;
				return true;
			}
			threadsVivos.pop_front();
		}
	}
	return false;
}

template<typename N, typename E>
inline bool Grafo<N, E>::noEsEsteNodo(Nodo *& nodo, Arista *& arista) const
{
	return arista->nodos[0] == nodo;
}
template <typename N, typename E>
struct ModeloGrafo {
private:
	Grafo<N, E> MyGrafo;
public:
	inline void ejecutarComando(const pair<string, vector<int> >& comando) {
		const string& str = comando.first;
		const vector<int>& argumentos = comando.second;

		if (str == "INSERTAR")
			MyGrafo.insertarNodo(argumentos.at(0));
	}
};

static size_t basura = 0;
enum direccion {
	BiDir = 0,
	Dir = 1
};
int main()
{
	Grafo<char, int> grafo;
	grafo.insertarNodo('A', 'B', 'C', 'D', 'E', 'X');
	grafo.insertarEnlace('A', 'B', 2, Dir);
	grafo.insertarEnlace('A', 'C', 3, Dir);
	grafo.insertarEnlace('B', 'C', 2, BiDir);
	grafo.insertarEnlace('B', 'D', 6, Dir);
	grafo.insertarEnlace('C', 'D', 7, Dir);
	grafo.insertarEnlace('C', 'E', 6, Dir);
	grafo.insertarEnlace('D', 'X', 7, Dir);
	grafo.insertarEnlace('D', 'E', 3, Dir);

	grafo.imprimir();
	if (!grafo.Dijktra('C', 'X')) {
		cout << "No hay camino" << endl;
	}
	system("pause");
	return 0;
}