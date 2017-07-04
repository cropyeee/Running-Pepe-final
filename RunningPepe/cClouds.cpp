#include "cClouds.h"

cClouds::cClouds()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}
cClouds::cClouds(double _posX,double _posY)
{
	posX = _posX;
	posY = _posY;
}

cClouds::~cClouds()
{
	free();
}
Uint32 cClouds::movingClouds(Uint32 interval, void* param)
{
	
	/*cClouds *self = reinterpret_cast<cClouds *>(param);
	self->MoveClouds();
	SDL_TimerID timerID = SDL_AddTimer(60, movingClouds,self);*/
	return interval;
}

void cClouds::MoveClouds()
{
	posX = posX - dxclouds;
		if (posX < (-mWidth))
			posX = 1200+mWidth;
	
	
}

cClouds::cClouds(double _posX, double _posY, SDL_Texture* _texture, int _width, int _height)
{
	posX = _posX;
	posY = _posY;
	mTexture = _texture;
	mWidth = _width;
	mHeight = _height;

}

cClouds::cClouds(SDL_Texture* _texture, int _width, int _height)
{
	posX = (rand() % 1280);
	posY = (rand() % 300) + 50;
	mTexture = _texture;
	mWidth = _width;
	mHeight = _height;

}