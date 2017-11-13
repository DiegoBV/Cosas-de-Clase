#pragma once
#include "Texture.h"
#include "SDL.h"

using namespace std;
enum MapCell { Empty, Wall, Food, Vitamins };
class Game;
class GameMap
{
private:
	int fils;
	int cols;
	MapCell** tablero2; //Matriz din�mica para el tablero
	Texture* vitamina;
	Texture* muro;
	Texture* comida;
	Game* game;

public:
	GameMap();
	~GameMap();
	GameMap(int fils, int cols, Texture* vit, Texture* m, Texture* com, Game* gam);//constructora con par�metros
	MapCell getCell(int fils, int cols); //devuelve una celda
	void modifica_Posicion(int x, int y, MapCell nuevoObjeto);
	void render_Mapa();
	void destruir_Mapa();
};

