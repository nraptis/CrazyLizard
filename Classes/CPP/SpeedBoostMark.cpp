//
//  SpeedBoostMark.cpp
//  LizDash
//
//  Created by Nick Raptis on 7/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "SpeedBoostMark.h"


SpeedBoostMark::SpeedBoostMark()
{
    mHeight = gGlobalScale * 16.0f + gRand.GetFloat(gGlobalScale * 24);
    mWidth = gGlobalScale * 1.0f + gRand.GetFloat(gGlobalScale * 1.0f);
    
    mX = -10.0f + gRand.GetFloat() * (gAppWidth + 10.0f);
    mY = -mHeight + gRand.GetFloat() * (gAppWidth + 10.0f);
    
    mSpeed = 5.0f + 4.5f * gGlobalScale;
    
    mAlpha = 0.66f + gRand.GetFloat() * 0.15f;
    
    mRed = 0.90f + gRand.GetFloat() * 0.05f;
    mGreen = 0.90f + gRand.GetFloat() * 0.05f;
    mBlue = 1.0f;
    
    //;
    
    //float                       mFade;
    
    //float                       mWidth;
    //float                       mHeight;
    
    //float                       mSpeed;
    
}

SpeedBoostMark::~SpeedBoostMark()
{
    
}


void SpeedBoostMark::Update()
{
    mAlpha -= 0.01f;
    if(mAlpha <= 0)
    {
        Kill();
    }
    
    mY += mSpeed;
    
    mHeight += mSpeed / 2.0f;
    
    //mAlpha = 2.0f + gRand.GetFloat();
    
    //mRed = 0.30f + gRand.GetFloat() * 0.05f;
    //mGreen = 0.30f + gRand.GetFloat() * 0.05f;
    //mBlue = 0.95f + gRand.GetFloat() * 0.05f;
}

void SpeedBoostMark::Draw(float pFade)
{
    Graphics::SetColor(mRed, mGreen, mBlue, mAlpha * pFade);
    Graphics::DrawRect(mX, mY, mWidth, mHeight);
}

