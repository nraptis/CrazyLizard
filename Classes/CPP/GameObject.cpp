//
//  GameObject.cpp
//  DoomKnights
//
//  Created by Nick Raptis on 1/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject()
{
    mIndex = 0;
    
    SetRadius(2.0f);
    
    mSnapRotation = false;
    
    mApp = gApp;
    
    mType = -1;
    
    mNode = 0;
    
    mData = 0;
    
    mBindIndex = -1;
    
    mScale = 1.0f;
    mRotation = 0.0f;
    mSpinRotation = 0.0f;
    
    mBindIndex = -1;
    
    mHit = false;
    mDodged = false;
    mCheckedItemProcs = false;
}

GameObject::~GameObject()
{
    //Log("~GameObject::GameObject()\n");
}

void GameObject::SetUp(float pOrbit)
{
    mOrbit = pOrbit;
    
    mOrbit = fmodf(mOrbit, 360.0f);
    if(mOrbit < 0)mOrbit += 360.0f;
    if(mOrbit >= 360.0f)mOrbit -= 360.0f;
    
    
    if(mSnapRotation)
    {
        mOrbit = fmodf(mOrbit, 360.0f);
        if(mOrbit < 0)mOrbit += 360.0f;
        if(mOrbit >= 360.0f)mOrbit -= 360.0f;
        
        int aRotationTicks = 24;
        
        
        float aBestOrbit = mOrbit;
        float aBestDist = 20000.0f;
        
        for(int i=0;i<aRotationTicks;i++)
        {
            float aPercent = (float)i / aRotationTicks;
            
            float aRotation = aPercent * 360.0f;
            
            float aRotationDiff = (aRotation - mOrbit);
            
            if(aRotationDiff < 0)aRotationDiff = (-aRotationDiff);
            
            if(aRotationDiff < aBestDist)
            {
                aBestDist = aRotationDiff;
                aBestOrbit = aRotation;
            }
        }
        
        mOrbit = aBestOrbit;
        
    }
    
    SetUp();
    
}

void GameObject::SetRadius(float pRadius)
{
    mRadius = pRadius;
    mRadiusSquared = (mRadius * mRadius);
}

void GameObject::SetUp()
{
    mFacing.mX = Sin(mOrbit);
    mFacing.mY = Cos(mOrbit);
    mFacing.mZ = 0.0f;
    
    mPos.mX = mFacing.mX * SEGMENT_RADIUS;
    mPos.mY = mFacing.mY * SEGMENT_RADIUS;
}
    
void GameObject::Update()
{
    
}

void GameObject::Draw()
{
    if(mData)
    {
        Transform();
        
        mData->Draw();
        
        TransformEnd();
    }
}

void GameObject::Transform()
{
    Graphics::MatrixPush();
    Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    Graphics::Scale(mScale);
    Graphics::Rotate(mRotation);
}

void GameObject::TransformEnd()
{
    Graphics::MatrixPop();
}

FString GameObject::TypeString(int pType)
{
    FString aReturn;
    
    if(pType == GO_TYPE_SPIKE_RANDOM)aReturn = "spike_random";
    else if(pType == GO_TYPE_BRANCH_RANDOM)aReturn = "branch_random";
    
    else if(pType == GO_TYPE_BRANCH)aReturn = "branch";
    else if(pType == GO_TYPE_BRANCH_BIG)aReturn = "branch_big";
    else if(pType == GO_TYPE_BRANCH_SMALL)aReturn = "branch_small";
    
    else if(pType == GO_TYPE_SPIKE)aReturn = "spike";
    else if(pType == GO_TYPE_SPIKE_BIG)aReturn = "spike_big";
    else if(pType == GO_TYPE_RING)aReturn = "rupee";
    else if(pType == GO_TYPE_FREE_LIFE)aReturn = "free_life";
    else if(pType == GO_TYPE_SPEED_BOOST)aReturn = "speed_boost";
    
    else if(pType == GO_TYPE_SPIKE_BOMB)aReturn = "spike_bomb";
    
    
    
    else if(pType == GO_TYPE_POISON_FLOWER)aReturn = "poison_flower";
    else if(pType == GO_TYPE_DIAMOND)aReturn = "diamond";
    
    
    else if(pType == SPIKEY_LEFT)aReturn = "spikey_left";
    else if(pType == SPIKEY_RIGHT)aReturn = "spikey_right";
    
    else if(pType == GO_TYPE_SNAIL)aReturn = "snail";
    
    else if(pType == GO_TYPE_POWER_UP_RANDOM)aReturn = "power_up_random";
    else if(pType == GO_TYPE_POWER_UP_BUBBLE)aReturn = "power_up_bubble";
    else if(pType == GO_TYPE_POWER_UP_RING)aReturn = "power_up_ring";
    else if(pType == GO_TYPE_POWER_UP_NUKE)aReturn = "power_up_nuke";
    
    else if(pType == GO_TYPE_BOX_PRIZE)aReturn = "box_prize";
    else if(pType == GO_TYPE_BOX_EXPLODE)aReturn = "box_explode";
    
    else if(pType == GO_TYPE_STAR)aReturn = "star";
    
    else if(pType == GO_TYPE_FLAG_LEFT)aReturn = "flag_left";
    else if(pType == GO_TYPE_FLAG_RIGHT)aReturn = "flag_right";
    
    else if(pType == GO_TYPE_I_FLAG_END)aReturn = "flag_i_end";
    else if(pType == GO_TYPE_I_FLAG_START)aReturn = "flag_i_start";
    
    else if(pType == GO_TYPE_BARREL)aReturn = "barrel";
    else if(pType == GO_TYPE_LUCKY_COIN)aReturn = "lucky_coin";
    
    return aReturn;
}

int GameObject::TypeIndex(char *pString)
{
    
    int aReturn = GO_TYPE_SNAIL;
    
    FString aString = FString(pString);
    
    if(aString == "spike_random")aReturn = GO_TYPE_SPIKE_RANDOM;;
    
    if(aString == "branch_random")aReturn = GO_TYPE_BRANCH_RANDOM;
    if(aString == "branch")aReturn = GO_TYPE_BRANCH;
    if(aString == "branch_big")aReturn = GO_TYPE_BRANCH_BIG;
    if(aString == "branch_small")aReturn = GO_TYPE_BRANCH_SMALL;
    
    if(aString == "spike")aReturn = GO_TYPE_SPIKE;
    if(aString == "spike_big")aReturn = GO_TYPE_SPIKE_BIG;    
    if(aString == "spike")aReturn = GO_TYPE_SPIKE;
    
    if(aString == "rupee")aReturn = GO_TYPE_RING;
    if(aString == "free_life")aReturn = GO_TYPE_FREE_LIFE;
    if(aString == "speed_boost")aReturn = GO_TYPE_SPEED_BOOST;
    if(aString == "spike_bomb")aReturn = GO_TYPE_SPIKE_BOMB;
    
    if(aString == "spikey_left")aReturn = SPIKEY_LEFT;
    if(aString == "spikey_right")aReturn = SPIKEY_RIGHT;
    
    if(aString == "poison_flower")aReturn = GO_TYPE_POISON_FLOWER;
    if(aString == "diamond")aReturn = GO_TYPE_DIAMOND;
    
    if(aString == "star")aReturn = GO_TYPE_STAR;
    
    if(aString == "power_up_random")aReturn = GO_TYPE_POWER_UP_RANDOM;
    if(aString == "power_up_bubble")aReturn = GO_TYPE_POWER_UP_BUBBLE;
    if(aString == "power_up_ring")aReturn = GO_TYPE_POWER_UP_RING;
    if(aString == "power_up_nuke")aReturn = GO_TYPE_POWER_UP_NUKE;
    
    if(aString == "box_prize")aReturn = GO_TYPE_BOX_PRIZE;
    if(aString == "box_explode")aReturn = GO_TYPE_BOX_EXPLODE;
    
    if(aString == "snail")aReturn = GO_TYPE_SNAIL;
    
    if(aString == "flag_left")aReturn = GO_TYPE_FLAG_LEFT;
    if(aString == "flag_right")aReturn = GO_TYPE_FLAG_RIGHT;
    
    if(aString == "flag_i_end")aReturn = GO_TYPE_I_FLAG_END;
    if(aString == "flag_i_start")aReturn = GO_TYPE_I_FLAG_START;
    
    if(aString == "barrel")aReturn = GO_TYPE_BARREL;
    if(aString == "lucky_coin")aReturn = GO_TYPE_LUCKY_COIN;
    
    return aReturn;
}


FVec3 GameObject::GetFlingVector(float pDegreesShift, float pProjectOut)
{
    
    float aOriginX = Sin(mOrbit) * (SEGMENT_RADIUS + 0.0f);
    float aOriginY = Cos(mOrbit) * (SEGMENT_RADIUS + 0.0f);
    
    float aTargetX = Sin(mOrbit + pDegreesShift) * (SEGMENT_RADIUS + pProjectOut);
    float aTargetY = Cos(mOrbit + pDegreesShift) * (SEGMENT_RADIUS + pProjectOut);
    
    float aDirX = (aTargetX - aOriginX);
    float aDirY = (aTargetY - aOriginY);
    
    float aDist = aDirX * aDirX + aDirY * aDirY;
    
    if(aDist > 0.001f)
    {
        aDist = sqrtf(aDist);
        aDirX /= aDist;
        aDirY /= aDist;
    }
    
    return FVec3(aDirX, aDirY, 0.0f);
}


//float aSphere2Rot = mGecko.mOrbit + mGecko.mRotation * 0.66f;
//
//float aSphere2X = Sin(aSphere2Rot) * SEGMENT_RADIUS;
//float aSphere2Y = Cos(aSphere2Rot) * SEGMENT_RADIUS;
//float aSphere2Z = mGecko.mPos.mZ + 2.0f;
//float aGeckoSphereRadius = 2.0f * 2.0f;
//float aDiffX, aDiffY, aDiffZ;
//float aDist;




