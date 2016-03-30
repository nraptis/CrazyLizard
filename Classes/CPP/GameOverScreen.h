/*
 *  GameOverScreen.h
 *  Darts
 *
 *  Created by Nick Raptis on 12/8/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLApp.h"


class Game;

class GameOverScreen : public FView
{
public:
	GameOverScreen();
	virtual ~GameOverScreen();
	
	GLApp			*mApp;
	
	virtual void	Update();
	virtual void	Draw();
	
	virtual void	Notify(void *pData);
    
    void            DrawText(int x, int y, FString text, FSprite *pFSprite);
    int             WidthText(FString text);
    
    FButton         mButtonDone;
    FButton         mButtonClose;
    
	float			mSin;
};