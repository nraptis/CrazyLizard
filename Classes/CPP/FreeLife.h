//
//  FreeLife.h
//  LizDash
//
//  Created by Nick Raptis on 3/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LizDash_FreeLife_h
#define LizDash_FreeLife_h

#include "GameObject.h"

class FreeLife : public GameObject
{
    
public:
    
    FreeLife();
    virtual ~FreeLife();
    
    virtual void                    Update();
    virtual void                    Draw();
    virtual void                    SetUp();
    
    float                           mWobbleSin;
    float                           mWobbleCos;
};

#endif
