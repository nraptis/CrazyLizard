//
//  Branch.cpp
//  LizDash
//
//  Created by Nick Raptis on 3/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Game.h"
#include "BranchBig.h"

BranchBig::BranchBig()
{
    SetRadius(1.8f);
    
    mBranchIndex = gRand.Get(5);
    
    mLeaves = &(mApp->mBranchBigLeaves[mBranchIndex]);
    
    mArm = &mApp->mBranchBigArm[mBranchIndex];
    mBase = &mApp->mBranchBigBase;
    
    mArmStump = &mApp->mBranchBigArmStump;
    mBaseStump = &mApp->mBranchBigBaseStump;
    
    mFalling = false;
    
    mType = GO_TYPE_BRANCH_BIG;
}

BranchBig::~BranchBig()
{
    
}

//
//
//
//2feb3a8cfbb9c7b8aaa234f49aa23c8d73cb3ce6
//
//
//