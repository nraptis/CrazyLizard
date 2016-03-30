

//  Game.h
//  DoomKnights
//
//  Created by Nick Raptis on 1/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.



#ifndef GAME_H
#define GAME_H

#define MAX_SPEED_STATES 100

#define VERTICAL_SPREAD (0.1f)

#define KILL_FLOOR_TREE (20.0f)
#define KILL_FLOOR_OBJECT (12.0f)
#define KILL_FLOOR_OBJECT_HIT (100.0f)

#define GECKO_START_Z (12.0f)
#define WAVE_START_Z (GECKO_START_Z + 9.0f)

#define SPAWN_DIST (64.0f)



#define SPEEDY_START_MODE 1

//#undef SPEEDY_START_MODE

#include "GLApp.h"
#include "FJoystick.h"
#include "Gecko.h"
#include "UberTree.h"
#include "FSpline.h"
#include "GameMenu.h"
#include "SpawnWave.h"
#include "AnimationEffect.h"
#include "TextBubble.h"
#include "WaveGenerator.h"
#include "AnimationGenerator.h"
#include "FXML.h"

class SpeedBooster;
class LuckyCoin;
class PoisonFlower;
class Snail;
class Item;
class Branch;
class BranchBig;
class BranchSmall;
class FreeLife;
class SpikeBomb;
class Ring;

class Game : public FView
{
public:
    
    Game();
	virtual ~Game();
    
    virtual void                        PositionContent();
    
    int                                 mTime;
    int                                 mMinutes;
    int                                 mSeconds;
    int                                 mMilliseconds;
    
    int                                 mEffectSequenceTestCount;
    
    void                                Restart(const char *pFilePath=0);
    
	GLApp                               *mApp;
    GameMenu                            *mMenu;
    
	virtual void                        Draw();
    virtual void                        DrawOver();
    
	virtual void                        Update();
    
    int                                 mTutorialIndex;
    
    float                               mTutorialArrowScale;
    float                               mTutorialArrowScaleSin;
    
    float                               mTutorialArrowCenterX;
    float                               mTutorialArrowCenterY;
    
    float                               mTutorialArrowRotation;
    
    bool                                ShouldPause();
    bool                                ShouldInteract();
    bool                                ShouldDisplayButtons();
    bool                                ShouldMove();
    bool                                ShouldIdle();
    bool                                ShouldResumePause();
    
    bool                                AnyMenuShowing();
    
    bool                                ShouldFadeInterface();
    
    float                               mInterfaceFade;
    
    virtual void                        Inactive();
    virtual void                        Active();
    
    virtual void                        Notify(void *pData);
    
    void                                Pause();
    void                                Unpause();
    void                                PauseToggle();
    
    void                                CheckSpawn();
    
    void                                FadeRestart(bool pGoToMenu=true);
    
    bool                                mFadeReset;
    bool                                mFadeResetToMenu;
    
    int                                 mFadeResetState;
    int                                 mFadeResetTimer;
    
    float                               mFadeResetAlpha;
    
    bool                                mMenuMode;
    bool                                mMenuFadeMode;
    bool                                mPaused;
    bool                                mWait;
    
    int                                 mStartGamePreventMoveTimer;
    
    bool                                mDidShowDialogBoxJoystick;
    bool                                mDidShowDialogBoxWhip;
    
    virtual void                        TouchDown(float pX, float pY, void *pData);
	virtual void                        TouchMove(float pX, float pY, void *pData);
    virtual void                        TouchUp(float pX, float pY, void *pData);
    virtual void                        TouchFlush();
    
    void                                Accelerometer(float x, float y, float z, bool pReverse);
    
    void                                UpdateGameObjects(FObjectList *pManager);
    void                                CollideGameObjects(FObjectList *pManager);
    
    GameObject                          *GenerateObject(int pType);
    GameObject                          *GenerateObject(SpawnWaveNode *pNode);
    
    FJoystick                           mJoystick;
    
    void                                ShiftGlobal(float pShiftAmount);
    
    int                                 mClimbSpeedIndex;
    float                               mClimbSpeed;
    
    FButton                             mButtonAttack;
    FButton                             mButtonPause;
    
    float                               GenerateObjectOrbit(float pX);
    float                               GenerateObjectZ(float pY);
    
    void                                ItemProc(Item *pItem, GameObject *pObject);
    
    void                                Hit(GameObject *pObject);
    void                                HitBranch(Branch *pBranch);
    void                                HitBranchBig(BranchBig *pBranch);
    void                                HitBranchSmall(BranchSmall *pBranch);
    void                                HitFreeLife(FreeLife *pFreeLife);
    void                                HitSpikeBomb(SpikeBomb *pSpikeBomb);
    void                                HitSpeedBooster(SpeedBooster *pSpeedBooster);
    void                                HitSnail(Snail *pSnail);
    void                                HitRing(Ring *pRing);
    void                                HitLuckyCoin(LuckyCoin *pLuckyCoin);
    void                                HitPoisonFlower(PoisonFlower *pPoisonFlower);
    
    void                                HitHarmful();
    void                                LoseLife();
    
    bool                                mHitInvincible;
    
    bool                                mHitAnimation;
    
    float                               mHitAnimationFade;
    float                               mHitAnimationFadeSpeed;
    float                               mHitAnimationShakeAmount;
    
    FList                               mWaveNodeList;
    FList                               mSpawnAddList;
    
    FList                               mItemList;
    void                                PositionItems();
    
    FObjectList                         mDoodads;
    FObjectList                         mObjects;
    
    FObjectList                         mGameObjectsRings;
    FObjectList                         mGameObjectsBranches;
    FObjectList                         mGameObjectsLuckyCoins;
    
    FObjectList                         mEffects;
    FObjectList                         mEffectsProjectiles;
    
    FObjectList                         mSpeedBoostMarks;
    FObjectList                         mTextBubbles;
    
    void                                AddTextBubble(TextBubble *pBubble);
    float                               mTextBubbleStartY;
    float                               mTextBubbleExtraSpeed;
    
    Gecko                               mGecko;
    
    UberTree                            mTree;
    
    void                                Die();
    void                                Recover();
    
    float                               mClimbHeight;
    
    bool                                mGameOver;
    int                                 mGameOverCameraDropTimer;
    int                                 mGameOverMenuShowTimer;
    
    bool                                mGameOverCanTapToReset;
    float                               mGameOverTapResetFade;
    
    float                               mGameOverCameraStartZ;
    float                               mGameOverCameraOffsetZ;
    float                               mGameOverCameraTargetZ;
    float                               mGameOverCameraTargetOffsetZ;
    
    float                               mGameOverCameraDist;
    float                               mGameOverFade;
    
    float                               mGameOverTextX[2];
    float                               mGameOverTextY[2];
    
    float                               mGameOverTextTargetX[2];
    float                               mGameOverTextTargetY[2];
    
    bool                                mResumeGameFromInactive;
    
    int                                 mLuckyCoinScoreFactor;
    int                                 mStarPitchDirection;
    
    float                               mStarPitch;
    
    float                               mAccelX;
    float                               mAccelY;
    float                               mAccelZ;
    
    bool                                mAccelReverse;
    bool                                mSymmetrical;
    
    float                               mCameraX;
    float                               mCameraY;
    float                               mCameraZ;
    
    float                               mCameraAspect;
    
    float                               mCameraOffsetX;
    float                               mCameraOffsetY;
    float                               mCameraOffsetZ;
    
    float                               mCameraFOV;
    
    float                               mCameraDist;
    float                               mCameraRotaion;
    float                               mCameraRotaionTarget;
    float                               mCameraRotaionOffset;
    
    float                               mRotationDifference;
    
    float                               mCameraHeight;
    
    bool                                mCameraWanderMode;
    
    FSpline                             mCameraWanderRotSpline;
    FSpline                             mCameraWanderPanSpline;
    FSpline                             mCameraWanderZoomSpline;
    
    float                               mCameraWanderPos;
    
    float                               mCameraWanderRot;
    float                               mCameraWanderZoom;
    float                               mCameraWanderPanZ;
    
    float                               mCameraWanderStartRot;
    float                               mCameraWanderStartZoom;
    float                               mCameraWanderStartPanZ;
    
    float                               mCameraWanderTargetRot;
    float                               mCameraWanderTargetZoom;
    float                               mCameraWanderTargetPanZ;
    
    int                                 mCameraWanderTimer;
    int                                 mCameraWanderTime;
    int                                 mCameraWanderWait;
    
    SpawnWaveNode                       *SpawnNodeFromXML(FXMLTag *pTag);
    
    
    void                                SetCurrentWave(SpawnWave *pTargetWave);
    void                                SetupWave(SpawnWave *pWave);
    
    int                                 mWaveIndex;
    
    WaveGenerator                       mWaveGenerator;
    AnimationGenerator                  mAnimationGenerator;
    
    SpawnWave                           *mWave;
    SpawnWave                           *mPreviousWave;
    
    float                               mWaveCurrentStartRot1;
    float                               mWaveCurrentStartRot2;
    
    float                               mWaveCurrentEndRot1;
    float                               mWaveCurrentEndRot2;
    
    float                               mWaveSpawnZ;
    float                               mWaveGap;
    
    float                               mWaveGapStart;
    float                               mWaveGapEnd;
    
    
    
#ifdef GAME_TEST_MODE
    
    FList                                mWaveNodeListEditorTemp;
    
    FButton                             mButtonTest;
    void                                DrawSphere(FVec3 pPos, float pRadius);
    
    bool                                mTestPause;
    
    bool                                mHideGecko;
    bool                                mHideObjects;
    
#endif
    
    
    void                                Dummy();
    
    
};

#endif








