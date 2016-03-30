
//  Ring.cpp
//  LizDash
//
//  Created by Nick Raptis on 2/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#include "Ring.h"
#include "Game.h"

Ring::Ring()
{
    SetRadius(1.15f);
    
    mSpinRotation = gRand.GetFloat() * 360.0f;
    mRotationSpeed = 4.0f;
    
    if(gRand.GetBool())mRotationSpeed = (-mRotationSpeed);
    
    mSequenceSparkle = 0;
    mSparkleFrame = 0.0f;
    
    mData = &(gApp->mRing);
    
    mType = GO_TYPE_RING;
}

Ring::~Ring()
{
    
}

void Ring::SetUp()
{
    GameObject::SetUp();
    mPos.mX = mFacing.mX * (SEGMENT_RADIUS * 1.16f);
    mPos.mY = mFacing.mY * (SEGMENT_RADIUS * 1.16f);
}

void Ring::Update()
{
    mSpinRotation += mRotationSpeed;
    if(mSpinRotation >= 360.0f)mSpinRotation-=360.0f;
    if(mSpinRotation < 0.0f)mSpinRotation+=360.0f;
    
    
    /*
    if(mSequenceSparkle == 0)
    {
        if((mSpinRotation >= 340.0f) || (mSpinRotation <= 20.0f))
        {
            if(gRand.Get(20) == 8)
            {
                mSequenceSparkle = &gApp->mRingSparkleSequence[gRand.Get(2)];
                mSparkleFrame = 0.0f;
            }
        }
    }
    else
    {
        mSparkleFrame += 0.6f;
        if(mSparkleFrame >= (float)(mSequenceSparkle->mCount))
        {
            mSparkleFrame = 0.0f;
            mSequenceSparkle = 0;
        }
    }
    */
}

void Ring::Draw()
{
    Transform();
    mData->Draw();
    TransformEnd();
}

void Ring::Transform()
{
    Graphics::MatrixPush();
    Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    //Graphics::RotateZ(-mOrbit + 180.0f);// + mSpinRotation);
    Graphics::RotateZ(mSpinRotation);
}

void Ring::TransformEnd()
{
    Graphics::MatrixPop();
}

void Ring::DrawEfficient()
{
    Transform();
    mData->DrawEfficient();
    TransformEnd();
}

void Ring::DrawEffects()
{
    
    /*
    
    if(mSequenceSparkle)
    {
        Graphics::MatrixPush();
        Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
        Graphics::RotateZ(-mOrbit + 180.0f + mSpinRotation);
        
        mSequenceSparkle->Draw(mSparkleFrame);
        
        Graphics::MatrixPop();
    }
    
    */
    
}




