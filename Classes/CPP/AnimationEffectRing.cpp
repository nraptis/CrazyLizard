
////////////////////////////////////////////////////////////////
//
//  AnimationEffectRing.cpp
//  LizDash
//
//  Created by Nick Raptis on 4/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
////////////////////////////////////////////////////////////////

#include "AnimationEffectRing.h"

AnimationEffectRing::AnimationEffectRing()
{
    mApp = gApp;
    mFrame = 0.0f;
}

AnimationEffectRing::~AnimationEffectRing()
{
    
}

void AnimationEffectRing::SetUp(float pOrbit, float pZ)
{
    mOrbit = pOrbit;
    
    mFacing.mX = Sin(mOrbit);
    mFacing.mY = Cos(mOrbit);
    mFacing.mZ = 0.0f;
    
    mPos.mX = mFacing.mX * (SEGMENT_RADIUS + 1.0f);
    mPos.mY = mFacing.mY * (SEGMENT_RADIUS + 1.0f);
    mPos.mZ = pZ;
}

void AnimationEffectRing::Update()
{
    mFrame += 0.66f;
    if(mFrame >= ((float)EFFECT_BURST_1_FRAMES))Kill();
}

void AnimationEffectRing::Draw()
{
    Graphics::MatrixPush();
    Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    Graphics::Scale(1.5f, 1.5f, 1.5f);
    Graphics::RotateZ(-mOrbit + 180.0f);
    Graphics::BlendSetAdditive();
    
    Graphics::SetColor();
    
    int aFrame = (int)mFrame;
    if((aFrame >= 0) && (aFrame < EFFECT_BURST_1_FRAMES))
    {
        mApp->mAnimationBurst1[aFrame]->Draw();
    }
    
    Graphics::MatrixPop();
}

