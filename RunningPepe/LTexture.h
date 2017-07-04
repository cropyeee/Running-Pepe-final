#ifndef LTEXTURE_H
#define LTEXTURE_H


#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <ctime>




class LTexture{
public:
	LTexture();
	LTexture(double _posX, double _posY);
	LTexture(double _posX, double _posY, SDL_Texture* _texture, int _width, int _height);
	LTexture(double _posX, double _posY, SDL_Texture* _texture, int _width, int _height,bool _police);
	~LTexture();

	bool loadFromFile(std::string path, SDL_Renderer *Renderer);
	bool loadFromRenderedText(int punkty, SDL_Renderer *Renderer);

	void free();
	void moveX(int dx);
	void setX(double _posX);
	void setPos(double x, double y);
	
	void mousePos(double x, double y);

	void carSpeed();
	void carRotate(int posXdx);
	void moveBackground(); 
	double bombfall(double dx);
	

	void render(SDL_Renderer *Renderer);
	void renderFlip(SDL_Renderer *Renderer);
	
	

	int getWidth();
	int getHeight();
	void changeHit();
	void start();
	bool returnHit();
	bool returnPolice();
	double getX();
	double getY();
	double returnDXC();
	SDL_Rect* getCollider();
	SDL_Texture* getTexture();
protected:
	SDL_Texture* mTexture;
	SDL_Renderer* gRenderer;
	SDL_Rect* clip = NULL;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int poprzedniePrzyspieszenie = -5000;
	int mWidth;
	int mHeight;
	double dxc = 1; //1 initial car speed
	double dxb = 0.1; //0.1 initial background speed
	double dxclouds = 0.05; //0.05 initial clouds speed
	double angle = 0.0;
	bool hit = false;
	bool police=true;
	TTF_Font *gFont=TTF_OpenFont("orange_juice.ttf", 72);
	
	int modulo = 1;
	double posX;
	double posY;
	double VelY=0;
	SDL_Rect Collider;
	double posPoliceX;
};

#endif