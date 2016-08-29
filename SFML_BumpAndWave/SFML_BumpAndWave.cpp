#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bump2D.h"
#include "WavingImage.h"
sf::Uint8 *destMask;

int main()
{
	srand(time(NULL));
	sf::RenderWindow okno(sf::VideoMode(800, 600), "Okno");
	okno.setVerticalSyncEnabled(true);	// 60fps

	Bump2D *bump = new Bump2D("obrazek5.jpg", "light3.png", 250, 10);
	WavingImage *wave = new WavingImage();

	sf::Clock zegar;
	sf::Texture destTexture;
	sf::Sprite destSprite;
	destTexture.create(800, 600);
	float alfa = 0;
	float r = 10, dr = 0.6;
	float freq = 0.2;

	while (okno.isOpen())
	{
		sf::Event event;
		while (okno.pollEvent(event)) {
			if (event.type == sf::Event::Closed)	okno.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))	okno.close();

		alfa += 10;
		freq += 0.002;
		r += dr;
		if (r < 5 || r>70)
			dr = -dr;

		okno.clear();
		zegar.restart();
		bump->drawAndUpdate();
		destMask = bump->getDestinationMask();
		wave->setImageMask(destMask);

		wave->generateSinus(alfa, r, 2);
		wave->waveToImage();
		wave->setDestinationTexture(destTexture);

		destSprite.setTexture(destTexture);
		okno.draw(destSprite);

		std::cout << "czas: " << zegar.getElapsedTime().asMilliseconds() << std::endl;
		okno.display();
	}
	delete bump;
	delete wave;
	return 0;
}

