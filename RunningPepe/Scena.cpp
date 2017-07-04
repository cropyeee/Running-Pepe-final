#include "Scena.h"


Scena::Scena()
{
	gRenderer = NULL;
	gWindow = NULL;
	koniec = false;
}

Scena::~Scena()
{

}

void Scena::createWindow()
{
	gWindow = SDL_CreateWindow("Running Pepe!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
}

void Scena::createRenderer()
{
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

void Scena::destroyRenderer()
{
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
}

void Scena::destroyWindow()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
}

SDL_Renderer* Scena::returnRenderer()
{
	return gRenderer;
}

SDL_Window* Scena::returnWindow()
{
	return gWindow;
}

int Scena::returnScreenHeight()
{
	return SCREEN_HEIGHT;
}

int Scena::returnScreenWidth()
{
	return SCREEN_WIDTH;
}

void Scena::addObjects(cCharacter *_bohater, std::vector<cClouds*> _chmury, std::vector<LTexture*> _cars, std::vector<LTexture*> _tla,LTexture *_celownik,LTexture *_tekst,LTexture *_menu,LTexture *_predator,LTexture *_bomb,LTexture *_jail)
{
	bohater = *_bohater;
	chmury = _chmury;
	cars = _cars;
	tla = _tla;
	celownik = *_celownik;
	tekst = *_tekst;
	menu = *_menu;
	dron = *_predator;
	bomba = *_bomb;
	jail = *_jail;
	blast = Mix_LoadWAV("blast.wav");
	load = Mix_LoadWAV("load.wav");
	scream = Mix_LoadWAV("scream.wav");
	miss = Mix_LoadWAV("miss.wav");
	punch = Mix_LoadWAV("punch.wav");
	syrena = Mix_LoadWAV("syrena.wav");
	jump = Mix_LoadWAV("jump.wav");
	Mix_VolumeMusic(32);
	Mix_VolumeChunk(jump, 15);
	Mix_VolumeChunk(punch, 15);
	Mix_VolumeChunk(scream, 25);
	Mix_VolumeChunk(blast, 30);
	Mix_VolumeChunk(syrena, 25);
}

void Scena::draw()
{
	//std::cout << "draw" << std::endl;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	for (auto b : tla)
	{
		b->render(gRenderer);
	}

	for (auto c : chmury)
	{
		c->render(gRenderer);
	}
	bohater.render(gRenderer);
	for (auto c : cars)
		c->render(gRenderer);
	
	SDL_RenderPresent(gRenderer);
}

bool Scena::czyKoniec()
{
	return koniec;
}

void Scena::zmienKoniec()
{
	koniec =true;
}


Uint32 Scena::gamelogic(Uint32 interval)
{
	//std::cout << "gamelogic" << std::endl;
	if(!koniec)
	{
		if (started == true)
		{
			if (loaded == true & (SDL_GetTicks() - CzasOstatniegoStrzalu) > 1500)
			{
				Mix_PlayChannel(-1, load, 0);
				loaded = false;
			}
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			if (currentKeyStates[SDL_SCANCODE_SPACE] && bohater.returnSkok() == false && bohater.returnOpadanie() == false) // klikniecie spacji
			{
				Mix_PlayChannel(-1, jump, 0);
				bohater.changeSkok(cars[0]->returnDXC());
				currentKeyStates = SDL_GetKeyboardState(NULL);
			}
			int dx = rand() % 1500;
			for (auto c : cars)
			{
				if (SDL_HasIntersection(bohater.getCollider(), c->getCollider())) //kolizja
				{
					Mix_PlayChannel(-1, punch, 0);
					Mix_PlayChannel(-1, syrena, 3);
					Mix_HaltMusic();
					koniec = true;

					//std::cout << "Kolizja" << std::endl;
				}
				if (SDL_HasIntersection(bomba.getCollider(), c->getCollider()))
				{
					std::cout << "Trafiono bomba!" << std::endl;
					
					bomba.setPos(0, 0);
					if (c->returnPolice() == true)
					{
						Mix_PlayChannel(-1, blast, 0);
						std::cout << "Trafiono policje" << std::endl;
						c->changeHit();
						//c->setX((rand() % 1000));
						punkty = punkty + 20;
						std::cout << punkty << std::endl;
						strzal = false;
						//CzasOstatniegoStrzalu = SDL_GetTicks();
					}
					else
					{
						Mix_PlayChannel(-1, scream, 0);
						std::cout << "Trafiono cywila" << std::endl;
						c->changeHit();
						punkty = punkty - 10;
						strzal = false;
						//CzasOstatniegoStrzalu = SDL_GetTicks();
					}
					//bomba.mousePos(-500, -500);
				}
			}
			for (auto c : cars)
			{
				c->carRotate(dx); //obracanie i ruszanie auta
			}
			int i = 1;
			for (std::vector<LTexture*>::iterator it = cars.begin(); it != cars.end(); it++)
			{

				for (std::vector<LTexture*>::iterator it1 = cars.begin() + i; it1 != cars.end(); it1++)
				{
					//if ((*it1)->getX() < ((*it)->getX() + (*it)->getWidth()) && (*it1)->getX() > ((*it)->getX()) && (*it1)->getY() == (*it)->getY())
					//	(*it1)->moveX(400);
					if (((*it1)->getX() > (*it)->getX()) && (*it1)->getY() == (*it)->getY())
					{
						if (((*it1)->getX() - (*it)->getX()) < 600)
						{
							int dx = rand() % 300; //int dx = 400 - ((*it1)->getX() - (*it)->getX());
							(*it1)->moveX(dx);
						}
					}
				}
			}

			if ((SDL_GetTicks() - prevPointTime) > 2000)
			{
				punkty++;
				prevPointTime = SDL_GetTicks();
			}

			for (auto c : chmury)//poruszanie chmurami
				c->MoveClouds();

			for (auto b : tla)
				b->moveBackground(); //poruszanie tlem

			if (bohater.returnSkok() == true) //skok
			{
				bohater.jump();
			}
			if (strzal == true)
			{
				if (bomba.bombfall(0) > 550)
				{
					Mix_PlayChannel(-1, miss, 0);
					strzal = false;
					bomba.setPos(0, 0);
				}
				
			}
			tekst.loadFromRenderedText(punkty, gRenderer);

			
		}
		return interval;
	}
	
	return interval;
}

Uint32 Scena::draws(Uint32 interval)
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	for (auto b : tla)
	{
		b->render(gRenderer);
	}

	for (auto c : chmury)
	{
		c->render(gRenderer);
	}

	bohater.render(gRenderer);

	

	for (auto c : cars)
	{
		//if (c->returnHit()!=true)
		//	c->render(gRenderer);
		//else
			c->renderFlip(gRenderer);
	}
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (started)
	{
		celownik.mousePos(x, y);
		if ((SDL_GetTicks() - CzasOstatniegoStrzalu)>1500)
			celownik.render(gRenderer);
		dron.mousePos(x, 0);
		dron.render(gRenderer);
		if (strzal == false)
		{
			
				bomba.mousePos(x, 45);
				bomba.render(gRenderer);
		}
		if(strzal==true)
			bomba.render(gRenderer);
		// wczesniejszy strzal
		/*if (!strzal)
		{
			bomba.mousePos(x, 45);
			if ((SDL_GetTicks() - CzasOstatniegoStrzalu) > 1500)
				bomba.render(gRenderer);
		}
		else
		{
			if (bomba.bombfall(x) < 530)
				bomba.render(gRenderer);
			else strzal = false;
		}*/
	}
	tekst.render(gRenderer);
	if (koniec==true)
		jail.render(gRenderer);
	if (!started)
		menu.render(gRenderer);
	
	SDL_RenderPresent(gRenderer);
	return interval;
}

void Scena::addPoints(int add)
{
	punkty += add;
	std::cout << punkty << std::endl;
}

void Scena::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		// wczesniejszy strzal
		/*int x, y;
		SDL_GetMouseState(&x, &y);
		std::cout << "Kliknieto " << x << " " << y << std::endl;
		
			for (auto c : cars)
			{
				if (x<(c->getX() + c->getWidth()) && x>c->getX() && y<c->getY() + c->getHeight() && y>c->getY() && (SDL_GetTicks() - CzasOstatniegoStrzalu) > 1500)
				{
					if (c->returnPolice() == true)
					{
						std::cout << "Trafiono policje" << std::endl;
						c->changeHit();
						//c->setX((rand() % 1000));
						punkty = punkty + 20;
						std::cout << punkty << std::endl;
						//CzasOstatniegoStrzalu = SDL_GetTicks();
					}
					else
					{
						std::cout << "Trafiono cywila" << std::endl;
						c->changeHit();
						punkty = punkty - 10;
						//CzasOstatniegoStrzalu = SDL_GetTicks();
					}
				}
			}
			strzal = true;
			CzasOstatniegoStrzalu = SDL_GetTicks();*/ 
		if ((SDL_GetTicks() - CzasOstatniegoStrzalu) > 1500&&strzal==false)
		{
			strzal = true;
			loaded = true;
			CzasOstatniegoStrzalu = SDL_GetTicks();
		}
	}
	if (e->type == SDL_KEYDOWN&&started==false)
		if (e->key.keysym.sym == SDLK_SPACE)
		{
			start();
			started = true;
		}
}

void Scena::close()
{
	Mix_FreeMusic(soundtrack);
	Mix_FreeChunk(blast);
	Mix_FreeChunk(load);
	Mix_FreeChunk(scream);
	Mix_FreeChunk(miss);
	Mix_FreeChunk(punch);
	Mix_FreeChunk(syrena);
	Mix_FreeChunk(jump);
	soundtrack = NULL;
	blast = NULL;
	load = NULL;
	scream = NULL;
	miss = NULL;
	punch = NULL;
	jump = NULL;
	syrena = NULL;
	tekst.free();
}

void Scena::playSoundtrack()
{
	Mix_PlayMusic(soundtrack, -1);
}


void Scena::AddStartTime(int time)
{
	prevPointTime = time;
}

void Scena::start()
{
	for (auto c : cars)
		c->start();
	for (auto c : chmury)
		c->start();
	for (auto b : tla)
		b->start();
}