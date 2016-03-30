//  SpikeBomb.cpp
//  LizDash
//
//  Created by Nick Raptis on 2/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#include "SpikeBomb.h"
#include "Game.h"

SpikeBomb::SpikeBomb()
{
    mData = &(gApp->mBomb);
    
    mType = GO_TYPE_SPIKE_BOMB;
    
    mScaleSin = gRand.GetFloat(360.0f);
    mRotationSin = gRand.GetFloat(360.0f);
    mRotationCos = gRand.GetFloat(360.0f);
    
    mSparkFrame = 0.0f;
}

SpikeBomb::~SpikeBomb()
{
    
}

void SpikeBomb::Update()
{
    mScaleSin += 5.0f;
    if(mScaleSin >= 360.0f)mScaleSin -= 360.0f;
    
    mRotationSin += 8.0f;
    if(mRotationSin >= 360.0f)mRotationSin -= 360.0f;
    
    mRotationCos += 6.5f;
    if(mRotationCos >= 360.0f)mRotationCos -= 360.0f;
    
    mSparkFrame += 0.66f;
    if(mSparkFrame >= (float)SPARK_FRAMES)mSparkFrame -= ((float)SPARK_FRAMES);
    
}

void SpikeBomb::Draw()
{
    Graphics::MatrixPush();
    
    Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    
    //Graphics::Scale(1.0f, 1.0f, Sin(mScaleSin) * 0.1f + 1.0f);
    
    Graphics::RotateY(Sin(mRotationSin) * 10);
    Graphics::RotateX(Cos(mRotationCos) * 4.0f);
    Graphics::RotateZ(-mOrbit + 180.0f);
    
    mData->Draw();
    
    Graphics::MatrixPop();
    
}


void SpikeBomb::SetUp()
{
    mFacing.mX = Sin(mOrbit);
    mFacing.mY = Cos(mOrbit);
    mFacing.mZ = 0.0f;
    
    mPos.mX = mFacing.mX * (SEGMENT_RADIUS + 1.20f);
    mPos.mY = mFacing.mY * (SEGMENT_RADIUS + 1.20f);
}

void SpikeBomb::DrawEffects()
{
    int aFrame = (int)mSparkFrame;
    if(aFrame < 0)aFrame = 0;
    if(aFrame >= SPARK_FRAMES)aFrame = (SPARK_FRAMES - 1);
    
    //Graphics::BlendSetAdditive();
    Graphics::BlendSetAlpha();
    Graphics::MatrixPush();
    
    Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    
    Graphics::RotateY(Sin(mRotationSin) * 10);
    Graphics::RotateX(Cos(mRotationCos) * 4.0f);
    Graphics::RotateZ(-mOrbit + 180.0f);
    
    mApp->mAnimationBombSpark[aFrame]->Draw();
    
    Graphics::MatrixPop();
    Graphics::BlendSetAlpha();
}
