#include "stdafx.h"
#include "WavingImage.h"


WavingImage::WavingImage()
{
	destTexture.create(800, 600);	// stwórz texure do wyœwietlania
}

WavingImage::~WavingImage()	{	}

void WavingImage::generateSinus(float newAlfa, float radius, float frequency) {
	float nx, ny;
	float deg = (3.1415 / 180) / frequency;

	// stwórz now¹ falê pionow¹
	for (int y = 0; y < Height; y++) {
		nx = sin(deg*(y + newAlfa))*radius + 0;
		dx[y] = (int)nx;
	}

	// stwórz now¹ falê poziom¹
	for (int x = 0; x < Width; x++) {
		ny = sin(deg*(x + newAlfa))*radius + 0;
		dy[x] = (int)ny;
	}
}

void WavingImage::waveToImage() {
	// przekszta³æ obrazek wzglêdem przesuniêæ dx i dy
	int nx, ny;
	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Height; y++) {
			int offsetLight = (x + (y*Width)) * 4;
			nx = dx[y];
			ny = dy[x];
			if (nx + x > 0 && nx + x < Width && ny + y>0 && ny + y < Height) {
				int offset = ((nx+x) + ((ny+y)*Width)) * 4;
				imageDest[offset] = imageMask[offsetLight];
				imageDest[offset + 1] = imageMask[offsetLight + 1];
				imageDest[offset + 2] = imageMask[offsetLight + 2];
				imageDest[offset+3] = 255;
			}
		}
	}
}

