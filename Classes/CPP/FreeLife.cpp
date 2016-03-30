//
//  FreeLife.cpp
//  LizDash
//
//  Created by Nick Raptis on 2/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "FreeLife.h"
#include "Game.h"

FreeLife::FreeLife()
{
    mScale = 1.0f;
    
    mType = GO_TYPE_FREE_LIFE;
    
    mData = &(mApp->mHeart);
    
    mWobbleSin = gRand.GetFloat(360.0f);
    mWobbleCos = gRand.GetFloat(360.0f);
    
}

FreeLife::~FreeLife()
{
    
}

void FreeLife::Update()
{
    mWobbleSin += 6.45f;
    if(mWobbleSin >= 360.0f)mWobbleSin -= 360.0f;
    
    mWobbleCos += 14.0f;
    if(mWobbleCos >= 360.0f)mWobbleCos -= 360.0f;
    
}

void FreeLife::SetUp()
{
    
    mFacing.mX = Sin(mOrbit);
    mFacing.mY = Cos(mOrbit);
    mFacing.mZ = 0.0f;
    
    mPos.mX = mFacing.mX * (SEGMENT_RADIUS + 1.2f);
    mPos.mY = mFacing.mY * (SEGMENT_RADIUS + 1.2f);
}

void FreeLife::Draw()
{
    Graphics::MatrixPush();
    Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    
    Graphics::RotateY(Sin(mWobbleSin) * 14.0f);
    Graphics::RotateX(Cos(mWobbleCos) * 6.0f);
    Graphics::RotateZ(180.0f - mOrbit);
    
    mData->Draw();
    
    Graphics::MatrixPop();
}
