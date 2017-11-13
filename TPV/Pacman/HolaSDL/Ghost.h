#pragma once
#include "Texture.h"
#include "SDL.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
//using namespace std;
class Game;
class Ghost
{
private:
	//Posicion inicial
	int posInX, posInY;

	//Posicion actual
	int posActX, posActY;

	//Direcci�n actual
	struct Dirs {
		int dirX;
		int dirY;
	};

	//N�mero Fantasma
	int numFantasma;

	Dirs posiblesDirs[4];
	Dirs actualDir;

	//Punteros
	//Textura
	Texture* textura;
	//Game (Para conocer el entorno)
	Game* juego;

	//Rect�ngulo para dibujarlo
	SDL_Rect rectDes;
	int posibles_Dirs();
	
	
public:
	Ghost();
	Ghost(SDL_Renderer* &renderer, string dirTextura, int orX, int orY, int numFant, Texture* text, Game* gam);
	~Ghost();


	//M�todos del juego
	void update(); //Actualiza la posici�n del fantasma en la direcci�n actual y 
				  //actualiza la direccion aleatoriamente
	void render(SDL_Renderer* &renderer); //Pinta el estado actual en pantalla
	void muerte(); //Muere y vuelve a la posici�n inicial
	void cambiaDir();
};

