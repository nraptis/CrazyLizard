//
//  SpeedBoostMark.h
//  LizDash
//
//  Created by Nick Raptis on 7/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "GLApp.h"

#ifndef LizDash_SpeedBoostMark_h
#define LizDash_SpeedBoostMark_h

class SpeedBoostMark : public FObject
{
public:
    
    SpeedBoostMark();
    virtual ~SpeedBoostMark();
    
    
    virtual void                Update();
    virtual void                Draw(float pFade);
    
    float                       mX;
    float                       mY;
    
    float                       mAlpha;
    float                       mRed;
    float                       mGreen;
    float                       mBlue;
    
    float                       mWidth;
    float                       mHeight;
    
    float                       mSpeed;
    
};


#endif
