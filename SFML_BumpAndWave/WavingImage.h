#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>

class WavingImage
{
private:
	sf::Image destinationImage;
	sf::Texture destTexture;
	int Width = 800;
	int Height = 600;
	int dx[1000];
	int dy[1000];
	sf::Uint8 imageMask[800 * 600 * 4];
	sf::Uint8 imageDest[800 * 600 * 4];

public:
	void generateSinus(float, float, float);
	void waveToImage();
	void setDestinationTexture(sf::Texture &destinationTexture) {
		destTexture.update(imageDest);
		destinationTexture = destTexture;
	}
	void setImageMask(sf::Uint8 *source) {
		for (int x = 0; x < Width; x++) {
			for (int y = 0; y < Height; y++) {
				int offset = (x + (y*Width)) * 4;
				imageMask[offset] = source[offset];
				imageMask[offset+1] = source[offset+1];
				imageMask[offset+2] = source[offset+2];
				imageMask[offset+3] = source[offset+3];
			}
		}
	}
	sf::Uint8* getDestinationMask() { return imageDest; }

	WavingImage();
	~WavingImage();
};

