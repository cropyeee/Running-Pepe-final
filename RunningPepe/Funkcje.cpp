#include "Funkcje.h"

bool init(Scena &scena)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER|SDL_INIT_AUDIO) < 0)//
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window

		scena.createWindow();
		if (scena.returnWindow() == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			scena.createRenderer();
			if (scena.returnRenderer() == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(scena.returnRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize JPG loading
				int imgFlags = IMG_INIT_JPG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				if (TTF_Init() == -1)
				{
					success = false;
				}
				if (Mix_OpenAudio(22100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


bool loadMedia(Scena &scena, LTexture &background, LTexture &police, cCharacter &character, cClouds &cloud, LTexture &background2, LTexture &crosshair, LTexture &tekst, LTexture &menu, LTexture &civil1, LTexture &civil2, LTexture &civil3, LTexture &predator, LTexture &bomb,LTexture &jail)
{
	//Loading success flag
	bool success = true;

	//Load bacground
	if (!background.loadFromFile("droga1_modified_asd21.png", scena.returnRenderer()))
	{
		std::cout << "Failed to load background" << std::endl;
		success = false;
	}
	if (!background2.loadFromFile("droga1_modified_asd2_odbicie1.png",scena.returnRenderer()))
	{
		std::cout << "Failet to load background" << std::endl;
		success = false;
	}

	if (!character.loadFromFile("pepe_biegnaca_final1_alpha.png", scena.returnRenderer()))
	{
		std::cout << "Failed to load character" << std::endl;
		success = false;
	}
	if (!police.loadFromFile("police_modified1.png", scena.returnRenderer()))
	{
		std::cout << "Failed to load police car" << std::endl;
		success = false;
	}
	if (!cloud.loadFromFile("cloud_modified1.png", scena.returnRenderer()))
	{
		std::cout << "Failed to load cloud" << std::endl;
		success = false;
	}
	if (!crosshair.loadFromFile("crosshair_final.png", scena.returnRenderer()))
	{
		std::cout << "Failed to load crosshair" << std::endl;
		success = false;
	}
	if (!predator.loadFromFile("predator.png", scena.returnRenderer()))
	{
		success = false;
	}
	if (!bomb.loadFromFile("bomb1.png", scena.returnRenderer()))
	{
		success = false;
	}
	if (!menu.loadFromFile("menu.png", scena.returnRenderer()))
	{
		std::cout << "Failed to load menu" << std::endl;
		success = false;
	}
	if (!jail.loadFromFile("pepe_jail.png", scena.returnRenderer()))
		success = false;
	if (!civil1.loadFromFile("car1_modified.png", scena.returnRenderer()))
		success = false;
	if (!civil2.loadFromFile("car2_modified.png", scena.returnRenderer()))
		success = false;
	if (!civil3.loadFromFile("car3_modified.png", scena.returnRenderer()))
		success = false;

	return success;
}



void close(Scena &scena, LTexture &background, LTexture &police, cCharacter &character, cClouds &cloud, LTexture &background2, LTexture &crosshair, LTexture &menu, LTexture &civil1, LTexture &civil2, LTexture &civil3, LTexture &predator, LTexture &bomb,LTexture &jail)
{
	//Free loaded image
	background.free();
	character.free();
	police.free();
	cloud.free();
	background2.free();
	crosshair.free();
	predator.free();
	menu.free();
	bomb.free();
	civil1.free();
	civil2.free();
	civil3.free();
	jail.free();
	



	//Destroy Window
	scena.destroyRenderer();
	scena.destroyWindow();
	scena.zmienKoniec();
	scena.close();

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

Uint32 gamelogic(Uint32 interval, void * param) {
	Scena *self = reinterpret_cast<Scena *>(param);

	if (!self->czyKoniec())
		self->gamelogic(interval);

	if (!self->czyKoniec())
		self->draws(interval);
		
	if (!self->czyKoniec())
		SDL_TimerID callback = SDL_AddTimer(6, gamelogic, self);

	return interval;
}

Uint32 drawing(Uint32 interval, void*param)
{
	/*Scena *self = reinterpret_cast<Scena*>(param);
	if (!self->czyKoniec())
		self->draws(interval);

	if (!self->czyKoniec())
		SDL_TimerID draws = SDL_AddTimer(6, drawing, self);*/
	return interval;
}