//
//  AchievementBox.h
//  LizDash
//
//  Created by Nick Raptis on 1/14/13.
//
//

#ifndef ACHIEVEMENT_BOX_H
#define ACHIEVEMENT_BOX_H

#include "FSprite.h"

class AchievementText
{
public:
    
    AchievementText(const char *pName);
    ~AchievementText();
    
    FSprite                  mSprite;
    
    FString                 mName;
    
};

class AchievementBox
{
public:
    
    AchievementBox(AchievementText *pText);
    ~AchievementBox();
    
    void                    Update();
    void                    Draw();

    float                   mX;
    float                   mY;

    float                   mScale;
    float                   mScaleSpeed;

    float                   mShiftY;
    
    FSprite                  *mTextFSprite;

    int                     mMode;
    
    int                     mTimer;
    
    bool                    mKilled;
    
};

#endif
