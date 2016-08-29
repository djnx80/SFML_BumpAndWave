#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bump2D.h"
#include "WavingImage.h"

int main()
{
	// init random and open window
	srand(time(NULL));
	sf::RenderWindow okno(sf::VideoMode(800, 600), "Okno");
	okno.setVerticalSyncEnabled(true);	// 60fps

	// make new object, load the files and set light size and how many lights
	Bump2D *bump = new Bump2D("obrazek5.jpg", "light3.png", 250, 10);
	// this object is responsible for the waves
	WavingImage *wave = new WavingImage();
	//  this will be used to get our bump effect as rgba array
	sf::Uint8 *destMask;

	// initialize data for display and for calculations
	sf::Clock zegar;
	sf::Texture destTexture;
	sf::Sprite destSprite;
	destTexture.create(800, 600);
	// this will be use for waving, to make an animation
	float alfa = 0;
	float r = 10, dr = 0.6;
	float freq = 0.2;

	while (okno.isOpen())
	{
		// check the events
		sf::Event event;
		while (okno.pollEvent(event)) {
			if (event.type == sf::Event::Closed)	okno.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))	okno.close();

		// it will be used in wave calcs
		alfa += 10;
		freq += 0.002;
		r += dr;
		if (r < 5 || r>70)
			dr = -dr;

		// clear the window, restart the timer
		okno.clear();
		zegar.restart();
		// update and draw the bump to Uint8 array (rgba)
		bump->drawAndUpdate();
		// get the array and use it as a source for wave
		destMask = bump->getDestinationMask();
		wave->setImageMask(destMask);

		// generate new sinus on the side and top
		wave->generateSinus(alfa, r, 2);
		// do the wave
		wave->waveToImage();
		// get the texture and display it
		wave->setDestinationTexture(destTexture);
		destSprite.setTexture(destTexture);
		okno.draw(destSprite);
		okno.display();

		// time to see how long does it take to do one loop (iteration)
		std::cout << "czas: " << zegar.getElapsedTime().asMilliseconds() << std::endl;
	}
	// delete objects 
	delete bump;
	delete wave;
	return 0;
}

