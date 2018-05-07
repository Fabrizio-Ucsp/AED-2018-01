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
	cout << "Estas son las reglas" << endl;

}
int main(){
	Game<int> Juego;
	int menu_item = 1;

	while (menu_item !=0) {
		cout << "Presione 1 para iniciar el juego" << endl;
		cout << "Presion 2 para mostrar las reglas del juego" << endl;
		cout << "Presione 0 para salir" << endl;
		cin >> menu_item;
		if (menu_item == 1) Juego.init_game();
		if (menu_item == 2) mostrar_reglas();
	}

	



	char end;
	cin >> end;
	return 0;
}