
//  EnemySnail.h
//  LizDash
//  
//  Created by Nick Raptis on 4/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#ifndef ENEMY_SNAIL_H
#define ENEMY_SNAIL_H

#include "GameObject.h"

class Snail : public GameObject
{
public:
    
    Snail();
    virtual ~Snail();
    
    virtual void                    Update();
    virtual void                    Draw();
    virtual void                    DrawEffects();
    
    void                            Kaboom();
    
    bool                            mFalling;
    
    FVec3                           mHitSpeed;
    FVec3                           mHitRot;
    FVec3                           mHitRotSpeed;
};

#endif
