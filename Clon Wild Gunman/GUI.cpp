#include "GUI.h"

GUI::GUI() {
	font.loadFromFile("Biondeggiare.otf");
	text1.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	textTilte.setFont(font);

	text1.setCharacterSize(30);
	text2.setCharacterSize(30);
	text3.setCharacterSize(30);
	textTilte.setCharacterSize(45);

	text1.setFillColor(sf::Color::Black);
	text2.setFillColor(sf::Color::Black);
	text3.setFillColor(sf::Color::Black);
	textTilte.setFillColor(sf::Color::Black);

	text1.setStyle(sf::Text::Bold);
	text2.setStyle(sf::Text::Bold);
	text3.setStyle(sf::Text::Bold);
	textTilte.setStyle(sf::Text::Bold);

	text1.setString("Play");
	text2.setString("Exit");
	text3.setString("GD: Ian Erbes");
	textTilte.setString("Wild Gang");

	texture.loadFromFile("imagenes/boton.png");
	button1.setTexture(texture);
	button2.setTexture(texture);

	//Posiciones de los botones
	button1.setPosition(265, 410);
	button2.setPosition(265, 470);

	text1.setPosition(370, 420);
	text2.setPosition(370, 485);
	text3.setPosition(320, 550);
	textTilte.setPosition(310, 348);


	cursorTexture.loadFromFile("imagenes/mira.png");
	cursorSprite.setTexture(cursorTexture);
	cursorSprite.setPosition(400, 300);

	background.loadFromFile("imagenes/MainMenu.png");
	bg.setTexture(background);

	selectSoundBuffer.loadFromFile("audio/Disparo.wav");
	selectSound.setBuffer(selectSoundBuffer);

	songBuffer.loadFromFile("audio/MainMenuSonido.wav");
	musicSong.setBuffer(songBuffer);
}

int GUI::mainMenu(RenderWindow* w) {
	w->setMouseCursorVisible(false);
	musicSong.setLoop(true);
	musicSong.play();
	while (w->isOpen()) {
		Event e;
		//Control de eventos
		while (w->pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed: {
				musicSong.stop();
				w->close();
			}break;
			case sf::Event::MouseMoved: {
				cursorSprite.setPosition((float)e.mouseMove.x, (float)e.mouseMove.y);
			}break;
			case sf::Event::MouseButtonPressed: {
				if (button1.getGlobalBounds().intersects(cursorSprite.getGlobalBounds())) {
					selectSound.play();
					musicSong.stop();
					return(0);
				}
				if (button2.getGlobalBounds().intersects(cursorSprite.getGlobalBounds())) {
					selectSound.play();
					musicSong.stop();
					return(1);
				}
			}break;
			}

		}
		//Dibujado
		w->clear();
		w->draw(bg);
		w->draw(button1);
		w->draw(text1);
		w->draw(button2);
		w->draw(text2);
		w->draw(text3);
		w->draw(textTilte);
		w->draw(cursorSprite);
		w->display();
	}
	w->clear();
}

GUI::~GUI() {

}