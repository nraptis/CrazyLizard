/*
 *  GameOverScreen.cpp
 *  Darts
 *
 *  Created by Nick Raptis on 12/8/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GameOverScreen.h"
#include "Game.h"
#include "MainMenu.h"
#include "GLApp.h"

GameOverScreen::GameOverScreen()
{
    mApp=((GLApp*)gApp);
    
    float aButtonWidth = mApp->mMenuButtonBack[0].mWidth;
    float aButtonHeight = mApp->mMenuButtonBack[0].mHeight;
    
    mButtonDone.Setup(gAppWidth2 - (aButtonWidth / 2.0f), MENU_DONE_BUTTON_Y, mApp->mMenuButtonBack, 2, this);
    mButtonDone.SetOverlays(&(mApp->mMenuButtonTextContinue));
    
    //mApp->mHSList.PadScore(768);
    //mApp->mHSList.PadScore(1024);
    //mApp->mHSList.PadScore(1280);
    //mApp->mHSList.PadScore(1536);
    //mApp->mHSList.PadScore(2048);
    
    //mApp->mHSList.mRecent=-1;
    
    //mApp->mHSList.Add("USER", gApp->mScore);
    
	mSin = 0;
    
    //mApp->AchProgress("gameover_3");
    
    //GameCenterSyncAll();
    //GameCenterSubmitScore(mApp->mHSList.GetHighestScore(), "crazy_lizard_scores");

}

GameOverScreen::~GameOverScreen()
{
	
}

void GameOverScreen::Update()
{
	mSin+=10;
}

void GameOverScreen::Draw()
{
	Graphics::SetColor();
    
    
    mApp->mMenuBackPanel.Center(gAppWidth2, MENU_PANEL_CENTER_Y);
    //mApp->mMenuHeaderGameOver.Center(gAppWidth2, MENU_HEADER_Y);
    
    
    //App->mOptionsOverlay.Center(gAppWidth2, MENU_PANEL_CENTER_Y);
    //mApp->mMenuTextOptions.Center(gAppWidth2, MENU_PANEL_CENTER_Y - 87.0f * gGlobalScale);
    
    /*
    int aMaxWidth=0;
    for(int i=0;i<mApp->mHSList.mSize;i++)
	{
        int aWidth = WidthText(FString(gApp->mHSList.mScore[i]));
        if(aWidth > aMaxWidth)aMaxWidth=aWidth;
	}
    
    int aDrawX = gAppWidth2 - (aMaxWidth / 2) - (gApp->mScoreRanks.mWidth / 2);
    int aDrawY = gAppHeight2 - 126 * gGlobalScale;
    
    mApp->mScoreRanks.Draw(aDrawX, aDrawY-2*gGlobalScale);
    aDrawX += gApp->mScoreRanks.mWidth;
    
    for(int i=0;i<mApp->mHSList.mSize;i++)
	{
		if(i == mApp->mHSList.mRecent)
        {
            DrawText(aDrawX, aDrawY, FString(gApp->mHSList.mScore[i]), gApp->mNumberBigHilighted);
        }
        else
        {
            DrawText(aDrawX, aDrawY, FString(gApp->mHSList.mScore[i]), gApp->mNumberBig);
        }
        
        aDrawY += 40 * gGlobalScale;
	}
    */
}

void GameOverScreen::DrawText(int x, int y, FString text, FSprite *pFSprite)
{
	
	for(int i=0;i<text.mLength;i++)
	{
		int aIndex = (int)(text.mData[i]) - (int)('0');
        
        
		if(aIndex>=0&&aIndex<=9){}
		else if(text.mData[i] == '%')aIndex=10;
		else if(text.mData[i] == ':')aIndex=11;
		else if(text.mData[i] == ')')aIndex=12;
		else if(text.mData[i] == '.')aIndex=13;
		else
		{
			if(text.mData[i] == ' ')x+=6;
			aIndex=-1;
		}		
		
        
		if(aIndex >= 0)
		{
			pFSprite[aIndex].Draw(x,y);
			x += pFSprite[aIndex].mWidth - 2;
		}
	}
}

int GameOverScreen::WidthText(FString text)
{
    
	int aWidth=0;
    for(int i=0;i<text.mLength;i++)
	{
		int aIndex = (int)(text.mData[i]) - (int)('0');
		
		if(aIndex>=0&&aIndex<=9){}
		else if(text.mData[i] == '%') aIndex=10;
		else if(text.mData[i] == ':')aIndex=11;
		else if(text.mData[i] == ')')aIndex=12;
		else if(text.mData[i] == '.')aIndex=13;
		else
		{
			if(text.mData[i] == ' ')aWidth+=6;
			aIndex=-1;
		}		
		
		if(aIndex >= 0)
		{
			//aWidth += mApp->mNumberBig[aIndex].mWidth - 2;
		}
	}
	return aWidth;
}

void GameOverScreen::Notify(void *pData)
{
    if((pData == &mButtonDone) || (pData == &mButtonClose))
    {
        gGame->FadeRestart();
        
        gApp->mGameOverScreen = 0;
        Kill();
    }
}
