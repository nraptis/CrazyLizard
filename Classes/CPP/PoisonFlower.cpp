//
//  PoisonFlower.cpp
//  LizDash
//
//  Created by Nick Raptis on 4/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PoisonFlower.h"
#include "Game.h"
#include "Gecko.h"

PoisonFlower::PoisonFlower()
{
    mType = GO_TYPE_POISON_FLOWER;
    
    mSnapRotation = true;
    
    mFalling = false;
    
    //mLeaves = &(mApp->mFlowerLeaves);
    //mData = &(mApp->mFlowerSpiked);
}

PoisonFlower::~PoisonFlower()
{
    
}

void PoisonFlower::Update()
{
    if(mHit)
    {
        mHitRot += mHitRotSpeed;
        
        mPos += mHitSpeed;
        
        mHitSpeed.mZ -= 0.005f;
        
        mHitSpeed.mX *= 0.99f;
        mHitSpeed.mY *= 0.99f;
        mHitSpeed.mZ -= 0.025f;
        
        mHitRotSpeed.mX *= 0.925f;
        mHitRotSpeed.mY *= 0.925f;
        mHitRotSpeed.mZ *= 0.925f;
    }
}

void PoisonFlower::Draw()
{
    Graphics::MatrixPush();
    Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    Graphics::Scale(mScale);
    Graphics::RotateZ(-mOrbit + 180.0f + mSpinRotation);
    if(mHit)
    {
        Graphics::RotateX(mHitRot.mX);
        Graphics::RotateY(mHitRot.mY);
    }
    
    if(mLeaves)mLeaves->Draw();
    if(mData)mData->Draw();
    
    Graphics::MatrixPop();
}

void PoisonFlower::DrawEffects()
{
    
}

void PoisonFlower::Kaboom()
{
    
    float aAngleDiff = DistanceBetweenAngles(gGame->mGecko.mOrbit, mOrbit);
    
    //FVec3 aFlingVector = GetFlingVector(aAngleDiff * 1.5f, 1.0f);
    //mHitSpeed = FVec3(aFlingVector.mX * 0.23f + mFacing.mX * 0.075f, aFlingVector.mY * 0.23f + mFacing.mY * 0.075f, gGame->mGecko.mSpeedClimb + 0.3f);
    
    mHitSpeed = FVec3(mFacing.mX * 0.205f, mFacing.mY * 0.205f, gGame->mGecko.mSpeedClimb + 0.3f);
    mHitRot = FVec3(0.0f, 0.0f, 0.0f);
    
    //mHitRotSpeed = FVec3(gRand.GetFloat(-2.0f, 2.0f), gRand.GetFloat(-4.123f, -6.5f), gRand.GetFloat(4.0f, 8.0f));
    
    mHitRotSpeed = FVec3(5.0f, 1.666f, -1.0f);
    mHit = true;
}
