#include "LTexture.h"

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::LTexture(double _posX, double _posY, SDL_Texture* _texture, int _width, int _height)
{
	posX = _posX;
	posY = _posY;
	mTexture = _texture;
	mWidth = _width;
	mHeight = _height;
}

LTexture::LTexture(double _posX, double _posY, SDL_Texture* _texture, int _width, int _height, bool _police)
{
	posX = _posX;
	posY = _posY;
	mTexture = _texture;
	mWidth = _width;
	mHeight = _height;
	police = _police;
}

bool LTexture::returnPolice()
{
	return police;
}


void LTexture::setX(double rand)
{
	posX = 1280 + mWidth + rand;
}

void LTexture::moveX(int dx)
{
	posX = posX + dx;
}

LTexture::LTexture(double _posX, double _posY)
{
	posX = _posX;
	posY = _posY;
}


LTexture::~LTexture()
{
	free();
}

double LTexture::getX()
{
	return posX;
}

double LTexture::getY()
{
	return posY;
}
bool LTexture::loadFromFile(std::string path, SDL_Renderer *Renderer)
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));

		newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture" << SDL_GetError() << std::endl;
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(int punkty, SDL_Renderer *Renderer)
{
	free();

	std::string points = std::to_string(punkty);
	points = "Score: " + points;
	SDL_Color textColor = { 0, 188, 255 };
	if (gFont)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, points.c_str(), textColor);
		if (textSurface == NULL)
		{
			std::cout << "Unable to render text surface!" << std::endl;
		}
		else
		{
			mTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);
			if (mTexture == NULL)
			{
				std::cout << "Unable to create texture from rendered text!" << std::endl;
			}
			else
			{
				mWidth = textSurface->w;
				mHeight = textSurface->h;
			}
			SDL_FreeSurface(textSurface);
		}
		return mTexture != NULL;
	}
	else std::cout << "Unable to load font" << std::endl;
}

void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		posX = 0;
		posY = 0;
	}
}

void LTexture::render(SDL_Renderer *Renderer)
{
	
	SDL_Rect renderQuad = { posX, posY, mWidth, mHeight };
	Collider = renderQuad;
	SDL_RenderCopy(Renderer, mTexture, NULL, &renderQuad);
}

void LTexture::renderFlip(SDL_Renderer *Renderer)
{
	SDL_Rect renderQuad = { posX, posY, mWidth, mHeight };
	Collider = renderQuad;
	/*if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}*/
	SDL_RenderCopyEx(Renderer, mTexture,NULL, &renderQuad,angle,center,flip);
}



int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

SDL_Texture* LTexture::getTexture()
{
	return mTexture;
}


void LTexture::carSpeed()
{
	if (hit != true)
	{
		if (posX < (-mWidth))
		{
			posX = 1280 + mWidth + (rand() % 2000);
			std::cout << "PosX: " << posX << std::endl;
		}
		else
		{
			if ((SDL_GetTicks() - poprzedniePrzyspieszenie) > 15000)
			{
				dxc = dxc + 0.25;
				std::cout << "Przyspieszenie " << dxc << std::endl;
				poprzedniePrzyspieszenie = SDL_GetTicks();
			}
			else
			{
				posX = posX - dxc;
			}
		}
	}
}

void LTexture::carRotate(int posXdx)
{
	if (hit == true)
	{
		angle += 1;
		posX += 3;
		posY -= 2;
		if (posX > 1280 + mWidth)
		{
			angle = 0;
			hit = false;
			posX = 1280 + mWidth + (rand() % 5000);
			posY = 530;
			clip = NULL;
			center = NULL;
			flip = SDL_FLIP_NONE;
		}
	}
	else
	{
		if (posX < (-mWidth))
		{
			posX = 1280 + mWidth + (rand() % 5000);
			std::cout << "PosX: " << posX << std::endl;
		}
		else
		{
			if ((SDL_GetTicks() - poprzedniePrzyspieszenie) > 15000)
			{
				dxc = dxc + 0.20;
				std::cout << "Przyspieszenie " << dxc << std::endl;
				poprzedniePrzyspieszenie = SDL_GetTicks();
			}
			else
			{
				posX = posX - dxc;
			}
		}
	}

}

SDL_Rect* LTexture::getCollider()
{
	return &Collider;
}

void LTexture::moveBackground()
{
	posX -= dxb;
	if (posX < -mWidth)
		posX = 1280;
}

void LTexture::mousePos(double x, double y)
{
	posX = x-mWidth/2.0;
	if (y!=0)
		posY = y-mHeight/2.0;
	else posY = 0;
}

void LTexture::changeHit()
{
	if (hit == false)
	{
		hit = true;
	}
	else hit = false;
}

bool LTexture::returnHit()
{
	return hit;
}

void LTexture::start()
{
	dxb = 0.1;
	dxc = 1;
	dxclouds = 0.05;
}

double LTexture::returnDXC()
{
	return dxc;
}

double LTexture::bombfall(double dx)
{
	//posX = dx - mWidth / 2.0;
	posY +=5;

	return posY;
}

void LTexture::setPos(double x, double y)
{
	posX = x;
	posY = y;
}