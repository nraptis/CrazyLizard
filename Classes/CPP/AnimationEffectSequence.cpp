//
//  AnimationEffectSequence.cpp
//  LizDash
//
//  Created by Nick Raptis on 9/17/12.
//
//

#include "AnimationEffectSequence.h"

AnimationEffectSequence::AnimationEffectSequence()
{
    mApp = gApp;
    mFrame = 0.0f;
    
    mData = 0;
    mFrameCount = 0;
}

AnimationEffectSequence::~AnimationEffectSequence()
{
    
}

void AnimationEffectSequence::SetSpriteSequence(FModelDataIndexed **pModel, int pFrameCount)
{
    mData = pModel;
    mFrameCount = pFrameCount;
}

void AnimationEffectSequence::SetUp(float pOrbit, float pZ)
{
    mOrbit = pOrbit;
    
    mFacing.mX = Sin(mOrbit);
    mFacing.mY = Cos(mOrbit);
    
    mFacing.mZ = 0.0f;
    
    mPos.mX = mFacing.mX * (SEGMENT_RADIUS + 1.0f);
    mPos.mY = mFacing.mY * (SEGMENT_RADIUS + 1.0f);
    mPos.mZ = pZ;
}

void AnimationEffectSequence::Update()
{
    mFrame += 0.66f;
    
    if(mFrame >= ((float)mFrameCount))
    {
        Kill();
    }    
}


void AnimationEffectSequence::Draw()
{
    Graphics::MatrixPush();
    Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    Graphics::Scale(mScale);
    Graphics::RotateZ(-mOrbit + 180.0f); 
    
    if(mAdditive)Graphics::BlendSetAdditive();
    else Graphics::BlendSetAlpha();
    
    Graphics::SetColor();
    
    int aFrame = (int)mFrame;
    if((aFrame >= 0) && (aFrame < mFrameCount))
    {
        mData[aFrame]->Draw();
    }
    
    Graphics::MatrixPop();
}

