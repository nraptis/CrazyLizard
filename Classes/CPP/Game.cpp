
/*
***  Game.cpp
**** Created by Nick Raptis on 2/20/11.
***  Copyright 2011 __MyCompanyName__. All rights reserved.
*/

#include "Game.h"
#include "FXML.h"

#ifdef GAME_TEST_MODE
#include "Editor.h"
#endif

#include "TextBubble.h"
#include "SpeedBoostMark.h"
#include "MainMenu.h"
#include "Effect.h"
#include "AchievementBox.h"
#include "SpeedBooster.h"
#include "LuckyCoin.h"
#include "PoisonFlower.h"
#include "Snail.h"
#include "Item.h"
#include "Branch.h"
#include "BranchBig.h"
#include "BranchSmall.h"
#include "FreeLife.h"
#include "SpikeBomb.h"
#include "Ring.h"

Game::Game()
{
    
    Log("GAME CREATED..\n");
    
    mName = "Game";
    
    SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    mApp = gApp;
    
    mMenu = 0;
    
    mTextBubbleStartY = gAppHeight2 + 2.0f * 100.0f;
    
    mClipsContent = false;
    
    mMenuMode = true;
    mMenuFadeMode = false;
    
    mFadeReset = false;
    mFadeResetToMenu = false;
    mFadeResetState = 0;
    mFadeResetAlpha = 0.0f;
    
    mInterfaceFade = 0.0f;
    
    mEffectSequenceTestCount = 0;
    
    gGame = this;
    
    
    mJoystick.mSpriteBackground = &(mApp->mJoystickBack);
    mJoystick.mSpriteKnob = &(mApp->mJoystickKnob);
    
    mJoystick.mDiffMultX = 0.45f;
    mJoystick.mDiffMultY = 0.45f;
    
    mJoystick.SetRadius(100.0f * 2.0f);
    mJoystick.mMaxDragLength = 16.0f * 2.0f;
    
    AddChild(mJoystick);
    
    float aButtonWidth;
    float aButtonHeight;
    float aAddHeight = gAdBannerHeight;
    
    aButtonWidth = mApp->mButtonAttack[0].mWidth;
    aButtonHeight = mApp->mButtonAttack[0].mHeight;
    
    mButtonAttack.Setup(gAppWidth - (aButtonWidth + 22.0f * 2.0f), gAppHeight - (aButtonHeight + aAddHeight + 48.0f), mApp->mButtonAttack, 2, this);
    mButtonAttack.mTriggerOnDown = true;
    mButtonAttack.mTriggerOnUp = false;
    
    
//    aButtonWidth = mApp->mButtonRestore.mWidth;
//    aButtonHeight = mApp->mButtonRestore.mHeight;
//    
//    mButtonRestore.Setup(gAppWidth2 - (aButtonWidth / 2.0f), gAppHeight - (aButtonHeight + aAddHeight + 160.0f * gGlobalScale), aButtonWidth, aButtonHeight);
//    mButtonRestore.mSpriteUp = &mApp->mButtonRestore;
//    mButtonRestore.mMultiTouch = true;
//    mButtonRestore.mDrawManual = true;
//    AddChild(mButtonRestore);
//    
//    aButtonWidth = mApp->mButtonUpgrade.mWidth;
//    aButtonHeight = mApp->mButtonUpgrade.mHeight;
//    
//    //mButtonUpgrade.Setup(gAppWidth2 - (aButtonWidth / 2.0f), gAppHeight - (aButtonHeight + aAddHeight + 160.0f * gGlobalScale), mApp->mButtonUpgrade, 1, this);
//    mButtonUpgrade.Setup(gAppWidth2 - (aButtonWidth / 2.0f), gAppHeight - (aButtonHeight + aAddHeight + 160.0f * gGlobalScale), aButtonWidth, aButtonHeight);
//    mButtonUpgrade.mSpriteUp = &mApp->mButtonUpgrade;
//    mButtonUpgrade.mMultiTouch = true;
//    mButtonUpgrade.mDrawManual = true;
//    AddChild(mButtonUpgrade);
    
    aButtonWidth = mApp->mButtonPause[0].mWidth;
    aButtonHeight = mApp->mButtonPause[0].mHeight;
    
    mButtonPause.Setup(3.0f * 2.0f, 75.0f * 2.0f, mApp->mButtonPause, 2, this);
    
#ifdef GAME_TEST_MODE
    
    mTestPause = false;
    
    mButtonTest.Setup(gAppWidth2 - aButtonWidth / 2.0f, 10.0f, mApp->mButtonPause, 2, this);
    
    mHideGecko = false;
    mHideObjects = true;
    
#endif
    
    mWave = 0;
    mPreviousWave = 0;
    
    //mItemList += GenerateItem(ITEM_EVADE_BRANCH);
    //mItemList += GenerateItem(ITEM_EVADE_SNAIL);
    //mItemList += GenerateItem(ITEM_EVADE_ALL);
    //mItemList += GenerateItem(ITEM_BRANCH_NUKE);
    //PositionItems();
    
    Restart(0);
}

void Game::Restart(const char *pFilePath)
{
    
    if(mWave)
    {
        delete mWave;
        mWave = 0;
    }
    
    if(mPreviousWave)
    {
        delete mPreviousWave;
        mPreviousWave=0;
    }
    
    EnumList(GameObject, aObject, mObjects.mObjects)
    {
        aObject->Kill();
    }
    
    EnumList(GameObject, aObject, mGameObjectsRings.mObjects)
    {
        aObject->Kill();
    }
    
    EnumList(GameObject, aObject, mGameObjectsBranches.mObjects)
    {
        aObject->Kill();
    }
    
    EnumList(GameObject, aObject, mGameObjectsLuckyCoins.mObjects)
    {
        aObject->Kill();
    }
    
    
    mDidShowDialogBoxJoystick = false;
    mDidShowDialogBoxWhip = false;
    
    
    mTutorialIndex = 0;
    
    mTutorialArrowScale = 1.0f;
    mTutorialArrowScaleSin = 0.0f;
    
    mTutorialArrowCenterX = mJoystick.mX;
    mTutorialArrowCenterY = mJoystick.mY;
    
    mTutorialArrowRotation = 0.0f;
    
    mGecko.Reset();
    mTree.Reset();
    mWaveGenerator.Reset();
    
    mStartGamePreventMoveTimer = 0;
    
    mTextBubbleExtraSpeed = 0.0f;
    
    mClimbHeight = 0.0f;
    
    mEffectSequenceTestCount = 0;
    
    mGameOver = false;
    mGameOverCameraDropTimer = 0;
    
    mGameOverMenuShowTimer = 0;
    
    mGameOverCameraStartZ = 0.0f;
    mGameOverCameraOffsetZ = 0.0f;
    mGameOverCameraDist = 0.0f;
    mGameOverCameraTargetZ = 0.0f;
    mGameOverCameraTargetOffsetZ = 0.0f;
    mGameOverCanTapToReset = false;
    mGameOverTapResetFade = 0.0f;
    
    mGameOverFade = 0.0f;;
    
    for(int i=0;i<2;i++)
    {
        mGameOverTextX[i] = -gAppWidth;
        mGameOverTextY[i] = -gAppHeight;
        
        mGameOverTextTargetX[i] = gAppWidth;
        mGameOverTextTargetY[i] = gAppHeight;
    }
    
    mCameraWanderMode = false;
    
    mCameraWanderStartRot = 0.0f;
    mCameraWanderStartZoom = 0.0f;
    mCameraWanderStartPanZ = 0.0f;
    
    mCameraWanderRot = mCameraWanderStartRot;
    mCameraWanderZoom = mCameraWanderStartZoom;
    mCameraWanderPanZ = mCameraWanderStartPanZ;
    
    mCameraWanderTargetRot = 30.0f;
    mCameraWanderTargetZoom = 2.0f;
    mCameraWanderTargetPanZ = 0.0f;
    
    mCameraWanderTimer = 0;
    mCameraWanderTime = 100;
    mCameraWanderWait = 0;
    
    mCameraWanderPos = 0.0f;
    
    mCameraWanderRotSpline.Clear();
    mCameraWanderPanSpline.Clear();
    mCameraWanderZoomSpline.Clear();
    
    mCameraWanderRotSpline.SetClosed(1);
    mCameraWanderPanSpline.SetClosed(1);
    mCameraWanderZoomSpline.SetClosed(1);
    
    mCameraWanderRotSpline.AddPoint(-70.0f , 0.0f);
    mCameraWanderRotSpline.AddPoint(10.0f, 0.0f);
    mCameraWanderRotSpline.AddPoint(-25.0f, 0.0f);
    mCameraWanderRotSpline.AddPoint(80.0f, 0.0f);
    
    mCameraWanderPanSpline.AddPoint(0.25f, 0.0f);
    mCameraWanderPanSpline.AddPoint(1.25f, 0.0f);
    mCameraWanderPanSpline.AddPoint(0.0f, 0.0f);
    mCameraWanderPanSpline.AddPoint(-0.4f, 0.0f);
    
    mCameraWanderZoomSpline.AddPoint(-8.0f, 0.0f);
    mCameraWanderZoomSpline.AddPoint(1.0f, 0.0f);
    mCameraWanderZoomSpline.AddPoint(-2.0f, 0.0f);
    mCameraWanderZoomSpline.AddPoint(-7.5f, 0.0f);
    
    mTime = 0;
    mMinutes = 0;
    mSeconds = 0;
    mMilliseconds = 0;
    
#ifdef GAME_TEST_MODE
    mTestPause = false;
#endif
    
    mApp->mScore = 0;
    mApp->mRingCount = 0;
    
    mApp->mLivesMax = 3;
    mApp->mLives = mApp->mLivesMax;
    
    mApp->mClimbHeight = 0.0f;
    
    mResumeGameFromInactive = false;
    
    //float aButtonWidth;
    //float aButtonHeight;
    //float aAddHeight = gAdBannerHeight;
    
    
    //aButtonWidth = mApp->mButtonAttack[0].mWidth;
    //aButtonHeight = mApp->mButtonAttack[0].mHeight;
    
    //mButtonAttack.Setup(gAppWidth - (aButtonWidth + 22.0f * gGlobalScale), gAppHeight - (aButtonHeight + aAddHeight + 160.0f * gGlobalScale), mApp->mButtonAttack, 2, this);
    
    //aButtonWidth = mApp->mButtonPause[0].mWidth;
    //aButtonHeight = mApp->mButtonPause[0].mHeight;
    
    mClimbSpeedIndex = 0;
    mClimbSpeed = GECKO_SPEED_0;
    
    //float aTargetSpeed = GECKO_SPEED_0;
    //float aTargetSpeedAdd = 0.02f;
    
    mClimbHeight = 0.0f;

    
    //VERTICAL_SPREAD = 0.1f;
    
    mWaveSpawnZ = 12.0f;
    mWaveGap = 12.0f;
    
    mAccelReverse = false;
    mSymmetrical = false;
    
    mStarPitchDirection = 1.0;
    mStarPitch = 1.0f;
    
    mAccelX = 0;
    mAccelY = 0;
    mAccelZ = 0;
    
    
    mHitAnimation = false;
    mHitAnimationShakeAmount = 0.0f;
    
    mHitAnimationFade = 0.0f;
    mHitAnimationFadeSpeed = 0.0f;
    
    mPaused = false;
    mWait = false;
    
    mLuckyCoinScoreFactor = 0;
    
    mCameraHeight = -7.25f;
    mCameraOffsetX = 0.0f;
    mCameraOffsetY = 0.0f;
    mCameraOffsetZ = 5.8f;
    mCameraFOV = 64.0f;
    mCameraDist = 25.87f;
    mCameraRotaionTarget = 0.0f;
    mCameraRotaionOffset = 0.0f;
    mCameraRotaion = 0.0f;
    
    mRotationDifference = 0.0f;
    
    mWaveCurrentStartRot1 = 0.0f;
    mWaveCurrentStartRot2 = 0.0f;
    
    mWaveCurrentEndRot1 = 0.0f;
    mWaveCurrentEndRot2 = 10.0f;
    
    mWaveGapStart = 0.0f;
    mWaveGapEnd = 0.0f;
    
    mGecko.mPos.mZ = GECKO_START_Z;
    
    mWaveIndex = 1;
    
#ifdef GAME_TEST_MODE
    if(gEditor == 0)
    {
#endif
        
        SpawnWave *aWave = mWaveGenerator.Generate(0);//GenerateFirst();
        mWaveSpawnZ = WAVE_START_Z;
        SetupWave(aWave);
        
        mGecko.SetUp(mWaveCurrentStartRot1 + 180.0f);
        
#ifdef GAME_TEST_MODE
    }
    else
    {
        mWave = 0;
    }
    
#endif
    
    CheckSpawn();
    
    UpdateGameObjects(&mObjects);
    UpdateGameObjects(&mGameObjectsRings);
    UpdateGameObjects(&mGameObjectsBranches);
    UpdateGameObjects(&mGameObjectsLuckyCoins);
    
    PositionContent();
    
    
    mJoystick.mEnabled = false;
    mButtonAttack.mEnabled = false;
    mButtonPause.mEnabled = false;
    
    //mEnabled
}

Game::~Game()
{
    Log("\n\nGame::~Game();\n\n");
    
    mObjects.Free();
    mGameObjectsRings.Free();
    mGameObjectsBranches.Free();
    mGameObjectsLuckyCoins.Free();
    
    mDoodads.Free();
    mEffects.Free();
    mEffectsProjectiles.Free();
    mTextBubbles.Free();
    
    if(mMenu)mMenu->Kill();
	mMenu=0;
}

void Game::PositionContent()
{
    
    SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    mJoystick.SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    mCameraAspect = (float)gAppWidth / (float)gAppHeight;
    
    float aButtonWidth = mApp->mButtonAttack[0].mWidth;
    float aButtonHeight = mApp->mButtonAttack[0].mHeight;
    
    mButtonAttack.Setup(gAppWidth - (aButtonWidth + 22.0f * 2.0f), gAppHeight - (aButtonHeight + gAdBannerHeight + 48.0f), mApp->mButtonAttack, 2, this);
    
    //mButtonAttack.SetX(gAppWidth - (aButtonWidth + 22.0f * gGlobalScale));
    
}

void Game::Pause()
{
    //mGecko.Pause();
    mPaused = true;
}

void Game::Unpause()
{
    //mGecko.Unpause();
    mPaused = false;
}

void Game::PauseToggle()
{
    if(mPaused)
    {
        Unpause();
    }
    else
    {
        Pause();
    }
}

void Game::Update()
{
    
    if(mMenuMode)
    {
        mJoystick.mEnabled = false;
        mButtonAttack.mEnabled = false;
        mButtonPause.mEnabled = false;
    }
    else
    {
        mJoystick.mEnabled = true;
        mButtonAttack.mEnabled = true;
        mButtonPause.mEnabled = true;
    }
    
    
    if(mFadeReset)
    {
        if(mFadeResetState == 0)
        {
            mFadeResetTimer = 10;
            mFadeResetAlpha += 0.0165f;
            if(mFadeResetAlpha >= 1.0f)
            {
                
                mFadeResetState = 1;
                
                Restart();
                
                if(mFadeResetToMenu)
                {
                    if(mMenu)
                    {
                        mMenu->Kill();
                        mMenu=0;
                    }
                    
                    gApp->CleanForGame();
                    gApp->ShowMainMenu();
                    
                    //mFadeResetToMenu = false;
                
                }
            }
        }
        else if(mFadeResetState == 1)
        {
            mFadeResetTimer--;
            if(mFadeResetTimer <= 0)
            {
                mFadeResetState = 2;
            }
        }
        else
        {
            mFadeResetAlpha -= 0.0135f;
            if(mFadeResetAlpha <= 0.0f)
            {
                mFadeResetAlpha = 0.0f;
                mFadeResetState = 0;
                mFadeReset = false;
            }
        }
    }
    else
    {
        if(ShouldFadeInterface())
        {
            if(mInterfaceFade < 1.0f)
            {
                mInterfaceFade += 0.01f;
                if(mInterfaceFade > 1.0f)
                {
                    mInterfaceFade = 1.0f;
                }
            }
        }
        else
        {
            if(mInterfaceFade > 0.0f)
            {
                mInterfaceFade -= 0.01f;
                if(mInterfaceFade < 0.0f)
                {
                    mInterfaceFade = 0.0f;
                }
            }
        }
    }
    
    
    if(mApp->mDialogWindow)
    {
        mTutorialArrowScaleSin += 12.0f;
        if(mTutorialArrowScaleSin >= 360.0f)mTutorialArrowScaleSin -= 360.0f;
        mTutorialArrowScale = 0.88f + Sin(mTutorialArrowScaleSin) * 0.075f;
    }
    
    
    float aAddHeight = gAdBannerHeight;
    
    mJoystick.mX = 130.0f;
    mJoystick.mY = ((gAppHeight - aAddHeight) - 130.0f);
    
    mButtonAttack.SetY((gAppHeight - (mApp->mButtonAttack[0].mHeight + aAddHeight + 48.0f)));
    
    
    //TODO: Eventually remove this...
    
    if(ShouldPause())return;
    
    mTime++;
    
    mWait = false;
    
    if(mMenuMode)mInterfaceFade = 0.0f;
    
    if(mMenuMode)mCameraWanderMode = 1;
    else mCameraWanderMode = 0;
    
    if(ShouldIdle())
    {
        mGecko.mIdle = true;
    }
    else
    {
        mGecko.mIdle = false;
    }
    
    mClimbHeight += (mGecko.mSpeedClimb + mGecko.mSpeedClimbExtra);
    
    if(mGameOver)
    {
        //Log("mGameOverCameraDropTimer = %d, mGameOverMenuShowTimer = %d\n", mGameOverCameraDropTimer, mGameOverMenuShowTimer);
        
        mGameOverFade += 0.001f;
        
        if(mGameOverFade >= 0.66f)
        {
            mGameOverFade = 0.66f;
        }
        
        if(mGameOverCameraDropTimer > 0)
        {
            mGameOverCameraDropTimer--;
            
            mGameOverCameraOffsetZ -= 0.10f;
            mGameOverCameraDist *= 0.995f;
            mGameOverCameraTargetOffsetZ -= 0.025f;
            
            if(mGameOverCameraDropTimer <= 0)
            {
                mGameOverMenuShowTimer = 80;
            }
        }
        else
        {
            if(mGameOverMenuShowTimer > 0)
            {
                mGameOverMenuShowTimer--;
                
                if(mGameOverMenuShowTimer <= 0)
                {
                    mGameOverTapResetFade = 0.0f;
                    mGameOverCanTapToReset = true;
                    //mApp->ShowGameOverScreen();
                }
            }
        }
    }
    
    if(mGameOver)
    {
        for(int i=0;i<2;i++)
        {
            float aHopSpeed = 5.5f;
            
            aHopSpeed = fabsf(mGameOverTextTargetX[i] - mGameOverTextX[i]) * 0.050f + 0.5f;
            if(aHopSpeed >= 7.0f)aHopSpeed = 7.0f;
            
            if(mGameOverTextX[i] < mGameOverTextTargetX[i])
            {
                mGameOverTextX[i] += aHopSpeed;
                if(mGameOverTextX[i] > mGameOverTextTargetX[i])
                {
                    mGameOverTextX[i] = mGameOverTextTargetX[i];
                }
            }
            else if(mGameOverTextX[i] > mGameOverTextTargetX[i])
            {
                mGameOverTextX[i] -= aHopSpeed;
                if(mGameOverTextX[i] < mGameOverTextTargetX[i])
                {
                    mGameOverTextX[i] = mGameOverTextTargetX[i];
                }
            }
        }
        
        if(mGameOverCanTapToReset)
        {
            mGameOverTapResetFade += 0.01f;
            if(mGameOverTapResetFade >= 1.0f)mGameOverTapResetFade = 1.0f;
        }
    }
    
    
    
    if(mCameraWanderMode)
    {
        mCameraWanderPos += 0.005f;
        if(mCameraWanderPos >= mCameraWanderRotSpline.Max())
        {
            mCameraWanderPos -= mCameraWanderRotSpline.Max();
        }
        
        mCameraWanderRot = mCameraWanderRotSpline.GetX(mCameraWanderPos);
        mCameraWanderZoom = mCameraWanderZoomSpline.GetX(mCameraWanderPos);
        mCameraWanderPanZ = mCameraWanderPanSpline.GetX(mCameraWanderPos) + 3.0f;
        
        mStartGamePreventMoveTimer = 220;
        
    }
    else
    {
        if(mStartGamePreventMoveTimer > 0)mStartGamePreventMoveTimer--;
    }
    
    mGecko.Update();
    
    if(mGecko.mBoosting)
    {
        if(true)
        {
            SpeedBoostMark *aBoostMark = new SpeedBoostMark();
            mSpeedBoostMarks.Add(aBoostMark);
        }
    }
    
    if(gRand.Get(300) == 150)
    {
        mApp->mSoundAmbience[gRand.Get(11)].Play();
    }
    
    mCameraRotaionTarget = mGecko.mOrbit;
    
#ifdef GAME_TEST_MODE
    if(gEditor)
    {
        mCameraRotaion = mCameraRotaionTarget;
    }
    else
    {
#endif
        mRotationDifference = DistanceBetweenAngles(mCameraRotaion, mCameraRotaionTarget);
        mCameraRotaion += mRotationDifference * 0.45f;

#ifdef GAME_TEST_MODE
    }
#endif
    
    float aGeckoZ = mGecko.mPos.mZ;
    float aBottom = mTree.BottomZ();
    if(aGeckoZ - KILL_FLOOR_TREE >= aBottom)
    {
        mTree.BumpUp();
    }
    
    
    
    UpdateGameObjects(&mObjects);
    UpdateGameObjects(&mGameObjectsRings);
    UpdateGameObjects(&mGameObjectsBranches);
    UpdateGameObjects(&mGameObjectsLuckyCoins);
    
    
    CollideGameObjects(&mObjects);
    CollideGameObjects(&mGameObjectsRings);
    CollideGameObjects(&mGameObjectsBranches);
    CollideGameObjects(&mGameObjectsLuckyCoins);
    
    TextBubble *aLastTextBubble = (TextBubble*)mTextBubbles.mObjects.Last();
    if(aLastTextBubble != 0)
    {
        
        if(aLastTextBubble->mY > mTextBubbleStartY)
        {
            mTextBubbleExtraSpeed += 0.05f;
            if(mTextBubbleExtraSpeed > 3.0f)mTextBubbleExtraSpeed=3.0f;
        }
        else
        {
            if(mTextBubbleExtraSpeed > 0)
            {
                mTextBubbleExtraSpeed -= 0.05f;
                if(mTextBubbleExtraSpeed < 0)
                {
                    mTextBubbleExtraSpeed = 0.0f;
                }
            }
        }
    }
    else mTextBubbleExtraSpeed = 0.0f;
    
    EnumList(TextBubble, aBubble, mTextBubbles.mObjects)
    {
        aBubble->mY -= mTextBubbleExtraSpeed;
    }
    
    
    
    mTextBubbles.Update();
    mEffects.Update();
    mEffectsProjectiles.Update();
    mDoodads.Update();
    mSpeedBoostMarks.Update();
    
    mTree.Update();
    
    
    
    mGecko.mSpeedClimb = 0.0f;
    mGecko.mSpeedClimbExtra = 0.0f;
    mGecko.mSpeedAngular = 0.0f;
    
    
    if(ShouldMove())
    {
        float aAccelFactor;
        
        //if(mAccelReverse)aAccelFactor = -mAccelX;
        //else
        
        aAccelFactor = (-mAccelX);
        
        float aJoystickPercent = (mJoystick.mPercentY);
        
        float aSpeedAngular = 0.0f;
        
        float aJoystickAngularSpeed = (-4.0f) * (mJoystick.mPercentX);
        float aAccelerometerAngularSpeed = aAccelFactor * 8.0f;
        
        



        
#ifdef GAME_TEST_MODE
        
        if(mTestPause || (gEditor != 0))
        {
            mGecko.mSpeedClimb = 0;
            mGecko.mSpeedClimbExtra = aJoystickPercent * (-(GECKO_SPEED_0 * 1.5f));
            aSpeedAngular = aJoystickAngularSpeed;
            
            mGecko.mSpeedAngular = aSpeedAngular;
        }
        else
        {
            
#endif
            mGecko.mSpeedClimb = mClimbSpeed;
            
            if(mJoystick.IsClicked())
            {
                aSpeedAngular = aJoystickAngularSpeed;
            }
            else
            {
                if(gApp->mControlMethod == CONTROL_METHOD_BOTH)
                {
                    aSpeedAngular = aAccelerometerAngularSpeed;
                }
                else
                {
                    aSpeedAngular = 0.0f;
                }
            }
            
            if(aJoystickPercent > 0.0f)aJoystickPercent *= 0.25f;
            
            if(mStartGamePreventMoveTimer > 0)
            {
                mGecko.mSpeedAngular = 0.0f;
                mGecko.mSpeedClimbExtra = 0.0f;
            }
            
            else
            {
                mGecko.mSpeedAngular = aSpeedAngular;
                mGecko.mSpeedClimbExtra = aJoystickPercent * (-(GECKO_SPEED_0 * 1.5f));
            }
        }
        
        
#ifdef GAME_TEST_MODE
        
        if(ShouldIdle())
        {
            
        }
    }
    
#endif
    
    
    /*
    if((mButtonAttack.mPressed == false) && (mButtonPause.mPressed == false))
    {
        for(int i=0;i<mApp->mMultiTouchCount;i++)
        {
            float aDiff = (gAppWidth2 - (float)mApp->mMultiTouchX[i]);
            float aPercent = aDiff / gAppWidth2;
            
            mGecko.mSpeedAngular = aPercent * 15.0f;
            aAngularMod = true;
            
            break;
        }
    }
     
    */
    
    EnumList(GameObject, aObject, mGameObjectsLuckyCoins.mObjects)
    {
        LuckyCoin *aCoin = ((LuckyCoin *)aObject);
        if((aCoin->mPassed==false) && (aCoin->mDodged==false) && (aCoin->mHit==false))
        {
            if((aCoin->mPos.mZ - aGeckoZ) < (-3.5f))
            {
                aCoin->mPassed = true;
                mLuckyCoinScoreFactor = 0;
            }
        }
    }
    
    if(mWave == 0)
    {
        if((mApp->mDidShowTutorialDialogBoxes==false) && (mWaveIndex == 1))
        {
            SpawnWave *aWave = mWaveGenerator.GenerateTrainingWave(0);
            SetupWave(aWave);
            mWaveIndex++;
        }
        else
        {
            SpawnWave *aWave = mWaveGenerator.Generate(mWaveIndex);
            SetupWave(aWave);
            mWaveIndex++;
        }
        
        if(mWaveIndex < 12)mClimbSpeed = GECKO_SPEED_0;
        else if(mWaveIndex < 20)mClimbSpeed = GECKO_SPEED_1;
        else if(mWaveIndex < 32)mClimbSpeed = GECKO_SPEED_2;
        else if(mWaveIndex < 40)mClimbSpeed = GECKO_SPEED_3;
        else if(mWaveIndex < 52)mClimbSpeed = GECKO_SPEED_4;
        else if(mWaveIndex < 64)mClimbSpeed = GECKO_SPEED_5;
        else if(mWaveIndex < 100)mClimbSpeed = GECKO_SPEED_6;
        else if(mWaveIndex < 150)mClimbSpeed = GECKO_SPEED_7;
        else if(mWaveIndex < 200)mClimbSpeed = GECKO_SPEED_8;
        else if(mWaveIndex < 250)mClimbSpeed = GECKO_SPEED_9;
        else if(mWaveIndex < 300)mClimbSpeed = GECKO_SPEED_10;
        
    }
    
    CheckSpawn();
    

    if(mHitAnimation)
    {
        if(mHitAnimationShakeAmount > 0)
        {
            mHitAnimationShakeAmount *= 0.985f;
            mHitAnimationShakeAmount -= 0.01f;
            if(mHitAnimationShakeAmount <= 0)
            {
                mHitAnimationShakeAmount = 0;
            }
        }
        
        if(mHitAnimationFadeSpeed > 0)
        {
            mHitAnimationFadeSpeed -= 0.0028f;
            mHitAnimationFade += mHitAnimationFadeSpeed;
        }
        else
        {
            mHitAnimationFadeSpeed -= 0.0015f;
            
            mHitAnimationFade += mHitAnimationFadeSpeed;
            
            if(mHitAnimationFade <= 0)
            {
                mHitAnimationFade = 0.0f;
            }
        }
        
        if((mHitAnimationFade <= 0) && (mHitAnimationShakeAmount <= 0.0f))
        {
            mHitAnimation = false;
        }
    }
    
    EnumList(Item, aItem, mItemList)
    {
        aItem->Update();
    }
    
    mJoystick.Update();
    
    //TODO: Tutorial Stuff...
    /*
    if(mApp->mDidShowTutorialDialogBoxes == false)
    {
        if(mDidShowDialogBoxJoystick == false)
        {
            if(mClimbHeight >= 76.0f)
            {
                mApp->ShowDialogWindow(&mApp->mDialogBoxTextJoystick);
                mDidShowDialogBoxJoystick = true;
                
                mTutorialArrowCenterX = mJoystick.mX + 84.0f * gGlobalScale;
                mTutorialArrowCenterY = mJoystick.mY;
                
                mTutorialArrowRotation = -90;
                
                mTutorialIndex = 0;
            }
        }
        
        if(mDidShowDialogBoxWhip == false)
        {
            if(mClimbHeight >= 150.0f)
            {
                mApp->mDidShowTutorialDialogBoxes = true;
                
                mApp->ShowDialogWindow(&mApp->mDialogBoxTextAttack);
                
                mDidShowDialogBoxWhip = true;
                
                mTutorialArrowCenterX = mButtonAttack.GetCenterX() - 80.0f * gGlobalScale;
                mTutorialArrowCenterY = mButtonAttack.GetCenterY();
                
                mTutorialIndex = 1;
                
                mTutorialArrowRotation = 90.0f;
                
                //mApp->SaveStatic();
            }
        }
    }
    */
    
    if(aGeckoZ >= 20)
    {
        //Log("GECKO SHIFFFTTTT: %f\n", aGeckoZ);
        //ShiftGlobal(-20.0f);
    }
}

void Game::Draw()
{
    Graphics::SetColor();
    
    FVec2 aCameraPush;
    FVec2 aGeckoPush = AngleToVector(mGecko.mOrbit);
    
    float aTargetX;
    float aTargetY;
    
    if(mCameraWanderMode)
    {
        aCameraPush = AngleToVector(mCameraRotaion + mCameraRotaionOffset + mCameraWanderRot);
        
        aTargetX = aGeckoPush.mX * (SEGMENT_RADIUS);
        aTargetY = aGeckoPush.mY * (SEGMENT_RADIUS);
        
        mCameraX = aTargetX + aCameraPush.mX * (mCameraDist);// + mCameraWanderZoom);
        mCameraY = aTargetY + aCameraPush.mY * (mCameraDist);// + mCameraWanderZoom);
    }
    else
    {
        aCameraPush = AngleToVector(mCameraRotaion + mCameraRotaionOffset);
        
        aTargetX = aGeckoPush.mX * (SEGMENT_RADIUS);
        aTargetY = aGeckoPush.mY * (SEGMENT_RADIUS);
        
        if(mGameOver)
        {
            mCameraX = aTargetX + aCameraPush.mX * (mGameOverCameraDist);
            mCameraY = aTargetY + aCameraPush.mY * (mGameOverCameraDist);
        }
        else
        {
            mCameraX = aTargetX + aCameraPush.mX * (mCameraDist);
            mCameraY = aTargetY + aCameraPush.mY * (mCameraDist);
        }
    }
    
    mCameraZ = mGecko.mPos.mZ + mCameraHeight;
    
    if(mCameraX == 0 && mCameraY == 0)
    {
        mCameraX = 0.01f;
    }
    
    Graphics::MatrixGoProjection();
    Graphics::MatrixLoadIdentity();
    
    Graphics::MatrixPerspective(mCameraFOV, mCameraAspect);
    
    Graphics::MatrixGoModelView();
    Graphics::MatrixLoadIdentity();
    
    
    
    if(mGameOver)
    {
        Graphics::MatrixLookAt(mCameraX, mCameraY, (mGameOverCameraTargetZ + mGameOverCameraTargetOffsetZ),// - aCameraFussiness,
                               mGecko.mPos.mX+mCameraOffsetX,mGecko.mPos.mY+mCameraOffsetY,mGameOverCameraStartZ + mGameOverCameraOffsetZ,
                               0,0,1.0f);
    }
    else if(mCameraWanderMode)
    {
        Graphics::MatrixLookAt(mCameraX, mCameraY, mCameraZ + mCameraWanderPanZ,
                               mGecko.mPos.mX+mCameraOffsetX-3.0f , mGecko.mPos.mY+mCameraOffsetY,mGecko.mPos.mZ+mCameraOffsetZ,
                               0,0,1.0f);
    }
    else
    {
        Graphics::MatrixLookAt(mCameraX, mCameraY, mCameraZ,// - aCameraFussiness,
                               mGecko.mPos.mX+mCameraOffsetX,mGecko.mPos.mY+mCameraOffsetY,mGecko.mPos.mZ+mCameraOffsetZ,
                               0,0,1.0f);
    }
    
    
    Graphics::SetShadeSmooth();
    
    
    Graphics::ClearDepth(0.1f,0.0f,0.0f);
    Graphics::EnableDepth();
    
    //GL_COLOR_BUFFER_BIT
    //Indicates the buffers currently enabled for color
    //    writing.
    //    GL_DEPTH_BUFFER_BIT
    
    Graphics::EnableCullFaces();
    Graphics::DepthMaskTrue();
    
    
    
    /*
    
    Clip(0.0f,0.0f,gAppWidth,gAppHeight);
    
    
    
    Graphics::Go3D();
    Graphics::MatrixGoProjection();
    Graphics::MatrixLoadIdentity();
    
    float aAspect = (float)gAppWidth / (float)gAppHeight;
     
    
    gluPerspective(64.0f, aAspect, 0.1f, 255.0f);
    
    float aCameraFussiness = fabsf(mRotationDifference) * 0.15f;
    aCameraFussiness = 0.0f;
    
    Graphics::MatrixGoModelView();
    Graphics::MatrixLoadIdentity();
    
    
    
    if(mGameOver)
    {
        
        Graphics::MatrixLookAt(mCameraX, mCameraY, (mGameOverCameraTargetZ + mGameOverCameraTargetOffsetZ) - aCameraFussiness,
                               mGecko.mPos.mX+mCameraOffsetX,mGecko.mPos.mY+mCameraOffsetY,mGameOverCameraStartZ + mGameOverCameraOffsetZ,
                               0,0,1.0f);
    }
    else if(mCameraWanderMode)
    {
        Graphics::MatrixLookAt(mCameraX, mCameraY, mCameraZ + mCameraWanderPanZ,
                               mGecko.mPos.mX+mCameraOffsetX,mGecko.mPos.mY+mCameraOffsetY,mGecko.mPos.mZ+mCameraOffsetZ,
                               0,0,1.0f);
    }
    else
    {
        Graphics::MatrixLookAt(mCameraX, mCameraY, mCameraZ - aCameraFussiness,
                               mGecko.mPos.mX+mCameraOffsetX,mGecko.mPos.mY+mCameraOffsetY,mGecko.mPos.mZ+mCameraOffsetZ,
                               0,0,1.0f);
    }
    
    
    
    
    if(mHitAnimationShakeAmount > 0)
    {
        float aShakeX = gRand.GetFloat(-mHitAnimationShakeAmount, mHitAnimationShakeAmount);
        float aShakeY = gRand.GetFloat(-mHitAnimationShakeAmount, mHitAnimationShakeAmount);
        
        Translate(aShakeX, aShakeY);
    }
    
    
    
    Graphics::SetColor();
    
    
    //float aPanoZTrans = gTestSlide1 * 50.0f + -25.0f;
    //aPanoZTrans = -16.0f;
     
    */
    
    
    if(mHitAnimationShakeAmount > 0)
    {
        float aShakeX = gRand.GetFloat(-mHitAnimationShakeAmount, mHitAnimationShakeAmount);
        float aShakeY = gRand.GetFloat(-mHitAnimationShakeAmount, mHitAnimationShakeAmount);
        
        Graphics::Translate(aShakeX, aShakeY);
    }
    
    Graphics::BlendDisable();
    
    Graphics::MatrixPush();
    Graphics::Translate(0, 0, mGecko.mPos.mZ - 16.0f);
    Graphics::Rotate(mGecko.mOrbit);
    
    float *aXYZ = mApp->mPano[0].mXYZ;
    float *aUVW = mApp->mPano[0].mUVW;
    float *aNormal = mApp->mPano[0].mNormal;
    unsigned short *aIndex = mApp->mPano[0].mIndex;
    
    Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex + 0, 72, mApp->mPanoUVW.mTexture);
    
    aUVW = mApp->mPano[1].mUVW;
    
    Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex + 72, 72, mApp->mPanoUVW.mTexture);
    
    Graphics::MatrixPop();
    Graphics::EnableDepth();
    Graphics::ClearDepth();
    
    Graphics::EnableCullFaces();
    Graphics::DepthMaskTrue();
    
    mTree.Draw();
    
    mDoodads.Draw();
    
    Graphics::SetColor();
    
    mGecko.Draw();
    
#ifdef GAME_TEST_MODE
    if(gEditor == 0)
    {
#endif
        mObjects.Draw();
        
        mApp->mRing.DrawEfficientSetup();
        
        EnumList(Ring, aObject, mGameObjectsRings.mObjects)
        {
            if(aObject->mKill == 0)
            {
                aObject->DrawEfficient();
            }
        }
        
        mGameObjectsBranches.Draw();
        mGameObjectsLuckyCoins.Draw();
        
#ifdef GAME_TEST_MODE
    }
    else
    {
        Graphics::SetColor();
        
        EnumList(EditorWaveNode, aNode, mWaveNodeListEditorTemp)
        {
            
            aNode->mObjectOrbit = GenerateObjectOrbit(aNode->mX);
            aNode->mObjectZ = GenerateObjectZ(aNode->mY);
            aNode->DrawObject();
            
            if(mSymmetrical)
            {
                float aHoldOrbit = aNode->mObjectOrbit;
                aNode->mObjectOrbit += 180.0f;
                aNode->DrawObject();
                aNode->mObjectOrbit = aHoldOrbit;
            }
        }
    }
#endif
    

    
    Graphics::BlendEnable();
    Graphics::DisableCullFaces();
    Graphics::DepthMaskFalse();
    
    mEffects.Draw();
    mEffectsProjectiles.Draw();
    
    Graphics::SetColor();
    //Graphics::BlendDisable();
    EnumList(GameObject, aObject, mGameObjectsRings.mObjects)aObject->DrawEffects();
    
    
    //Graphics::BlendEnable();
    Graphics::BlendSetAlpha();
    EnumList(GameObject, aObject, mGameObjectsBranches.mObjects)aObject->DrawEffects();
    
    
    EnumList(GameObject, aObject, mGameObjectsLuckyCoins.mObjects)
    {
        aObject->DrawEffects();
    }
    
    EnumList(GameObject, aObject, mObjects.mObjects)
    {
        aObject->DrawEffects();
    }
    
#ifdef GAME_TEST_MODE
    
    Graphics::SetColor();
    
    float aSphereRot;
    
    float aSphereX[4];
    float aSphereY[4];
    float aSphereZ[4];
    float aSphereRadius[4];
    
    aSphereX[0] = mGecko.mPos.mX;
    aSphereY[0] = mGecko.mPos.mY;
    aSphereZ[0] = mGecko.mPos.mZ - 0.2f;
    aSphereRadius[0] = 1.3f;
    
    aSphereRot = mGecko.mOrbit - mGecko.mRotation * 0.25f;
    aSphereX[1] = Sin(aSphereRot) * SEGMENT_RADIUS;
    aSphereY[1] = Cos(aSphereRot) * SEGMENT_RADIUS;
    aSphereZ[1] = mGecko.mPos.mZ + 1.2f;
    aSphereRadius[1] = 1.3f;
    
    aSphereRot = mGecko.mOrbit - mGecko.mRotation * 0.58f;
    aSphereX[2] = Sin(aSphereRot) * SEGMENT_RADIUS;
    aSphereY[2] = Cos(aSphereRot) * SEGMENT_RADIUS;
    aSphereZ[2] = mGecko.mPos.mZ + 2.4f;
    aSphereRadius[2] = 1.3f;
    
    aSphereRot = mGecko.mOrbit + mGecko.mRotation * 0.25f;
    aSphereX[3] = Sin(aSphereRot) * SEGMENT_RADIUS;
    aSphereY[3] = Cos(aSphereRot) * SEGMENT_RADIUS;
    aSphereZ[3] = mGecko.mPos.mZ - 1.2f;
    aSphereRadius[3] = 1.3f;
    
    if(gTestFlag2)
    {
        Graphics::BlendSetAdditive();
        for(int i=0;i<4;i++)
        {
            SetColorSwatch(i);
            Graphics::DrawSphere12(aSphereX[i], aSphereY[i], aSphereZ[i], aSphereRadius[i]);
        }
        if(mGecko.mAttacking)
        {
            Graphics::SetColor(0.7f, 0.2f, 0.4f);
            Graphics::DrawSphere12(mGecko.mPos.mX, mGecko.mPos.mY, mGecko.mPos.mZ, COLLIDE_RADIUS_ATTACK);
        }
        if(mGecko.mBoosting)
        {
            Graphics::SetColor(0.2f, 0.7f, 0.4f);
            Graphics::DrawSphere12(mGecko.mPos.mX, mGecko.mPos.mY, mGecko.mPos.mZ, COLLIDE_RADIUS_BOOST);
        }
        Graphics::SetColor(0.5f,0.5f,0.5f);
        EnumList(GameObject, aObject, mObjects.mObjects)
        {
            Graphics::DrawSphere12(aObject->mPos.mX, aObject->mPos.mY, aObject->mPos.mZ, aObject->mRadius);
        }
        EnumList(GameObject, aObject, mGameObjectsRings.mObjects)
        {
            Graphics::DrawSphere12(aObject->mPos.mX, aObject->mPos.mY, aObject->mPos.mZ, aObject->mRadius);
        }
        EnumList(GameObject, aObject, mGameObjectsBranches.mObjects)
        {
            Graphics::DrawSphere12(aObject->mPos.mX, aObject->mPos.mY, aObject->mPos.mZ, aObject->mRadius);
        }
        EnumList(GameObject, aObject, mGameObjectsLuckyCoins.mObjects)
        {
            Graphics::DrawSphere12(aObject->mPos.mX, aObject->mPos.mY, aObject->mPos.mZ, aObject->mRadius);
        }
    }
    
#endif
    
    //Graphics::Go2D();
    DrawTransform();
    
    //Graphics::DepthMaskFalse();
    Graphics::DisableDepth();
    Graphics::BlendSetAlpha();// ();// ();
    Graphics::BlendEnable();
    
    
    if(mHitAnimation)
    {
        Graphics::SetColor(1.0f, 0.0f, 0.0f, mHitAnimationFade);
        Graphics::DrawRect(0.0f, 0.0f, gAppWidth, gAppHeight);
    }
    
    if(mGecko.mBoosting)
    {
        float aBoostSin = Sin(mGecko.mBoostSin);
        float aBoostPercent = mGecko.mBoostPercent;
        
        Graphics::BlendSetAdditive();
        
        EnumList(SpeedBoostMark, aBoostMark, mSpeedBoostMarks.mObjects)
        {
            aBoostMark->Draw(aBoostPercent);
        }
        
        //Graphics::SetColor(0.9f, 0.9f, 1.0f, aBoostPercent * 0.33f);
        //DrawRect(0.0f, 0.0f, gAppWidth, gAppHeight);
        
        Graphics::SetColor(aBoostPercent);
        
        int aFireFrame = (int)mGecko.mBoostFrameFire;
        
        int aFireFrame2 = aFireFrame + 7;
        if(aFireFrame2 >= FIRE_FRAMES)aFireFrame2 -= FIRE_FRAMES;
        
        if(aFireFrame < 0)aFireFrame = 0;
        if(aFireFrame >= FIRE_FRAMES)aFireFrame = (FIRE_FRAMES - 1);
        
        float aSinShift = aBoostSin * aBoostPercent * (-20.0f);
        aSinShift = 0.0f;
        
        
        float aFireballX = gAppWidth2 - 12.0f;
        float aFireballY = gAppHeight2 + 180.0f + aSinShift;
        
        mApp->mAnimationFire[aFireFrame].Draw(aFireballX, aFireballY, 2.6f, 180.0f + mGecko.mRotation);
        
        /*
        
        Graphics::MatrixPush();
        
        Graphics::Translate(gAppWidth2 - 6.0f * gGlobalScale, gAppHeight2 + ((80.0f * gGlobalScale) + aSinShift), 0.0f);
        Graphics::Scale(2.6f);
        Graphics::Rotate(180.0f + mGecko.mRotation);
        Graphics::Translate(0.0f, -18.0f * gGlobalScale, 0.0f);
        
        mApp->mAnimationFire[aFireFrame].Draw();
        
        Graphics::MatrixPop();
        
        */
        
        
    }
    else
    {
        //mGecko.GoBoost();
    }
    
    Graphics::BlendSetAlpha();
    Graphics::SetColor();
    
    
#ifdef GAME_TEST_MODE
    if(gEditor)return;
#endif
    
    //mApp->mOverlay.Draw(gAppWidth2, gAppHeight2, 1.0f, 0.0f);
    
    float aAddHeight = (float)gAdBannerHeight;
    
    mTextBubbles.Draw();
    
    Graphics::SetColor();
    
    
    
    mJoystick.mColor.mAlpha = mInterfaceFade;
    
    mButtonAttack.mColor.mAlpha = mInterfaceFade;
    mButtonAttack.mColorDown.mAlpha = mInterfaceFade;
    mButtonAttack.mColorUp.mAlpha = mInterfaceFade;
    
    mButtonPause.mColor.mAlpha = mInterfaceFade;
    mButtonPause.mColorDown.mAlpha = mInterfaceFade;
    mButtonPause.mColorUp.mAlpha = mInterfaceFade;
    
    
    
    mJoystick.mHidden = false;
    mButtonAttack.mHidden = false;
    
    if(mInterfaceFade > 0)
    {
        
        
        Graphics::SetColor(mInterfaceFade);
        
        if(mApp->mDialogWindow)
        {
            if(mTutorialIndex != 0)mButtonAttack.mHidden = true;
            if(mTutorialIndex != 1)mJoystick.mHidden = false;
        }
        
        float aX = 0.0f;//-5.0f * gGlobalScale;
        float aY = 0.0f;
        
        float aDownShift = 46.0f; //gGlobalScale * 23.0f;
        
        mApp->mGameLabelScore.Draw(aX, aY);
        mApp->mGameLabelHeight.Draw(aX, aY + aDownShift);
        mApp->mGameLabelRings.Draw(aX, aY + aDownShift * 2.0f);
        
        aX += (mApp->mGameLabelScore.mWidth + 8.0f);
        
        
        mApp->mFontScore.Draw(FString(mApp->mScore), aX, aY);
        //mApp->mFontScore.Reset();
        //mApp->mFontScore.WriteNumber(mApp->mScore);
        //mApp->mFontScore.Draw(aX, aY);
        //mApp->mFontScore.Reset();
        
        
        FString aHeightString;
        aHeightString.ParseFloat(mClimbHeight / 2.0f);
        aHeightString = aHeightString.GetSubString(0, aHeightString.mLength - 4);
        mApp->mFontScore.Draw(aHeightString.c(), aX, aY + aDownShift);
        //mApp->mFontScore.Write(aHeightString.c());
        //mApp->mFontScore.Draw(aX, aY + aDownShift);
        //mApp->mFontScore.Reset();
        
        
        mApp->mFontScore.Draw(FString(mApp->mRingCount), aX, aY + aDownShift * 2.0f);
        //mApp->mFontScore.WriteNumber(mApp->mRingCount);
        //mApp->mFontScore.Draw(aX, aY + aDownShift * 2.0f);
        //mApp->mFontScore.Reset();
        
        
        int aLifeColumns = mApp->mLivesMax;
        if(aLifeColumns > 4)aLifeColumns = 4;
        
        float aLifeSpacingH = 4.0f;
        float aLifeWidth = mApp->mLifeEmpty.mWidth;
        float aLifeHeight = mApp->mLifeEmpty.mHeight;
        
        float aLifeXStart = gAppWidth - (aLifeSpacingH + aLifeWidth) * aLifeColumns;
        float aLifeX = aLifeXStart;
        float aLifeY = 4.0f;
        
        int aLifeCol = 0;
        
        for(int aLifeIndex=0;aLifeIndex<mApp->mLivesMax;aLifeIndex++)
        {
            
            if(aLifeIndex < mApp->mLives)mApp->mLifeFull.Draw(aLifeX, aLifeY);
            else mApp->mLifeEmpty.Draw(aLifeX, aLifeY);
            
            aLifeCol++;
            if(aLifeCol == 4)
            {
                aLifeY += aLifeHeight;
                aLifeX = aLifeXStart;
                aLifeCol = 0;
            }
            else
            {
                aLifeX += (aLifeSpacingH + aLifeWidth);
            }
        }
    }
    else
    {
        
    }
    
    
    if(mApp->mAchievementBox)
    {
        mApp->mAchievementBox->Draw();
    }
    
    EnumList(Item, aItem, mItemList)
    {
        aItem->Draw();
    }
    
    if(mResumeGameFromInactive)
    {
        Graphics::SetColor(0.0f, 0.0f, 0.0f, 0.5f);
        Graphics::DrawRect(0.0f, 0.0f, gAppWidth, gAppHeight);
        Graphics::SetColor();
        mApp->mGameTextPause.Draw(gAppWidth2, gAppHeight2, 1.0f, 0.0f);
    }
    
    if(mApp->mPauseFade > 0)
    {
        Graphics::SetColor(0.0f, 0.0f, 0.0f, mApp->mPauseFade);
        Graphics::DrawRect(0.0f, 0.0f, gAppWidth, gAppHeight);
    }
    
    if(mGameOverFade > 0)
    {
        Graphics::SetColor(0.0f, 0.0f, 0.0f, mGameOverFade);
        Graphics::DrawRect(0.0f, 0.0f, gAppWidth, gAppHeight);
    }
    
    
    if(mGameOver)
    {
        Graphics::SetColor();
        
        mApp->mGameOverText[0].Center(mGameOverTextX[0], mGameOverTextY[0]);
        mApp->mGameOverText[1].Center(mGameOverTextX[1], mGameOverTextY[1]);
        
        if(mGameOverCanTapToReset)
        {
            Graphics::SetColor(mGameOverTapResetFade);
            mApp->mGameOverTapResumeText.Center(gAppWidth2, gAppHeight2 + 144.0f);
            Graphics::SetColor();
        }
    }
    
    if(mFadeReset)
    {
        if(mFadeResetAlpha >= 0.0f)
        {
            Graphics::SetColor(0.0f, 0.0f, 0.0f, mFadeResetAlpha);
            Graphics::DrawRect(0.0f, 0.0f, gAppWidth, gAppHeight);
        }
    }
    
    Graphics::SetColor();
}

void Game::DrawOver()
{
    
    if(mApp->mDialogWindow)
    {
        /*
         for(int i=0;i<4;i++)
         {
         float aArrowShiftX = 0.0f;
         float aArrowShiftY = 0.0f;
         
         float aArrowRot = i * 90;
         
         if(i == 0)aArrowShiftY = mTutorialArrowShift;
         if(i == 1)aArrowShiftX = -mTutorialArrowShift;
         if(i == 2)aArrowShiftY = -mTutorialArrowShift;
         if(i == 3)aArrowShiftX = mTutorialArrowShift;
         
         mApp->mTutorialButtonArrow.Draw(mTutorialArrowCenterX + aArrowShiftX, mTutorialArrowCenterY + aArrowShiftY, mTutorialArrowScale, aArrowRot);
         }
         */
        
        
        mApp->mTutorialButtonArrow.Draw(mTutorialArrowCenterX, mTutorialArrowCenterY, mTutorialArrowScale, mTutorialArrowRotation);
        
        if(mTutorialIndex == 0)mJoystick.Draw();
        else mButtonAttack.Draw();
        
    }
    
}




void Game::Notify(void *pData)
{
    
    if(mMenuMode)
    {
        return;
    }
    
    if(pData==&mButtonPause)
	{
		if(!mMenu)
		{
			mMenu=new GameMenu();
            AddChild(mMenu);
			//*this+=mMenu;
		}
	}
    
    if(pData == &mButtonAttack)
    {
        mGecko.GoAttack();
    }
    
	if(pData==mMenu && pData!=0)
	{
		mMenu->Kill();
		mMenu=0;
	}
    
#ifdef GAME_TEST_MODE
    if(pData==&mButtonTest)
    {
        mTestPause = !mTestPause;
    }
#endif
    
}

void Game::TouchDown(float pX, float pY, void *pData)
{
    
    int aIndex=0;
    EnumList(GameObject, aObject, mGameObjectsRings.mObjects)
    {
        
        Log("Ring[%d] Kill[%d]\n", aIndex, aObject->mKill);
        
        aIndex++;
    }
    /*
    if(ShouldInteract())
    {
        mJoystick.TouchDown(pX, pY, pData);
        mButtonAttack.TouchDown(pX, pY, pData);
        mButtonPause.TouchDown(pX, pY, pData);
    }
    else
    {
        mJoystick.TouchFlush();
        mButtonAttack.TouchFlush();
        mButtonPause.TouchFlush();
    }
    */
    
    if(mGameOver && mGameOverCanTapToReset)
    {
        mGameOverCanTapToReset = false;
        FadeRestart();
    }
    
    //HitHarmful();
    //LoseLife();
    
    mResumeGameFromInactive = false;
    

#ifdef GAME_TEST_MODE

    if(pX <= 50.0f)
    {
        if(mGameOver)
        {
            Recover();
        }
    }
    
    if((pY > (gAppHeight - gAppHeight / 4)) && (pX > (gAppWidth - gAppWidth / 6)))
    {
        //mHideGecko = !mHideGecko;
    }
    
    else if((pY>(gAppHeight-gAppHeight/4)) && (pX>(gAppWidth-gAppWidth/2)))
    {
        //mHideGecko = !mHideGecko;
    }
    
    //mHideObjects=true;
    
#endif
    
    
}

void Game::TouchMove(float pX, float pY, void *pData)
{
    
    /*
    
    if(ShouldInteract())
    {
        mJoystick.TouchMove(pX, pY, pData);
        mButtonAttack.TouchMove(pX, pY, pData);
        mButtonPause.TouchMove(pX, pY, pData);
    }
    else
    {
        mJoystick.TouchFlush();
        mButtonAttack.TouchFlush();
        mButtonPause.TouchFlush();
    }
    
    */
    
}

void Game::TouchUp(float pX, float pY, void *pData)
{
    /*
    
    if(ShouldInteract())
    {
        mJoystick.TouchUp(pX, pY, pData);
        mButtonAttack.TouchUp(pX, pY, pData);
        mButtonPause.TouchUp(pX, pY, pData);
    }
    else
    {
        mJoystick.TouchFlush();
        mButtonAttack.TouchFlush();
        mButtonPause.TouchFlush();
    }
    
    */
    
}

void Game::TouchFlush()
{
    /*
    
    mJoystick.TouchFlush();
    mButtonAttack.TouchFlush();
    mButtonPause.TouchFlush();
    
    */
    
}





void Game::Accelerometer(float x, float y, float z, bool pReverse)
{
    mAccelX = x;
    mAccelY = y;
    mAccelZ = z;
    
    mAccelReverse = pReverse;
}

void Game::UpdateGameObjects(FObjectList *pManager)
{
    
#ifdef GAME_TEST_MODE
    mHideGecko = gTestFlag3;
#endif
    
    
    
    float aGeckoZ = mGecko.mPos.mZ;
    
    float aFloor = (aGeckoZ - KILL_FLOOR_OBJECT);
    float aFloorHit = (aGeckoZ - KILL_FLOOR_OBJECT_HIT);
    
    
    EnumList(GameObject, aObject, pManager->mObjects)
    {
        if(aObject->mHit)
        {
            if(aObject->mPos.mZ <= aFloorHit)
            {
                aObject->Kill();
            }
        }
        else
        {
            if(aObject->mPos.mZ <= aFloor)
            {
                aObject->Kill();
            }
        }
    }
    
    pManager->Update();
    
}

void Game::CollideGameObjects(FObjectList *pManager)
{
    float aDiffX, aDiffY, aDiffZ;
    float aDist;
    
    float aSphereBoostX = mGecko.mPos.mX;
    float aSphereBoostY = mGecko.mPos.mY;
    float aSphereBoostZ = mGecko.mPos.mZ;
    
    if(mGecko.mBoosting)
    {
        mHitInvincible = true;
        EnumList(GameObject, aObject, pManager->mObjects)
        {
            
            for(int i=0;i<4;i++)
            {
                if((aObject->mHit==false) && (aObject->mDodged==false))
                {
                    aDiffX = aObject->mPos.mX - aSphereBoostX;
                    aDiffY = aObject->mPos.mY - aSphereBoostY;
                    aDiffZ = aObject->mPos.mZ - aSphereBoostZ;
                    
                    aDist = aDiffX * aDiffX + aDiffY * aDiffY + aDiffZ * aDiffZ;
                    
                    //if(aDist <= (aSphereRadius[i] + aObject->mRadiusSquared))
                    if(aDist <= ((COLLIDE_RADIUS_BOOST + aObject->mRadius) * (COLLIDE_RADIUS_BOOST + aObject->mRadius)))
                    {
                        Hit(aObject);
                    }
                }
            }
        }        
        return;
    }
    
    float aSphereAttackX = mGecko.mPos.mX;
    float aSphereAttackY = mGecko.mPos.mY;
    float aSphereAttackZ = mGecko.mPos.mZ;
    
    if(mGecko.mAnimAttack)
    {
        mHitInvincible = true;
        
        int aType;
        EnumList(GameObject, aObject, pManager->mObjects)
        {
            aType = aObject->mType;
            
            if(aType == GO_TYPE_RING ||
               aType == GO_TYPE_SNAIL)
            {
                for(int i=0;i<3;i++)
                {
                    if((aObject->mHit==false) && (aObject->mDodged==false))
                    {
                        aDiffX = aObject->mPos.mX - aSphereAttackX;
                        aDiffY = aObject->mPos.mY - aSphereAttackY;
                        aDiffZ = aObject->mPos.mZ - aSphereAttackZ;
                        
                        aDist = aDiffX * aDiffX + aDiffY * aDiffY + aDiffZ * aDiffZ;
                        
                        if(aDist <= (COLLIDE_RADIUS_ATTACK + aObject->mRadius) * (COLLIDE_RADIUS_ATTACK + aObject->mRadius))
                        {
                            Hit(aObject);
                        }
                    }
                }
            }
        }
        
        
        EnumList(GameObject, aObject, pManager->mObjects)
        {
            aType = aObject->mType;
            
            if(aType == GO_TYPE_LUCKY_COIN ||
               aType == GO_TYPE_SPEED_BOOST ||
               aType == GO_TYPE_FREE_LIFE)
            {
                for(int i=0;i<3;i++)
                {
                    if((aObject->mHit==false) && (aObject->mDodged==false))
                    {
                        aDiffX = aObject->mPos.mX - aSphereAttackX;
                        aDiffY = aObject->mPos.mY - aSphereAttackY;
                        aDiffZ = aObject->mPos.mZ - aSphereAttackZ;
                        
                        aDist = aDiffX * aDiffX + aDiffY * aDiffY + aDiffZ * aDiffZ;
                        
                        if(aDist <= (COLLIDE_RADIUS_ATTACK_SPECIAL_ITEMS + aObject->mRadius) * (COLLIDE_RADIUS_ATTACK_SPECIAL_ITEMS + aObject->mRadius))
                        {
                            Hit(aObject);
                        }
                    }
                }
            }
        }
        
        
        
    }
    
    
    float aSphereRot;
    
    float aSphereX[4];
    float aSphereY[4];
    float aSphereZ[4];
    float aSphereRadius[4];
    
    
    aSphereX[0] = mGecko.mPos.mX;
    aSphereY[0] = mGecko.mPos.mY;
    aSphereZ[0] = mGecko.mPos.mZ - 0.2f;
    aSphereRadius[0] = 1.3f;
    
    aSphereRot = mGecko.mOrbit - mGecko.mRotation * 0.25f;
    aSphereX[1] = Sin(aSphereRot) * SEGMENT_RADIUS;
    aSphereY[1] = Cos(aSphereRot) * SEGMENT_RADIUS;
    aSphereZ[1] = mGecko.mPos.mZ + 1.2f;
    aSphereRadius[1] = 1.3f;
    
    aSphereRot = mGecko.mOrbit - mGecko.mRotation * 0.58f;
    aSphereX[2] = Sin(aSphereRot) * SEGMENT_RADIUS;
    aSphereY[2] = Cos(aSphereRot) * SEGMENT_RADIUS;
    aSphereZ[2] = mGecko.mPos.mZ + 2.4f;
    aSphereRadius[2] = 1.3f;
    
    aSphereRot = mGecko.mOrbit + mGecko.mRotation * 0.25f;
    aSphereX[3] = Sin(aSphereRot) * SEGMENT_RADIUS;
    aSphereY[3] = Cos(aSphereRot) * SEGMENT_RADIUS;
    aSphereZ[3] = mGecko.mPos.mZ - 1.2f;
    aSphereRadius[3] = 1.3f;

    mHitInvincible = false;
    
    EnumList(GameObject, aObject, pManager->mObjects)
    {
        
        for(int i=0;i<4;i++)
        {
            if((aObject->mHit==false) && (aObject->mDodged==false))
            {
                aDiffX = aObject->mPos.mX - aSphereX[i];
                aDiffY = aObject->mPos.mY - aSphereY[i];
                aDiffZ = aObject->mPos.mZ - aSphereZ[i];
                
                aDist = aDiffX * aDiffX + aDiffY * aDiffY + aDiffZ * aDiffZ;
                
                if(aDist <= ((aSphereRadius[i] + aObject->mRadius) * (aSphereRadius[i] + aObject->mRadius)))
                {
                    Hit(aObject);
                }
            }
        }
    }
}

void Game::ItemProc(Item *pItem, GameObject *pObject)
{
    if(pItem)
    {
        pItem->mCoolDown = pItem->mCoolDownTime;
        
        if(pItem->mID == ITEM_BRANCH_NUKE)
        {
            EnumList(Branch, aObject, mGameObjectsBranches.mObjects)
            {
                if(aObject->mHit == false)
                {
                    aObject->mHit = true;
                    aObject->Kaboom();
                }
            }
        }
        
        //ITEM_EVADE_BRANCH);
        
        //mItemList += GenerateItem(ITEM_EVADE_SNAIL);
        //mItemList += GenerateItem(ITEM_EVADE_ALL);
        //mItemList += GenerateItem(ITEM_BRANCH_NUKE);
        
    }
}

void Game::Hit(GameObject *pObject)
{
    
    if(pObject)
    {
        if(mHitInvincible == false)
        {
            EnumList(Item, aItem, mItemList)
            {
                if(aItem->mCoolDown <= 0)
                {
                    if(pObject->mDodged == false)
                    {
                        if(aItem->WillDodge(pObject))
                        {
                            pObject->mDodged = true;
                            ItemProc(aItem, pObject);
                            
                            TextBubble *aBubble = new TextBubble();
                            if(gRand.GetBool())aBubble->SetSprite(&mApp->mGameTextDodge);
                            else aBubble->SetSprite(&mApp->mGameTextEvade);
                            AddTextBubble(aBubble);
                        }
                        else if(aItem->WillAbsorb(pObject))
                        {
                            pObject->mDodged = true;
                            ItemProc(aItem, pObject);
                            
                            TextBubble *aBubble = new TextBubble();
                            aBubble->SetSprite(&mApp->mGameTextAbsorb);
                            AddTextBubble(aBubble);
                        }
                    }
                }
            }
        }
        
        if(pObject->mDodged == false)
        {
            pObject->mHit = true;
            
            int aType = pObject->mType;
            
            if(aType == GO_TYPE_RING)HitRing((Ring *)pObject);
            else if(aType == GO_TYPE_BRANCH)HitBranch((Branch *)pObject);
            else if(aType == GO_TYPE_BRANCH_SMALL)HitBranchBig((BranchBig *)pObject);
            else if(aType == GO_TYPE_BRANCH_BIG)HitBranchSmall((BranchSmall *)pObject);
            else if(aType == GO_TYPE_FREE_LIFE)HitFreeLife((FreeLife*)pObject);
            else if(aType == GO_TYPE_POISON_FLOWER)HitPoisonFlower((PoisonFlower*)pObject);
            else if(aType == GO_TYPE_SPEED_BOOST)HitSpeedBooster((SpeedBooster*)pObject);
            else if(aType == GO_TYPE_SPIKE_BOMB)HitSpikeBomb((SpikeBomb*)pObject);
            else if(aType == GO_TYPE_SNAIL){HitSnail((Snail *)pObject);}
            else if(aType == GO_TYPE_LUCKY_COIN){HitLuckyCoin((LuckyCoin *)pObject);}
            
        }
    }
}

void Game::HitHarmful()
{
    
    if(mHitInvincible)
    {
        
    }
    else
    {
        if(mHitAnimation == false)
        {
            mGecko.mHitTimer = 100;
            
            LoseLife();
            
            TextBubble *aBubble = new TextBubble();
            aBubble->SetSprite(&mApp->mGameTextLifeLose);
            AddTextBubble(aBubble);
        }
    }
}

void Game::HitSnail(Snail *pSnail)
{
    HitHarmful();
    
    if(mGecko.mAttacking)
    {
        mApp->AchProgressGroup("snail");
        
        mApp->mSoundSnailWhipped.Play();
        mApp->mScore += 25;
    }
    else
    {
        mApp->mSoundSnail.Play();
    }
    
    pSnail->Kaboom();
    
}


void Game::HitBranchBig(BranchBig *pBranch)
{
    mAnimationGenerator.GenerateAnimation(pBranch);
    
    HitHarmful();
    
    if(mGecko.mBoosting)mApp->mSoundBranchHitBoost.Play();
    else mApp->mSoundBranchHit.Play();
    
    pBranch->Kaboom();
}

void Game::HitBranchSmall(BranchSmall *pBranch)
{
    mAnimationGenerator.GenerateAnimation(pBranch);
    HitHarmful();
    pBranch->Kaboom();
    
    if(mGecko.mBoosting)mApp->mSoundBranchHitBoost.Play();
    else mApp->mSoundBranchHit.Play();
}

void Game::HitBranch(Branch *pBranch)
{
    mApp->AchProgressGroup("branch");
    
    mAnimationGenerator.GenerateAnimation(pBranch);
    HitHarmful();
    pBranch->Kaboom();
    
    if(mGecko.mBoosting)mApp->mSoundBranchHitBoost.Play();
    else mApp->mSoundBranchHit.Play();
}

void Game::HitFreeLife(FreeLife *pFreeLife)
{
    mApp->AchProgressGroup("heart");
    
    if(mApp->mLives < mApp->mLivesMax)
    {
        mApp->mLives++;
        mApp->mScore += 250;
        
        TextBubble *aBubble = new TextBubble();
        aBubble->SetSprite(&mApp->mGameTextLifeGain);
        AddTextBubble(aBubble);
    }
    else
    {
        mApp->mScore += 1000;
        TextBubble *aBubble = new TextBubble();
        aBubble->SetText(FString("+1000").c());
        AddTextBubble(aBubble);
    }
    
    mAnimationGenerator.GenerateAnimation(pFreeLife);
    
    
    mApp->mSoundFreeLife.Play();
    pFreeLife->Kill();
    
    
}


void Game::HitSpikeBomb(SpikeBomb *pSpikeBomb)
{
    mAnimationGenerator.GenerateAnimation(pSpikeBomb);
    
    pSpikeBomb->Kill();
    
    mApp->mSoundExplosion.Play();
    
    HitHarmful();
}

void Game::HitSpeedBooster(SpeedBooster *pSpeedRamp)
{
    mApp->AchProgressGroup("boost");
    mAnimationGenerator.GenerateAnimation(pSpeedRamp);
    mApp->mScore += 200;
    pSpeedRamp->Kill();
    mGecko.GoBoost();
}

void Game::HitRing(Ring *pRing)
{
    mApp->AchProgressGroup("ring");
    
    mAnimationGenerator.GenerateAnimation(pRing);
    
    mApp->mRingCount += 1;
    mApp->mScore += (8 + gRand.Get(2));
    
    if(mStarPitchDirection == 1)
    {
        mStarPitch += 0.03f;
        if(mStarPitch >= 2.4)
        {
            mStarPitch = 2.4;
            mStarPitchDirection = 0;
        }
    }
    else
    {
        mStarPitch -= 0.03f;
        if(mStarPitch <= 1)
        {
            mStarPitch = 1;
            mStarPitchDirection = 1;
        }
    }
    
    mApp->mSoundRing.PlayPitched(mStarPitch);
    
    pRing->Kill();
}


void Game::HitLuckyCoin(LuckyCoin *pLuckyCoin)
{
    mAnimationGenerator.GenerateAnimation(pLuckyCoin);
    
    mApp->mSoundLuckyCoin.Play();
    
    EnumList(LuckyCoin, aCoin, mGameObjectsLuckyCoins.mObjects)
    {
        if(aCoin != pLuckyCoin)
        {
            if(fabsf(aCoin->mPos.mZ - pLuckyCoin->mPos.mZ) < (1.0f))
            {
                aCoin->mPassed = true;
            }
        }
    }
    
    mLuckyCoinScoreFactor += 100;
    mApp->mScore += mLuckyCoinScoreFactor;
    
    TextBubble *aBubble = new TextBubble();
    aBubble->SetText(FString(FString("+") + FString((int)mLuckyCoinScoreFactor)).c());
    AddTextBubble(aBubble);
    
    pLuckyCoin->Kill();
}

void Game::HitPoisonFlower(PoisonFlower *pPoisonFlower)
{
    HitHarmful();
    
    pPoisonFlower->Kaboom();
    
    if(mGecko.mAttacking)mApp->mSoundSnailWhipped.Play();
    else mApp->mSoundSnail.Play();
}

/*
void Game::SpawnNodeRemove(SpawnWaveNode *pNode)
{
    if(!pNode)
    {
        return;
    }
    EnumList(GameObject, aObject, mObjects.mObjects)
    {
        if(aObject->mNode == pNode)
        {
            aObject->mNode = 0;
            aObject->Kill();
        }
    }
    SpawnNodeRemove(pNode);
}
 

bool Game::SpawnNodeExists(SpawnWaveNode *pNode)
{
    EnumList(GameObject, aObject, mObjects.mObjects)
    {
        if(aObject->mNode == pNode && aObject->mKill == 0)
        {
            return true;
        }
    }
    return false;
}
*/

GameObject *Game::GenerateObject(int pType)
{
    GameObject *aReturn = 0;
    
    if(pType == GO_TYPE_BRANCH_RANDOM)
    {
        int aRand = gRand.Get(3);
        if(aRand == 0)aReturn = new BranchSmall();
        else if(aRand == 1) aReturn = new BranchBig();
        else aReturn = new Branch();
    }
    
    if(pType == GO_TYPE_BRANCH)aReturn = new Branch();
    if(pType == GO_TYPE_BRANCH_BIG)aReturn = new BranchBig();
    if(pType == GO_TYPE_BRANCH_SMALL)aReturn = new BranchSmall();
    
    if(pType == GO_TYPE_FREE_LIFE)aReturn = new FreeLife();
    
    if(pType == GO_TYPE_SPEED_BOOST)aReturn = new SpeedBooster();
    if(pType == GO_TYPE_SPIKE_BOMB)aReturn = new SpikeBomb();
    if(pType == GO_TYPE_RING)aReturn = new Ring();
    
    if(pType == GO_TYPE_POISON_FLOWER)aReturn = new PoisonFlower();
    if(pType == GO_TYPE_SNAIL)aReturn = new Snail();
    if(pType == GO_TYPE_LUCKY_COIN)
    {
        if((gRand.Get(12) == 4))aReturn = new FreeLife();
        else aReturn = new LuckyCoin();
    }
    
    return aReturn;
}

GameObject *Game::GenerateObject(SpawnWaveNode *pNode)
{
    GameObject *aReturn = 0;
    
    if(pNode)
    {
        aReturn = GenerateObject(pNode->mType);
    }
    
    return aReturn;
}


float Game::GenerateObjectOrbit(float pX)
{
    float aReturn = 0.0f;
    float aXPercent = (pX - EDITOR_START_X - (EDITOR_SECTION_WIDTH / 2.0f)) / EDITOR_SECTION_WIDTH;
    
    aReturn = aXPercent * 360.0f;
    aReturn = fmodf(aReturn, 360.0f);
    
    while(aReturn >= 360.0f)aReturn -= 360.0f;
    while(aReturn < 0)aReturn += 360.0f;
    
    return aReturn;
}

float Game::GenerateObjectZ(float pY)
{
    return (gAppHeight - pY) * (VERTICAL_SPREAD * (0.65f));
}

void Game::SetupWave(SpawnWave *pWave)
{
    //Log("Setting Up Wave..!\n");
    
    if(pWave == 0)return;
    
    float aPreviousGapEnd = mWaveGapEnd;
    float aRotationDifference = 0.0f;
    
    mWaveGapEnd = pWave->mPaddingEnd;
    mWaveGapStart = pWave->mPaddingStart;
    
    aRotationDifference = (mWaveCurrentEndRot1 - pWave->mRotationStart1);
    
    //Log("Rotation Info: CurEnd: %f   New Start: %f\n", mWaveCurrentEndRot1, pWave->mRotationStart1);
    
    pWave->mRotationStart1 += aRotationDifference;
    pWave->mRotationStart2 += aRotationDifference;
    
    pWave->mRotationEnd1 += aRotationDifference;
    pWave->mRotationEnd2 += aRotationDifference;
    
    pWave->mRotationStart1 = fmodf(pWave->mRotationStart1, 360.0f);
    if(pWave->mRotationStart1 >= 360.0f)pWave->mRotationStart1 -= 360.0f;
    if(pWave->mRotationStart1 < 0)pWave->mRotationStart1 += 360.0f;
    
    pWave->mRotationStart2 = fmodf(pWave->mRotationStart2, 360.0f);
    if(pWave->mRotationStart2 >= 360.0f)pWave->mRotationStart2 -= 360.0f;
    if(pWave->mRotationStart2 < 0)pWave->mRotationStart2 += 360.0f;
    
    pWave->mRotationEnd1 = fmodf(pWave->mRotationEnd1, 360.0f);
    if(pWave->mRotationEnd1 >= 360.0f)pWave->mRotationEnd1 -= 360.0f;
    if(pWave->mRotationEnd1 < 0)pWave->mRotationEnd1 += 360.0f;
    
    pWave->mRotationEnd2 = fmodf(pWave->mRotationEnd2, 360.0f);
    if(pWave->mRotationEnd2 >= 360.0f)pWave->mRotationEnd2 -= 360.0f;
    if(pWave->mRotationEnd2 < 0)pWave->mRotationEnd2 += 360.0f;
    
    float aMinZ = pWave->mMinZ;
    float aMaxZ = pWave->mMaxZ;
    
    bool aFirst = true;
    
    EnumList(SpawnWaveNode, aNode, pWave->mNodeList)
    {
        if(aFirst == true)
        {
            aMinZ = aNode->mObjectZ;
            aMaxZ = aNode->mObjectZ;
            aFirst = false;
        }
        else
        {
            if(aNode->mObjectZ < aMinZ)aMinZ = aNode->mObjectZ;
            if(aNode->mObjectZ > aMaxZ)aMaxZ = aNode->mObjectZ;
        }
    }
    
    float aWaveHeight = (aMaxZ - aMinZ);
    EnumList(SpawnWaveNode, aNode, pWave->mNodeList)
    {
        aNode->mObjectZ -= aMinZ;
        aNode->mObjectZ += mWaveSpawnZ;
        aNode->mObjectOrbit += aRotationDifference;
    }
    
    aMaxZ -= aMinZ;
    aMinZ = 0;
    
    aMaxZ += mWaveSpawnZ;
    aMinZ += mWaveSpawnZ;
    
    mWaveSpawnZ += (aWaveHeight + mWaveGapEnd);
    
    mWaveCurrentStartRot1 = pWave->mRotationStart1;
    mWaveCurrentStartRot2 = pWave->mRotationStart2;
    
    mWaveCurrentEndRot1 = pWave->mRotationEnd1;
    mWaveCurrentEndRot2 = pWave->mRotationEnd2;
    
    mWave = pWave;
    
    CheckSpawn();
}

void Game::CheckSpawn()
{
    if(mWave)
    {
        float aGeckoZ = mGecko.mPos.mZ;
        
        mSpawnAddList.mCount = 0;
        
        EnumList(SpawnWaveNode, aNode, mWave->mNodeList)
        {
            if((aNode->mObjectZ - SPAWN_DIST) < aGeckoZ)
            {
                mSpawnAddList += aNode;
            }
        }
        
        int aType;
        
        GameObject *aObject;
        
        EnumList(SpawnWaveNode, aNode, mSpawnAddList)
        {
            aType = aNode->mType;
            aObject = GenerateObject(aType);
            if(aObject)
            {
                aObject->mPos.mZ = aNode->mObjectZ;
                aObject->SetUp(aNode->mObjectOrbit);
                
                if(aObject->mType == GO_TYPE_RING)
                {
                    mGameObjectsRings.Add(aObject);
                }
                else if(aObject->mType == GO_TYPE_LUCKY_COIN)
                {
                    mGameObjectsLuckyCoins.Add(aObject);
                }
                else if((aObject->mType == GO_TYPE_BRANCH_RANDOM) || (aObject->mType == GO_TYPE_BRANCH_BIG ) || (aObject->mType == GO_TYPE_BRANCH_SMALL) || (aObject->mType == GO_TYPE_BRANCH))
                {
                    mGameObjectsBranches.Add(aObject);
                }
                else
                {
                    mObjects.Add(aObject);
                }
            }
            
            mWave->mNodeList -= aNode;
            
            delete aNode;
        }
        
        if(mWave->mNodeList.mCount <= 0)
        {
            delete mPreviousWave;
            mPreviousWave = mWave;
            mWave = 0;
        }
        
    }
    
}

#ifdef GAME_TEST_MODE
void Game::DrawSphere(FVec3 pPos, float pRadius)
{
    Graphics::BlendEnable();
    Graphics::BlendSetAlpha();
    
    //Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.5f);
    
    Graphics::MatrixPush();
    Graphics::Translate(pPos.mX ,pPos.mY , pPos.mZ);
    Graphics::Scale(pRadius);
    
    //mApp->mEffectSphere.Draw();
    
    Graphics::MatrixPop();
}
#endif

void Game::LoseLife()
{
    
    //mGameOverCameraDropTimer = 200;
    
    if(mGameOver == false)
    {
        mGecko.Hurt();
        
        mApp->mLives--;
        
        if(gApp->mInvincible)
        {
            mApp->mLives = mApp->mLivesMax;
        }
        
        //TODO: Kludge... Remove
        //if(mApp->mLives <= 0)mApp->mLives = mApp->mLivesMax;
        
        if(mApp->mLives <= 0)
        {
            mApp->mLives = 0;
            
            Die();
            
            //mApp->mLives = mApp->mLivesMax;
            
        }
        
        mHitAnimation = true;
        mHitAnimationShakeAmount = 0.66f;
        
        mHitAnimationFadeSpeed = 0.05f;
        mHitAnimationFade = 0.0f;
    }
}

void Game::Die()
{
    mGameOver = true;
    
    mGameOverCameraDropTimer = 70;
    
    mGameOverCameraStartZ = mGecko.mPos.mZ+mCameraOffsetZ;
    mGameOverCameraOffsetZ = 0.0f;
    mGameOverCameraDist = mCameraDist;
    
    mGameOverCameraTargetZ = mGecko.mPos.mZ + mCameraHeight;
    mGameOverCameraTargetOffsetZ = 0.0f;
    
    mGameOverFade = 0.0f;
    
    mGameOverTextTargetX[0] = gAppWidth2;
    mGameOverTextTargetY[0] = gAppHeight2 - 132.0f * 2.0f;
    
    mGameOverTextTargetX[1] = gAppWidth2;
    mGameOverTextTargetY[1] = gAppHeight2 - 12.0f * 2.0f;
    
    mGameOverTextX[0] = mGameOverTextTargetX[0] - (float)gAppWidth * 0.85f;
    mGameOverTextY[0] = mGameOverTextTargetY[0];
    
    mGameOverTextX[1] = mGameOverTextTargetX[1] + (float)gAppWidth * 0.85f;
    mGameOverTextY[1] = mGameOverTextTargetY[1];
    
    
    mGameOverTextTargetX[1] = gAppWidth2;
    mGameOverTextTargetY[1] = gAppHeight2 - 40.0f * 2.0f;
    
    mGecko.Die();
    
}

void Game::Recover()
{
    mGameOver = false;
    mGecko.Recover();
}

void Game::AddTextBubble(TextBubble *pBubble)
{
    //mTextBubbleStartY
    
    float aY = mTextBubbleStartY;
    
    TextBubble *aLastTextBubble = (TextBubble*)mTextBubbles.mObjects.Last();
    
    if(aLastTextBubble != 0)
    {
        float aBottomY = aLastTextBubble->mY + (aLastTextBubble->mHeight / 2.0f);
        aBottomY += pBubble->mHeight / 2.0f;
        
        if(aBottomY > aY)
        {
            aY = aBottomY;
        }
        //aLastTextBubble
    }
    pBubble->mY = aY;
    
    mTextBubbles.Add(pBubble);
}

SpawnWaveNode *Game::SpawnNodeFromXML(FXMLTag *pTag)
{
    SpawnWaveNode *aNode = new SpawnWaveNode();
    
    aNode->mType = GameObject::TypeIndex(pTag->GetParamValue("type"));;//FString(pTag->GetParamValue("type")).ToInt();
    
    float aX = IntToFloat(FString(pTag->GetParamValue("x")).ToInt());
    float aY = IntToFloat(FString(pTag->GetParamValue("y")).ToInt());
    //float aZ = IntToFloat(FString(pTag->GetParamValue("z")).ToInt());
    
    aNode->mObjectOrbit = GenerateObjectOrbit(aX);
    aNode->mObjectZ = GenerateObjectZ(aY);
    
    //Log("Spawning Node [%d] - (%f %f %f)\n", aNode->mType, aNode->mX, aNode->mY, aNode->mZ);
    
    return aNode;
}

void Game::FadeRestart(bool pGoToMenu)
{
    mFadeResetToMenu = pGoToMenu;
    mFadeReset = true;
    mFadeResetState = 0;
    mFadeResetAlpha = 0.0f;
}

bool Game::AnyMenuShowing()
{
    bool aReturn = false;
    
    if(mMenu)aReturn = true;
    if(mMenuMode)aReturn = true;
    if(mApp->mOptions)aReturn = true;
    if(mApp->mDialogWindow)aReturn = true;
    if(mApp->mPurchaseDialog)aReturn = true;
    if(mApp->mPurchaseDialogRestore)aReturn = true;
    
    return aReturn;
}

bool Game::ShouldFadeInterface()
{
    bool aReturn = true;
    if(mMenuMode)aReturn = false;
    //if(mGameOver)aReturn = false;
    return aReturn;
}

void Game::PositionItems()
{
    
    /*
    float aWidth = mApp->mItemBack.mWidth;
    float aHeight = mApp->mItemBack.mHeight;
    
    float aSpacing = 0.0f * gGlobalScale;
    float aTop = 36.0f * gGlobalScale;
    
    int aYIndex = 0;
    
    EnumList(Item, aItem, mItemList)
    {
        aItem->mX = gAppWidth - (aWidth / 2.0f + aSpacing);
        aItem->mY = aTop + (aHeight / 2.0f + aSpacing) + (aHeight + aSpacing) * aYIndex;
        
        aYIndex++;
    }
    */
    
}

bool Game::ShouldPause()
{
    bool aReturn = false;
    
    if(mMenuMode == false)
    {
        if(mMenu)aReturn = true;
        if(mApp->mOptions)aReturn = true;
        if(mResumeGameFromInactive)aReturn = true;
        if(mApp->mDialogWindow)aReturn = true;
        if(mApp->mPurchaseDialog)aReturn = true;
        if(mApp->mPurchaseDialogRestore)aReturn = true;
    }
    
    if(mFadeReset)
    {
        if(mFadeResetState == 0)aReturn = true;
    }
    
    return aReturn;
}

bool Game::ShouldInteract()
{
    bool aReturn = true;
    
    if(AnyMenuShowing())aReturn = false;
    
    if(mGameOver)aReturn = false;
    if(mPaused)aReturn = false;
    return aReturn;
}

bool Game::ShouldDisplayButtons()
{
    bool aReturn = true;
    
    if(mMenu)aReturn = false;
    if(mMenuMode)aReturn = false;
    if(mApp->mOptions)aReturn = false;
    
    
    return aReturn;
}

bool Game::ShouldMove()
{
    bool aReturn = true;
    
    if(mMenu)aReturn = false;
    if(mMenuMode)aReturn = false;
    if(mApp->mOptions)aReturn = false;
    if(mGameOver)aReturn = false;
    
    return aReturn;
}

bool Game::ShouldIdle()
{
    bool aReturn = false;
    if(mMenuMode)aReturn = true;
    return aReturn;
}


bool Game::ShouldResumePause()
{
    bool aReturn = true;
    
    if(AnyMenuShowing())aReturn = false;
    if(mGameOver)aReturn = false;
    
    return aReturn;
}

void Game::Inactive()
{
    FView::Inactive();
    
    mJoystick.TouchFlush();
    mButtonAttack.TouchFlush();
    mButtonPause.TouchFlush();
}

void Game::Active()
{
    FView::Active();
    if(ShouldResumePause())mResumeGameFromInactive = true;
    
    mJoystick.TouchFlush();
    mButtonAttack.TouchFlush();
    mButtonPause.TouchFlush();
}

void Game::ShiftGlobal(float pShiftAmount)
{
    mGecko.mPos.mZ += pShiftAmount;
    
    EnumList(GameObject, aObject, mObjects.mObjects)
    {
        aObject->mPos.mZ += pShiftAmount;
    }
    EnumList(GameObject, aObject, mGameObjectsRings.mObjects)
    {
        aObject->mPos.mZ += pShiftAmount;
    }
    EnumList(GameObject, aObject, mGameObjectsBranches.mObjects)
    {
        aObject->mPos.mZ += pShiftAmount;
    }
    EnumList(GameObject, aObject, mGameObjectsLuckyCoins.mObjects)
    {
        aObject->mPos.mZ += pShiftAmount;
    }
    
    EnumList(Effect, aObject, mEffects.mObjects)
    {
        aObject->mPos.mZ += pShiftAmount;
    }
    
    if(mWave)
    {
        EnumList(SpawnWaveNode, aNode, mWave->mNodeList)
        {
            aNode->mObjectZ += pShiftAmount;
        }
    }
    
    mTree.Shift(pShiftAmount);
    mWaveSpawnZ += pShiftAmount;
}

void Game::Dummy()
{
    Item *aItem = new Item();
    
    FreeLife *aFreeList = new FreeLife();
    
    
    
}