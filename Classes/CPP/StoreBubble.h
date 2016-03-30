//
//  StoreBubble.h
//  LizDash
//
//  Created by Nick Raptis on 12/19/12.
//
//

#ifndef STORE_BUBBLE_H
#define STORE_BUBBLE_H

#include "GLApp.h"

class StoreBubble
{
public:
    
    StoreBubble();
    virtual ~StoreBubble();
    
    GLApp                           *mApp;
    
    virtual void                    Update();
    virtual void                    Draw();
    
    float                           mOffsetY;
    
};


#endif
