//  AnimationGenerator.cpp
//  LizDash
//
//  Created by Nick Raptis on 7/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#include "AnimationGenerator.h"
#include "GameObject.h"
#include "Game.h"
#include "AnimationEffectRing.h"
#include "AnimationEffectSequence.h"

AnimationGenerator::AnimationGenerator()
{
    mApp = gApp;
}

AnimationGenerator::~AnimationGenerator()
{
    
}


void AnimationGenerator::GenerateAnimation(GameObject *pObject)
{
    if(pObject->mType == GO_TYPE_RING)GenerateAnimationRing(pObject);
    if(pObject->mType == GO_TYPE_FREE_LIFE)GenerateAnimationFreeLife(pObject);
    if(pObject->mType == GO_TYPE_LUCKY_COIN )GenerateAnimationLuckyCoin(pObject);
    if(pObject->mType == GO_TYPE_SPIKE_BOMB)GenerateAnimationBomb(pObject);
}

void AnimationGenerator::GenerateAnimationRing(GameObject *pObject)
{
    AnimationEffectRing *aEffect;
    aEffect = new AnimationEffectRing();
    aEffect->SetUp(pObject->mOrbit, pObject->mPos.mZ);
    gGame->mEffects.Add(aEffect);
}

void AnimationGenerator::GenerateAnimationRingSuper(GameObject *pObject)
{
    
}

void AnimationGenerator::GenerateAnimationFreeLife(GameObject *pObject)
{
    AnimationEffectSequence *aEffectSequence = new AnimationEffectSequence();
    aEffectSequence->SetSpriteSequence(gApp->mAnimationBurst1, EFFECT_BURST_1_FRAMES);
    aEffectSequence->SetUp(pObject->mOrbit, pObject->mPos.mZ);
    aEffectSequence->mScale = 2.5f;
    aEffectSequence->mAdditive = true;
    gGame->mEffects.Add(aEffectSequence);
}
void AnimationGenerator::GenerateAnimationLuckyCoin(GameObject *pObject)
{
    
    AnimationEffectSequence *aEffectSequence = new AnimationEffectSequence();
    aEffectSequence->SetSpriteSequence(gApp->mAnimationBurst1, EFFECT_BURST_1_FRAMES);
    aEffectSequence->SetUp(pObject->mOrbit, pObject->mPos.mZ);
    aEffectSequence->mScale = 3.0f;
    aEffectSequence->mAdditive = true;
    gGame->mEffects.Add(aEffectSequence);
    
    /*
    AnimationEffectSequence *aEffectSequence = new AnimationEffectSequence();
    aEffectSequence->SetSpriteSequence(gApp->mAnimationBurst2, EFFECT_BURST_2_FRAMES);
    aEffectSequence->SetUp(pObject->mOrbit, pObject->mPos.mZ);
    aEffectSequence->mScale = 2.5f;
    aEffectSequence->mAdditive = true;
    gGame->mEffects += aEffectSequence;
    */
    
}

void AnimationGenerator::GenerateAnimationBomb(GameObject *pObject)
{
    AnimationEffectSequence *aEffectSequence = new AnimationEffectSequence();
    aEffectSequence->SetSpriteSequence(gApp->mAnimationExplode, EFFECT_EXPLODE_FRAMES);
    aEffectSequence->SetUp(pObject->mOrbit, pObject->mPos.mZ);
    aEffectSequence->mScale = 3.0f;
    aEffectSequence->mAdditive = false;
    gGame->mEffects.Add(aEffectSequence);
}

void AnimationGenerator::GenerateAnimationBranch(GameObject *pObject)
{
    
}

void AnimationGenerator::GenerateAnimationCrate(GameObject *pObject)
{
    
}
