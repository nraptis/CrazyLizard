//
//  AnimationEffectRing.h
//  DoomKnights
//
//  Created by Nick Raptis on 1/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ANIMATION_EFFECT_RING_H
#define ANIMATION_EFFECT_RING_H

#include "GLApp.h"
#include "Effect.h"

class AnimationEffectRing : public Effect
{
public:
    
    AnimationEffectRing();
    virtual ~AnimationEffectRing();
    
    virtual void                    SetUp(float pOrbit, float pZ);
    
    virtual void                    Update();
    virtual void                    Draw();
};

#endif
