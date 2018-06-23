#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;
template<typename G>
struct Nodo{
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
	set<Arista*> ArApuntYRecibidas;
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
struct Arista{
	using Nodo = typename G::Nodo;
	using E = typename G::Weight;
	E peso;
	bool dir;      
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
	if (nodos[0]->existe && nodos[1]->existe) {
		nodos[0]->eliminarAristaApuntadayRecibida(this);
		nodos[1]->eliminarAristaApuntadayRecibida(this);
	}
	else {                          
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
	Nodo* buscarNodo(const N& contenido, size_t& pos = nada) const;
public:
	Grafo() = default;
	~Grafo();

	bool insertarNodo(const N& n);
	template<typename... Args>
	bool insertarNodo(const N& n, Args... otrosParametros);
	bool removerNodo(const N& cont_arista);

	bool InsAri(const N& contenido_a, const N& contenido_b, E peso);
	bool removerEnlace(const N& contenido_a, const N& contenido_b);
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
	for_each(universoNodos.begin(), universoNodos.end(), [](Nodo* nodo) {delete nodo; });
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
bool Grafo<N, E>::removerNodo(const N& cont_arista) {
	size_t pos = 0;
	delete buscarNodo(cont_arista, pos);

	auto kill = universoNodos.begin();
	advance(kill, pos);
	universoNodos.erase(kill);

	return true;
}

template<typename N, typename E>
bool Grafo<N, E>::InsAri(const N& contenido_a, const N& contenido_b, E peso) {
	Nodo* Nodo_A = buscarNodo(contenido_a);
	Nodo* Nodo_B = buscarNodo(contenido_b);
	if (!Nodo_A || !Nodo_B) return false; //Si no encuentra un nodo

	Arista* nuevaArista = new Arista(Nodo_A, Nodo_B, peso, 0);
	if (!nuevaArista) return false;

	Nodo_A->agregarAristaApuntada(nuevaArista);
	Nodo_B->agregarAristaRecibida(nuevaArista);
	Nodo_B->agregarAristaApuntada(nuevaArista);
	Nodo_A->agregarAristaRecibida(nuevaArista);
	return true;
}

template<typename N, typename E>
bool Grafo<N, E>::removerEnlace(const N& contenido_a, const N& contenido_b)
{
	Nodo* Nodo_A = buscarNodo(contenido_a);
	Nodo* Nodo_B = buscarNodo(contenido_b);
	if (!Nodo_A || !Nodo_B) return false;
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
	return false;
}

template<typename N, typename E>
void Grafo<N, E>::imprimir() const {
	for (Nodo* itrNodos : universoNodos) {
		cout << itrNodos->dato << "->";
		for (Arista* itrAristas : itrNodos->aristasApuntadas) {
			cout << itrAristas->peso << '(' << itrAristas->nodos[noEsEsteNodo(itrNodos, itrAristas)]->dato << "), ";
		}
		cout << "\b\b  \n";
	}
}

template<typename N, typename E>
bool Grafo<N, E>::Dijktra(const N& cont_nodoOrigen, const N& cont_nodoDestino)
{
	for_each(universoNodos.begin(), universoNodos.end(), [](Nodo* nodo) {nodo->distancia = INT_MAX; });
	Nodo* nodoOrigen = buscarNodo(cont_nodoOrigen);
	Nodo* nodoDestino = buscarNodo(cont_nodoDestino);
	if (!nodoOrigen || !nodoDestino) return false;
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
			if (ctn.currentNodo == nodoDestino) {
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
}static size_t nada = 0;

int main()
{
	Grafo<char, int> G;
	cout << "Ingrese el numero de vertices :" << endl;
	int ver; cin >> ver;
	cout << "Ingrese el numero de aristas :" << endl;
	int ari; cin >> ari;
	// LO DE WIKIPEDIA :V
	/*
	G.insertarNodo('0', '1', '2', '3', '4', '5'); //6
	G.InsAri('0', '1', 7);                        //9
	G.InsAri('0', '5', 14);
	G.InsAri('0', '2', 9);
	G.InsAri('1', '2', 10);
	G.InsAri('1', '3', 15);
	G.InsAri('2', '5', 2);
	G.InsAri('2', '3', 11);
	G.InsAri('3', '4', 6);
	G.InsAri('4', '5', 9);
	*/
	char letra;
	for (int i = 0; i < ver; i++) {
		letra = '0' + i;
		G.insertarNodo(letra);
		//cout << "letra: " << letra << endl;
	}
	char ini;
	char fin;
	int peso;
	for (int i = 0; i < ari; i++) {
		cout << "Inserte el inicio, fin y peso de la arista: " << endl;
		cin >> ini >> fin >> peso;
		G.InsAri(ini,fin,peso);
	}
	//G.imprimir();
	cout << "Escriba los nodos que desea saber su camino: " << endl;
	cin >> ini >> fin;
	if (!G.Dijktra(ini, fin)) { cout << "No hay camino" << endl; }
	system("pause");
	return 0;
}