//
// Created by diego on 23/05/18.
//

#ifndef ROGUEEMBLEMGAME_TEXTURE_H
#define ROGUEEMBLEMGAME_TEXTURE_H

#include <SFML/Graphics.hpp>
#include "Resource.h"


//Wrapper class for a texture that will be rendered
class Texture : public Resource {
public:
	//Constructor if no path is given no file is loaded
	explicit Texture(int id, std::string path = "");

	~Texture() override ;

	//Loads a texture from a file, returns true on success
	bool load(std::string& loadPath) override ;


	//Renders the texture to a window in a certain position
	virtual void render(sf::RenderWindow& window, int x, int y);
	virtual void render(sf::RenderWindow& window, int x, int y,int w, int h);

	//Returns true if texture is empty
	bool isValidResource() override;

	//Returns width and height
	virtual int getWidth() const{ return tWidth;	}
	virtual int getHeight() const{ return tHeight;	}

protected:

	//The actual texture
	sf::Texture texture;


	//Width and height of the texture
	int tWidth;
	int tHeight;

};



#endif //ROGUEEMBLEMGAME_TEXTURE_H
