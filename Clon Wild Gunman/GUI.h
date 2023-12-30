#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class GUI
{
private:
	Texture texture, cursorTexture, background;
	Sprite button1, button2, cursorSprite, bg;
	SoundBuffer selectSoundBuffer, songBuffer;
	Sound selectSound, musicSong;
	Font font;
	Text text1, text2, text3, textTilte;

public:
	GUI();
	int mainMenu(RenderWindow* w);
	~GUI();
};

