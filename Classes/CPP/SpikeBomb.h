//
//  SpikeBomb.h
//  LizDash
//
//  Created by Nick Raptis on 3/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SPIKE_BOMB_H
#define SPIKE_BOMB_H

#include "GameObject.h"

class SpikeBomb : public GameObject
{
public:
    
    SpikeBomb();
    virtual ~SpikeBomb();
    
    virtual void                    Update();
    virtual void                    Draw();
    virtual void                    DrawEffects();
    virtual void                    SetUp();
    
    float                           mScaleSin;
    float                           mRotationSin;
    float                           mRotationCos;
    
    float                           mSparkFrame;
};

#endif