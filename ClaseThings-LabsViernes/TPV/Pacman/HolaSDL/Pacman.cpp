#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(): GameCharacter(){}


Pacman::~Pacman()
{
}

Pacman::Pacman(int posY, int posX, Texture* text, Game* gam): GameCharacter(posX, posY, text, gam), vidas(3){
	nuevaDir.dirX = 0;
	nuevaDir.dirY = 0;
} //contructora con par�metros


bool Pacman::siguiente_Dir(int dX, int dY) { //si pulsas una tecla, se guarda la nueva direccion, si no, se mantiene la antigua
	nuevaDir.dirX = dX;
	nuevaDir.dirY = dY;
	int tempX = posActX;
	int tempY = posActY;
	return (game->siguiente_casilla(tempX, tempY, nuevaDir.dirX, nuevaDir.dirY));
}

void Pacman::render() {//pinta la textura correcta
	this->animar();
	GameCharacter::render();
}

void Pacman::comer() { //comrpueba si la casilla en la que estas es comida o vitamina, si lo es, la cambia por casilla vacia
	if (game->consulta(posActY, posActX) == Food || game->consulta(posActY, posActX) == Vitamins) {
		game->come(posActY, posActX);
	}
}

void Pacman::modifica_Rectangulo() { //modifica el rectangulo destino, asignandole la x y la y multiplicandolo por las medidas del tablero
	rectDest.y = posActY * game->dame_Altura() / game->dame_FilasTablero();
	rectDest.x = posActX * game->dame_Anchura() / game->dame_ColumnasTablero();
}

void Pacman::mueve_Pacman() {
	if (siguiente_Dir(nuevaDir.dirX, nuevaDir.dirY)) { //si con la nueva direccion que pulsaste puede moverse... (aqui se hace lo de la memoria del movimiento)
		actualDir.dirX = nuevaDir.dirX;
		actualDir.dirY = nuevaDir.dirY;
	}

	game->siguiente_casilla(posActX, posActY, actualDir.dirX, actualDir.dirY);

	donut();
	modifica_Rectangulo();
}

void Pacman::update() {
	if (!game->comprueba_colisiones(posActX, posActY)){
		mueve_Pacman();
		comer();
	}
}

void Pacman::reduceVidas() {
	vidas--;
}

bool Pacman::he_Muerto() {
	return (vidas == 0);
}

void Pacman::animar() {
	GameCharacter::animar(IniText, TextsFils, ColsText);
}

void Pacman::loadFromFile(ifstream& file) {
	GameCharacter::loadFromFile(file);
	int aux; //para saber si el archivo acaba o no
	file >> aux;
	if (file.fail()) {
		file.clear();
	}
	else {
		vidas = aux;
	}
}

void Pacman::saveToFile(ofstream& file) {
	GameCharacter::saveToFile(file);
	file << this->vidas;
}

void Pacman::render(bool) {
}

int Pacman::dame_Vidas(){
	return this->vidas;
}

int Pacman::ghostType() {
	return 0;
}

bool Pacman::reproduce(){
	return false;
}

bool Pacman::dead(){
	return false;
}




