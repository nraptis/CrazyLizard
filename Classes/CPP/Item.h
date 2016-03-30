//
//  Item.h
//  LizDash
//
//  Created by Nick Raptis on 1/2/13.
//
//

#ifndef LizDash_Item_h
#define LizDash_Item_h

#include "GLApp.h"
#include "GameObject.h"

#define ITEM_EVADE_BRANCH 0
#define ITEM_EVADE_SNAIL 1

#define ITEM_EVADE_ALL 10

#define ITEM_BRANCH_NUKE 11


class Item
{
public:
    
    Item();
    virtual ~Item();
    
    void                    Update();
    void                    Draw();
    
    float                   mX;
    float                   mY;
    
    GLApp                   *mApp;
    
    FSprite                  *mSprite;
    FString                 mName;
    
    float                   mModelRotation;
    
    float                   mDodgeChanceAll;
    float                   mDodgeChanceBranch;
    float                   mDodgeChanceSnail;
    float                   mDodgeChanceBomb;
    float                   mDodgeChanceFlower;
    
    float                   mAbsorbChanceAll;
    float                   mAbsorbChanceBranch;
    float                   mAbsorbChanceSnail;
    float                   mAbsorbChanceBomb;
    float                   mAbsorbChanceFlower;
    
    float                   mWobble1;
    float                   mWobbleSpeed1;
    
    float                   mWobble2;
    float                   mWobbleSpeed2;
    
    float                   mWobble3;
    float                   mWobbleSpeed3;
    
    float                   mRechargeFlash;
    
    int                     mID;
    int                     mCoolDown;
    int                     mCoolDownTime;
    
    bool                    WillDodge(GameObject *pObject);
    bool                    WillAbsorb(GameObject *pObject);
};

Item                        *GenerateItem(int pItemIdentifier);

#endif
