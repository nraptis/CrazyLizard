//
//  SpeedBooster.h
//  LizDash
//
//  Created by Nick Raptis on 3/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SPEED_BOOSTER_H
#define SPEED_BOOSTER_H

#include "GameObject.h"

class SpeedBooster : public GameObject
{
public:
    
    SpeedBooster();
    virtual ~SpeedBooster();
    
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