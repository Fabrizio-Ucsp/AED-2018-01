#include "game.h"
void iniciar_cartas(){
	Cards_List<int> List;
	cout << "Inicio" << endl;
	List.CrearCartas();
	List.Print();
	cout << "Primera impresion" << endl;
	List.Barajear();
	List.Barajear();
	List.Print();
	List.Print_palo("Corazon");
	List.Print_palo("Espada");
	List.Print_palo("Coco");
	List.Print_palo("Trebol");
	cout << "Fin" << endl;
}

void mostrar_reglas() {
	system("cls");
	cout << "Estas son las reglas: " << endl;
	cout << "Si quieres deshacerte de una carta en tu mano" << endl;
	cout << "debes emparejarla con la clasificacion(4, 10, K, A…) o el palo(trebol, coco, corazon, espada)" << endl;
	cout << "de otra carta en la pila.Debes colocar la carta en la parte superior de la " << endl;
	cout << "pila de descarte y luego le tocará el turno al jugador a tu izquierda." << endl;
	cout << "En este juego, las cartas con número 8 son los comodines,se puede colocar en cualquier situacion." << endl;
	cout << "pero eso si,el jugador tiene que poner cualquier carta tambien pero ya empezar de nuevo con la regla de emparejamiento" << endl;
	cout << "La carta 'J' permite cambiar la direccion en la que se entragan las cartas, asi que usalas sabiamente." << endl;
	cout << "Toma una carta de la pila si no tienes ninguna en tu mano que puedas jugar." << endl;
	cout << "El ganador es aquel que se queda sin cartas" << endl;
	cout << "Cuando la pila de la baraja se quede sin cartas se contara una puntuacion por jugador" << endl;
	cout << "Las cartas con números (incluyendo los ases) valen lo mismo que su denominación, mientras que las figuras (J, Q, K) valen 10 puntos " << endl;
	cout << "cada una y las cartas con número 8 son realmente 'locas', ya que valen 50 puntos." << endl;
	cout << "Si un jugador se queda sin cartas, se termina la partida. Todos los jugadores deben calcular la puntuación de las cartas que aún tengan " << endl;
	cout << "en la mano.El jugador que haya ganado la partida suma el total de la puntuación final de cada jugador a su propia puntuación." << endl;
	cout << "Baraja las cartas y continúa el juego hasta que un jugador alcance la meta en cuanto a la puntuación o la supere.La cantidad de jugadores" << endl;
	cout << "determinará la meta de la puntuación.Después de cada partida, se vuelven a barajar las cartas y el juego sigue hasta que un jugador alcance " << endl;
	cout << "alguna de las siguientes puntuaciones o la supere : " << endl;
	cout << "100 puntos(2 jugadores)" << endl;
	cout << "150 puntos(3 jugadores)" << endl;
	cout << "200 puntos(4 jugadores)" << endl;
	system("pause");
	system("cls");
}
int main(){
	Game<int> Juego;
	int menu_item = 1;

	while (menu_item != 0) {
		cout << "  _____   ___      _______  _______  _______  _______" << endl;
		cout << " |  _  | |   |    |       ||       ||       ||       |" << endl;
		cout << " | |_| | |   |    |   _   ||       ||   _   ||  _____|" << endl;
		cout << "|   _   ||   |    |  | |  ||       ||  | |  || |_____" << endl;
		cout << "|  | |  ||   |___ |  |_|  ||      _||  |_|  ||_____  |" << endl;
		cout << "|  |_|  ||       ||       ||     |_ |       | _____| |" << endl;
		cout << "|_______||_______||_______||_______||_______||_______|" << endl;
		cout << "Presione 1 para iniciar el juego" << endl;
		cout << "Presion 2 para mostrar las reglas del juego" << endl;
		cout << "Presione 0 para salir" << endl;
		cin >> menu_item;
		if (menu_item == 1) Juego.init_game();
		if (menu_item == 2) mostrar_reglas();
		if (menu_item == 0) { menu_item=0; };
	}

	return 0;
}