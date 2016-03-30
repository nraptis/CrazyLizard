
#include "MainMenu.h"
#include "MainMenuLetter.h"

MainMenu *gMainMenu = 0;

MainMenu::MainMenu()
{
    mName = "Main Menu";
    
    SetFrame(0.0f, 0.0f, 768.0f, 1024.0f);
    
    mClipsContent = false;
    
    gMainMenu = this;
	mApp = ((GLApp*)gApp);
    
    //GameCenterSubmitScore(mApp->mHSList.GetHighestScore(), "crazy_lizard_scores");
    //GameCenterSyncAll();
    
    mCameraLeftRightSin = 0.0f;
    mCameraUpDownSin = 0.0f;
    
    mAnimatingIn = false;
    mAnimatingOut = false;
    
    float aBigButtonWidth = mApp->mMainMenuButtonPlay[0].mWidth;
    float aBigButtonHeight = mApp->mMainMenuButtonPlay[0].mHeight;
    
    float aSmallButtonWidth = mApp->mMainMenuButtonHS[0].mWidth;
    float aSmallButtonHeight = mApp->mMainMenuButtonHS[0].mHeight;
    
    float aButtonYGap = -2.0f * gGlobalScale;
    
    float aButtonX;
    
    if(gIsLargeScreen)
    {
        aButtonX = gAppWidth - (aBigButtonWidth + 20.0f * gGlobalScale);
    }
    else
    {
        aButtonX = gAppWidth - (aBigButtonWidth + 4.0f * gGlobalScale);
    }
    
    // 
    
    //float aButtonY = gAppHeight - 230.0f * gGlobalScale;
    float aButtonY = gAppHeight - 160.0f * gGlobalScale;
    
    aButtonY -= (80.0f * gGlobalScale);
    
    float aRightButtonX = (aButtonX + aBigButtonWidth) - aSmallButtonWidth;
    
    mButtonPlay.AddOverlay(&(mApp->mMainMenuButtonPlay[0]), &(mApp->mMainMenuButtonPlay[1]));
    mButtonPlay.SetPos(aButtonX, aButtonY);
    
    
    
    aButtonY += (aButtonYGap + aBigButtonHeight);
    
    mButtonAchievements.SetOverlays(&(mApp->mMainMenuButtonAch[0]), &(mApp->mMainMenuButtonAch[1]));
    mButtonAchievements.SetUpTopLeft(aButtonX, aButtonY, this);
    
    mButtonHighScores.SetOverlays(&(mApp->mMainMenuButtonHS[0]), &(mApp->mMainMenuButtonHS[1]));
    mButtonHighScores.SetUpTopLeft(aRightButtonX, aButtonY, this);
    
    aButtonY += (aButtonYGap + aSmallButtonHeight);
    
    mButtonOptions.SetOverlays(&(mApp->mMainMenuButtonOptions[0]), &(mApp->mMainMenuButtonOptions[1]));
    mButtonOptions.SetUpTopLeft(aButtonX, aButtonY, this);
    
    
    mButtonGames.SetOverlays(&(mApp->mMainMenuButtonGames[0]), &(mApp->mMainMenuButtonGames[1]));
    mButtonGames.SetUpTopLeft(aRightButtonX, aButtonY, this);
    
    aButtonY += (aButtonYGap + aSmallButtonHeight);
    
    //mButtonStore.SetOverlays(mApp->mMainMenuButtonPlay[0], mApp->mMainMenuButtonPlay[1]);
    //mButtonStore.SetUpTopLeft(aButtonX, aButtonY, this);
    
    mButton[0] = &mButtonPlay;
    mButton[1] = &mButtonAchievements;
    mButton[2] = &mButtonHighScores;
    mButton[3] = &mButtonOptions;
    mButton[4] = &mButtonGames;
    //mButton[5] = &mButtonStore;
    
    
    for(int i=0;i<MM_BUTTON_COUNT;i++)
    {
        //mButtonPos[i] = FVec2(mButton[i]->mX, mButton[i]->mY);
        //mButtonPos[i] = FVec2(mButton[i]->mX, mButton[i]->mY);
        //mButtonVel[i] = FVec2(0.0f, 0.0f);
        //mButtonOffset[i] = FVec2(0.0f, 0.0f);
        //mButtonWait[i] = 0;
    }
    
    for(int i=0;i<MM_BUTTON_COUNT;i++)
    {
        //mButton[i]->mDrawManual = true;
        //mButton[i]->mMultiTouch = true;
    }
    
    float aLetterTop = 9.50f;
    float aLetterZ = aLetterTop;
    float aLetterX = -4.5f;
    float aLetterY = 8.0f;
    
    mCameraDist = 25.87f;
    if(gIsLargeScreen == false)
    {
        mCameraDist = 28.0f;
        if(gAppHeight < 500.0f)
        {
            
        }
    }
    
    for(int i=0;i<5;i++)
    {
        MainMenuLetter *aLetter = new MainMenuLetter();
        aLetter->mPos = FVec3(aLetterX, aLetterY, aLetterZ);
        aLetter->mData = &(gApp->mTitleTextCrazy[4-i]);
        aLetterX += 2.25f;
        mLetters += aLetter;
    }
    
    aLetterZ -= 4.0f;
    aLetterX = -5.65f;
    
    for(int i=0;i<6;i++)
    {
        MainMenuLetter *aLetter = new MainMenuLetter();
        aLetter->mPos = FVec3(aLetterX, aLetterY, aLetterZ);
        aLetter->mData = &(gApp->mTitleTextLizard[5-i]);
        aLetterX += 2.25f;
        mLetters += aLetter;
    }
    
    AnimateIn();
}

void MainMenu::PositionContent()
{
    //Log("MMSubs[%f x %f]\n", gAppWidth, gAppHeight);
    
    float aBigButtonWidth = mApp->mMainMenuButtonPlay[0].mWidth;
    float aBigButtonHeight = mApp->mMainMenuButtonPlay[0].mHeight;
    
    float aSmallButtonWidth = mApp->mMainMenuButtonHS[0].mWidth;
    float aSmallButtonHeight = mApp->mMainMenuButtonHS[0].mHeight;
    
    float aButtonYGap = -2.0f * gGlobalScale;
    
    float aButtonX;
    
    if(gIsLargeScreen)
    {
        aButtonX = gAppWidth - (aBigButtonWidth + 20.0f * gGlobalScale);
    }
    else
    {
        aButtonX = gAppWidth - (aBigButtonWidth + 4.0f * gGlobalScale);
    }
    
    //
    
    //float aButtonY = gAppHeight - 230.0f * gGlobalScale;
    float aButtonY = gAppHeight - (aSmallButtonHeight + 52.0f);
    float aRightButtonX = (aButtonX + aBigButtonWidth) - aSmallButtonWidth;
    
    
    mButtonOptions.SetOverlays(&(mApp->mMainMenuButtonOptions[0]), &(mApp->mMainMenuButtonOptions[1]));
    mButtonOptions.SetUpTopLeft(aButtonX, aButtonY, this);
    
    mButtonGames.SetOverlays(&(mApp->mMainMenuButtonGames[0]), &(mApp->mMainMenuButtonGames[1]));
    mButtonGames.SetUpTopLeft(aRightButtonX, aButtonY, this);
    
    aButtonY -= (aButtonYGap + aSmallButtonHeight);
    
    mButtonAchievements.SetOverlays(&(mApp->mMainMenuButtonAch[0]), &(mApp->mMainMenuButtonAch[1]));
    mButtonAchievements.SetUpTopLeft(aButtonX, aButtonY, this);
    
    mButtonHighScores.SetOverlays(&(mApp->mMainMenuButtonHS[0]), &(mApp->mMainMenuButtonHS[1]));
    mButtonHighScores.SetUpTopLeft(aRightButtonX, aButtonY, this);
    
    aButtonY -= (aButtonYGap + aBigButtonHeight);
    
    mButtonPlay.SetOverlays(&(mApp->mMainMenuButtonPlay[0]), &(mApp->mMainMenuButtonPlay[1]));
    mButtonPlay.SetUpTopLeft(aButtonX, aButtonY, this);
    
    
    
}


MainMenu::~MainMenu()
{
    
    FreeList(MainMenuLetter, mLetters);
    
    for(int i=0;i<MM_BUTTON_COUNT;i++)mButton[i]=0;
    
    gMainMenu = 0;
    
}

void MainMenu::RenderLetters()
{
    EnumList(MainMenuLetter, aLetter, mLetters)
    {
        //aLetter->mPos = FVec3(gRand.GetFloat(-6.0f,6.0f), 8.0f, 18.0f);
        aLetter->Draw();
    }
}

void MainMenu::Update()
{
    
    mCameraLeftRightSin += 2.0f;;
    if(mCameraLeftRightSin >= 360.0f)mCameraLeftRightSin -= 360.0f;
    
    mCameraUpDownSin += 0.65f;
    if(mCameraUpDownSin >= 360.0f)mCameraUpDownSin -= 360.0f;
    
    if(mAnimatingIn)
    {
        
        for(int i=0;i<MM_BUTTON_COUNT;i++)
        {
            if(mButtonAnimationDelay[i] > 0)
            {
                mButtonAnimationDelay[i]--;
            }
            else
            {
                if(mButtonAnimationMode[i] == 0)
                {
                    mButtonScaleSpeed[i] = 0.035f;
                    mButtonScale[i] += mButtonScaleSpeed[i];
                    
                    if(mButtonScale[i] > 1.0f)
                    {
                        mButtonAnimationMode[i] = 1;
                    }
                }
                else if(mButtonAnimationMode[i] == 1)
                {
                    mButtonScale[i] += mButtonScaleSpeed[i];
                    mButtonScaleSpeed[i] -= 0.01f;
                    
                    if(mButtonScale[i] < 1.0f)
                    {
                        mButtonScale[i] = 1.0f;
                        mButtonAnimationMode[i] = 2;
                    }
                }
                else
                {
                    
                }
                
                //if(mButtonScale[i] > 1.15f)mButtonScale[i] = 1.15f;
                
                //mButtonScaleSpeed[i] *= 0.99f;
            }
            
            /*
            mButtonScale[i] = 0.0f;
             = 0.075f;
            mButtonFade[i] = 0.0f;
            mButtonFadeSpeed[i] = 0.0f;
            mButtonScaleDir[i] = 0.0f;
            mButtonScaleDelay[i] = i * 20;
            */
            
        }
        
    }
    
    EnumList(MainMenuLetter, aLetter, mLetters)aLetter->Update();
    
}

void MainMenu::Draw()
{
    
    Graphics::MatrixGoProjection();
    Graphics::MatrixLoadIdentity();
    
    Graphics::MatrixPerspective(64.0f, (float)gAppWidth / (float)gAppHeight);
    
    Graphics::MatrixGoModelView();
    Graphics::MatrixLoadIdentity();
    
    
    
    float aX = 0.0f;
    float aY = 0.0f;
    float aZ = 0.0f;
    
    float aRotation = Sin(mCameraLeftRightSin) * 0.1f;
    
    float aCameraX = aX + Sin(aRotation) * mCameraDist;
    float aCameraY = aY + Cos(aRotation) * mCameraDist;
    
    float aCameraZ = aZ + 0.25f + Sin(mCameraUpDownSin) * 1.5f;
    
    Graphics::MatrixLookAt(aCameraX,aCameraY,aCameraZ,
                           aX, aY, aZ,
                           0.0f,0.0f,1.0f);
    
    Graphics::SetShadeSmooth();
    Graphics::EnableCullFaces();
    Graphics::DepthMaskTrue();
    Graphics::BlendDisable();
    Graphics::EnableDepth();
    Graphics::ClearDepth();
    Graphics::BlendDisable();
    
    EnumList(MainMenuLetter, aLetter, mLetters)
    {
        aLetter->Draw();
    }
    
    Graphics::Go2D();
    Graphics::BlendEnable();
    Graphics::BlendSetAlpha();
    
    
    /*
    for(int i=0;i<MM_BUTTON_COUNT;i++)
    {
        if(mButton[i])
        {
            EnumList(ButtonLayer, aLayer, mButton[i]->mLayerList)
            {
                FSprite *aFSprite = aLayer->mSpriteUp;
                
                if(mButton[i]->mPressed)
                {
                    if(aLayer->mSprite[1])
                    {
                        aFSprite = aLayer->mSprite[1];
                    }
                }
                if(aFSprite)
                {
                    float aWidth = aFSprite->mWidth;
                    float aHeight = aFSprite->mHeight;
                    
                    float aX = mButton[i]->mX + aLayer->mOffsetX;
                    float aY = mButton[i]->mY + aLayer->mOffsetY;
                    
                    if(mButtonScale[i] > 0.0f)
                    {
                        aFSprite->Draw(aX + aWidth / 2.0f, aY + aHeight / 2.0f, mButtonScale[i], 0.0f);
                    }
                }
            }
        }
    }
    */
    
    DrawTransform();
    
    Graphics::SetColor();
    Graphics::OutlineRect(0.0f, 0.0f, gAppWidth, gAppHeight, 15.0f);
    
}

void MainMenu::AnimateIn()
{
    Log("###\n###\nANIMATE IN!!!\n###\n###\n");
    
    for(int i=0;i<MM_BUTTON_COUNT;i++)
    {
        mButtonScale[i] = 0.0f;
        mButtonScaleSpeed[i] = 0.075f;
        mButtonFade[i] = 0.0f;
        mButtonFadeSpeed[i] = 0.0f;
        mButtonAnimationMode[i] = 0;
        mButtonAnimationDelay[i] = 8 + i * 6; //40 + i * 14;
    }
    
    /*
    for(int i=0;i<MM_BUTTON_COUNT;i++)
    {
        mButtonPos[i] = FVec2(mButton[i]->mX, mButton[i]->mY);
        
        
        mButtonPos[i] = FVec2(mButton[i]->mX, mButton[i]->mY);
        
        mButtonVel[i] = FVec2(0.0f, 0.0f);
        
        mButtonOffset[i] = FVec2(0.0f, 0.0f);
        
        mButtonWait[i] = 0;
    }
    
    
    mButtonWait[0] = 0;
    
    mButtonWait[1] = 30;
    mButtonWait[2] = 35;
    
    mButtonWait[3] = 60;
    mButtonWait[4] = 65;
    
    mButtonWait[5] = 90;
    
    for(int i=0;i<MM_BUTTON_COUNT;i++)
    {
        mButtonOffset[i] = FVec2(20.0f, 760.0f);
    }
    
    */
    
    mAnimatingIn = true;
    mAnimatingOut = false;
}

void MainMenu::AnimateOut()
{
    mAnimatingIn = false;
    mAnimatingOut = true;
}

void MainMenu::Touch(int x, int y)
{
    //AnimateIn();
}

void MainMenu::Drag(int x, int y)
{
    
}

void MainMenu::Release(int x, int y)
{
    
}

void MainMenu::MultiTouch(int x, int y, void *pData)
{
    for(int i=0;i<MM_BUTTON_COUNT;i++)
    {
        //if(mButton[i])mButton[i]->MultiTouch(x, y, pData);
    }
}

void MainMenu::MultiRelease(int x, int y, void *pData)
{
    for(int i=0;i<MM_BUTTON_COUNT;i++)
    {
        //if(mButton[i])mButton[i]->MultiRelease(x, y, pData);
    }
}

void MainMenu::MultiDrag(int x, int y, void *pData)
{
    for(int i=0;i<MM_BUTTON_COUNT;i++)
    {
        //if(mButton[i])mButton[i]->MultiDrag(x, y, pData);
    }
}

void MainMenu::FlushMultiTouch()
{
    for(int i=0;i<MM_BUTTON_COUNT;i++)
    {
        //if(mButton[i])mButton[i]->FlushMultiTouch();
    }
}

void MainMenu::Notify(void *pData)
{
	if(pData==&mButtonGames)
	{
        //OpenURL((const char*)"itms://itunes.com/apps/sunshine-games");
        
        //sunshine-games
        //OpenURL((const char*)"itms://itunes.com/apps/froggy-studios/id389062016");
        
        //OpenURL((const char*)"https://itunes.apple.com/us/artist/froggy-studios/id389062016");
        
        //OpenURL((const char*)"itms://itunes.com/apps/froggystudios");

        //OpenURL((const char*)"https://itunes.apple.com/froggy-studios/id389062016");
        
        
        
        //TODO: Correct link, dslkfsnldkf
        //OpenURL((const char*)"itms-apps://itunes.com/apps/froggystudios");
	}
	if(pData==&mButtonPlay)
	{
        mApp->PlayGame();
	}
	if(pData==&mButtonOptions)
	{
		mApp->ShowOptions();
    }
	if(pData==&mButtonHighScores)
	{
        mApp->ShowGameCenterMenu();
        //GameCenterShowLeaderboard("crazy_lizard_scores");
	}
	if(pData==&mButtonAchievements)
	{
        mApp->ShowGameCenterMenu();
        //GameCenterShowAchievements();
        
    }
    if(pData == &mButtonStore)
    {
        mApp->ShowDialogWindow(&(mApp->mDialogBoxTextJoystick));
    }
}


