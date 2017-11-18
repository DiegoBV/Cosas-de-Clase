#include "GameMap.h"
#include "Game.h"

/* Esto es una cosa opcional, luego vemos si lo metemos o no xD
class GameMap(){
	friend class Game; La clase Game puede acceder a los atributos privados de GameMap
}
*/

GameMap::GameMap() //Crea un tablero con un array din�mico
{	
}
GameMap::GameMap(int fils, int cols, Texture* vit, Texture* m, Texture* com, Game* gam) { //Constructora con par�metros
	textsMapa[0] = m;
	textsMapa[1] = com; //asignacion de punteros
	textsMapa[2] = vit;
	game = gam;
	if (fils != 0 && cols != 0) {
		this->fils = fils;
		this->cols = cols;

		//Creaci�n de la matriz
		tablero = new MapCell*[fils]; //Es una matriz de punteros, para referenciar las casillas
		for (int r = 0; r < fils; r++) {
			tablero[r] = new MapCell[cols]; //Ahora s� son arrays din�micos completos
		}
	}
	else {
		tablero = nullptr;
	}
}
/*
//////////
Alternativa
//////////

En vez de hacer un array de punteros a arrays din�micos, se hace todo en un mismo array din�mico
MapCell* celdas; //Esto en el .h

Contructora:
GameMap(int fils, int cols){
	celdas = new MapCell[fils*cols];
}

Destructora:
~GameMap(){
	delete[] celdas;
}

Acceso:
MapCell getCell(int fila, int columna){
	return celdas [fils*cols + columna]; //Esto no lo entiendo muy bien xD Habr�a que revisarlo
}

*/

GameMap::~GameMap()  //Destructora por defecto del tablero de juego, destruye el array din�mico
{
	if (tablero != nullptr) {
		for (int r = 0; r < fils; r++) {
			delete[] tablero[r];
		}
		delete[] tablero;
	}
}
MapCell GameMap::getCell(int fils, int cols) {
	if (fils < game->dame_FilasTablero() && fils >= 0 && cols < game->dame_ColumnasTablero() && cols >= 0) 
		return tablero[fils][cols];
}

void GameMap::modifica_Posicion(int x, int y, MapCell nuevoObjeto) {
	tablero[x][y] = nuevoObjeto;
}

void GameMap::render_Mapa() {
	for (int i = 0; i < fils; i++) {
		for (int j = 0; j < cols; j++) {
			SDL_Rect des;
			des.x = j * game->dame_Anchura() / cols;
			des.y = i * game->dame_Altura() / fils;
			des.w = game->dame_Anchura() / cols;
			des.h = game->dame_Altura() / fils;
			if ((int)tablero[i][j] > 0) {
				textsMapa[(int)tablero[i][j] - 1]->RenderFrame(game->dame_Renderer(), des); //para ahorrarse el switch, cambiamos a entero la pos del 
				//tablero y le mandamos que haga render
			}
		}
	}
}
