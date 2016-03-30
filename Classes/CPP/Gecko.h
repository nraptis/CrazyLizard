//
//  Gecko.h
//  LizDash
//
//  Created by Nick Raptis on 2/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LizDash_Gecko_h
#define LizDash_Gecko_h

#define GECKO_SPEED_0 (0.27f)
#define GECKO_SPEED_1 (0.32f)
#define GECKO_SPEED_2 (0.37f)
#define GECKO_SPEED_3 (0.41f)
#define GECKO_SPEED_4 (0.45f)
#define GECKO_SPEED_5 (0.50f)
#define GECKO_SPEED_6 (0.53f)
#define GECKO_SPEED_7 (0.58f)
#define GECKO_SPEED_8 (0.64f)
#define GECKO_SPEED_9 (0.70f)
#define GECKO_SPEED_10 (0.80f)

#define GECKO_FRAME_SPEED_BASE (1.66f)
#define GECKO_FRAME_SPEED_CLIMB (5.25f)

#define COLLIDE_RADIUS_BOOST (7.64f)
#define COLLIDE_RADIUS_ATTACK (7.15f)

#define COLLIDE_RADIUS_ATTACK_SPECIAL_ITEMS (4.5f)

//#include "AnimatedCharacter.h"

#include "GameObject.h"
#include "GLApp.h"

class Gecko : public GameObject
{
public:
    
    Gecko();
    virtual ~Gecko();
    
    void                            Reset();
    
    bool                            mIdle;
    
    void                            Reposition();
    
    virtual void                    Update();
    virtual void                    Draw();
    virtual void                    DrawEffects();
    
    void                            SetSequence(FModelDataSequence *pSequence);
    
    float                           mRotation;
    
    float                           mRotationX;
    float                           mRotationY;
    float                           mRotationZ;
    
    float                           mAnimRotationX;
    float                           mAnimRotationY;
    float                           mAnimRotationZ;
    
    float                           mAnimHeightShift;
    
    float                           mFrame;
    float                           mFrameSpeed;
    float                           mFrameMax;
    
    float                           mLastFrame;
    
    FModelDataSequence               *mSequenceRun;
    FModelDataSequence               *mSequenceIdle;
    FModelDataSequence               *mSequenceSpeedBoost;
    FModelDataSequence               *mSequenceDie;
    FModelDataSequence               *mSequenceAttack;
    
    FObjectList                     mEffects;
    
    FModelDataSequence               *mCurrentSequence;
    
    float                           mOrbit;
    float                           mTargetRotation;
    
    float                           mSpeedAngular;
    float                           mSpeedClimb;
    float                           mSpeedClimbExtra;
    
    bool                            mDidPlayFootstep1;
    bool                            mDidPlayFootstep2;
    
    int                             mAnimHurt;
    int                             mAnimBoost;
    int                             mAnimAttack;
    
    
    void                            Recover();
    
    void                            Die();
    
    bool                            mDead;
    
    float                           mDeadSpeedX;
    float                           mDeadSpeedY;
    float                           mDeadSpeedZ;
    
    float                           mDeadX;
    float                           mDeadY;
    float                           mDeadZ;
    
    
    void                            Hurt();
    
    inline void                     ClearAnims(){mAnimHurt=0;mAnimBoost=0;mAnimAttack=0;
                                                 mAnimRotationX=0;mAnimRotationY=0;mAnimRotationZ=0;mAnimHeightShift=0;
        mAttacking=false;mBoosting=false;}
    
    bool                            mAttacking;
    
    bool                            mHit;
    int                             mHitTimer;
    int                             mHitMode;
    float                           mHitSin;
    float                           mHitFade;
    
    void                            GoBoost();
    void                            GoHurt();
    void                            GoAttack();
    
    bool                            mBoosting;
    bool                            mBoostingDown;
    
    float                           mBoostSin;
    float                           mBoostPercent;
    float                           mBoostFadeIn;
    float                           mBoostSpeedAdd;
    float                           mBoostPush;
    float                           mBoostPushExtra;
    float                           mBoostFrameFire;
    
};

#endif
