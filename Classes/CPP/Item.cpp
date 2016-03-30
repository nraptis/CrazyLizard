//
//  Item.cpp
//  LizDash
//
//  Created by Nick Raptis on 1/2/13.
//

#include "Item.h"

Item::Item()
{
    mApp = gApp;
    mSprite = 0;
    
    mName = "Jesus";
    
    mID = -1;
    
    mModelRotation = 0.0f;
    
    mDodgeChanceAll = 0.0f;
    
    mRechargeFlash = 0.0f;
    
    mDodgeChanceBranch = 0.0f;
    mDodgeChanceSnail = 0.0f;
    mDodgeChanceBomb = 0.0f;
    mDodgeChanceFlower = 0.0f;
    
    mAbsorbChanceAll = 0.0f;
    mAbsorbChanceBranch = 0.0f;
    mAbsorbChanceSnail = 0.0f;
    mAbsorbChanceBomb = 0.0f;
    mAbsorbChanceFlower = 0.0f;
    
    mX = gRand.GetFloat(400.0f) + 120.0f;
    mY = gRand.GetFloat(500.0f) + 200.0f;
    
    mCoolDown = 0;
    mCoolDownTime = 500 + gRand.Get(200);

    
    mWobble1 = gRand.GetFloat() * 360.0f;
    mWobbleSpeed1 = 2.0f;
    
    mWobble2 = gRand.GetFloat() * 360.0f;
    mWobbleSpeed2 = 2.0f;
    
    mWobble3 = gRand.GetFloat() * 360.0f;
    mWobbleSpeed3 = 2.0f;
    
}

Item::~Item()
{
    
}

void Item::Update()
{
    
    if(mRechargeFlash > 0)
    {
        mRechargeFlash *= 0.975f;
        mRechargeFlash -= 0.005f;
        if(mRechargeFlash < 0)mRechargeFlash = 0;
    }
    
    if(mCoolDown > 0)
    {
        mCoolDown--;
        if(mCoolDown <= 0)mRechargeFlash = 1.0f;
    }
    
    mModelRotation += 5.0f;
    if(mModelRotation >= 360.0f)mModelRotation -= 360.0f;
    
    mWobble1 += mWobbleSpeed1;
    if(mWobble1 >= 360.0f)
    {
        mWobble1 -= 360.0f;
        mWobbleSpeed1 = 1.25f + gRand.GetFloat(0.5f);
    }
    
    mWobble2 += mWobbleSpeed2;
    if(mWobble2 >= 360.0f)
    {
        mWobble2 -= 360.0f;
        mWobbleSpeed2 = 1.25f + gRand.GetFloat(0.5f);
    }
    
    mWobble3 += mWobbleSpeed3;
    if(mWobble3 >= 360.0f)
    {
        mWobble3 -= 360.0f;
        mWobbleSpeed3 = 1.25f + gRand.GetFloat(0.5f);
    }
    
}

void Item::Draw()
{
    /*
    mApp->mItemBack.Center(mX, mY);
    
    float aWobble1 = Sin(mWobble1) * 16.0f;
    float aWobble2 = Cos(mWobble2) * 12.0f;
    
    Graphics::EnableDepth();
    Graphics::ClearDepth();
    
    Graphics::MatrixPush();
    Graphics::Translate(mX, mY, 0.0f);
    
    Graphics::Scale(gGlobalScale * 12.0f, gGlobalScale * 12.0f, gGlobalScale * 12.0f);
    Graphics::RotateZ(90.0f);
    
    //Graphics::RotateX(mModelRotation);
    
    Graphics::RotateX(90.0f + Sin(mWobble3) * 15.0f);
    
    Graphics::RotateY(aWobble1);
    Graphics::RotateZ(aWobble2);
    
    mApp->mTalismanLEV.Draw();
    
    Graphics::MatrixPop();
    Graphics::DisableDepth();
    
    if(mCoolDown <= 0)
    {
        mApp->mItemRingLoaded.Center(mX, mY);
    }
    else
    {
        float aPercent = (float)mCoolDown / (float)mCoolDownTime;
        mApp->mItemRingCooldown.DrawRadial(mX, mY, 180.0f - (1 - aPercent) * 360.0f, 180.0f);
    }
    
    if(mRechargeFlash > 0.0f)
    {
        if(mRechargeFlash > 1.0f)Graphics::SetColor(1.0f);
        else Graphics::SetColor(mRechargeFlash);
        
        mApp->mItemFlash.Center(mX, mY);
        
        Graphics::SetColor();
    }
    */
}

bool Item::WillDodge(GameObject *pObject)
{
    bool aReturn = false;
    float aRand = gRand.GetFloat();
    if(pObject)
    {
        if(pObject->mType == GO_TYPE_BRANCH || pObject->mType == GO_TYPE_BRANCH_BIG || pObject->mType == GO_TYPE_BRANCH_SMALL || pObject->mType == GO_TYPE_BRANCH_RANDOM)
        {
            if((mDodgeChanceBranch > 0) && (aRand <= mDodgeChanceBranch))aReturn=true;
        }
        if(pObject->mType == GO_TYPE_SNAIL)
        {
            if((mDodgeChanceSnail > 0) && (aRand <= mDodgeChanceSnail))aReturn=true;
        }
        if(pObject->mType == GO_TYPE_SPIKE_BOMB)
        {
            if((mDodgeChanceBomb > 0) && (aRand <= mDodgeChanceBomb))aReturn=true;
        }
        if(pObject->mType == GO_TYPE_POISON_FLOWER)
        {
            if((mDodgeChanceBomb > 0) && (aRand <= mDodgeChanceBomb))aReturn=true;
        }
        if(pObject->mType == GO_TYPE_BRANCH || pObject->mType == GO_TYPE_BRANCH_BIG || pObject->mType == GO_TYPE_BRANCH_SMALL || pObject->mType == GO_TYPE_BRANCH_RANDOM || pObject->mType == GO_TYPE_SNAIL || pObject->mType == GO_TYPE_SPIKE_BOMB || pObject->mType == GO_TYPE_POISON_FLOWER)
        {
            if((mDodgeChanceAll > 0) && (aRand <= mDodgeChanceAll))aReturn=true;
        }
    }
    return aReturn;
}

bool Item::WillAbsorb(GameObject *pObject)
{
    bool aReturn = false;
    float aRand = gRand.GetFloat();
    if(pObject)
    {
        if(pObject->mType == GO_TYPE_BRANCH || pObject->mType == GO_TYPE_BRANCH_BIG || pObject->mType == GO_TYPE_BRANCH_SMALL || pObject->mType == GO_TYPE_BRANCH_RANDOM)
        {
            if((mAbsorbChanceBranch > 0) && (aRand <= mAbsorbChanceBranch))aReturn=true;
        }
        if(pObject->mType == GO_TYPE_SNAIL)
        {
            if((mAbsorbChanceSnail > 0) && (aRand <= mAbsorbChanceSnail))aReturn=true;
        }
        if(pObject->mType == GO_TYPE_SPIKE_BOMB)
        {
            if((mAbsorbChanceBomb > 0) && (aRand <= mAbsorbChanceBomb))aReturn=true;
        }
        if(pObject->mType == GO_TYPE_POISON_FLOWER)
        {
            if((mAbsorbChanceFlower > 0) && (aRand <= mAbsorbChanceFlower))aReturn=true;
        }
        if(pObject->mType == GO_TYPE_BRANCH || pObject->mType == GO_TYPE_BRANCH_BIG || pObject->mType == GO_TYPE_BRANCH_SMALL || pObject->mType == GO_TYPE_BRANCH_RANDOM || pObject->mType == GO_TYPE_SNAIL || pObject->mType == GO_TYPE_SPIKE_BOMB || pObject->mType == GO_TYPE_POISON_FLOWER)
        {
            if((mAbsorbChanceAll > 0) && (aRand <= mAbsorbChanceAll))aReturn=true;
        }
    }
    
    return aReturn;
    
}



Item *GenerateItem(int pItemIdentifier)
{
    Item *aReturn = new Item();
    
    aReturn->mID = pItemIdentifier;
    
    if(pItemIdentifier == ITEM_EVADE_BRANCH)
    {
        aReturn->mName = "evade_branch";
        aReturn->mCoolDownTime = 60 * 5;
        aReturn->mDodgeChanceBranch = 1.0f;
    }
    
    if(pItemIdentifier == ITEM_EVADE_SNAIL)
    {
        aReturn->mName = "evade_snail";
        aReturn->mCoolDownTime = 60 * 20;
        aReturn->mDodgeChanceBranch = 1.0f;
    }
    
    if(pItemIdentifier == ITEM_EVADE_ALL)
    {
        aReturn->mName = "evade_all";
        aReturn->mCoolDownTime = 60 * 30;
        aReturn->mDodgeChanceAll = 1.0f;
    }
    
    if(pItemIdentifier == ITEM_BRANCH_NUKE)
    {
        aReturn->mName = "branch_nuke";
        aReturn->mCoolDownTime = 60 * 120;
        aReturn->mDodgeChanceBranch = 1.0f;
    }
    
    return aReturn;
}

