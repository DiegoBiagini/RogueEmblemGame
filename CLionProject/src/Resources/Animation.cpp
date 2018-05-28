//
// Created by diego on 28/05/18.
//

#include "Animation.h"


Animation::Animation(int id, std::string path)
		: Texture(id, std::move(path)) {
	singleImageHeight = 0;
	singleImageWidth = 0;
	imagesInRow = 0;
	nImages = 0;
	currentFrameCount = 0;
	currentImage = 0;
	advanceMilliseconds = 0;
	running = false;
}


bool Animation::isValidResource() {
	//It's valid if the texture is loaded, and the frame data is valid
	return Texture::isValidResource() && !frameRects.empty() && nImages == frameRects.size();
}


void Animation::render(sf::RenderWindow &window, int x, int y) {
	render(window, x, y, singleImageWidth, singleImageHeight);
}

void Animation::render(sf::RenderWindow &window, int x, int y, int w, int h) {
	//Creates rectangle in which it will be rendered
	sf::IntRect dstRect{x, y, w, h};

	//Gets rectangle in texture relative to current frame
	sf::IntRect currentFrameRect = frameRects.at(static_cast<unsigned long>(currentImage));

	sf::Sprite sprite(texture, currentFrameRect);
	sprite.setPosition(dstRect.left, dstRect.top);
	window.draw(sprite);

	if (running) {
		//Increase frame counter
		currentFrameCount++;

		//If image was displayed for enough time go to the next one
		if (1000.f / MAX_FRAMERATE * currentFrameCount >= advanceMilliseconds) {
			currentFrameCount = 0;
			currentImage = (currentImage + 1) % nImages;
		}
	}
}

void Animation::setupAnimation(int nImages, int singleImageWidth, int singleImageHeight, int imagesInRow,
							   int advanceMilliseconds) {
	//Set ups attributes
	this->singleImageWidth = singleImageWidth;
	this->singleImageHeight = singleImageHeight;
	this->imagesInRow = imagesInRow;
	this->nImages = nImages;
	this->advanceMilliseconds = advanceMilliseconds;

	currentFrameCount = 0;
	currentImage = 0;

	//Construct the vector with the coordinates
	for (int i = 0; i < nImages; i++) {
		sf::IntRect rect;
		rect.left = (i % imagesInRow) * singleImageWidth;
		rect.top = (i / imagesInRow) * singleImageHeight;
		rect.width = singleImageWidth;
		rect.height = singleImageHeight;

		frameRects.emplace_back(rect);
	}

	startAnimation();
}

void Animation::startAnimation() {
	running = true;
}

void Animation::pauseAnimation() {
	running = false;
}

void Animation::stopAnimation() {
	running = false;
	currentImage = 0;
	currentFrameCount = 0;
}

