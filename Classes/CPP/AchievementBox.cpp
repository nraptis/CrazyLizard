//
//  AchievementBox.cpp
//  LizDash
//
//  Created by Nick Raptis on 1/14/13.
//
//

#include "AchievementBox.h"
#include "GLApp.h"


AchievementText::AchievementText(const char *pName)
{
    mName = pName;
    FString aPath = FString("ach_text_") + mName;
    mSprite.Load(aPath.c());
}

AchievementText::~AchievementText()
{
    
}

AchievementBox::AchievementBox(AchievementText *pText)
{
    mX = gAppWidth2;
    mY = gApp->mAchievementBack.mHeight / 2.0f + 16.0f;
    
    mScale = 0.0f;
    
    mScaleSpeed = 0.015f;
    mShiftY = 0.0f;
    mTextFSprite = &(pText->mSprite);
    
    mTimer = 95;
    
    mKilled = false;
    mMode = 0;
    
    gApp->mSoundAchievement.Play();
}

AchievementBox::~AchievementBox()
{
    
}

void AchievementBox::Update()
{
    if(mMode == 0)
    {
        mScale += mScaleSpeed;
        mScaleSpeed += 0.001f;
        if(mScale >= 1.0f)mMode = 1;
    }
    else if(mMode == 1)
    {
        mScale += mScaleSpeed;
        mScaleSpeed -= 0.01f;
        if(mScale <= 1.0f)
        {
            mScale = 1.0f;
            mMode = 2;
        }
    }
    else if(mMode == 2)
    {
        mTimer--;
        if(mTimer <= 0)
        {
            mTimer = 0;
            mMode = 3;
        }
    }
    else if(mMode == 3)
    {
        mScale -= 0.035f;
        if(mScale <= 0.0f)
        {
            mScale = 0.0f;
            mKilled = true;
        }
    }
}

void AchievementBox::Draw()
{
    if(mScale > 0)
    {
        float aRotation = 0.0f;
        float aShift = ((1 - mScale) * (300.0f));
        
        Graphics::SetColor(0.85f);
        
        gApp->mAchievementBack.Draw(mX, mY - aShift, mScale, aRotation);
        if(mTextFSprite)mTextFSprite->Draw(mX, mY - aShift, mScale, aRotation);
        
        Graphics::SetColor();
    }
}
