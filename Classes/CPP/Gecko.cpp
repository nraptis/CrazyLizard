

//////////////
//
//  Gecko.cpp
//  LizDash
//
//  Created by Nick Raptis on 2/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//////////////


#include "Gecko.h"
#include "UberTree.h"
#include "Game.h"

#ifdef GAME_TEST_MODE
#include "Editor.h"
#endif

Gecko::Gecko()
{
    mIdle = true;
    
    mScale = 1.0f;
    
    mPos.mY = SEGMENT_RADIUS;
    mType = GO_TYPE_GECKO;
    
    mSequenceRun = &gApp->mGeckoSequenceRun;
    mSequenceIdle = &gApp->mGeckoSequenceIdle;
    mSequenceSpeedBoost = &gApp->mGeckoSequenceBoost;
    mSequenceDie = &gApp->mGeckoSequenceHurt;
    mSequenceAttack = &gApp->mGeckoSequenceAttack;
    
    Reset();
}

void Gecko::Reset()
{
    mRotation = 0.0f;
    
    mRotationX = 90.0f;
    mRotationY = 120.0f;
    mRotationZ = 180.0f;
    
    mAnimRotationX = 0.0f;
    mAnimRotationY = 0.0f;
    mAnimRotationZ = 0.0f;
    
    mScale = 1.0f;
    mPos.mZ = 0.0f;
    
    mAttacking = false;
    
    
    mDead = false;
    
    mDeadSpeedX = 0.0f;
    mDeadSpeedY = 0.0f;
    mDeadSpeedZ = 0.0f;
    
    mDeadX = 0.0f;
    mDeadY = 0.0f;
    mDeadZ = 0.0f;

    mSequenceRun = &gApp->mGeckoSequenceRun;
    mSequenceIdle = &gApp->mGeckoSequenceIdle;
    mSequenceSpeedBoost = &gApp->mGeckoSequenceBoost;
    mSequenceDie = &gApp->mGeckoSequenceHurt;
    mSequenceAttack = &gApp->mGeckoSequenceAttack;
    
    mSpeedAngular = 0.0f;
    mSpeedClimb = GECKO_SPEED_0;
    mSpeedClimbExtra = 0.0f;
    
    mFrameSpeed = 1.25f;
    mFrame = 0.0f;
    mLastFrame = 0.0f;
    mFrameMax = 0.0f;
    
    mAnimHurt = 0;
    mAnimBoost = 0;
    mAnimAttack = 0;
      
    mOrbit = 0.0f;//180.0f;//0.0f;
    
    mHit = false;
    mHitTimer = 0;
    mHitSin = 0.0f;
    mHitFade = 0.0f;
    mHitMode = 0;
    
    mBoostFadeIn = 0.0f;
    
    mLastFrame = 0.0f;
    
    SetSequence(mSequenceRun);
    
    mBoosting = false;
    mBoostingDown = false;
    
    mBoostSin = 0.0f;
    mBoostPush = 0.0f;
    mBoostPushExtra = 2.0f;
    mBoostPercent = 0.0f;
    mBoostSpeedAdd = 0.0f;
    
    mBoostFrameFire = 0.0f;
    
    Reposition();
}

Gecko::~Gecko()
{
    
}

void Gecko::Hurt()
{
    mHit = true;
    
    mHitMode = 0;
    mHitFade = 0.0f;
    mHitSin = 0.0f;
    mHitTimer = 0;
    
}

void Gecko::Update()
{
    //Log("Gecko Position: [%f %f %f]\n", mPos.mX, mPos.mY, mPos.mZ);
    //Log("Gecko Position: [%f %f %f]\n", mPos.mX, mPos.mY, mPos.mZ);
    
    mBoostFrameFire += 0.44f;
    
    if(mBoostFrameFire >= FIRE_FRAMES)
    {
        mBoostFrameFire -= ((float)FIRE_FRAMES);
    }
    
    if(mDead)
    {
        if(mDeadZ >= (-20.0f))
        {
            mDeadX += mDeadSpeedX;
            mDeadY += mDeadSpeedY;
            mDeadZ += mDeadSpeedZ;
            
            mDeadSpeedZ -= 0.0025f;
            
        }
        
        if(mCurrentSequence != mSequenceIdle)
        {
            SetSequence(mSequenceSpeedBoost);
        }
        
    }
    else if(mIdle)
    {
        if(mCurrentSequence != mSequenceIdle)
        {
            SetSequence(mSequenceIdle);
        }
    }
    else
    {
        if(mAnimHurt > 0)
        {
            if(mCurrentSequence != mSequenceDie)SetSequence(mSequenceDie);
        }
        else if(mBoosting)
        {
            if(mCurrentSequence != mSequenceSpeedBoost)SetSequence(mSequenceSpeedBoost);
            
            mBoostSin += 12.0f;
            if(mBoostSin >= 360.0f)mBoostSin -= 360.0f;
            mBoostPush = Sin(mBoostSin) * mBoostPercent;
            mBoostPushExtra = 1.0f * mBoostPercent;
        }
        else if(mAnimAttack > 0)
        {
            if(mCurrentSequence != mSequenceAttack)SetSequence(mSequenceAttack);
        }
        else
        {
            ClearAnims();
            if(mCurrentSequence != mSequenceRun)
            {
                SetSequence(mSequenceRun);
            }
        }
    }
    
    
    
    mOrbit += mSpeedAngular;
    
    if(mBoosting)
    {
        mTargetRotation = (mSpeedAngular * (-3.0f));
    }
    else
    {
        mTargetRotation = (mSpeedAngular * (-9.0f));
    }
    
    if(mTargetRotation >= 38.0f)mTargetRotation = 38.0f;
    if(mTargetRotation <= -38.0f)mTargetRotation = -38.0f;
    float aAngleDiff = DistanceBetweenAngles(mTargetRotation, mRotation);
    
    mRotation -= (aAngleDiff * 0.20f);
    if(mBoosting)mPos.mZ += mSpeedClimb + (0.75f * mBoostPercent);
    else mPos.mZ += mSpeedClimb;
    
    mPos.mZ += mSpeedClimbExtra;
    
    
    
    Reposition();
    
    if(mOrbit >= 360.0f)mOrbit -= 360.0f;
    if(mOrbit < 0.0f)mOrbit += 360.0f;
    
    float aFrameSpeedAngular = fabsf(mSpeedAngular) * 0.35f;
    float aClimbSpeedOverBase = ((mSpeedClimb + mSpeedClimbExtra) - GECKO_SPEED_0);
    
    mFrameSpeed = GECKO_FRAME_SPEED_BASE + (aClimbSpeedOverBase * GECKO_FRAME_SPEED_CLIMB) + (aFrameSpeedAngular);
    
    if(mCurrentSequence == mSequenceIdle)
    {
        mFrameSpeed = 0.5f;
    }
    
    if(mCurrentSequence == mSequenceSpeedBoost)
    {
        mFrameSpeed = 0.5f;
    }
    
    if(mAnimAttack)
    {
        mFrame += 2.0f;
    }
    else
    {
        mFrame += mFrameSpeed;
    }
    
    
    if(mFrame >= mFrameMax)
    {
        mFrame -= mFrameMax;
        if(mAnimAttack > 0)
        {
            mAnimAttack = 0;
            ClearAnims();
            if(mCurrentSequence != mSequenceRun)SetSequence(mSequenceRun);
        }
    }
    
    if(mAnimAttack > 0)mAttacking = true;
    else mAttacking = false;
    
    if(mHit)
    {
        mHitSin += 15.0f;
        if(mHitSin >= 360.0f)
        {
            mHitSin -= 360.0f;
        }
        
        if(mHitMode == 0)
        {
            mHitFade += 0.025f;
            
            if(mHitFade >= 1.0f)
            {
                mHitMode = 1;
                mHitFade = 1.0f;
                mHitTimer = 0;
            }
            
        }
        else if(mHitMode == 1)
        {
            mHitTimer++;
            
            if(mHitTimer >= 5)
            {
                mHitMode = 2;
            }
        }
        else
        {
            mHitFade -= 0.0075f;
            
            if(mHitFade <= 0)
            {
                mHit = false;
                mHitFade = 0.0f;
            }
        }
    }
    
    if(mAnimHurt > 0)mAnimHurt--;
    if(mAnimAttack > 0)mAnimAttack--;
    
    if(mBoosting)
    {
        if(mAnimBoost > 0)
        {
            mBoostPercent = 1.0f;
            mAnimBoost--;
            if(mAnimBoost <= 0)
            {
                mBoostingDown = true;
            }
        }
        else
        {
            mBoostPercent -= 0.025f;
            if(mBoostPercent <= 0)
            {
                mApp->mSoundSpeedBoosFireLoop.Stop();
                
                mBoostPercent = 0.0f;
                mBoosting = false;
            }
        }
    }
    
    
    
    if(mLastFrame <= 15 && mFrame >= 15)
    {
        if(mDidPlayFootstep1 == false)
        {
            mApp->mSoundFootstep[gRand.Get(3)].Play(0.25f);
            mDidPlayFootstep1 = true;   
        }
    }
    else
    {
        mDidPlayFootstep1 = false;
    }
    
    if(mLastFrame <= 36 && mFrame >= 36)
    {
        if(mDidPlayFootstep2 == false)
        {
            mApp->mSoundFootstep[gRand.Get(3)].Play(0.25f);
            mDidPlayFootstep2 = true;   
        }
    }
    else
    {
        mDidPlayFootstep2 = false;
    }
    
    mLastFrame = mFrame;
    
    mEffects.Update();
}

void Gecko::Draw()
{
    
    Graphics::MatrixPush();
    
    float aBoostShift = mBoostPush;
    
    if(mAnimBoost > 0)
    {
        
    }
    else
    {
        aBoostShift = 0.0f;
    }
    
    if(mDead)
    {
        Graphics::Translate(mPos.mX + mDeadX, mPos.mY + mDeadY, mPos.mZ + mDeadZ);
    }
    else
    {
        Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    }
    
    
    //Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);// + aBoostShift);
    
    //Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
    
    Graphics::RotateZ(-mOrbit + 180.0f);
    Graphics::RotateY(mRotation);
    
    //Graphics::Scale(mScale);
    //Graphics::RotateX(mRotationX);
    //Graphics::RotateY(-mOrbit + 180.0f);
    //Graphics::RotateZ(mRotationZ + mRotation);
    
    Graphics::RotateX(mAnimRotationX);
    Graphics::RotateY(mAnimRotationY);
    Graphics::RotateZ(mAnimRotationZ);
    
    if(mCurrentSequence)
    {

#ifdef GAME_TEST_MODE
        
        if(gEditor)
        {
            mSpeedClimb = 0.3f;
            mFrameSpeed = 0.66f;
            
            Graphics::BlendEnable();
            Graphics::BlendSetAlpha();
            
            Graphics::SetColor(0.5f);
            
        }
        
#endif
        
        //Graphics::BlendEnable();
        //Graphics::BlendSetAlpha();
        
        
        /*
		if(mHit)
        {
            glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_ADD);
            float aColor = (Sin(mHitSin) + 1.0f) * 0.25f;
            Graphics::SetColor(mHitFade * (0.33f + aColor), 0.0f, 0.0f, 1.0f);
        }
        */
        
         //GL_ADD);
        
        //glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_BLEND); //GL_ADD);
        
        
        
        
        // mHitSin
        mCurrentSequence->SetSprite(&(mApp->mGeckoUVW));
        mCurrentSequence->Draw(mFrame);
        
        //glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        
        Graphics::SetColor();
        
        //if(gEditor)
        //{
        //    Graphics::BlendDisable();
        //    Graphics::SetColor(1.0f);
        //}
        
    }
    
    Graphics::MatrixPop();
    
    /*
    FVec2 aAxis2 = AngleToVector(mOrbit + 90.0f); //gGame->mEffectRotation2);
    FVec3 aAxis = FVec3(aAxis2.mX, aAxis2.mY, 0.0f);
    for(float aRot = 0;aRot <= 360.0f;aRot += 30.0f)
    {
        FVec2 aDir2 = AngleToVector(aRot);
        FVec3 aDir = FVec3(aDir2.mX, aDir2.mY, 0.0f);
        //aDir = Rotate3D(aDir, aAxis, gGame->mEffectRotation1);
        aDir = Rotate3D(aDir, (-aAxis), 90.0f);// gGame->mEffectRotation3);
        Graphics::DrawSphere12(aDir.mX * 2.5f + mPos.mX, aDir.mY * 2.5f + mPos.mY, aDir.mZ * 2.5f + mPos.mZ);
    }
    */
    
    
    /*
    float aHop;
    float aStarShift = 1.6f;
    aHop = 0.0f + mDizzyOrbit;
    for(int i=0;i<6;i++)
    {
        FVec3 aDir = AngleToFVec3D(aHop) * aStarShift;
        Graphics::MatrixPush();
        Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
        Graphics::RotateX(mRotationX);
        Graphics::RotateY(-mOrbit + 180.0f);
        Graphics::Translate(-mApp->mXFormHead.GetX(mFrame), -mApp->mXFormHead.GetY(mFrame), mApp->mXFormHead.GetZ(mFrame));
        Graphics::Translate(aDir.mX, aDir.mY, aDir.mZ);
        Graphics::RotateZ(mRotationZ + mRotation);
        Graphics::RotateX(Sin(mDizzyWobble[i]) * 20.0f);
        //Graphics::Translate(aDir.mX,aDir.mY,aDir.mZ);
        Graphics::RotateZ(mDizzyRotation[i]);
        if((i&1)==0)
        {
            mApp->mOuchStarBig.Draw();
        }
        else
        {
            mApp->mOuchStarSmall.Draw();
        }
        aHop += 60.0f;
        Graphics::MatrixPop();
    }
    */
    
}

void Gecko::DrawEffects()
{
    mEffects.Draw();
}

void Gecko::Reposition()
{
    mFacing = FVec3(Sin(mOrbit), Cos(mOrbit), 0.0f);
    
    mPos.mX = mFacing.mX * ( SEGMENT_RADIUS + 0.20f);
    mPos.mY = mFacing.mY * ( SEGMENT_RADIUS + 0.20f);
    
    //mPos.mX = mFacing.mX * ( SEGMENT_RADIUS + mAnimHeightShift + 0.25f );
    //mPos.mY = mFacing.mY * ( SEGMENT_RADIUS + mAnimHeightShift + 0.25f );
}



void Gecko::SetSequence(FModelDataSequence *pSequence)
{
    if(pSequence)
    {
        mCurrentSequence = pSequence;
        mFrame = 0.0f;
        mFrameMax = (float)pSequence->mCount;
    }
    else mCurrentSequence = 0;
}

void Gecko::GoBoost()
{
    mApp->mSoundSpeedBoosStart.Play();
    mApp->mSoundSpeedBoosFireLoop.Play();
    
    //mApp->mSoundFallDown.Play();
    
    ClearAnims();
    
    mAnimBoost = 160;
    
    mAnimRotationX = 0.0f;
    mAnimRotationY = 0.0f;
    mAnimRotationZ = 0.0f;
    
    mBoosting = true;
    mBoostingDown = false;
    
    mBoostPercent = 1.0f;
    
}

void Gecko::GoHurt()
{
    //temp thing
    
    ClearAnims();
    mAnimHurt = 100;
}

void Gecko::GoAttack()
{
    if((mAttacking == false) && (mBoosting == false))
    {
        mApp->mSoundTailWhip.Play();
        ClearAnims();
        mAnimAttack = 60;
    }
}

void Gecko::Recover()
{
    mDead = false;
}


void Gecko::Die()
{
    mDead = true;
    
    mDeadSpeedX = mFacing.mX * 0.04f;
    mDeadSpeedY = mFacing.mY * 0.04;;
    mDeadSpeedZ = -0.01f;
    
    mDeadX = 0.0f;
    mDeadY = 0.0f;
    mDeadZ = 0.0f;
    
}



