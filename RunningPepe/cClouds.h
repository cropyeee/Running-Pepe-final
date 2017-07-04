#ifndef CCLOUDS_H
#define CCLOUDS_H

#include "LTexture.h"

class cClouds :public LTexture{
public:
	cClouds();
	cClouds(double _posX, double _posY);
	cClouds(double _posX, double _posY, SDL_Texture* _texture,int _width, int _height);
	cClouds(SDL_Texture* _texture, int _width, int _height);
	static Uint32 movingClouds(Uint32 interval, void* param); //clouds callback
	~cClouds();
	void MoveClouds();
};
//extern cClouds;

#endif