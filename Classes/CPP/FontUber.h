//
//  FontUber.h
//  LizDash
//
//  Created by Nick Raptis on 3/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LizDash_FontUber_h
#define LizDash_FontUber_h

#include "FSprite.h"

class FontUber
{
public:
    
    FontUber();
    virtual ~FontUber();
    
    FSprite                          mSprite[256];
    
    virtual void                    Update();
    virtual void                    Draw();
    virtual void                    Center();
    
    virtual void                    Draw(float pX, float pY);
    virtual void                    Center(float pX, float pY);
    
    
};

#endif
