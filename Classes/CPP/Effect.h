//
//  Effect.h
//  LizDash
//
//  Created by Nick Raptis on 10/24/12.
//
//

#ifndef EFFECT_H
#define EFFECT_H

#include "GLApp.h"
#include "FModelData.h"
#include "FModelDataSequence.h"

class Effect : public FObject
{
public:
    
    Effect();
    virtual ~Effect();
    
    GLApp                           *mApp;
    
    virtual void                    SetUp(float pOrbit, float pZ);
    
    virtual void                    Update();
    virtual void                    Draw();
    
    float                           mFrame;
    float                           mOrbit;
    
    float                           mScale;
    
    bool                            mAdditive;
    
    FVec3                           mPos;
    FVec3                           mFacing;
};

#endif
