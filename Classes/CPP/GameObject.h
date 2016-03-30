
//  GameObject.h
//  Created by Nick Raptis on 1/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#define GO_TYPE_NULL (-1)

#define GO_TYPE_RING 0
#define GO_TYPE_LUCKY_COIN 1
#define GO_TYPE_BRANCH_RANDOM 2
#define GO_TYPE_SNAIL 3
#define GO_TYPE_POWER_UP_RANDOM 4
#define GO_TYPE_SPEED_BOOST 5
#define GO_TYPE_SPIKE_BOMB 6

#define GO_TYPE_POISON_FLOWER 7
#define GO_TYPE_DIAMOND 8

#define GO_TYPE_BOX_PRIZE 60
#define GO_TYPE_BOX_EXPLODE 61

#define SPIKEY_LEFT 62
#define SPIKEY_RIGHT 63

#define GO_TYPE_FREE_LIFE 9
#define GO_TYPE_BARREL 10
#define GO_TYPE_STAR 11

#define GO_TYPE_SPIKE_RANDOM 12

#define GO_TYPE_FLAG_LEFT 13
#define GO_TYPE_FLAG_RIGHT 14

#define GO_TYPE_I_FLAG_START 15
#define GO_TYPE_I_FLAG_END 15

#define GO_TYPE_BUTTERFLY 20
#define GO_TYPE_HUMMING_BIRD 21

#define GO_TYPE_BRANCH 100
#define GO_TYPE_BRANCH_SMALL 101
#define GO_TYPE_BRANCH_BIG 102

#define GO_TYPE_SPIKE 110
#define GO_TYPE_SPIKE_BIG 111

#define GO_TYPE_POWER_UP_BUBBLE 120
#define GO_TYPE_POWER_UP_RING 121
#define GO_TYPE_POWER_UP_NUKE 122

#define GO_TYPE_GECKO 999

#include "GLApp.h"
#include "FModelData.h"
#include "SpawnWave.h"

class GameObject : public FObject
{
public:
    
    GameObject();
    virtual ~GameObject();
    
    GLApp                   *mApp;
    
    virtual void            SetUp(float pOrbit);
    virtual void            SetUp();
    
    virtual void            Update();
    virtual void            Draw();
    
    virtual void            DrawEffects(){}
    
    bool                    mSnapRotation;
    
    static FString          TypeString(int pType);
    static int              TypeIndex(char *pString);
    
    FModelDataIndexed        *mData;
    int                     mBindIndex;
    
    float                   mRadius;
    float                   mRadiusSquared;
    void                    SetRadius(float pRadius);
    
    FVec3                   GetFlingVector(float pDegreesShift, float pProjectOut);
    
    bool                    mHit;
    bool                    mDodged;
    bool                    mCheckedItemProcs;
    
    int                     mType;
    
    int                     mIndex;
    
    float                   mScale;
    float                   mRotation;
    float                   mSpinRotation;
    
    float                   mOrbit;
    
    SpawnWaveNode           *mNode;
    
    FVec3                   mPos;
    FVec3                   mVel;
    FVec3                   mFacing;
    
    virtual void            Transform();
    virtual void            TransformEnd();
};

#endif
