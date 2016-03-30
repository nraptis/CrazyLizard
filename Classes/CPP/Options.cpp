
#include "Options.h"
#include "Game.h"

Options::Options()
{
	mApp = ((GLApp*)gApp);
    
    float aButtonWidth = mApp->mMenuButtonBack[0].mWidth;
    float aButtonHeight = mApp->mMenuButtonBack[0].mHeight;
    
    mButtonDone.Setup(gAppWidth2 - (aButtonWidth / 2.0f), MENU_DONE_BUTTON_Y, mApp->mMenuButtonBack, 2, this);
    mButtonDone.SetOverlays(&(mApp->mMenuButtonTextDone));
    
    
    
    mButtonControl1.Setup(gAppWidth2 - 102.0f * gGlobalScale, gAppHeight2 - 111.0f * gGlobalScale, &(mApp->mOptionsControlSegment[0]), this);
    
    mButtonControl2.Setup(gAppWidth2 - 34.0f * gGlobalScale, gAppHeight2 - 111.0f * gGlobalScale, &(mApp->mOptionsControlSegment[1]), this);
    
    
    
    mMusicSlider.SetSprite(&mApp->mOptionsThumb);
	mMusicSlider.Size(gAppWidth2 - 46.0f * gGlobalScale, gAppHeight2 - 38.0f * gGlobalScale, 152.0f * gGlobalScale, mApp->mOptionsThumb.mHeight);
	mMusicSlider.SetPercent(gVolumeMusic);
    AddChild(mMusicSlider);
    
    
    
    mSFXSlider.SetSprite(&mApp->mOptionsThumb);
	mSFXSlider.Size(gAppWidth2 - 46.0f * gGlobalScale, gAppHeight2 + 0.0f * gGlobalScale, 152.0f * gGlobalScale, mApp->mOptionsThumb.mHeight);
	mSFXSlider.SetPercent(gVolumeSound);
    AddChild(mSFXSlider);
    
    
    UpdateControlButtons();
}

Options::~Options()
{
	//mApp->SaveStatic();
}

void Options::Update()
{
    

}

void Options::Draw()
{
    Graphics::SetColor();
    
    if(gGame->mMenu == 0)mApp->mMenuBackPanel.Center(gAppWidth2, MENU_PANEL_CENTER_Y);
    
    mApp->mMenuHeaderOptions.Center(gAppWidth2, MENU_HEADER_Y);
    
    mApp->mOptionsControlSegmentUnderlay.Center(gAppWidth2, gAppHeight2 - 86.0f * gGlobalScale);
    
    mApp->mOptionsSliderMusic.Center(gAppWidth2 - 2.0f * gGlobalScale, gAppHeight2 - 24.0f * gGlobalScale);
    mApp->mOptionsSliderSFX.Center(gAppWidth2 - 2.0f * gGlobalScale, gAppHeight2 + 13.0f * gGlobalScale);
    
}

void Options::Touch(int x, int y)
{
    /*
    
	PlayMusic(gSandbox + "music.mp3");
	
	if(mRect[0].Contains(x,y))
	{
		mApp->mSoundOn=true;
	}
    
	else if(mRect[1].Contains(x,y))
	{
		mApp->mSoundOn=false;
	}
	
	else if(mRect[2].Contains(x,y))
	{
		mApp->mMusicOn=true;
	}
    
	else if(mRect[3].Contains(x,y))
	{
		mApp->mMusicOn=false;
	}
    
    */
}

void Options::Notify(void *pData)
{
    
    if(pData == &mSFXSlider)
    {
        core_sound_setVolume(mSFXSlider.GetPercent());
        return;
    }
    
    if(pData == &mMusicSlider)
    {
        core_sound_musicSetVolume(mMusicSlider.GetPercent());
        return;
    }
    
    
    
    
    
    
	if(pData==&mButtonDone)
	{
		//mApp->SaveStatic();
        
		mApp->mOptions=0;
		Kill();
	}
    
    /*
    if(pData==&mButtonMusicCheck)
    {
        if(mButtonMusicCheck.mCheckBoxState)
        {
            PlayMusic("music.mp3");
        }
        else
        {
            SwitchToAppMusic();
        }
    }
    
    mApp->mSoundOn=mButtonSFXCheck.mCheckBoxState;
    
    if(pData == &mButtonSFXCheck)
    {
        if(mApp->mSoundOn)
        {
            gApp->mSoundGlobalButtonClick.Play();
        }
    }
    
    */
    
    if(pData == &mButtonControl1)mApp->mControlMethod = CONTROL_METHOD_JOYSTICK;
    if(pData == &mButtonControl2)mApp->mControlMethod = CONTROL_METHOD_BOTH;
    
    UpdateControlButtons();
    
    /*
    if(pData == &mButtonLightCheck)
    {
        mApp->mLightEnabled = !(mApp->mLightEnabled);
        if(mApp->mSoundOn)
        {
            gApp->mSoundGlobalButtonClick.Play();
        }
    }
    */
    
}


void Options::UpdateControlButtons()
{
    mButtonControl1.mSpriteUp = &(mApp->mOptionsControlSegment[0]);
    mButtonControl2.mSpriteUp = &(mApp->mOptionsControlSegment[1]);
    //mButtonControl3.mSpriteUp = &(mApp->mOptionsControlSegment[2]);
    
    
    if(mApp->mControlMethod == CONTROL_METHOD_JOYSTICK)
    {
        mButtonControl1.mSpriteUp = &(mApp->mOptionsControlSegmentSelected[0]);
    }
    else //else if(mApp->mControlMethod == CONTROL_METHOD_ACCELEROMETER)
    {
        
        mButtonControl2.mSpriteUp = &(mApp->mOptionsControlSegmentSelected[1]);
    }
    //else{mButtonControl3.mSpriteUp = &(mApp->mOptionsControlSegmentSelected[2]);}
    
}


