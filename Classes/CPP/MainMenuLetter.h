//
//  MainMenuLetter.h
//  LizDash
//
//  Created by Nick Raptis on 9/29/12.
//
//

#ifndef MAIN_MENU_LETTER_H
#define MAIN_MENU_LETTER_H

#include "GLApp.h"

class MainMenuLetter : public FObject
{
public:
    
    MainMenuLetter();
    virtual ~MainMenuLetter();
    
    virtual void            Update();
    virtual void            Draw();
    
    FModelDataIndexed        *mData;
    
    
    float                   mWobbleXSin;
    float                   mWobbleXSinSpeed;
    
    float                   mWobbleYSin;
    float                   mWobbleYSinSpeed;
    
    float                   mWobbleZSin;
    float                   mWobbleZSinSpeed;
    
    
    float                   mScale;
    float                   mRotationBase;
    float                   mRotationOffset;
    
    FVec3                   mPos;
};

#endif
