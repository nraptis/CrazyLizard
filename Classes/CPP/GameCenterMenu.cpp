/*
 *  GameCenterMenu.cpp
 *  Template
 *
 *  Created by Nick Raptis on 11/3/10.
 *  Copyright 2010 Raptisoft LLC. All rights reserved.
 *
 */

#include "GameCenterMenu.h"
#include "Game.h"

GameCenterMenu::GameCenterMenu()
{
	mApp=((GLApp*)gApp);
    
    float aSpacing = 3.0f * gGlobalScale;
    
    float aButtonWidth = mApp->mMenuButtonBack[0].mWidth;
    float aButtonHeight = mApp->mMenuButtonBack[0].mHeight;
    
    
    //mButtonDone.Setup(gAppWidth2 - (aButtonWidth / 2.0f), MENU_DONE_BUTTON_Y, mApp->mMenuButtonBack, 2, this);
    mButtonDone.Setup(&(mApp->mMenuButtonBack[0]), &(mApp->mMenuButtonBack[1]),
                      gAppWidth2 - (aButtonWidth / 2.0f), MENU_DONE_BUTTON_Y);
    
    
    mButtonDone.Setup(&mApp->mMenuButtonBack[0], &mApp->mMenuButtonBack[1], gAppWidth2 - (aButtonWidth / 2.0f), MENU_DONE_BUTTON_Y);
    
    //                  , , 2, this);
    
    mButtonDone.AddOverlay(&(mApp->mMenuButtonTextClose));
    
    mButtonRetry.Setup(gAppWidth2 - (aButtonWidth / 2.0f), mButtonDone.GetFrame().mY - (aButtonHeight + aSpacing), mApp->mMenuButtonBack, 2, this);
    mButtonRetry.SetOverlays(&(mApp->mMenuButtonTextTryAgain));
    mArrowRotation=gRand.GetFloat(360.0f);
    
    mAchievementMode=false;
    mLeaderboardMode=false;
    
    mLeaderboardName="";
}

GameCenterMenu::~GameCenterMenu()
{
	//mApp->SaveStatic();
}

void GameCenterMenu::Update()
{
    mArrowRotation += 5.0f;
    if(mArrowRotation >= 360.0f)mArrowRotation-=360.0f;
}

void GameCenterMenu::ShowLeaderboard(FString pName)
{
    
}

void GameCenterMenu::ShowAchievements()
{
    
}

void GameCenterMenu::Draw()
{
    Graphics::SetColor();
    /*
    if(GameCenterIsShowing())
    {
        mButtonDone.RemoveFromParent();
        mButtonRetry.RemoveFromParent();
        
        return;
    }
    else
    {
        AddChild(mButtonClose);
    }
    
    mApp->mMenuBackPanel.Center(gAppWidth2, MENU_PANEL_CENTER_Y);
    
    mButtonRetry.RemoveFromParent();
    
    if(GameCenterIsConnecting())
    {
        mApp->mMenuArrow.Draw(gAppWidth2, gAppHeight2-73.0f*gGlobalScale, 1, mArrowRotation);
        mApp->mMenuTextGC.Center(gAppWidth2,gAppHeight2 + 4.0f * gGlobalScale);
        mApp->mMenuHeaderGC.Center(gAppWidth2, MENU_HEADER_Y);
    }
    else
    {
        AddChild(mButtonRetry);
        mApp->mMenuTextGCError.Center(gAppWidth2, MENU_PANEL_CENTER_Y);
    }
    
    Graphics::SetColor();
    */
}

void GameCenterMenu::Touch(int x, int y)
{
    
}

void GameCenterMenu::Notify(void *pData)
{
    /*
    if(pData == &mButtonRetry)
    {
        if(GameCenterModeLeaderboard())
        {
            GameCenterShowLeaderboard("crazy_lizard_scores");
        }
        else
        {
            GameCenterModeAchievements();
        }
    }
    */
    
    if(pData==&mButtonDone || pData==&mButtonClose)
	{
		//mApp->SaveStatic();
		mApp->mGameCenterMenu=0;
		Kill();
	}
    
}


