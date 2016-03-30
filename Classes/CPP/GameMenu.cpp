#include "GameMenu.h"
#include "Game.h"

GameMenu::GameMenu()
{
	mApp = ((GLApp*)gApp);
	mGame = mApp->mGame;
    
    SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    float aSpacing = 3.0f * gGlobalScale;
    
    float aButtonWidth = mApp->mMenuButtonBack[0].mWidth;
    float aButtonHeight = mApp->mMenuButtonBack[0].mHeight;
    
    mButtonResumeGame.Setup(gAppWidth2 - (aButtonWidth / 2.0f), MENU_DONE_BUTTON_Y, mApp->mMenuButtonBack, 2, this);
    mButtonResumeGame.SetOverlays(&(mApp->mMenuButtonTextResumeGame));
    
    mButtonSettings.Setup(gAppWidth2 - (aButtonWidth / 2.0f), mButtonResumeGame.GetFrame().mY - (aButtonHeight + aSpacing), mApp->mMenuButtonBack, 2, this);
    mButtonSettings.SetOverlays(&(mApp->mMenuButtonTextOptions));
    
    mButtonQuit.Setup(gAppWidth2 - (aButtonWidth / 2.0f), mButtonSettings.GetFrame().mY - (aButtonHeight + aSpacing), mApp->mMenuButtonBack, 2, this);
    mButtonQuit.SetOverlays(&(mApp->mMenuButtonTextMainMenu));
    
    //mButtonResumeGame.mDrawManual = true;
    //mButtonSettings.mDrawManual = true;
    //mButtonQuit.mDrawManual = true;
    
}

GameMenu::~GameMenu()
{
	
}
	
void GameMenu::Update()
{
	
}

void GameMenu::Draw()
{
    Graphics::SetColor();
    
    mApp->mMenuBackPanel.Center(gAppWidth2, MENU_PANEL_CENTER_Y);
    
    if(mApp->mOptions == 0)
    {
        mApp->mMenuHeaderPaused.Center(gAppWidth2, MENU_HEADER_Y);
        
        //mButtonResumeGame.Draw();
        //mButtonSettings.Draw();
        //mButtonQuit.Draw();
        
    }
}
	
void GameMenu::Touch(int x, int y)
{
	
}

void GameMenu::Drag(int x, int y)
{
	
}

void GameMenu::Release(int x, int y)
{
	
}
	
void GameMenu::Notify(void *pData)
{
	if(pData==&mButtonResumeGame)
	{
		if(mGame)mGame->Notify(this);
	}
	else if(pData==&mButtonSettings)
	{
		mApp->ShowOptions();
	}

    else if(pData==&mButtonGameCenter)
	{
		//mApp->ShowOptions();
	}
	else //mButtonMainMenu
	{
        if(mGame)
        {
            mGame->Notify(this);
            mGame->FadeRestart();
        }
    }
}