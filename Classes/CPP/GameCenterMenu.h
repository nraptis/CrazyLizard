//
//  GameCenterMenu.h
//  CrazyDartsArc
//
//  Created by Nick Raptis on 10/23/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CrazyDartsArc_GameCenterMenu_h
#define CrazyDartsArc_GameCenterMenu_h

#include "GLApp.h"

class GameCenterMenu : public FView
{
public:
	GameCenterMenu();
	virtual ~GameCenterMenu();
	
	GLApp			*mApp;
	
	virtual void	Update();
	virtual void	Draw();
	
	virtual void	Notify(void *pData);
	
	virtual void	Touch(int x, int y);
    
    void            ShowLeaderboard(FString pName);
    void            ShowAchievements();
    
    bool            mAchievementMode;
    bool            mLeaderboardMode;
    
    FString         mLeaderboardName;
    
    float           mArrowRotation;
    
    FButton         mButtonClose;
	FButton         mButtonDone;
    FButton         mButtonRetry;
};


#endif
