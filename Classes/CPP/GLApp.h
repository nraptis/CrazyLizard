#pragma once


#define GAME_TEST_MODE 1
#undef GAME_TEST_MODE

#define EDITOR_SECTION_WIDTH (512.0f)
#define EDITOR_SECTION_WIDTH_2 (EDITOR_SECTION_WIDTH / 2.0f)
#define EDITOR_START_X ((768 - EDITOR_SECTION_WIDTH) / 2.0f)

#include "FApp.h"
#include "FModelData.h"
#include "FModelDataSequence.h"
#include "FFont.h"
#include "AchievementBox.h"
#include "app_global.h"

//crazy_lizard_upgrade
//crazy_lizard_scores

//TODO: FOR EDITOR, MORE THAN 16...
#ifdef GAME_TEST_MODE
#define SEGMENT_COUNT 60
#else
#define SEGMENT_COUNT 16
#endif


//#define SEGMENT_COUNT 50

#define SEGMENT_HEIGHT (8.0f)
#define SEGMENT_RADIUS (5.0)

#define FIRE_FRAMES 21
#define RING_SPARKLE_FRAMES 45

#define SPARK_FRAMES 11

#define EFFECT_BURST_1_FRAMES 27
//#define EFFECT_BURST_2_FRAMES 37

#define EFFECT_EXPLODE_FRAMES 54

//#define EFFECT_LUCKY_HALO_FRAMES (11)

#define CONTROL_METHOD_JOYSTICK 0
#define CONTROL_METHOD_BOTH 1

#define ANIM_SHIFT_OVER_GECKO (1.32f)

#define MX(x) (gAppWidth2  + (((x) - (320.0f / 2.0f)) * gGlobalScale))
#define MY(y) (gAppHeight2 + (((y) - (480.0f / 2.0f)) * gGlobalScale))

#define TX(x) ((320.0f / 2.0f) + (((x) - gAppWidth2) / gGlobalScale))
#define TY(y) ((480.0f / 2.0f) + (((y) - gAppHeight2) / gGlobalScale))

#define MENU_PANEL_CENTER_Y (gAppHeight2 - 40.0f * gGlobalScale)
#define MENU_DONE_BUTTON_Y (gAppHeight2 + 46.0f * gGlobalScale)

#define MENU_HEADER_Y (gAppHeight2 - 154.0f * gGlobalScale)

class Game;
class Store;

#ifdef GAME_TEST_MODE
class Editor;
#endif

class Options;
class PurchaseDialog;
class PurchaseDialogRestore;
class MainMenu;
class GameOverScreen;
class GameCenterMenu;
class DialogWindow;

class GLApp : public FApp
{
public:
	
    GLApp();
	virtual ~GLApp();
    
    virtual void                            Update();
    
    virtual void                            DrawOver();
    
    virtual void                            CleanForGame();
    virtual void                            Clean();
	virtual void                            Load();
    
    virtual void                            LoadImagesSplatted();
    virtual void                            LoadImagesUnsplatted();
    
    
	virtual void                            LoadComplete();
    virtual void                            Accelerometer(float x, float y, float z, bool pReverse);
    
    virtual void                            Message(FString pMessage, FString pArguments);
    
	virtual void                            SuccessfulPurchase(char* pId);
	virtual void                            FailPurchase(char* pId);
	virtual void                            CancelPurchase(char* pId);
    
	virtual void                            PauseForIAd();
	virtual void                            UnpauseForIAd();
    
    void                                    ExitGame();
    void                                    PlayGame();
    void                                    ShowMainMenu();
    
    void                                    ShowOptions();
    void                                    ShowGameOverScreen();
    void                                    ShowFailScreen();
    
    void                                    ShowGameCenterMenu();
    void                                    ShowStore();
    
    void                                    ShowDialogWindow(FSprite *pFSprite);
    
    virtual void                            AchProgress(const char *pAchievementName, int pCount=1);
    virtual void                            AchProgressGroup(const char *pGroupName, int pCount=1);
    
    FList                                   mRecentAchievementList;
    FList                                   mAchievementTextList;
    
    AchievementBox                          *mAchievementBox;
    
    Options                                 *mOptions;
    PurchaseDialog                          *mPurchaseDialog;
    PurchaseDialogRestore                   *mPurchaseDialogRestore;
    MainMenu                                *mMainMenu;
    GameOverScreen                          *mGameOverScreen;
    Game                                    *mGame;
    
#ifdef GAME_TEST_MODE
    Editor                                  *mEditor;
#endif
    
    GameCenterMenu                          *mGameCenterMenu;
    Store                                   *mStore;
    DialogWindow                            *mDialogWindow;
    
    FString                                 mLastEditorPath;
    void                                    TestEditorToggle();
    
    
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    //
    //
    //          Non-Model Flat 2-D FSprites
    //
    //
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    
    
    ///Achievement Shitttttt
    ///
    
    FSprite                                 mAchievementBack;
    
    ///
    ///////////
    
    //FSprite                                 mItemBack;
    //FSprite                                 mItemRingCooldown;
    //FSprite                                 mItemRingLoaded;
    //FSprite                                 mItemFlash;
    
    FSprite                                 mGameOverText[2];
    FSprite                                 mGameOverTapResumeText;
    
    
    FSprite                                 mMainMenuButtonPlay[2];
    FSprite                                 mMainMenuButtonAch[2];
    FSprite                                 mMainMenuButtonHS[2];
    FSprite                                 mMainMenuButtonOptions[2];
    FSprite                                 mMainMenuButtonStore[2];
    FSprite                                 mMainMenuButtonGames[2];
    
    FSprite                                 mMenuButtonBack[2];
    
    FSprite                                 mMenuButtonTextResumeGame;
    FSprite                                 mMenuButtonTextOptions;
    FSprite                                 mMenuButtonTextMainMenu;
    FSprite                                 mMenuButtonTextTryAgain;
    FSprite                                 mMenuButtonTextClose;
    FSprite                                 mMenuButtonTextContinue;
    FSprite                                 mMenuButtonTextDone;
    
    FSprite                                 mDialogBoxButtonClose;
    FSprite                                 mDialogBoxBack;
    FSprite                                 mDialogBoxTextJoystick;
    FSprite                                 mDialogBoxTextAttack;
    FSprite                                 mTutorialButtonArrow;
    
    FSprite                                 mMenuArrow;
    
    FFont                                   mFontScore;
    FFont                                   mFontGold;
    
    FSprite                                 mButtonAttack[2];
    FSprite                                 mButtonPause[2];
    FSprite                                 mButtonUpgrade;
    FSprite                                 mButtonRestore;
    
    
    FSprite                                 mLifeEmpty;
    FSprite                                 mLifeFull;
    
    FSprite                                 mGameTextLifeGain;
    FSprite                                 mGameTextLifeLose;
    
    FSprite                                 mGameTextDodge;
    FSprite                                 mGameTextAbsorb;
    FSprite                                 mGameTextEvade;
    
    FSprite                                 mGameLabelScore;
    FSprite                                 mGameLabelRings;
    FSprite                                 mGameLabelHeight;
    
    FSprite                                 mGameTextPause;
    
    FSprite                                 mJoystickKnob;
    FSprite                                 mJoystickKnobSelected;
    FSprite                                 mJoystickBack;
    
    FSprite                                 mOptionsThumb;
    FSprite                                 mOptionsSliderMusic;
    FSprite                                 mOptionsSliderSFX;
    
    FSprite                                 mOptionsControlSegmentUnderlay;
    FSprite                                 mOptionsControlSegment[2];
    FSprite                                 mOptionsControlSegmentSelected[2];
    
    FSprite                                 mMenuBackPanel;
    
    FSprite                                 mMenuHeaderOptions;
    FSprite                                 mMenuHeaderPaused;
    FSprite                                 mMenuHeaderGC;
    FSprite                                 mMenuHeaderPurchase;
    FSprite                                 mMenuHeaderRestorePurchase;
    
    
    FSprite                                 mMenuTextGC;
    FSprite                                 mMenuTextPurchase;
    
    
    FSprite                                 mMenuTextGCError;
    FSprite                                 mMenuTextPurchaseSuccess;
    FSprite                                 mMenuTextPurchaseCanceled;
    FSprite                                 mMenuTextPurchaseError;
    
    
    
    
    
    FSprite                                 mAnimationFire[FIRE_FRAMES];
    
    FModelDataIndexed                        mTitleTextCrazy[5];
    FModelDataIndexed                        mTitleTextLizard[6];
    FSprite                                 mTitleTextUVW;
    
    FSprite                                 mAnimationSparkUVW[SPARK_FRAMES];
    FModelDataIndexed                        **mAnimationSpark;
    FModelDataIndexed                        **mAnimationBombSpark;
    
    FSprite                                 mAnimationBurst1UVW[EFFECT_BURST_1_FRAMES];
    FModelDataIndexed                        **mAnimationBurst1;
    
    //FSprite                                 mAnimationBurst2UVW[EFFECT_BURST_2_FRAMES];
    //FModelDataIndexed                        **mAnimationBurst2;
    
    FSprite                                 mAnimationExplodeUVW[EFFECT_EXPLODE_FRAMES];
    FModelDataIndexed                        **mAnimationExplode;
    
    //FSprite                                 mAnimationLuckyHaloUVW[EFFECT_LUCKY_HALO_FRAMES];
    //FModelDataIndexed                        **mAnimationLuckyHalo;
    
    //FModelDataIndexed                        mFlowerLeaves;
    //FSprite                                 mFlowerLeavesUVW;
    
    //FModelDataIndexed                        mFlowerSpiked;
    //FSprite                                 mFlowerSpikedUVW;
    
    FSprite                                 mSnailUVW;
    FModelDataIndexed                        mSnail;
    
    FModelDataIndexed                        mStar;
    FSprite                                 mStarUVW;
    
    FModelDataIndexed                        mBomb;
    FSprite                                 mBombUVW;
    
    FModelDataIndexed                        mSpeedBoost;
    FSprite                                 mSpeedBoostUVW;
    
    FSprite                                 mBranchUVW;
    FModelDataIndexed                        mBranchArm[3];
    FModelDataIndexed                        mBranchBase;
    FModelDataIndexed                        mBranchArmStump;
    FModelDataIndexed                        mBranchBaseStump;
    
    FSprite                                 mBranchBigUVW;
    FModelDataIndexed                        mBranchBigArm[5];
    FModelDataIndexed                        mBranchBigBase;
    FModelDataIndexed                        mBranchBigArmStump;
    FModelDataIndexed                        mBranchBigBaseStump;
    
    FSprite                                 mBranchSmallUVW;
    FModelDataIndexed                        mBranchSmallArm[3];
    FModelDataIndexed                        mBranchSmallBase;
    FModelDataIndexed                        mBranchSmallArmStump;
    FModelDataIndexed                        mBranchSmallBaseStump;
    
    FModelDataIndexed                        mBranchLeaves[3];
    FModelDataIndexed                        mBranchBigLeaves[5];
    FModelDataIndexed                        mBranchSmallLeaves[3];
    
    FSprite                                 mLeavesUVW;
    
    FModelDataIndexed                        mDynomite;
    FSprite                                 mDynomiteUVW;
    
    FModelDataIndexed                        mHeart;
    FSprite                                 mHeartUVW;
    
    FSprite                                 mPanoUVW;
    FModelDataIndexed                        mPano[2];
    
    
    FModelDataIndexed                        mRing;
    FSprite                                 mRingUVW;
    
    FSprite                                 mGeckoUVW;
    
    FModelDataSequence                       mGeckoSequenceRun;
    FModelDataSequence                       mGeckoSequenceIdle;
    FModelDataSequence                       mGeckoSequenceBoost;
    FModelDataSequence                       mGeckoSequenceHurt;
    FModelDataSequence                       mGeckoSequenceAttack;
    
    FSprite                                 mTreeBark;
    FModelDataIndexed                        mTreeRing;
    
    
    
    
    FSound                                   mSoundAchievement;
    
    FSound                                   mSoundAmbience[11];
    FSound                                   mSoundFootstep[3];
    
    FSound                                   mSoundBranchHit;
    FSound                                   mSoundBranchHitBoost;
    
    FSound                                   mSoundFreeLife;
    
    FSound                                   mSoundSpeedBoosStart;
    FSound                                   mSoundSpeedBoosFireLoop;
    
    FSound                                   mSoundRing;
    
    FSound                                   mSoundSnail;
    FSound                                   mSoundSnailWhipped;
    
    FSound                                   mSoundExplosion;
    FSound                                   mSoundLuckyCoin;
    FSound                                   mSoundTailWhip;
    
    int                                     mControlMethod;
    
    float                                   mPauseFade;
    
    int                                     mScore;
    int                                     mRingCount;
    
    int                                     mLives;
    int                                     mLivesMax;
    
    float                                   mClimbHeight;
    
    bool                                    mDidShowTutorialDialogBoxes;
    
    bool                                    mInvincible;
    
    FString                                 mLoopingWaveName;
    
};

extern Game *gGame;

extern float gGlobalScale;







