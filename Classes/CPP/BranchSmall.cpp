
//  BranchSmall.cpp
//  LizDash
//
//  Created by Nick Raptis on 5/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#include "BranchSmall.h"

BranchSmall::BranchSmall()
{
    SetRadius(1.25f);
    
    mBranchIndex = gRand.Get(3);
    
    mLeaves = &(mApp->mBranchSmallLeaves[mBranchIndex]);
    
    mArm = &mApp->mBranchSmallArm[mBranchIndex];
    mBase = &mApp->mBranchSmallBase;
    
    mArmStump = &mApp->mBranchSmallArmStump;
    mBaseStump = &mApp->mBranchSmallBaseStump;
    
    mFalling = false;
    
    mType = GO_TYPE_BRANCH_SMALL;
}

BranchSmall::~BranchSmall()
{
    
}


