//
//  AnimationGenerator.h
//  LizDash
//
//  Created by Nick Raptis on 7/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ANIMATION_GENERATOR_H
#define ANIMATION_GENERATOR_H

#include "GLApp.h"

class GameObject;

class AnimationGenerator
{
public:
    
    AnimationGenerator();
    ~AnimationGenerator();
    
    GLApp                   *mApp;
    
    
    void                    GenerateAnimation(GameObject *pObject);
    
    
    void                    GenerateAnimationRing(GameObject *pObject);
    void                    GenerateAnimationRingSuper(GameObject *pObject);
    void                    GenerateAnimationFreeLife(GameObject *pObject);
    void                    GenerateAnimationLuckyCoin(GameObject *pObject);
    
    void                    GenerateAnimationBomb(GameObject *pObject);
    
    void                    GenerateAnimationBranch(GameObject *pObject);
    void                    GenerateAnimationCrate(GameObject *pObject);
    
    
};

#endif
