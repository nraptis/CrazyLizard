#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "GLApp.h"

class Game;

class GameMenu : public FView
{
public:
	
	GameMenu();
	virtual ~GameMenu();
    
	GLApp               *mApp;
	Game                *mGame;
    
	virtual void        Update();
	virtual void        Draw();
	
	virtual void        Touch(int x, int y);
	virtual void        Drag(int x, int y);
	virtual void        Release(int x, int y);
	
	virtual void        Notify(void *pData);
    
    int                 mNextMenuTicks;
    
    FButton             mButtonResumeGame;
    
    FButton             mButtonSettings;
    FButton             mButtonQuit;
    FButton             mButtonControls;
    FButton             mButtonGameCenter;
    
};

#endif
