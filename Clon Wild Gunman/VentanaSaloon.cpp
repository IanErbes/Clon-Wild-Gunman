#include "VentanaSaloon.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

VentanaSaloon::VentanaSaloon() {
	VentanaSaloon::positionX = 0;
	VentanaSaloon::positionY = 0;
	VentanaSaloon::isOpen = false;
	VentanaSaloon::isEnemy = false;
	sprite.setPosition(sf::Vector2f(positionX, positionY));
	loadSprites();
}

VentanaSaloon::VentanaSaloon(float posX, float posY) {
	positionX = posX;
	positionY = posY;
	isOpen = getRandomNumber(2);
	isEnemy = getRandomNumber(2);
	sprite.setPosition(sf::Vector2f(positionX, positionY));
	loadSprites();
}

void VentanaSaloon::setWindowStatus() {
	if (isOpen) {
		isEnemy = getRandomNumber(2);
		int index = getRandomNumber(3);
		if (isEnemy) {
			sprite.setTexture(window_enemy[index]);
		}
		else {
			sprite.setTexture(window_people[index]);
		}
	}
	else {
		sprite.setTexture(windowClose);
	}
}

void VentanaSaloon::loadSprites() {
	windowClose.loadFromFile("imagenes/ventana_abierta.png");
	windowOpen.loadFromFile("imagenes/ventana_abierta.png");
	window_people[0].loadFromFile("imagenes/ventana_civil1.png");
	window_people[1].loadFromFile("imagenes/ventana_civil2.png");
	window_people[2].loadFromFile("imagenes/ventana_civil3.png");
	window_enemy[0].loadFromFile("imagenes/ventana_vaquero1.png");
	window_enemy[1].loadFromFile("imagenes/ventana_vaquero2.png");
	window_enemy[2].loadFromFile("imagenes/ventana_vaquero3.png");
}

int VentanaSaloon::getRandomNumber(int max) {
	return(rand() % max);
}

void VentanaSaloon::resetWindow() {
	isEnemy = getRandomNumber(2);
	isOpen = getRandomNumber(2);
	setWindowStatus();
}
void VentanaSaloon::shot(int* points, int* lives) {
	if (isOpen) {
		sprite.setTexture(windowOpen);
		if (isEnemy) {
			*points += 100;
		}
		else {
			*points -= 1000;
			*lives -= 1;
		}
		isOpen = false;
	}

}
bool VentanaSaloon::getIsOpen() {
	return(isOpen);
}
Sprite VentanaSaloon::getSprite() {
	return(sprite);
}
void VentanaSaloon::closeWindow(int* points, int* lives) {
	if (isOpen) {
		if (isEnemy) {
			*lives -= 1;
		}
		else {
			*points += 100;
		}
	}
}

void VentanaSaloon::spriteCloseWindow() {
	sprite.setTexture(windowClose);
}
VentanaSaloon::~VentanaSaloon() {

}
