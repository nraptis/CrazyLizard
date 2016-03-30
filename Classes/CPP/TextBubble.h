//
//  TextBubble.h
//  LizDash
//
//  Created by Nick Raptis on 6/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef TEXT_BUBBLE_H
#define TEXT_BUBBLE_H

#include "GLApp.h"

class TextBubble : public FObject
{
public:
    
    TextBubble();
    virtual ~TextBubble();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    void                                SetSprite(FSprite *pFSprite);
    void                                SetText(const char *pText);
    
    GLApp                               *mApp;
    
    float                               mX;
    float                               mY;
    
    float                               mYSpeed;
    
    float                               mScale;
    
    float                               mWidth;
    float                               mHeight;
    
    int                                 mScaleMode;
    int                                 mScaleTimer;
    
    FString                             mText;
    FSprite                              *mSprite;
    
};

#endif
