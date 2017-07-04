#ifndef FUNKCJE_H
#define FUNKCJE_H

#include "Scena.h"
//class Scena;//forward declaration
//class LTexture;//forward declaration	
//class cCharacter;//forward decalaration
//class cClouds;// forward decalaration
//#include "cCharacter.h"
//#include "cClouds.h"
//#include "LTexture.h"
//Starts up SDL and creates window
bool init(Scena &scena);

//Loads media
bool loadMedia(Scena &scena, LTexture &background, LTexture &police, cCharacter &character, cClouds &cloud,LTexture &background2,LTexture &crosshair,LTexture &tekst,LTexture &menu,LTexture &civil1,LTexture &civil2,LTexture &civil3,LTexture &predator,LTexture &bomb,LTexture &jail);

//Frees media and shuts down SDL
void close(Scena &scena, LTexture &background, LTexture &police, cCharacter &character, cClouds &cloud, LTexture &background2, LTexture &crosshair, LTexture &menu, LTexture &civil1, LTexture &civil2, LTexture &civil3, LTexture &predator, LTexture &bomb,LTexture &jail);
Uint32 gamelogic(Uint32 interval, void * param);
Uint32 drawing(Uint32 interval, void*param);



#endif