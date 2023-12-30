#include <iostream>
#include "VentanaSaloon.h"
#include "GUI.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"

#define CROUNDS 3 //Contador de rondas por oleada

using namespace sf;

int main(int argc, char* argv[]) {
	Game* x = new Game();
	GUI* menu = new GUI();
	int opc = 0;
	RenderWindow* w = new RenderWindow(VideoMode(800, 600), "Wild Gang");
	srand(time(NULL));
	do {
		opc = menu->mainMenu(w);
		switch (opc) {
		case 0: {
			x->resetGame();
			x->startGame(w);
		}break;
		case 1: {

		}break;
		}
	} while (opc != 1);
}