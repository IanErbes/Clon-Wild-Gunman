#pragma once
#include <iostream>
#include "VentanaSaloon.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

class Game
{
private:
	//RenderWindow* w;
	VentanaSaloon* window[3];
	SoundBuffer bufferShotSound, bufferSoundDoor, bufferMusic;
	Sound shotSound, doorSound, musicSound;
	int points, lives, timePerRound, rounds, wave, round;
	clock_t timeOfRound;
	Font font;
	Text textScore, textLives, textwave, textRound, textGameOver;
	Sprite cursor, bg;
	Texture cursorTexture, background;
	std::string var;
	bool gameOver;
public:
	Game();
	void startGame(RenderWindow* w);
	void levelUp(int round, RenderWindow* w);
	void gameOverScreen(RenderWindow* w);
	void resetGame();
	~Game();
};

