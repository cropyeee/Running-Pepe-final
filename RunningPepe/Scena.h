#ifndef SCENA_H
#define SCENA_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "cClouds.h"
#include "cCharacter.h"



class Scena{
public:
	Scena();
	~Scena();
	SDL_Renderer* returnRenderer();
	SDL_Window* returnWindow();
	void createWindow();
	void createRenderer();
	void destroyWindow();
	void draw();
	Uint32 gamelogic(Uint32 interval);
	Uint32 draws(Uint32 interval);
	void destroyRenderer();
	void addObjects(cCharacter *_bohater, std::vector<cClouds*> _chmury, std::vector<LTexture*> _cars, std::vector<LTexture*> _tla,LTexture *_celownik,LTexture *_tekst,LTexture *_menu,LTexture *_predator,LTexture *_bomb,LTexture *_jail);
	int returnScreenWidth();
	int returnScreenHeight();
	bool czyKoniec();
	void zmienKoniec();
	void addPoints(int add);
	void handleEvent(SDL_Event* e);
	void close();
	void playSoundtrack();
	void AddStartTime(int time);
	void start();
protected:
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	bool koniec=false;
	bool started = false;
	bool loaded = true;
	bool strzal = false;
	int prevPointTime = 0;
	SDL_Renderer* gRenderer;
	SDL_Window* gWindow;
	cCharacter bohater;
	LTexture celownik;
	LTexture tekst;
	LTexture menu;
	LTexture dron;
	LTexture jail;
	LTexture bomba;
	Mix_Music *soundtrack = Mix_LoadMUS("soundtrack.mp3");
	Mix_Chunk *blast = NULL;
	Mix_Chunk *scream = NULL;
	Mix_Chunk *load = NULL;
	Mix_Chunk *miss = NULL;
	Mix_Chunk *punch = NULL;
	Mix_Chunk *syrena = NULL;
	Mix_Chunk *jump = NULL;
	int punkty=0;
	int CzasOstatniegoStrzalu = -3000;

	
	std::vector<cClouds*> chmury;
	std::vector<LTexture*> tla;
	std::vector<LTexture*> cars;
};
#endif

