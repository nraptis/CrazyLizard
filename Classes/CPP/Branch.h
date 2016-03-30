//
//  Branch.h
//  LizDash
//
//  Created by Nick Raptis on 2/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BRANCH_H
#define BRANCH_H

#include "GameObject.h"

class Branch : public GameObject
{
public:
    
    Branch();
    virtual ~Branch();
    
    virtual void                    Update();
    virtual void                    Draw();
    virtual void                    DrawEffects();
    
    virtual void                    SetUp();
    
    void                            Kaboom();
    
    bool                            mFalling;
    
    FVec3                           mHitPos;
    FVec3                           mHitSpeed;
    FVec3                           mHitRot;
    FVec3                           mHitRotSpeed;
    
    int                             mBranchIndex;
    
    FModelDataIndexed                *mLeaves;
    
    FModelDataIndexed                *mArm;
    FModelDataIndexed                *mBase;
    
    FModelDataIndexed                *mArmStump;
    FModelDataIndexed                *mBaseStump;
};

#endif
