#pragma once
#include "Texture.h"
#include "SDL.h"
#include "GameObject.h"

using namespace std;
enum MapCell { Empty, Wall, Food, Vitamins };
class GameMap: public GameObject
{
private:
	MapCell** tablero; //Matriz din�mica para el tablero
	Texture* textsMapa[3]; //array con las 3 texturas del mapa -> vitaminas, muros, comida
	void vector_Dinamico();
public:
	GameMap();
	GameMap(Game* game);
	~GameMap();
	GameMap(int fils, int cols, Texture* vit, Texture* m, Texture* com, Game* gam);//constructora con par�metros
	int fils;
	int cols;
	MapCell getCell(int fils, int cols); //devuelve una celda
	void modifica_Posicion(int x, int y, MapCell nuevoObjeto);
	virtual void loadFromFile(ifstream& file);
	virtual void render();
	virtual void render(bool);
	virtual void update();
	virtual void saveToFile(ofstream& file);
};

