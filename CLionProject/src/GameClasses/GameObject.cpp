//
// Created by diego on 27/05/18.
//

#include "GameObject.h"

int GameObject::getPosX() const {
	return posX;
}

int GameObject::getPosY() const {
	return posY;
}

void GameObject::setPosX(int posX){
	this->posX = posX;
}

void GameObject::setPosY(int posY){
	this->posY = posY;
}