#pragma once
#include "SDL.h"
#include "Texture.h"
#include "GameMap.h"
class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int winWidth;
	int winHeight;
	int winX, winY;
	Texture muro; //deberia ser un array, esto es pa probar
	Texture com;
	Texture vitam;
	MapCell** tab;
	GameMap map;
public:
	Game();
	~Game();
	void pinta_Mapa();
};

 
