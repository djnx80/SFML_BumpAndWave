#include "stdafx.h"
#include "Bump2D.h"


Bump2D::Bump2D(std::string imageFileName, std::string lightFileName, int lightSize, int howManyLightsTemp)
{
	// wczytaj obrazek i œwiat³o
	loadImage(imageFileName, bitplaneImage, 3);
	loadLight(lightFileName, lightSize);
	howManyLights = howManyLightsTemp;

	destTexture.create(800, 600);

	for (int i = 0; i < howManyLights; i++) {
		int tx = (rand() % 600) + 100;
		int ty = (rand() % 400) + 100;
		int tdx = (rand() % 20) - 10;
		int tdy = (rand() % 20) - 10;
		float wspLight = ((rand() % 30) + 10) / 10;
		wspLight = 1.8;
		light[i] = { tx, ty, tdx, tdy, wspLight };
	}
}


void Bump2D::updateLight() {
	for (int i = 0; i < howManyLights; i++) {
		light[i].pozX += light[i].dx;
		light[i].pozY += light[i].dy;
		if (light[i].pozX < 0 || light[i].pozX > 700)	light[i].dx = -light[i].dx;
		if (light[i].pozY < 0 || light[i].pozY > 500)	light[i].dy = -light[i].dy;
	}
}
void Bump2D::drawAndUpdate() {
	// skopiuj bitplane
	std::copy(imageMask, imageMask + sizeof(imageMask), destinationMask);

	for (int i = 0; i < howManyLights; i++)
		drawLight(light[i].pozX, light[i].pozY, light[i].wspLight);

	updateLight();


}
void Bump2D::drawLight(int pozX, int pozY, float wspLight) {
	sf::Color light, pixel;
	float wsp = 1.0;

	float r, g, b;
	int tr, tg, tb;

	for (int x = 0; x < maxLightSize; x++) {
		for (int y = 0; y < maxLightSize; y++) {

			if (pozX + x > 0 && pozX + x < Width - 1 && pozY + y > 0 && pozY + y < Height - 1) {
				light = lightMask[x][y];
				int total = light.r + light.g + light.b;
				int offset = ((pozX + x) + ((pozY + y)*Width)) * 4;
				tr = destinationMask[offset];
				tg = destinationMask[offset + 1];
				tb = destinationMask[offset + 2];
				r = (light.r / wspLight + tr) / wsp;
				g = (light.g / wspLight + tg) / wsp;
				b = (light.b / wspLight + tb) / wsp;

				if (r > 255) r = 255;
				if (g > 255) g = 255;
				if (b > 255) b = 255;

				pixel.r = r;
				pixel.g = g;
				pixel.b = b;
				if (total > 20) {
					destinationMask[offset] = r;
					destinationMask[offset + 1] = g;
					destinationMask[offset + 2] = b;
					//			destinationMask[offset+3] = 255;
				}
			}
		}
	}

}
void Bump2D::loadLight(std::string fileName, int lightSize) {
	// wczytaj swiatlo do tablicy
	maxLightSize = lightSize;
	sf::Image lightImage;
	lightImage.loadFromFile(fileName);
	for (int x = 0; x < maxLightSize; x++)
		for (int y = 0; y < maxLightSize; y++)
			lightMask[x][y] = lightImage.getPixel(x, y);
}
void Bump2D::loadImage(std::string fileName, sf::Image &bitplaneImage, float darkness) {
	// wczytaj obrazek do tablicy
	bitplaneImage.loadFromFile(fileName);

	sf::Color makeDarkerColor;
	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Height; y++) {
			makeDarkerColor = bitplaneImage.getPixel(x, y);
			makeDarkerColor.r = makeDarkerColor.r / darkness;
			makeDarkerColor.g = makeDarkerColor.g / darkness;
			makeDarkerColor.b = makeDarkerColor.b / darkness;
			bitplaneImage.setPixel(x, y, makeDarkerColor);

			int offset = (x + (y*Width)) * 4;
			imageMask[offset] = makeDarkerColor.r;
			imageMask[offset + 1] = makeDarkerColor.g;
			imageMask[offset + 2] = makeDarkerColor.b;
			imageMask[offset + 3] = 255;

		}
	}

}
