#include "cCharacter.h"

cCharacter::~cCharacter()
{
	free();
}

cCharacter::cCharacter()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

cCharacter::cCharacter(double _posX, double _posY)
{
	posX = _posX;
	posY = _posY;
}


void cCharacter::changeSkok(double _da)
{
	if (skok == false)
	{
		a = 100;
		da = _da;
		skok = true;
	}
	else skok = false;
}

void cCharacter::changeOpadanie()
{
	if (opadanie == true)
		opadanie = false;
	else opadanie = true;
}

bool cCharacter::returnSkok()
{
	return skok;
}

bool cCharacter::returnOpadanie()
{
	return opadanie;
}

void cCharacter::jump()
{
	a -= 0.5*da;
	posY -= a/45.0*da;
	if (posY > 470)
	{
		skok = false;
		a = 0;
	}
	
	/*
	if (posY > 290 && opadanie == false)
		posY -= posY*0.008;
	if (posY <= 290 && posY > 270 && opadanie == false)
		posY -= posY*0.006;
	if (posY <= 270 && posY > 230 && opadanie == false)
		posY -= posY*0.005;
	if (posY <= 230 && posY > 200 && opadanie == false)
		posY -= posY*0.004;
	if (posY <= 200 && posY > 190 && opadanie == false)
		posY -= posY*0.0025;
	if (posY == 190)
		opadanie = true;
	if (posY >= 190 && posY < 190.1 && opadanie==false)
	{
		posY += posY*0.0025;
		opadanie = true;
	}
	if (posY <= 470 && opadanie == true)
		posY += 0.1;*/
	/*if (posY >= 190.1 && posY < 185 && opadanie == true)
		posY += posY*0.004;
	if (posY >= 185 && posY < 170 && opadanie == true)
		posY += posY*0.005;
	if (posY >= 170 && posY < 200 && opadanie == true)
		posY += posY*0.006;
	if (posY >= 200 && posY < 250 && opadanie == true)
		posY += posY*0.007;
	if (posY >= 250 && posY <= 470 && opadanie == true)
		posY += posY*0.0085;
	if (posY >= 470 && opadanie == true)
	{

		//std::cout << "Wyladowal" << std::endl;
		opadanie = false;
		skok = false;
	}*/

}


/*void cCharacter::jump()
{		
	if (down == false)
	{
		posY += VelY;
		if (posY < 130)
		{
			posY = 130;
			down = true;
		}
	}
	if (down == true)
	{
		posY += -VelY;
		if (posY > 470)
		{
			posY = 470;
			VelY = 0;
			down == false;
		}
	}
}
*/