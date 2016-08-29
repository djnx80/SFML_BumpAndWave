#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bump2D
{
private:
	const int Width = 800;
	const int Height = 600;
	int maxLightSize;
	int howManyLights;
	// stw�rz �wiat�a
	struct theLight {
		int pozX, pozY, dx, dy;
		float wspLight;
	} light[600];

	sf::Color lightMask[300][300];					// tutaj jest �wiat�o
	sf::Uint8 imageMask[800 * 600 * 4];				// tutaj zapisany jest oryginalny obrazek
	sf::Uint8 destinationMask[800 * 600 * 4];		// obrazek wyj�ciowy, na nim operowa�
	sf::Texture destTexture;
	sf::Sprite destSprite;
	sf::Image bitplaneImage;

	void drawLight(int, int, float);
	void loadImage(std::string, sf::Image &, float);
	void loadLight(std::string, int);
	void updateLight();

public:
	Bump2D(std::string, std::string, int, int);
	~Bump2D() {}
	sf::Uint8* getDestinationMask() { return destinationMask; }
	void drawAndUpdate();
};

