#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class VentanaSaloon : sf::Sprite
{
private:
	float positionX;
	float positionY;
	bool isOpen;
	bool isEnemy;
	Texture windowClose;
	Texture windowOpen;
	Texture window_people[3];
	Texture window_enemy[3];
	Sprite sprite;
public:
	VentanaSaloon();
	VentanaSaloon(float posX, float posY);
	void loadSprites();
	void setWindowStatus();
	void resetWindow();
	int getRandomNumber(int max);
	void shot(int* points, int* lives);
	bool getIsOpen();
	Sprite getSprite();
	void closeWindow(int* points, int* lives);
	void spriteCloseWindow();
	~VentanaSaloon();
};

