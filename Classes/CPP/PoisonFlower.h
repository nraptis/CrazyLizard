//
//  PoisonFlower.h
//  LizDash
//
//  Created by Nick Raptis on 12/29/12.
//
//

#ifndef POISON_FLOWER_H
#define POISON_FLOWER_H

#include "GameObject.h"

class PoisonFlower : public GameObject
{
public:
    
    PoisonFlower();
    virtual ~PoisonFlower();
    
    virtual void                    Update();
    virtual void                    Draw();
    virtual void                    DrawEffects();
    
    FModelDataIndexed               *mLeaves;
    
    void                            Kaboom();
    
    bool                            mFalling;
    
    FVec3                           mHitSpeed;
    FVec3                           mHitRot;
    FVec3                           mHitRotSpeed;
};

#endif
