//Alejandro Mar�n P�rez / Diego Baratto Valdivia (2� Videojuegos)
#include "Game.h"
using namespace std;

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game juego; //Debe haber alg�n problema con esto porque el puntero da nulo
	juego.menu();
	SDL_Quit();
	return 0;
}