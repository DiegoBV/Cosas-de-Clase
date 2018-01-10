#include "Ghost.h"
#include "Game.h"


Ghost::Ghost(): GameCharacter() {} //constructora por defecto

Ghost::Ghost(int orX, int orY, int numFant, Texture* text, Game* gam, int type): GameCharacter(orX, orY, text, gam), numFantasma(numFant)
{	

	this->type = type; //Para que game sepa qu� tipo de fantasma es
	//Array con las posibles direcciones que puede tomar el fantasma
	//Rellenado con esas direcciones
	posiblesDirs[0].dirX = 0; //Arriba
	posiblesDirs[0].dirY = -1;
	posiblesDirs[1].dirX = 0; //Abajo
	posiblesDirs[1].dirY = 1;
	posiblesDirs[2].dirX = -1; //Izda
	posiblesDirs[2].dirY = 0;
	posiblesDirs[3].dirX = 1; //Dcha
	posiblesDirs[3].dirY = 0;

	actualDir.dirX = 0;  //Inicializamos de base hacia arriba, para probar cosas
	actualDir.dirY = 0;

	srand(time(nullptr));
}


Ghost::~Ghost()
{
}

void Ghost::update() {
	posibles.clear();
	game->siguiente_casilla(posActY, posActX, actualDir.dirX, actualDir.dirY);

	donut();

	cambiaDir();

	rectDest.x = game->obtenerPixelX(posActY);
	rectDest.y = game->obtenerPixelY(posActX);

}

void Ghost::render(bool vitamina) {
	if (vitamina){
		textura->ModificaRectangulo(0, 13);
	}
	else {
		textura->ModificaRectangulo(0, (this->numFantasma - 4) * 2); //modifica el rect�ngulo origen para dibujar el sprite adecuado...
	}

	animar(vitamina);

	GameCharacter::render();
}

int Ghost::posibles_Dirs() {
	int tempX;
	int tempY;
	int backward = 0;
	
	int j = 0; //Control del array de posibles

	//Exploramos las posibilidades 
	for (int i = 0; i < 4; i++) {
		tempX = posActY;
		tempY = posActX;

		if (actualDir.dirX == 0 && actualDir.dirY == 0){ //Para que se pueda iniciar
			posibles.push_back(i);
			j++;
		}
		else if ((posiblesDirs[i].dirX == (actualDir.dirX*-1)) && (posiblesDirs[i].dirY == (actualDir.dirY*-1))) { //Primero comprobamos que no es la dir contraria
			backward = i;
		}
		else if (game->siguiente_casilla(tempX, tempY, posiblesDirs[i].dirX, posiblesDirs[i].dirY)) { //Comprobamos que no hay muro
			posibles.push_back(i);
			j++;
		}
	}

	//Elecci�n de direccion
	if (j > 1) { //Hay m�s de una posici�n posible: escogemos una random
		return posibles[rand() % j];
	}
	else if (j == 1) { //S�lo hay una posibilidad, estamos en un pasillo
		return posibles[0];
	}
	else { //No hay posibilidades, callej�n sin salida, mueve atr�s
		return backward;
	}
}

void Ghost::cambiaDir() {
	int direction = -1;
	direction = posibles_Dirs();
	//posibles.clear();
	if (direction >= 0) { //Si puede cambiar de direccion ponemos la nueva direccion
		actualDir.dirX = posiblesDirs[direction].dirX;
		actualDir.dirY = posiblesDirs[direction].dirY;
	}
}

void Ghost::animar(bool vitamina){
	if (!vitamina){
		GameCharacter::animar((this->numFantasma - 4) * auxText, filsTex, colsTex);
	}
	else
	{
		filaSheet = 0;
		textura->Anima(100, filaSheet, posAsustado, filsTex, colsTex);
	}
}

void Ghost::saveToFile(ofstream& file) {
	file << "0" << " "; //guardamos el tipo del fantasma
	GameCharacter::saveToFile(file);
	file << endl;
}

int Ghost::ghostType() {
	return this->type;
}

bool Ghost::reproduce(){
	return false;
}

bool Ghost::dead(){
	return false;
}