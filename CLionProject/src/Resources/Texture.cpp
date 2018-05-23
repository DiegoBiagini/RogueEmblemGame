//
// Created by diego on 23/05/18.
//

#include "Texture.h"

Texture::Texture(int id, std::string path) :
		Resource(id,path)
{

	tWidth = 0;
	tHeight = 0;

	//If a path is given load the texture, else initialize to empty texture
	if(!this->path.empty())
		load(path);

}

Texture::~Texture() {
}

bool Texture::load(std::string& loadPath) {
	path = loadPath;

	texture.loadFromFile(loadPath);
	tWidth = texture.getSize().x;
	tHeight = texture.getSize().y;
}


bool Texture::isValidResource() {
	return texture.getSize().x != 0;
}

//Overloaded render methods
void Texture::render(sf::RenderWindow& window, int x, int y) {
	render(window, x, y, tWidth, tHeight);
}

void Texture::render(sf::RenderWindow& window, int x, int y, int w, int h) {
	//Creates rectangle in which it will be rendered
	sf::IntRect dstRect {x, y , w, h};

	//Set size at which it will be rendered
	sf::IntRect srcRect {0, 0, tWidth, tHeight};

	sf::Sprite sprite(texture,srcRect);
	sprite.setPosition(dstRect.left, dstRect.top);
	window.draw(sprite);

}


