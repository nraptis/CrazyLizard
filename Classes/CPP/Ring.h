//
//  Ring.h
//  LizDash
//
//  Created by Nick Raptis on 3/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef RUPEE_H
#define RUPEE_H

#include "GameObject.h"

class Ring : public GameObject
{
public:
    
    Ring();
    virtual ~Ring();
    
    FModelDataSequence                  *mSequenceSparkle;
    float                               mSparkleFrame;
    
    float                               mRotationSpeed;
    
    virtual void                        Transform();
    virtual void                        TransformEnd();
    virtual void                        DrawEfficient();
    
    virtual void                        Update();
    virtual void                        Draw();
    virtual void                        DrawEffects();
    
    virtual void                        SetUp();
};

#endif





