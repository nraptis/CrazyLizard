//
//  LuckyCoin.cpp
//  LizDash
//
//  Created by Nick Raptis on 2/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LuckyCoin.h"
#include "Game.h"

LuckyCoin::LuckyCoin()
{
    mPassed = false;
    mIgnorePass = false;
    
    mScale = 1.0f;
    
    mType = GO_TYPE_LUCKY_COIN;
    
    mData = &mApp->mStar;
    
    mWobbleSin = gRand.GetFloat(360.0f);
    mWobbleCos = gRand.GetFloat(360.0f);
}

LuckyCoin::~LuckyCoin()
{
    
}

void LuckyCoin::Update()
{
    mWobbleSin += 6.45f;
    if(mWobbleSin >= 360.0f)mWobbleSin -= 360.0f;
    
    mWobbleCos += 14.0f;
    if(mWobbleCos >= 360.0f)mWobbleCos -= 360.0f;
    
}

void LuckyCoin::SetUp()
{
    
    mFacing.mX = Sin(mOrbit);
    mFacing.mY = Cos(mOrbit);
    mFacing.mZ = 0.0f;
    
    mPos.mX = mFacing.mX * (SEGMENT_RADIUS + 1.45f);
    mPos.mY = mFacing.mY * (SEGMENT_RADIUS + 1.45f);
}

void LuckyCoin::Draw()
{
    Graphics::MatrixPush();
    Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    
    Graphics::RotateY(Sin(mWobbleSin) * 14.0f);
    Graphics::RotateX(Cos(mWobbleCos) * 6.0f);
    Graphics::RotateZ(180.0f - mOrbit);
    
    mData->Draw();
    
    Graphics::MatrixPop();
}
