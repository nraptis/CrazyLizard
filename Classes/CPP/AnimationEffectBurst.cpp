
////////////////////////////////////////////////////////////////
//
//  AnimationEffectBurst.cpp
//  LizDash
//
//  Created by Nick Raptis on 4/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
////////////////////////////////////////////////////////////////

#include "AnimationEffectBurst.h"

AnimationEffectBurst::AnimationEffectBurst()
{
    mApp = gApp;
    
    mKillTimer = 200;
    
    mData = 0;
    mSequence = 0;
    
    mTexture = 0;
    
    mScale = 1.0f;
    mScaleAdd = 0.0f;
    mScaleDecay = 1.0f;
    
    mRotationX = 0.0f;
    mRotationY = 0.0f;
    mRotationZ = 0.0f;
    
    mRotationSpeedX = 0.0f;
    mRotationSpeedY = 0.0f;
    mRotationSpeedZ = 0.0f;
    
    mFrame = 0.0f;
    mFrameSpeed = 0.66f;
    
    mPlayOnce = false;
    
    mColorSpeedA = 0.0f;
    mColorSpeedR = 0.0f;
    mColorSpeedG = 0.0f;
    mColorSpeedB = 0.0f;
    
    mColorA = 1.0f;
    mColorR = 1.0f;
    mColorG = 1.0f;
    mColorB = 1.0f;
    
    mVel = FVec3(0.0f, 0.0f, 0.0f);
    mAccel = FVec3(1.0f, 1.0f, 1.0f);
    
    mColorAdditive = false;
    
    //mShiftU = 0.0f;
    //mShiftV = 0.0f;
    //
    
    //
    //mShiftSpeedU = 0.0f;
    //mShiftSpeedV = 0.0f;
    
    mVelAddZ = 0.0f;
}

AnimationEffectBurst::~AnimationEffectBurst()
{
    
}

void AnimationEffectBurst::SetUp(float pOrbit, float pAnimTestShiftDist, float pAnimTestShiftDistSpeed, float pAnimTestShiftDistDecay,
                            float pAnimTestShiftZ, float pAnimTestShiftZSpeed, float pAnimTestShiftZSpeedAdd)
{
    SetUp(pOrbit, pAnimTestShiftDist, pAnimTestShiftDistSpeed);
    mPos.mZ = pAnimTestShiftZ;
    mVel.mZ = pAnimTestShiftZSpeed;
}

void AnimationEffectBurst::SetUp(float pOrbit, float pAnimTestShiftDist, float pAnimTestShiftDistSpeed)
{
    mOrbit = pOrbit;
    
    mFacing.mX = Sin(mOrbit);
    mFacing.mY = Cos(mOrbit);
    mFacing.mZ = 0.0f;
    
    mPos.mX = mFacing.mX * (SEGMENT_RADIUS + pAnimTestShiftDist);
    mPos.mY = mFacing.mY * (SEGMENT_RADIUS + pAnimTestShiftDist);
    
    mVel.mX = mFacing.mX * pAnimTestShiftDistSpeed;
    mVel.mY = mFacing.mY * pAnimTestShiftDistSpeed;
}

void AnimationEffectBurst::FlingRadial(float pRadialDegrees, float pSpeed)
{
    FVec3 aPushSpeed = FVec3(Sin(pRadialDegrees), 0.0f, Cos(pRadialDegrees));
    
    FVec3 aRotationAxis = FVec3(0.0f, 0.0f, 1.0f);
    
    aPushSpeed = Rotate3D(aPushSpeed, aRotationAxis, (180.0f - mOrbit));
    
    aPushSpeed *= pSpeed;
    
    mVel += aPushSpeed;
}

void AnimationEffectBurst::SetUp()
{
    
}

void AnimationEffectBurst::Update()
{
    mColorR -= mColorSpeedR;
    mColorG -= mColorSpeedG;
    mColorB -= mColorSpeedB;
    mColorA -= mColorSpeedA;
    
    //mShiftU += mShiftSpeedU;
    //mShiftV += mShiftSpeedV;
    
    //if(mShiftU > 1)mShiftU -= 1.0f;
    //if(mShiftU < 0)mShiftU += 1.0f;
    
    //if(mShiftV > 1)mShiftV -= 1.0f;
    //if(mShiftV < 0)mShiftV += 1.0f;
    
    mRotationX += mRotationSpeedX;
    mRotationY += mRotationSpeedY;
    mRotationZ += mRotationSpeedZ;
    
    mScale += mScaleAdd;
    mScaleAdd *= mScaleDecay;
    mVel.mZ += mVelAddZ;
    
    mVel *= mAccel;
    mPos += mVel;
    
    if(mSequence)
    {
        mFrame += mFrameSpeed;
        float aMaxFrame = (float)(mSequence->mCount);
        if(mFrame >= aMaxFrame)
        {
            if(mPlayOnce)
            {
                Kill();
            }
            else
            {
                mFrame -= aMaxFrame;
            }
        }
    }
    
    if(mColorA <= 0)
    {
        Kill();
    }
    
    if(mScale <= 0)
    {
        Kill();
    }
    
    if(mKillTimer > 0)
    {
        mKillTimer--;
        if(mKillTimer <= 0)
        {
            Kill();
        }
    }
}

void AnimationEffectBurst::Draw()
{
    Transform();
    
    if(mColorAdditive)Graphics::BlendSetAdditive();
    else Graphics::BlendSetAlpha();
    
    Graphics::SetColor(mColorR, mColorG, mColorB, mColorA);
    
    //Log("Color(%.2f, %.2f, %.2f, %.2f)\n", mColorR, mColorG, mColorB, mColorA);
    
    if(mData)
    {
        mData->SetTexture(mTexture);
        
        mData->Draw();
        
        //mData->DrawShifted(mShiftU, mShiftV);
    }
    
    if(mSequence)
    {
        mSequence->SetTexture(mTexture);
        mSequence->Draw(mFrame);
        
        //DrawShifted(mFrame, mShiftU, mShiftV);
    }
    
    TransformEnd();
}

void AnimationEffectBurst::Transform()
{
    Graphics::MatrixPush();
    Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    Graphics::Scale(mScale);
    Graphics::RotateZ(-mOrbit + 180.0f + mRotationZ);
    Graphics::RotateX(mRotationX);
    Graphics::RotateY(mRotationY);
}

void AnimationEffectBurst::TransformEnd()
{
    Graphics::MatrixPop();
}

