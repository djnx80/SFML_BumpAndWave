#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bump2D
{
private:
	const int Width = 800;		// window size
	const int Height = 600;
	int maxLightSize;	// light size (as square object)
	int howManyLights;	// how many lights to display
	// stwórz œwiat³a
	struct theLight {		// light coords 
		int pozX, pozY, dx, dy;
		float wspLight;	// how light is the light :)
	} light[600];

	sf::Color lightMask[300][300];					// tutaj jest œwiat³o
	sf::Uint8 imageMask[800 * 600 * 4];				// tutaj zapisany jest oryginalny obrazek
	sf::Uint8 destinationMask[800 * 600 * 4];		// obrazek wyjœciowy, na nim operowaæ
	sf::Texture destTexture;
	sf::Sprite destSprite;
	sf::Image bitplaneImage;

	void drawLight(int, int, float);		// main procedure, it add light to the destination
	void loadImage(std::string, sf::Image &, float);	// load the image to the array
	void loadLight(std::string, int);	// load the light
	void updateLight();	// and update the coords

public:
	Bump2D(std::string, std::string, int, int);		// (image, light, light size, how many lights)
	~Bump2D() {}
	sf::Uint8* getDestinationMask() { return destinationMask; }
	void drawAndUpdate();		// do all the stuff
};

