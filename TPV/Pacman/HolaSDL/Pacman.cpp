#include "Pacman.h"
#include "Game.h"

Pacman::Pacman()
{
}


Pacman::~Pacman()
{
}

Pacman::Pacman(int posY, int posX, Texture* text, Game* gam) { //contructora con par�metros
	this->game = gam; //asignacion de punteros a juego y textura
	this->textura = text;
	this->posX = posX;
	this->posY = posY;  //establece coordenadas y crea el rectangulo destino inicial
	rectDest.x = posX * game->dame_Anchura()/ game->dame_FilasTablero();
	rectDest.y = posY * game->dame_Altura()/ game->dame_ColumnasTablero();
	rectDest.w = game->dame_Anchura() / game->dame_FilasTablero(); //establece anchura y altura del fantasma
	rectDest.h = game->dame_Altura() / game->dame_ColumnasTablero();
	dirX = dirY = nX = nY = 0;
}
bool Pacman::siguiente_Dir(int dX, int dY) { //si pulsas una tecla, se guarda la nueva direccion, si no, se mantiene la antigua
	nX = dX;
	nY = dY;
	return (!game->comprueba_Muro(posY + nY, posX + nX));
}
void Pacman::render() {//pinta la textura correcta
	this->textura->ModificaRectangulo(0, 10);
	this->textura->RenderFrame(game->dame_Renderer(), rectDest);
}

void Pacman::comer() { //comrpueba si la casilla en la que estas es comida o vitamina, si lo es, la cambia por casilla vacia
	if (game->consulta(posY, posX) == Food || game->consulta(posY, posX) == Vitamins) {
		game->come(posY, posX);
	}
	//habr� que hacer que si es vitamina pues se llame al m�todo que haga algo a los fantasmas
}

void Pacman::modifica_Rectangulo() { //modifica el rectangulo destino, asignandole la x y la y multiplicandolo por las medidas del tablero
	this->rectDest.y = this->posY * game->dame_Altura() / game->dame_ColumnasTablero();
	this->rectDest.x = this->posX * game->dame_Anchura() / game->dame_FilasTablero();
}
void Pacman::elige_Direccion() {
	if (siguiente_Dir(nX, nY)) { //si con la nueva direccion que pulsaste puede moverse... (aqui se hace lo de la memoria del movimiento)
		dirX = nX;
		dirY = nY;  //asigna la nueva direccion a la actual y se mueve en esa direccion
		posX += dirX;
		posY += dirY;
		modifica_Rectangulo();
	}
	else {  //si no, comprueba que no haya muro y se sigue moviendo en la direccion antigua
		if (!game->comprueba_Muro(this->posY + dirY, this->posX + dirX)) {
			posX += dirX;
			posY += dirY;
			modifica_Rectangulo();
		}
	}
}

void Pacman::update() {
	elige_Direccion();
	comer();
	this->render();
}




