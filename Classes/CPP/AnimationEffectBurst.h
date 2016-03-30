//
//  AnimationEffectBurst.h
//  DoomKnights
//
//  Created by Nick Raptis on 1/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ANIMATION_EFFECT_BURST_H
#define ANIMATION_EFFECT_BURST_H

#include "GLApp.h"
#include "FModelData.h"
#include "FModelDataSequence.h"

class AnimationEffectBurst : public FObject
{
public:
    
    AnimationEffectBurst();
    virtual ~AnimationEffectBurst();
    
    GLApp                           *mApp;
    
    virtual void                    SetUp(float pOrbit, float pAnimTestShiftDist, float pAnimTestShiftDistSpeed, float pAnimTestShiftDistDecay,
                                          float pAnimTestShiftZ, float pAnimTestShiftZSpeed, float pAnimTestShiftZSpeedAdd);
    virtual void                    SetUp(float pOrbit, float pAnimTestShiftDist=0.0f, float pAnimTestShiftDistSpeed=0.0f);
    virtual void                    SetUp();
    
    virtual void                    Update();
    virtual void                    Draw();
    
    FModelDataSequence               *mSequence;
    FModelDataIndexed                *mData;
    
    FTexture                        *mTexture;
    int                             mKillTimer;
    
    void                            FlingRadial(float pRadialDegrees, float pSpeed);
    
    float                           mScale;
    float                           mScaleAdd;
    float                           mScaleDecay;
    
    float                           mFrame;
    float                           mFrameSpeed;
    
    bool                            mPlayOnce;
    
    float                           mRotationX;
    float                           mRotationY;
    float                           mRotationZ;
    
    float                           mRotationSpeedX;
    float                           mRotationSpeedY;
    float                           mRotationSpeedZ;
    
    float                           mOrbit;
    
    float                           mColorSpeedA;
    float                           mColorSpeedR;
    float                           mColorSpeedG;
    float                           mColorSpeedB;
    
    float                           mColorA;
    float                           mColorR;
    float                           mColorG;
    float                           mColorB;
    
    bool                            mColorAdditive;
    
    //float                           mShiftSpeedU;
    //float                           mShiftSpeedV;
    
    //float                           mShiftU;
    //float                           mShiftV;
    
    FVec3                           mPos;
    FVec3                           mVel;
    FVec3                           mAccel;
    FVec3                           mFacing;
    
    float                           mVelAddZ;
    
    virtual void                    Transform();
    virtual void                    TransformEnd();
};

class StoredAnimationEffectBurst
{
    int                             mAnimTestInputType;
    int                             mAnimTestInputIndex;
    int                             mAnimTestTextureIndex;
    int                             mAnimTestTextureGroup;
    
    bool                            mAnimTestAdditive;
    float                           mAnimTestFrameSpeed;
    
    float                           mAnimTestScale;
    float                           mAnimTestScaleAdd;
    float                           mAnimTestScaleDecay;
    
    float                           mAnimTestShiftDist;
    float                           mAnimTestShiftDistSpeed;
    float                           mAnimTestShiftDistDecay;
    
    float                           mAnimTestShiftZ;
    float                           mAnimTestShiftZSpeed;
    float                           mAnimTestShiftZSpeedAdd;
    
    float                           mAnimTestRotationX;
    float                           mAnimTestRotationY;
    float                           mAnimTestRotationZ;
    
    float                           mAnimTestRotationSpeedX;
    float                           mAnimTestRotationSpeedY;
    float                           mAnimTestRotationSpeedZ;
    
    float                           mAnimTestColorSpeedA;
    float                           mAnimTestColorSpeedR;
    float                           mAnimTestColorSpeedG;
    float                           mAnimTestColorSpeedB;
    
    float                           mAnimTestColorA;
    float                           mAnimTestColorR;
    float                           mAnimTestColorG;
    float                           mAnimTestColorB;
    
    float                           mAnimTestShiftSpeedU;
    float                           mAnimTestShiftSpeedV;
};

#endif
