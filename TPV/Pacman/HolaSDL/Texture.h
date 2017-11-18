#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

class Texture
{
private:
	SDL_Texture* textura;
	SDL_Rect rect; //Rect�ngulo de la textura
	int textH;   //Altura de la textura
	int textW;   //Anchura de la textura
	int filas;
	int columnas;
public:
	Texture(); //contructora por defecto
	Texture(SDL_Renderer* &renderer, string filename, int fils, int cols);//crea la textura a partir del archivo
	~Texture();
	void ModificaRectangulo(int fil, int col); //modifica el rectangulo origen
	void Render(SDL_Renderer* rnd, SDL_Rect dest); //render fondo
	void RenderFrame(SDL_Renderer* rnd, SDL_Rect dest); //render un frame esp�cifico
	void Anima(int veloc, int posInicialX, int posInicialY,int fil, int col);//anima la textura, hay q modificarlo
};

