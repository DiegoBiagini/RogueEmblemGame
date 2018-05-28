//
// Created by diego on 28/05/18.
//

#ifndef ROGUEEMBLEMGAME_ANIMATION_H
#define ROGUEEMBLEMGAME_ANIMATION_H

#include "Texture.h"
#include "../Utils/constants.h"

//Class to handle the animation of a texture
class Animation : public Texture {
public:
	explicit Animation(int id, std::string path = "");


	void render(sf::RenderWindow &window, int x, int y) override;

	void render(sf::RenderWindow &window, int x, int y, int w, int h) override;

	//Overridden functions

	bool isValidResource() override;

	//The getters for the dimensions of the texture now should return the dimensions of a single image
	int getWidth() const override {
		return singleImageWidth;
	};

	int getHeight() const override {
		return singleImageHeight;
	}

	//Load the rectangles that will define each single frame and how much time it takes for the animation to advance
	void
	setupAnimation(int nImages, int singleImageWidth, int singleImageHeight, int imagesInRow, int advanceMilliseconds);

	//Methods to start stop and pause animation
	void startAnimation();

	void pauseAnimation();

	void stopAnimation();

private:

	//Vector that contains frame coordinates
	std::vector<sf::IntRect> frameRects;

	//Number of frames of the animation
	int nImages;

	//Current frame of the animation
	int currentImage;

	//How many milliseconds relative to framerate it takes for the animation to advance one frame
	int advanceMilliseconds;

	//Whether the animation is running or not
	bool running;

	//How many times the current frame has been rendered
	int currentFrameCount;

	//Attributes used to construct vector of rectangles
	//Width and height of a single image
	int singleImageWidth;
	int singleImageHeight;

	//How many images are in a row
	int imagesInRow;


};


#endif //ROGUEEMBLEMGAME_ANIMATION_H
