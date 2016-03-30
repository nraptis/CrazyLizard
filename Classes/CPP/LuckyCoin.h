//
//  LuckyCoin.h
//  LizDash
//
//  Created by Nick Raptis on 2/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LUCKY_COIN_H
#define LUCKY_COIN_H

#include "GameObject.h"

class LuckyCoin : public GameObject
{
public:
    
    LuckyCoin();
    virtual ~LuckyCoin();
    
    virtual void                    Update();
    virtual void                    Draw();
    virtual void                    SetUp();
    
    float                           mWobbleSin;
    float                           mWobbleCos;
    
    bool                            mIgnorePass;
    bool                            mPassed;
};

#endif
