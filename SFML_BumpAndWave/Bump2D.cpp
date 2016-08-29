#include "stdafx.h"
#include "Bump2D.h"


Bump2D::Bump2D(std::string imageFileName, std::string lightFileName, int lightSize, int howManyLightsTemp)
{
	// load image and light
	loadImage(imageFileName, bitplaneImage, 3);
	loadLight(lightFileName, lightSize);
	howManyLights = howManyLightsTemp;

	// this will be used as destination
	destTexture.create(800, 600);

	// create new lights, all random except the light intensivity
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
	// make sure the light stays in window
	for (int i = 0; i < howManyLights; i++) {
		light[i].pozX += light[i].dx;
		light[i].pozY += light[i].dy;
		if (light[i].pozX < 0 || light[i].pozX > 700)	light[i].dx = -light[i].dx;
		if (light[i].pozY < 0 || light[i].pozY > 500)	light[i].dy = -light[i].dy;
	}
}
void Bump2D::drawAndUpdate() {
	// copy destination to the image, so we can operate on that
	std::copy(imageMask, imageMask + sizeof(imageMask), destinationMask);

	for (int i = 0; i < howManyLights; i++)
		drawLight(light[i].pozX, light[i].pozY, light[i].wspLight);

	updateLight();


}
void Bump2D::drawLight(int pozX, int pozY, float wspLight) {
	sf::Color light, pixel;
	float wsp = 1.0;	// make it darker or lighter, 1.0 is ok

	// store the colors
	float r, g, b;
	int tr, tg, tb;

	// check all the light points and do the calcs with background
	for (int x = 0; x < maxLightSize; x++) {
		for (int y = 0; y < maxLightSize; y++) {

			if (pozX + x > 0 && pozX + x < Width - 1 && pozY + y > 0 && pozY + y < Height - 1) {
				light = lightMask[x][y];
				// total will be used to check if the light is almost black or not
				int total = light.r + light.g + light.b;
				// we draw to array so we need to count the offset
				int offset = ((pozX + x) + ((pozY + y)*Width)) * 4;
				// and then get the colors from an array
				tr = destinationMask[offset];
				tg = destinationMask[offset + 1];
				tb = destinationMask[offset + 2];
				r = (light.r / wspLight + tr) / wsp;
				g = (light.g / wspLight + tg) / wsp;
				b = (light.b / wspLight + tb) / wsp;

				// can not be higher than 255
				if (r > 255) r = 255;
				if (g > 255) g = 255;
				if (b > 255) b = 255;

				// make new 
				pixel.r = r;
				pixel.g = g;
				pixel.b = b;
				// ignore the almost black lights so it doesn't look square in some cases
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
	// load image
	bitplaneImage.loadFromFile(fileName);

	// read the image to the array and make it darker
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
