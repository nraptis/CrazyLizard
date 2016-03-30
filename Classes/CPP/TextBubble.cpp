//
//  TextBubble.cpp
//  LizDash
//
//  Created by Nick Raptis on 6/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "TextBubble.h"

TextBubble::TextBubble()
{
    mX = gAppWidth2;
    mY = gAppHeight2 + 100.0f;
    
    mScale = 0.0f;
    
    mWidth = 0.0f;
    mHeight = 0.0f;
    
    mScaleMode = 0;
    mScaleTimer = 0;
    
    mYSpeed = 0.85f * gGlobalScale;
    
    mSprite = 0;
    
    mApp = gApp;
}

TextBubble::~TextBubble()
{
    
}

void TextBubble::Update()
{
    if(mScaleMode == 0)
    {
        mScale += 0.066f;
        if(mScale >= 1.0f)
        {
            mScale = 1.0f;
            mScaleMode = 1;
            mScaleTimer = 110;
        }
    }
    else if(mScaleMode == 1)
    {
        mScaleTimer--;
        if(mScaleTimer <= 0)
        {
            mScaleMode = 2;
        }
    }
    else
    {
        mScale -= 0.044f;
        if(mScale <= 0)
        {
            mScale = 0;
            Kill();
        }
    }
    
    mY -= mYSpeed;
    mYSpeed *= 0.9975f;
}

void TextBubble::Draw()
{
    Graphics::SetColor(mScale);
    
    if(mSprite)
    {
        mSprite->Draw(mX, mY, mScale, 0.0f);
    }
    else
    {
        mApp->mFontGold.Center(mText.c(), mX, mY, mScale);
        
        //mApp->mFontGold.Reset();
        //mApp->mFontGold.Write(mText.c());
        //mApp->mFontGold.Center(mX, mY, mScale);
    }
}

void TextBubble::SetSprite(FSprite *pFSprite)
{
    mSprite = pFSprite;
    mWidth = pFSprite->mWidth;
    mHeight = pFSprite->mHeight;
}

void TextBubble::SetText(const char *pText)
{
    mText = pText;
    mWidth = mApp->mFontGold.Width((char*)pText);
    mHeight = mApp->mFontGold.mMaxHeight;
}


