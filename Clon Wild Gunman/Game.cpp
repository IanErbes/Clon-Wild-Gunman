#include "Game.h"
#define CROUNDS 5

Game::Game() {
	points = 0, lives = 3, timePerRound = 5, rounds = 0, wave = 0, round = 0;

	gameOver = false;

	/*Carga de la tipografia*/
	if (!font.loadFromFile("Biondeggiare.otf")) {
		std::cout << "Error al cargar la fuente" << std::endl;
	}

	/*Carga de los sonidos*/
	//Sonido del arma
	if (!bufferShotSound.loadFromFile("audio/Disparo.wav")) {
		std::cout << "\nNo se pudo cargar el archivo: Disparo.wav\n" << std::endl;
	}
	shotSound.setBuffer(bufferShotSound);

	//Sonido de las puertas de la ventana
	if (!bufferSoundDoor.loadFromFile("audio/PuertaAbierta.wav")) {
		std::cout << "\nNo se pudo cargar el archivo: PuertaAbierta.wav\n" << std::endl;
	}
	doorSound.setBuffer(bufferSoundDoor);

	if (!bufferMusic.loadFromFile("audio/InGame.wav")) {
		std::cout << "\nNo se pudo cargar el archivo: InGame.wav\n" << std::endl;
	}
	musicSound.setBuffer(bufferMusic);
	musicSound.setLoop(true);

	/*Configuracion de la ventana de juego*/

	/*Configuracion de los objetos 'window'*/
	window[0] = new VentanaSaloon(51, 40);
	window[1] = new VentanaSaloon(552, 40);
	window[2] = new VentanaSaloon(302, 40);
	

	window[0]->setWindowStatus();
	window[1]->setWindowStatus();
	window[2]->setWindowStatus();
	

	/*Configuracion de la imagen de fondo y la del cursor*/
	if (!cursorTexture.loadFromFile("imagenes/mira.png")) {
		std::cout << "\nNo se pudo cargar el archivo: mira.png\n" << std::endl;
	}
	cursor.setTexture(cursorTexture);
	cursor.setPosition(0, 0);

	if (!background.loadFromFile("imagenes/saloon.png")) {
		std::cout << "\nNo se pudo cargar el archivo: saloon.png\n" << std::endl;
	}
	bg.setTexture(background);

	/*Configuracion de los textos del juego*/
	//Fuente
	textScore.setFont(font);
	textLives.setFont(font);
	textwave.setFont(font);
	textRound.setFont(font);
	textGameOver.setFont(font);

	//Tamano
	textScore.setCharacterSize(30);
	textLives.setCharacterSize(30);
	textwave.setCharacterSize(30);
	textRound.setCharacterSize(30);
	textGameOver.setCharacterSize(100);

	//Color
	textScore.setFillColor(sf::Color::White);
	textLives.setFillColor(sf::Color::White);
	textwave.setFillColor(sf::Color::White);
	textRound.setFillColor(sf::Color::White);
	textGameOver.setFillColor(sf::Color::Red);

	//Estilo
	textScore.setStyle(sf::Text::Bold);
	textLives.setStyle(sf::Text::Bold);
	textwave.setStyle(sf::Text::Bold);
	textRound.setStyle(sf::Text::Bold);
	textGameOver.setStyle(sf::Text::Bold);

	//Texto
	var = "Puntaje: " + std::to_string(points);
	textScore.setString(var);
	var = "Vidas: " + std::to_string(lives);
	textLives.setString(var);
	var = "Oleada: " + std::to_string(wave + 1);
	textwave.setString(var);
	var = "ROUND: " + std::to_string(round + 1);
	textRound.setString(var);
	var = " ";
	textGameOver.setString(var);

	//Posicion
	textScore.setPosition(10, 500);
	textLives.setPosition(10, 530);
	textwave.setPosition(10, 560);
	textRound.setPosition(370, 550);
	textGameOver.setPosition(250, 200);

	//Propiedades de inicio del juego
	timeOfRound = 0;
}

void Game::startGame(RenderWindow* w) {
	musicSound.play();
	timeOfRound = clock();
	while (w->isOpen() && !gameOver) {
		Event e;
		//Actualizacion de nivel
		if (rounds == CROUNDS) {
			rounds = 0;
			round++;
			levelUp(round, w);
			window[0]->resetWindow();
			window[1]->resetWindow();
			window[2]->resetWindow();
			doorSound.play();
			timeOfRound = clock();
			if (timePerRound != 1) {
				timePerRound--;
			}
		}
		if (lives <= 0) {
			gameOver = true;
		}
		if (points < 0) {
			points = 0;
		}
		//Control de eventos
		while (w->pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed: {
				musicSound.stop();
				w->close();
			}break;
			case sf::Event::MouseMoved: {
				cursor.setPosition((float)e.mouseMove.x, (float)e.mouseMove.y);
			}break;
			case sf::Event::MouseButtonPressed: {
				if (window[0]->getIsOpen() && window[0]->getSprite().getGlobalBounds().intersects(cursor.getGlobalBounds())) {
					shotSound.play();
					window[0]->shot(&points, &lives);
				}
				if (window[1]->getIsOpen() && window[1]->getSprite().getGlobalBounds().intersects(cursor.getGlobalBounds())) {
					shotSound.play();
					window[1]->shot(&points, &lives);
				}
				if (window[2]->getIsOpen() && window[2]->getSprite().getGlobalBounds().intersects(cursor.getGlobalBounds())) {
					shotSound.play();
					window[2]->shot(&points, &lives);
				}
			}break;
			}

		}
		//Si todas las ventanas estan cerradas (isOpen = false) => hay que reiniciarlas
		//Sino si existen ventanas abiertas se las cierra despues de un tiempo determinado y se cuentan los puntos y vidas
		if (!window[0]->getIsOpen() && !window[1]->getIsOpen() && !window[2]->getIsOpen()) {
			window[0]->resetWindow();
			window[1]->resetWindow();
			window[2]->resetWindow();
			wave++;
			rounds++;
			doorSound.play();
			timeOfRound = clock();
		}
		else if (((clock() - timeOfRound) / 1000) > timePerRound) {
			//Organiza Puntos y vidas al cerrar las ventanas
			window[0]->closeWindow(&points, &lives);
			window[1]->closeWindow(&points, &lives);
			window[2]->closeWindow(&points, &lives);
			//Reinicia las ventanas
			window[0]->resetWindow();
			window[1]->resetWindow();
			window[2]->resetWindow();
			wave++;
			rounds++;
			doorSound.play();
			timeOfRound = clock();
		}
		//Actualizacion de los textos
		var = "Puntaje: " + std::to_string(points);
		textScore.setString(var);
		var = "Vidas: " + std::to_string(lives);
		textLives.setString(var);
		var = "Oleadas: " + std::to_string(wave + 1);
		textwave.setString(var);
		//Dibujado
		w->clear();
		w->draw(bg);
		w->draw(window[0]->getSprite());
		w->draw(window[1]->getSprite());
		w->draw(window[2]->getSprite());
		w->draw(textScore);
		w->draw(textLives);
		w->draw(textwave);
		w->draw(textRound);
		w->draw(cursor);
		w->display();
	}
	gameOverScreen(w);
	musicSound.stop();
}

void Game::levelUp(int round, RenderWindow* w) {
	window[0]->spriteCloseWindow();
	window[1]->spriteCloseWindow();
	window[2]->spriteCloseWindow();

	var = "ROUND: " + std::to_string(round + 1);
	textRound.setString(var);
	w->clear();
	w->draw(bg);
	w->draw(window[0]->getSprite());
	w->draw(window[1]->getSprite());
	w->draw(window[2]->getSprite());
	w->draw(textScore);
	w->draw(textLives);
	w->draw(textwave);
	w->draw(textRound);
	w->draw(cursor);
	w->display();
	Sleep(1000);

	var = "!!!! Mata a los enemigos !!!!";
	textRound.setString(var);
	w->clear();
	w->draw(bg);
	w->draw(window[0]->getSprite());
	w->draw(window[1]->getSprite());
	w->draw(window[2]->getSprite());
	w->draw(textScore);
	w->draw(textLives);
	w->draw(textwave);
	w->draw(textRound);
	w->draw(cursor);
	w->display();
	Sleep(600);

	var = "ROUND: " + std::to_string(round + 1);
	textRound.setString(var);

}

void Game::gameOverScreen(RenderWindow* w) {
	window[0]->spriteCloseWindow();
	window[1]->spriteCloseWindow();
	window[2]->spriteCloseWindow();

	var = "GAME OVER";
	textGameOver.setString(var);
	bool confirm = true;
	while (w->isOpen() && confirm) {
		Event e;
		//Control de eventos
		while (w->pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed: {
				musicSound.stop();
				w->close();
			}break;
			case sf::Event::KeyPressed: {
				confirm = false;
			}break;
			case sf::Event::MouseMoved: {
				cursor.setPosition((float)e.mouseMove.x, (float)e.mouseMove.y);
			}break;
			case sf::Event::MouseButtonPressed: {
				confirm = false;
			}break;
			}

		}
		//Dibujado
		w->clear();
		w->draw(bg);
		w->draw(window[0]->getSprite());
		w->draw(window[1]->getSprite());
		w->draw(window[2]->getSprite());
		w->draw(textScore);
		w->draw(textLives);
		w->draw(textwave);
		w->draw(textRound);
		w->draw(textGameOver);
		w->draw(cursor);
		w->display();
	}
}

void Game::resetGame() {
	points = 0, lives = 3, timePerRound = 5, rounds = 0, wave = 0, round = 0;

	gameOver = false;

	window[0]->setWindowStatus();
	window[1]->setWindowStatus();
	window[2]->setWindowStatus();

	timeOfRound = 0;
}
Game::~Game() {
}
