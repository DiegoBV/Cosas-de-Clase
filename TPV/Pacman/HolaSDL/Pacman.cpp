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
	iniX = posX;
	iniY = posY;
	rectDest.x = posX * game->dame_Anchura()/ game->dame_ColumnasTablero();
	rectDest.y = posY * game->dame_Altura()/ game->dame_FilasTablero();
	rectDest.w = game->dame_Anchura() / game->dame_FilasTablero(); //establece anchura y altura del fantasma
	rectDest.h = game->dame_Altura() / game->dame_ColumnasTablero();
	dirX = dirY = nX = nY = 0;
	this->textura->ModificaRectangulo(0, 10);
}
bool Pacman::siguiente_Dir(int dX, int dY) { //si pulsas una tecla, se guarda la nueva direccion, si no, se mantiene la antigua
	nX = dX;
	nY = dY;
	return (!game->comprueba_Muro(posY + nY, posX + nX));
}
void Pacman::render() {//pinta la textura correcta
	this->textura->RenderFrame(game->dame_Renderer(), rectDest);
}

void Pacman::comer() { //comrpueba si la casilla en la que estas es comida o vitamina, si lo es, la cambia por casilla vacia
	if (game->consulta(posY, posX) == Food || game->consulta(posY, posX) == Vitamins) {
		game->come(posY, posX);
	}
	//habr� que hacer que si es vitamina pues se llame al m�todo que haga algo a los fantasmas
}

void Pacman::modifica_Rectangulo() { //modifica el rectangulo destino, asignandole la x y la y multiplicandolo por las medidas del tablero
	this->rectDest.y = this->posY * game->dame_Altura() / game->dame_FilasTablero();
	this->rectDest.x = this->posX * game->dame_Anchura() / game->dame_ColumnasTablero();
}

void Pacman::donut() { //hace las comprobaciones para el movimiento toroidal
	if (posY < 0) {
		posY = game->dame_FilasTablero() - 1;
	}
	if (posY >= game->dame_FilasTablero()) {
		posY = 0;
	}
	if (posX < 0) {
		posX = game->dame_ColumnasTablero() - 1;
	}
	if (posX >= game->dame_ColumnasTablero()) {
		posX = 0;
	}
}
void Pacman::mueve_Pacman() {
	if (siguiente_Dir(nX, nY)) { //si con la nueva direccion que pulsaste puede moverse... (aqui se hace lo de la memoria del movimiento)
		dirX = nX;
		dirY = nY;  //asigna la nueva direccion a la actual y se mueve en esa direccion
		posX += dirX;
		posY += dirY;
	}
	else {  //si no, comprueba que no haya muro y se sigue moviendo en la direccion antigua
		if (!game->comprueba_Muro(this->posY + dirY, this->posX + dirX)) {
			posX += dirX;
			posY += dirY;
		}
	}
	donut();
	modifica_Rectangulo();
	animar();
}

void Pacman::animar() {
	int filaSheet; //indica la fila donde animar (0, 1, 2, 3)
	if (this->dirX == 1) {
		filaSheet = 0;
	}
	else if (this->dirX == -1) {
		filaSheet = 2;
	}
	else if (this->dirY == 1) {
		filaSheet = 1;
	}
	else {
		filaSheet = 3;
	}
	this->textura->Anima(100, filaSheet, 10, 1, 2);
}

void Pacman::update() {
	mueve_Pacman();
	comer();
	this->render();
}

int Pacman::dame_IniX() {
	return this->iniX;
}

int Pacman::dame_IniY() {
	return this->iniY;
}





