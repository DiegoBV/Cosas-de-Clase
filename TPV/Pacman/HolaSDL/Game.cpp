#include "Game.h"



Game::Game()
{
	window = nullptr;
	renderer = nullptr;
	winWidth = 870;
	winHeight = 644;
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;
	this->path = "..\\images\\textura";
	//Inicializaci�n del sistema y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Texturas
	//texts[0] = vitaminas, texts[1] = muro, texts[2] = comida, texts[3] = spritesheet
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			texts[i] = new Texture(renderer, path + to_string(i) + ".png", 1, 4); //vitamina animada
		}
		else if (i == 3) {
			texts[i] = new Texture(renderer, path + to_string(i) + ".png", 4, 14); //carga las texturas de todos los personajes
		}
		else {
			texts[i] = new Texture(renderer, path + to_string(i) + ".png", 1, 1);
		}
	}

	//FrameRate
	this->frameRate = 120; //a + alto, + lento
	
}


Game::~Game() //destruye el renderer y la ventana
{	
	//Finalization
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	delete map; //borra el mapa
	for (int i = 0; i < 4; i++) {
		delete texts[i]; //bora cada una de las texturas creadas
	}
}

void Game::carga_Archivo(string name){
	int fils, cols;

	archivo.open(name);

	if (archivo.is_open()){
		archivo >> fils >> cols;
		this->filasTablero = fils;
		this->colsTablero = cols;
		map = new GameMap(fils, cols, texts[0], texts[1], texts[2], this);
		for (int i = 0; i < fils; i++){
			for (int j = 0; j < cols; j++){
				int pos;
				archivo >> pos;
				if (pos < 4) {
					map->modifica_Posicion(i, j, (MapCell)pos);
					if (pos == 2 || pos == 3) {
						setComida(1); //si es comida o vitamina aumentamos en 1 el numComida
					}
				}
				else if (pos == 9) {
					map->modifica_Posicion(i, j, Empty);
					pacman = Pacman(i, j, texts[3], this);
				}
				else if (pos != 4) {
					fantasmas[pos - 5] = Ghost(renderer, "..\\images\\characters1.png", i, j, pos, texts[3], this);
					map->modifica_Posicion(i, j, Empty);
				}
			}
		}
		archivo.close();
	}
}

void Game::pinta_Mapa() {
	map->render_Mapa();
}

bool Game::siguiente_casilla (int &X, int &Y, int dirX, int dirY) {
	//Primero calculamos la casilla siguiente
	int tempX = X + dirX;
	int tempY = Y + dirY;

	//Comprueba el tipo de casilla que es
	MapCell casilla = map->getCell(tempY, tempX);

	//Miramos si puede mover
	if (casilla != Wall) {
		X += dirX;
		Y += dirY;
		return true;
	}
	else
		return false;
}

void Game::setComida(int a) {
	numComida += a;
}

void Game::come(int x, int y) { //modifica la posicion a empty y reduce el numero de comida en 1
	if (map->getCell(x, y) == Vitamins){
		vitaminas = true;
		vitaminasTiempo = 30;
	}
	map->modifica_Posicion(x, y, Empty);
	setComida(-1);
}

MapCell Game::consulta(int x, int y) {
	return map->getCell(x, y);
}

bool Game::win() { //comprueba si se ha comido todo e.e
	return (numComida == 0);
}

void Game::handle_Events() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			exit = true;
		}
		else {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_RIGHT) {
					pacman.siguiente_Dir(1, 0);  //si es derecha le pasa la direccion derecha(1,0) y as� con todas las direcciones
				}
				else if (event.key.keysym.sym == SDLK_UP) {
					pacman.siguiente_Dir(0, -1);
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					pacman.siguiente_Dir(0, 1);
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					pacman.siguiente_Dir(-1, 0);
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE) {
					exit = true; //a�adido de si le das a escape sales tambien
				}
				else if (event.key.keysym.sym == SDLK_g) { //guardar partida
					this->guarda_Partida();
				}
			}
		}
	}
}

void Game::run() {
	while (!this->win() && !this->dame_exit()) {
		delay();
		tiempo_Vitamina(); //tiempo que los fantasmas est�n asustados
		SDL_RenderClear(renderer); //limpia el render
		comprueba_colisiones(pacman.posX, pacman.posY); //comprueba que los fantasmas y pacman se han o no chocado
		update_Fantasmas(); //update de los 4 fantasmas
		pacman.update(); //update del pacman
		animaciones_Extra(); //anima las vitaminas
		handle_Events(); //controla los eventos de teclado
		pinta_Mapa();   //pinta el tablero
		SDL_RenderPresent(renderer); //plasma el renderer en pantalla
	}
}

bool Game::comprueba_colisiones(int x, int y){
	for (int i = 0; i < 4; i++){
		if (fantasmas[i].posActX == y && fantasmas[i].posActY == x){
			if (vitaminas){
				fantasmas[i].muerte();
			}
			else{
				exit = true;
			}
		}
	}

	return exit;
}

//los gets de altura, anchura, renderer...
int Game::dame_Altura() {
	return this->winHeight;
}

int Game::dame_Anchura() {
	return this->winWidth;
}

int Game::dame_FilasTablero() {
	return this->filasTablero;
}

int Game::dame_ColumnasTablero() {
	return this->colsTablero;
}

bool Game::dame_exit() {
	return this->exit;
}
SDL_Renderer* Game::dame_Renderer() {
	return this->renderer;
}

void Game::delay() { //hace lo del Delay m�s eficiente
	startTime = SDL_GetTicks();
	frameTime = SDL_GetTicks() - startTime; 
	if (frameTime < frameRate) {
		SDL_Delay(frameRate - frameTime);
	}
}

int Game::obtenerPixelX(int posicion){
	return (winWidth / colsTablero) * posicion;
}

void Game::animaciones_Extra() {
	this->texts[0]->Anima(500, 0, 0, 1, 4); //anima las vitaminas fancy
}

int Game::obtenerPixelY(int posicion){
	return (winHeight / filasTablero) * posicion;
}

void Game::tiempo_Vitamina() { //temporizador vitaminas
	if (vitaminasTiempo > 0)
		vitaminasTiempo--;
	else
		vitaminas = false;
}

void Game::update_Fantasmas() { //update de todos los fantsasmas
	for (int i = 0; i < 4; i++) {
		fantasmas[i].update(vitaminas);
	}
}

void Game::menu() { //menu simple desde consola
	string eleccion;
	do {
		cout << "PACMAN!!!" << endl << "Cargar partida[c] o Nueva Partida[n]";
		cin >> eleccion;

		if (eleccion == "c") {
			this->carga_Archivo("..\\partidaGuardada.txt"); //no se controla que no exista el archivo
		}
		
	} while (eleccion != "c" && eleccion != "n");

	if (eleccion == "n") {
		cout << "Elige nivel [1 - 5]" << endl;
		cin >> eleccion;
		this->carga_Archivo("..\\level0" + eleccion + ".dat");
	}

}

void Game::guarda_Partida() {
	bool noEscribir = false; //para no sobreescribir
	partidaGuardada.open("..\\partidaGuardada.txt");
	if (partidaGuardada.is_open()) {
		partidaGuardada << this->dame_FilasTablero() << " " << this->dame_ColumnasTablero();
		partidaGuardada << endl;

		for (int i = 0; i < this->dame_FilasTablero(); i++) {
			for (int j = 0; j < this->dame_ColumnasTablero(); j++) {
				for (int r = 0; r < 4; r++) { //esto se podria hacer mejor. Recorre todos los fantasmas buscando la posIniX y la posIniY y los coloca en el archivo
					if (fantasmas[r].posInX == i && fantasmas[r].posInY == j) {
						partidaGuardada << r + 5 << " ";
						noEscribir = true; //si se pone a true, no puede sobreescribir
					}
				}
				if (pacman.dame_IniY() == i && pacman.dame_IniX() == j) { //coloca a Pacman en su posicion original
					partidaGuardada << 9 << " ";
				}
				else {
					if (!noEscribir)//si ningun fantasma se ha escrito, escribe la posicion adecuada
						partidaGuardada << (int)this->consulta(i, j) << " ";
				}
				noEscribir = false;
			}
			partidaGuardada << endl;
		}
	}
	partidaGuardada.close();
}