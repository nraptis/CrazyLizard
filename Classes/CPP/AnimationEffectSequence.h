//
//  AnimationEffectSequence.h
//  LizDash
//
//  Created by Nick Raptis on 9/17/12.
//
//

#ifndef ANIMATION_EFFECT_SEQUENCE_H
#define ANIMATION_EFFECT_SEQUENCE_H

#include "GLApp.h"
#include "Effect.h"

class AnimationEffectSequence : public Effect
{
public:
    
    AnimationEffectSequence();
    virtual ~AnimationEffectSequence();
    
    virtual void                    SetUp(float pOrbit, float pZ);
    virtual void                    SetSpriteSequence(FModelDataIndexed **pModel, int pFrameCount);
    
    virtual void                    Update();
    virtual void                    Draw();
    
    FModelDataIndexed                **mData;
    
    int                             mFrameCount;
    
};

#endif
