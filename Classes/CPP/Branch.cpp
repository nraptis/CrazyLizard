//  Branch.cpp
//  LizDash
//  Created by Nick Raptis on 3/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#include "Branch.h"
#include "Game.h"

Branch::Branch()
{
    SetRadius(1.6f);
    
    mBranchIndex = gRand.Get(3);
    
    mSnapRotation = true;
    
    mLeaves = &(mApp->mBranchLeaves[mBranchIndex]);
    
    mArm = &mApp->mBranchArm[mBranchIndex];
    mBase = &mApp->mBranchBase;
    
    mArmStump = &mApp->mBranchArmStump;
    mBaseStump = &mApp->mBranchBaseStump;
    
    mFalling = false;
    
    mType = GO_TYPE_BRANCH;
}

Branch::~Branch()
{
    
}

void Branch::SetUp()
{
    mFacing.mX = Sin(mOrbit);
    mFacing.mY = Cos(mOrbit);
    mFacing.mZ = 0.0f;
    
    mPos.mX = mFacing.mX * (SEGMENT_RADIUS);
    mPos.mY = mFacing.mY * (SEGMENT_RADIUS);
}

void Branch::Update()
{
    if(mHit)
    {
        mHitRot += mHitRotSpeed;
        mHitPos += mHitSpeed;
        
        mHitSpeed.mX *= 0.975f;
        mHitSpeed.mY *= 0.975f;
        mHitSpeed.mZ -= 0.01f;
        
        mHitRotSpeed.mX *= 0.95f;
        mHitRotSpeed.mY *= 0.95f;
        mHitRotSpeed.mZ *= 0.935f;
        
        mHitRot.mY *= 0.980f;
    }
}

void Branch::Draw()
{
    Graphics::SetColor();
    if(mHit)
    {
        
        Graphics::MatrixPush();
        
        Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
        Graphics::RotateZ(-mOrbit + 180.0f);
        
        mBase->Draw();
        
        //Graphics::BlendDisable();
        
        mBaseStump->Draw();
        
        Graphics::MatrixPop();
        Graphics::MatrixPush();
        
        Graphics::Translate(mPos.mX+mHitPos.mX, mPos.mY+mHitPos.mY, mPos.mZ+mHitPos.mZ);
        
        Graphics::RotateZ(-mOrbit + 180.0f + mHitRot.mZ);
        Graphics::RotateX(mHitRot.mX);
        Graphics::RotateY(mHitRot.mY);
        
        mArmStump->Draw();
        
        mArm->Draw();
        
        Graphics::MatrixPop();
    }
    else
    {
        Graphics::MatrixPush();
        
        Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
        Graphics::RotateZ(-mOrbit + 180.0f);
        
        mBase->Draw();
        mArm->Draw();
        
        Graphics::MatrixPop();
    }
}

void Branch::DrawEffects()
{
    //if(mLeaves)
    //{
        
        Graphics::MatrixPush();
    
        Graphics::Translate(mPos.mX+mHitPos.mX, mPos.mY+mHitPos.mY, mPos.mZ+mHitPos.mZ);
        Graphics::RotateZ(-mOrbit + 180.0f + mHitRot.mZ);
        Graphics::RotateX(mHitRot.mX);
        Graphics::RotateY(mHitRot.mY);
        
        mLeaves->Draw();
        
        Graphics::MatrixPop();
}

void Branch::Kaboom()
{
    mHitRot = FVec3(0.0f, 0.0f, 0.0f);
    mHitPos = FVec3(0.0f, 0.0f, 0.0f);
    
    mHitRotSpeed = FVec3(gRand.GetFloat(-2.5f, -4.65f), gRand.GetFloat(-4.0f, 4.0f) , gRand.GetFloat(-2.0f, 2.0f));
    
    float aPunch = gRand.GetFloat() * 0.15f + 0.075f;
    
    mHitSpeed = FVec3(mFacing.mX * aPunch + gRand.GetFloat(-0.025f, 0.025f), mFacing.mY * aPunch + gRand.GetFloat(-0.025f, 0.025f), gRand.GetFloat(0.0f, 0.25f));
    
    mHit = true;
}









