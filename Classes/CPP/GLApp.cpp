#include "GLApp.h"
#include "FModelData.h"

#ifdef GAME_TEST_MODE
#include "Editor.h"
#endif

#include "Options.h"
#include "MainMenu.h"
#include "GameOverScreen.h"
#include "GameCenterMenu.h"
#include "DialogWindow.h"
#include "Store.h"
#include "Game.h"
#include "app_global.h"
#include "core_includes.h"

Game *gGame = 0;
float gGlobalScale = 1.0f;

GLApp::GLApp()
{
	gApp = this;
    
    gGlobalScale = 1.0f;
    if(gIsLargeScreen)gGlobalScale = 2.0f;
    
    mDidShowTutorialDialogBoxes = false;
    
    mOptions = 0;
    mPurchaseDialog = 0;
    mPurchaseDialogRestore = 0;
    mMainMenu = 0;
    mGameOverScreen = 0;
    mGame = 0;
    mStore = 0;
    
#ifdef GAME_TEST_MODE
    mEditor = 0;
#endif
    
    mGameCenterMenu = 0;
    mDialogWindow = 0;
    
    mAchievementBox = 0;
    
    mPauseFade = 0.0f;
    
    mControlMethod = CONTROL_METHOD_BOTH;
    
    mInvincible = false;
    
    /*
    
    mAchievementManager.Add("dead_ringer");
    
    mAchievementManager.Add("ring_100", "ring", 500);
    mAchievementManager.Add("ring_250", "ring", 1000);
    mAchievementManager.Add("ring_500", "ring", 2500);
    mAchievementManager.Add("ring_1000", "ring", 5000);
    mAchievementManager.Add("ring_1500", "ring", 7500);
    mAchievementManager.Add("ring_2500", "ring", 10000);
    mAchievementManager.Add("ring_5000", "ring", 15000);
    mAchievementManager.Add("ring_7500", "ring", 20000);
    mAchievementManager.Add("ring_10000", "ring", 30000);
    mAchievementManager.Add("ring_12500", "ring", 40000);
    mAchievementManager.Add("ring_15000", "ring", 50000);
    
    mAchievementManager.Add("branch_5", "branch", 15);
    mAchievementManager.Add("branch_25", "branch", 50);
    mAchievementManager.Add("branch_50", "branch", 100);
    mAchievementManager.Add("branch_100", "branch", 250);
    mAchievementManager.Add("branch_250", "branch", 500);
    
    mAchievementManager.Add("snail_1", "snail", 1);
    mAchievementManager.Add("snail_10", "snail", 25);
    mAchievementManager.Add("snail_50", "snail", 50);
    mAchievementManager.Add("snail_100", "snail", 100);
    mAchievementManager.Add("snail_250", "snail", 250);
    mAchievementManager.Add("snail_500", "snail", 500);
    
    mAchievementManager.Add("boost_3", "boost", 3);
    mAchievementManager.Add("boost_10", "boost", 10);
    mAchievementManager.Add("boost_20", "boost", 25);
    mAchievementManager.Add("boost_30", "boost", 50);
    mAchievementManager.Add("boost_50", "boost", 100);
    
    //mAchievementManager.Print();
    
    */
    
    gSpriteScale = 2.0f;
    
    gViewController.SetNaturalSize(768.0f, 1024.0f);
    gViewController.FitTypeSetWidth();
    
}

GLApp::~GLApp()
{
    if(mGame)mGame->Kill();mGame=0;
}

void GLApp::CleanForGame()
{
    if(mGameCenterMenu)mGameCenterMenu->Kill();mGameCenterMenu=0;
    if(mOptions)mOptions->Kill();mOptions=0;
}

void GLApp::Clean()
{
    if(mGame)mGame->Kill();
    if(mOptions)mOptions->Kill();
    if(mMainMenu)mMainMenu->Kill();
    if(mGameOverScreen)mGameOverScreen->Kill();
#ifdef GAME_TEST_MODE
    if(mEditor)mEditor->Kill();
#endif
    if(mGameCenterMenu)mGameCenterMenu->Kill();
    if(mStore)mStore->Kill();
    
    mOptions = 0;
    mPurchaseDialog = 0;
    mPurchaseDialogRestore = 0;
    mMainMenu = 0;
    mGameOverScreen = 0;
    mGame = 0;
    
#ifdef GAME_TEST_MODE
    mEditor = 0;
#endif
    
    mGameCenterMenu = 0;
    mStore = 0;
}

void GLApp::Load()
{
    //gFModelDiscardNormals = true;
    
    /*
     mGeckoSequenceIdle.Load("gecko_attack_", 1000);
     mGeckoSequenceIdle.Save("_gecko_attack.seq");
     
     mGeckoSequenceIdle.Load("gecko_idle_", 600);
     mGeckoSequenceIdle.Save("_gecko_idle.seq");
     
     mGeckoSequenceIdle.Load("gecko_run_", 140);
     mGeckoSequenceIdle.Save("_gecko_run.seq");
     
     mGeckoSequenceIdle.Load("gecko_boost_", 1175);
     mGeckoSequenceIdle.Save("_gecko_boost.seq");
    
    exit(0);
    */
    
    
    
    
    
    
    
    LoadImagesSplatted();
    LoadImagesUnsplatted();
    
    
    
    
    
    FModelDataIndexed aRingShell;
    aRingShell.Load("effect_burst");
    
    mAnimationBurst1 = new FModelDataIndexed*[EFFECT_BURST_1_FRAMES];
    for(int i=0;i<EFFECT_BURST_1_FRAMES;i++)
    {
        mAnimationBurst1[i] = new FModelDataIndexed();
        mAnimationBurst1[i]->Clone(&aRingShell);
        mAnimationBurst1[i]->SetSprite(&(mAnimationBurst1UVW[i]));
    }
    
    /*
    
    mAnimationBurst2 = new FModelDataIndexed*[EFFECT_BURST_2_FRAMES];
    for(int i=0;i<EFFECT_BURST_2_FRAMES;i++)
    {
        mAnimationBurst2[i] = new FModelDataIndexed();
        mAnimationBurst2[i]->Clone(&aRingShell);
        mAnimationBurst2[i]->SetSprite(&(mAnimationBurst2UVW[i]));
    }
    
    mAnimationLuckyHalo = new FModelDataIndexed*[EFFECT_LUCKY_HALO_FRAMES];
    for(int i=0;i<EFFECT_LUCKY_HALO_FRAMES;i++)
    {
        mAnimationLuckyHalo[i] = new FModelDataIndexed();
        mAnimationLuckyHalo[i]->Clone(&aRingShell);
        mAnimationLuckyHalo[i]->SetSprite(&(mAnimationLuckyHaloUVW[i]));
    }
    
    */
    
    mAnimationExplode = new FModelDataIndexed*[EFFECT_EXPLODE_FRAMES];
    for(int i=0;i<EFFECT_EXPLODE_FRAMES;i++)
    {
        mAnimationExplode[i] = new FModelDataIndexed();
        mAnimationExplode[i]->Clone(&aRingShell);
        mAnimationExplode[i]->SetSprite(&(mAnimationExplodeUVW[i]));
    }
    
    
    
    
    FModelDataIndexed aRocketSpark;
    aRocketSpark.Load("rocket_spark");
    
    mAnimationSpark = new FModelDataIndexed*[SPARK_FRAMES];
    for(int i=0;i<SPARK_FRAMES;i++)
    {
        mAnimationSpark[i] = new FModelDataIndexed();
        mAnimationSpark[i]->Clone(&aRocketSpark);
        mAnimationSpark[i]->SetSprite(&(mAnimationSparkUVW[i]));
    }
    
    
    FModelDataIndexed aBombSpark;
    aBombSpark.Load("bomb_spark");
    
    mAnimationBombSpark = new FModelDataIndexed*[SPARK_FRAMES];
    for(int i=0;i<SPARK_FRAMES;i++)
    {
        mAnimationBombSpark[i] = new FModelDataIndexed();
        mAnimationBombSpark[i]->Clone(&aBombSpark);
        mAnimationBombSpark[i]->SetSprite(&(mAnimationSparkUVW[i]));
    }
    
    gImageBundler.EndBundle();
    
    
    
    mTreeRing.Load("tree_segment");
    
    mTitleTextCrazy[0].Load("intro_text_top_c");
    mTitleTextCrazy[1].Load("intro_text_top_r");
    mTitleTextCrazy[2].Load("intro_text_top_a");
    mTitleTextCrazy[3].Load("intro_text_top_z");
    mTitleTextCrazy[4].Load("intro_text_top_y");
    
    mTitleTextLizard[0].Load("intro_text_bottom_l");
    mTitleTextLizard[1].Load("intro_text_bottom_i");
    mTitleTextLizard[2].Load("intro_text_bottom_z");
    mTitleTextLizard[3].Load("intro_text_bottom_a");
    mTitleTextLizard[4].Load("intro_text_bottom_r");
    mTitleTextLizard[5].Load("intro_text_bottom_d");
    
    for(int i=0;i<5;i++)mTitleTextCrazy[i].SetSprite(&mTitleTextUVW);
    for(int i=0;i<6;i++)mTitleTextLizard[i].SetSprite(&mTitleTextUVW);
    
    mStar.Load("egg");
    mStar.SetSprite(&mStarUVW);
    
    mPano[0].Load("pano_wall");
    mPano[1].Clone(&(mPano[0]));
    
    mPano[0].SetSprite(&(mPanoUVW));
    mPano[1].SetSprite(&(mPanoUVW));
    
    mBranchBase.Load("branch_base");
    mBranchArmStump.Load("branch_stump_arm");
    mBranchBaseStump.Load("branch_stump_base");
    
    mBranchBase.SetSprite(&(mBranchUVW));
    mBranchArmStump.SetSprite(&(mBranchUVW));
    mBranchBaseStump.SetSprite(&(mBranchUVW));
    
    mBranchBigBase.Load("branch_big_base");
    mBranchBigArmStump.Load("branch_big_stump_arm");
    mBranchBigBaseStump.Load("branch_big_stump_base");

    mBranchBigBase.SetSprite(&(mBranchBigUVW));
    mBranchBigArmStump.SetSprite(&(mBranchBigUVW));
    mBranchBigBaseStump.SetSprite(&(mBranchBigUVW));
    
    mBranchSmallBase.Load("branch_small_base");
    mBranchSmallArmStump.Load("branch_small_stump_arm");
    mBranchSmallBaseStump.Load("branch_small_stump_base");
    
    mBranchSmallBase.SetSprite(&(mBranchSmallUVW));
    mBranchSmallArmStump.SetSprite(&(mBranchSmallUVW));
    mBranchSmallBaseStump.SetSprite(&(mBranchSmallUVW));
    
    for(int i=0;i<5;i++)
    {
        FString aPath;
        
        aPath = FString("branch_big_arm_") + FString((i + 1));
        mBranchBigArm[i].Load(aPath.c());
        mBranchBigArm[i].SetSprite(&(mBranchBigUVW));
        
        aPath = FString("branch_big_leaves_") + FString((i + 1));
        mBranchBigLeaves[i].Load(aPath.c());
        mBranchBigLeaves[i].SetSprite(&(mLeavesUVW));
    }
    
    for(int i=0;i<3;i++)
    {
        FString aPath;
        
        aPath = FString("branch_arm_") + FString((i + 1));
        mBranchArm[i].Load(aPath.c());
        mBranchArm[i].SetSprite(&(mBranchUVW));

        aPath = FString("branch_small_arm_") + FString((i + 1));
        mBranchSmallArm[i].Load(aPath.c());
        mBranchSmallArm[i].SetSprite(&(mBranchSmallUVW));
        
        aPath = FString("branch_leaves_") + FString((i + 1));
        mBranchLeaves[i].Load(aPath.c());
        mBranchLeaves[i].SetSprite(&(mLeavesUVW));

        aPath = FString("branch_small_leaves_") + FString((i + 1));
        mBranchSmallLeaves[i].Load(aPath.c());
        mBranchSmallLeaves[i].SetSprite(&(mLeavesUVW));
    }
    
    mSnail.Load("snail");
    mSnail.SetSprite(&mSnailUVW);
    
    mRing.Load("ring");
    mRing.SetSprite(&mRingUVW);
    
    
    mBomb.Load("bomb");
    mBomb.SetSprite(&mBombUVW);
    
    mSpeedBoost.Load("rocket");
    mSpeedBoost.SetSprite(&mSpeedBoostUVW);
    
    mHeart.Load("heart");
    mHeart.SetSprite(&mHeartUVW);
    
    mGeckoSequenceRun.Load("gecko_run.seq");
    
    mGeckoSequenceIdle.Load("gecko_idle.seq");
    
    //mGeckoSequenceHurt.Load("gecko_die.seq");
    //mGeckoSequenceBoostStart.Load("gecko_dash_leap.seq");
    mGeckoSequenceBoost.Load("gecko_boost.seq");
    mGeckoSequenceAttack.Load("gecko_attack.seq");
    
    mGeckoSequenceRun.SetSprite(&mGeckoUVW);
    mGeckoSequenceBoost.SetSprite(&mGeckoUVW);
    mGeckoSequenceIdle.SetSprite(&mGeckoUVW);
    mGeckoSequenceHurt.SetSprite(&mGeckoUVW);
    mGeckoSequenceAttack.SetSprite(&mGeckoUVW);
    
    
    
    
    mTreeRing.SetSprite(&(mTreeBark));
    
    mSoundRing.Load("ring", 4);
    
    mSoundFootstep[0].Load("footstep1", 1);
    mSoundFootstep[1].Load("footstep2", 1);
    mSoundFootstep[2].Load("footstep3", 1);
    
    mSoundBranchHit.Load("branch_snap_2", 1);
    mSoundBranchHitBoost.Load("branch_snap_3", 1);
    
    mSoundLuckyCoin.Load("lucky_coin", 1);
    mSoundTailWhip.Load("tail_whip", 1);
    
    mSoundExplosion.Load("explosion", 1);
    
    mSoundFreeLife.Load("free_life", 1);
    
    mSoundSpeedBoosStart.Load("speed_boost", 1);
    mSoundSpeedBoosFireLoop.Load("speed_boost_fire", 1);
    
    mSoundSnail.Load("snail_bump", 2);
    mSoundSnailWhipped.Load("snail_whip", 2);
    
    mSoundAchievement.Load("achievement", 1);

    
    mSoundAmbience[0].Load("amb_bird_1", 1);
    mSoundAmbience[1].Load("amb_bird_2", 1);
    mSoundAmbience[2].Load("amb_bird_3", 1);
    mSoundAmbience[3].Load("amb_bird_4", 1);
    mSoundAmbience[4].Load("amb_creak_1", 1);
    mSoundAmbience[5].Load("amb_creak_2", 1);
    mSoundAmbience[6].Load("amb_frog_1", 1);
    mSoundAmbience[7].Load("amb_frog_2", 1);
    mSoundAmbience[8].Load("amb_frog_3", 1);
    mSoundAmbience[9].Load("amb_monkey_1", 1);
    mSoundAmbience[10].Load("amb_monkey_2", 1);
    
    
    
}

void GLApp::LoadImagesSplatted()
{
    //mItemBack.Load("item_back");
    //mItemRingCooldown.Load("item_ring_cooldown");
    //mItemRingLoaded.Load("item_ring_charged");
    //mItemFlash.Load("item_ring_flash");
    
    
    gImageBundler.mAutoBundle = false;
    
    gImageBundler.mInset = 0;
    gImageBundler.mBorder = 2;
    
    gImageBundler.StartBundle("game_overlay");
    
    for(int i=0;i<FIRE_FRAMES;i++)
    {
        int aIndex = i + 80;
        FString aString;
        if(aIndex >= 100)aString = FString("fire_") + FString((aIndex));
        else  aString = FString("fire_0") + FString((aIndex));
        mAnimationFire[i].Load(aString.c());
    }
    
    mJoystickKnob.Load("joystick_knob");
    mJoystickBack.Load("joystick_back");
    
    mLifeEmpty.Load("life_empty");
    mLifeFull.Load("life_full");
    
    mButtonAttack[0].Load("button_attack");
    mButtonAttack[1].Load("button_attack_down");
    
    mButtonPause[0].Load("button_pause");
    mButtonPause[1].Load("button_pause_down");
    
    
    mFontScore.LoadRange('0', '9', "font_score_");
    mFontScore.Load((char*)"$.):");
    
    mFontGold.LoadRange('0', '9', "font_gold_");
    mFontGold.Load((char*)"+");
    
    mGameLabelScore.Load("game_label_score");
    mGameLabelRings.Load("game_label_rings");
    mGameLabelHeight.Load("game_label_height");
    
    mGameTextLifeGain.Load("praise_text_life_gain");
    mGameTextLifeLose.Load("praise_text_life_lose");
    mGameTextDodge.Load("praise_text_dodge");
    mGameTextAbsorb.Load("praise_text_absorb");
    mGameTextEvade.Load("praise_text_evade");
    
    
    
    gImageBundler.StartBundle("achievements");
    
    mAchievementBack.Load("achievement_back");
    
    //TODO: Achievs..
    //FList aAchList;
    //mAchievementManager.GetAllAchievements(&aAchList);
    //EnumList(Achievement, aAchievement, aAchList)
    //{
    //    mAchievementTextList += new AchievementText(aAchievement->mName.c());
    //}
    
    
    
    mButtonUpgrade.Load("button_upgrade");
    mButtonRestore.Load("button_restore");
    
    mDialogBoxButtonClose.Load("popover_button_close");
    
    mDialogBoxTextJoystick.Load("dialog_box_tip_joystick");
    mDialogBoxTextAttack.Load("dialog_box_tip_attack");
    mTutorialButtonArrow.Load("tutorial_arrow");
    
    
    
    
    
    
    gImageBundler.StartBundle("interface_menus_1");
    
    mDialogBoxBack.Load("dialog_box_back");
    
    mMainMenuButtonPlay[0].Load("main_menu_button_play");
    mMainMenuButtonPlay[1].Load("main_menu_button_play_down");
    
    mMainMenuButtonAch[0].Load("main_menu_button_ach");
    mMainMenuButtonAch[1].Load("main_menu_button_ach_down");
    
    mMainMenuButtonHS[0].Load("main_menu_button_hs");
    mMainMenuButtonHS[1].Load("main_menu_button_hs_down");
    
    mMainMenuButtonOptions[0].Load("main_menu_button_options");
    mMainMenuButtonOptions[1].Load("main_menu_button_options_down");
    
    mMainMenuButtonStore[0].Load("main_menu_button_store");
    mMainMenuButtonStore[1].Load("main_menu_button_store_down");
    
    mMainMenuButtonGames[0].Load("main_menu_button_games");
    mMainMenuButtonGames[1].Load("main_menu_button_games_down");
    
    
    mOptionsControlSegmentUnderlay.Load("options_control_underlay");
    
    mOptionsControlSegment[0].Load("options_control_joystick");
    mOptionsControlSegment[1].Load("options_control_accel");
    
    mOptionsControlSegmentSelected[0].Load("options_control_joystick_selected");
    mOptionsControlSegmentSelected[1].Load("options_control_accel_selected");
    
    mMenuTextGCError.Load("menu_text_gc_error");
    
    mMenuHeaderGC.Load("menu_header_gc");
    mMenuHeaderPurchase.Load("menu_header_purchase");
    mMenuHeaderRestorePurchase.Load("menu_header_restore_purchase");
    
    
    
    gImageBundler.StartBundle("interface_menus_2");
    
    
    mMenuTextPurchaseSuccess.Load("menu_text_purchase_success");
    mMenuTextPurchaseCanceled.Load("menu_text_purchase_canceled");
    mMenuTextPurchaseError.Load("menu_text_purchase_error");
    
    mGameOverText[1].Load("game_over_text_over");
    
    mMenuArrow.Load("menu_arrow");
    
    mGameTextPause.Load("pause_text");
    mGameOverTapResumeText.Load("game_over_text_tap");
    
    
    mMenuButtonBack[0].Load("menu_button_down");
    mMenuButtonBack[1].Load("menu_button");
    
    mMenuButtonTextResumeGame.Load("menu_button_text_resume");
    mMenuButtonTextOptions.Load("menu_button_text_options");
    mMenuButtonTextMainMenu.Load("menu_button_text_main_menu");
    mMenuButtonTextTryAgain.Load("menu_button_text_try_again");
    mMenuButtonTextClose.Load("menu_button_text_close");
    mMenuButtonTextContinue.Load("menu_button_text_continue");
    mMenuButtonTextDone.Load("menu_button_text_done");
    
    
    mMenuTextGC.Load("menu_bottom_text_gc");
    mMenuTextPurchase.Load("menu_bottom_text_itunes");
    
    mOptionsThumb.Load("options_slider_thumb");
    mOptionsSliderMusic.Load("options_slider_music");
    mOptionsSliderSFX.Load("options_slider_sfx");
    
    
    
    gImageBundler.StartBundle("interface_menus_3");
    
    
    
    mGameOverText[0].Load("game_over_text_game");
    
    mMenuBackPanel.Load("game_menu_back");
    
    mMenuHeaderOptions.Load("menu_header_options");
    mMenuHeaderPaused.Load("menu_header_paused");
    
    
    
    
    gImageBundler.mModelMode = true;
    gImageBundler.mEdgeBorder = 0;
    gImageBundler.mBorder = 0;
    gImageBundler.mInset = 0;
    gImageBundler.mEdgeBorder = 0;
    
    
    
    
    for(int i=0;i<SPARK_FRAMES;i++)
    {
        int aIndex = i;
        FString aString = FString("spark_") + FString((aIndex));
        mAnimationSparkUVW[i].Load(aString.c());
    }
    
    for(int i=0;i<EFFECT_BURST_1_FRAMES;i++)
    {
        int aIndex = i;
        FString aString;
        if(aIndex >= 10)aString = FString("bst1_0") + FString((aIndex));
        else aString = FString("bst1_00") + FString((aIndex));
        mAnimationBurst1UVW[i].Load(aString.c());
    }
    
    
    gImageBundler.StartBundle("uvw_effects");
    
    
    for(int i=0;i<EFFECT_EXPLODE_FRAMES;i++)
    {
        int aIndex = i;
        FString aString;
        if(aIndex >= 10)aString = FString("exp2_0") + FString((aIndex));
        else aString = FString("exp2_00") + FString((aIndex));
        mAnimationExplodeUVW[i].Load(aString.c());
    }
    
    gImageBundler.EndBundle();
    
}

void GLApp::LoadImagesUnsplatted()
{
    
    mBranchUVW.Load("branch_uvw");
    mBranchBigUVW.Load("branch_big_uvw");
    mBranchSmallUVW.Load("branch_small_uvw");
    mRingUVW.Load("ring_uvw");
    mStarUVW.Load("egg_uvw");
    mSnailUVW.Load("snail_uvw");
    mBombUVW.Load("bomb_uvw");
    mSpeedBoostUVW.Load("rocket_uvw");
    mHeartUVW.Load("heart_uvw");
    mGeckoUVW.Load("gecko_uvw");
    mTitleTextUVW.Load("intro_text_uvw");
    mLeavesUVW.Load("leaves_uvw");
    
    mPanoUVW.Load("pano_wall");
    mTreeBark.Load("bark_base");
}

void GLApp::LoadComplete()
{
    
    //mEditor = new Editor();
    mGame = new Game();
    
    gViewController.ViewAdd(mGame);
    
#ifdef GAME_TEST_MODE
    
    if(mEditor)
    {
        ViewAdd(mEditor);
    }
    
    if(mEditor == 0)
    {
        
#endif
        
        mMainMenu = new MainMenu();
        gViewController.ViewAdd(mMainMenu);
        
#ifdef GAME_TEST_MODE
    
    }
    
#endif
    
    
    //core_sound_musicPlay("game_music.mp3", true);
    
    
    
    
    /*
    
    if(mMusicOn)
    {
        
        //Log("\n[[Music = On]\n");
        //PlayMusic("game_music.mp3");
    }
    else
    {
        Log("\n[[Music = Off]\n");
    }
    
    */
    
}

void GLApp::TestEditorToggle()
{
#ifdef GAME_TEST_MODE
    if(mGame == 0)mGame = new Game();
    
    bool aHasGame = false;
    
    EnumList(FView, aFView, mChildren)
    {
        if(aFView == mGame)aHasGame = true;
    }
    
    if(aHasGame)
    {
        *this -= mGame;
        *this += mEditor;
    }
    else
    {
        mGame->Restart("test_level.xml");
        
        *this += mGame;
        *this -= mEditor;
    }    
#endif
}

void GLApp::Update()
{
    bool aFade = false;
    
    if(mGame)
    {
        if(mGame->mMenu)aFade = true;
    }
    
    if(mOptions)aFade = true;
    if(mDialogWindow)aFade = true;
    if(mPurchaseDialog)aFade = true;
    
    if(aFade)
    {
        mPauseFade +=  0.01f;
        if(mPauseFade >= 0.80f)mPauseFade = 0.80f;
    }
    else
    {
        mPauseFade = 0.0f;
    }
    
    if(mMainMenu)
    {
        if(mMainMenu->mAnimatingOut)
        {
            
            //TODO: Need to actually delete MM?
            //mMainMenu->Kill();
            
            mMainMenu->RemoveFromParent();
            
            //RemoveChild(mMainMenu);
            //mMainMenu = 0;
        }
    }
    
    //TODO: Achs..
    /*
    if(mAchievementBox == 0)
    {
        if(mRecentAchievementList.mCount > 0)
        {
            Achievement *aAchievement = (Achievement *)mRecentAchievementList.Pop();
            if(aAchievement)
            {
                FString aName = aAchievement->mName;
                EnumList(AchievementText, aText, mAchievementTextList)
                {
                    if(aText->mName == aName)
                    {
                        if(mAchievementBox == 0)
                        {
                            mAchievementBox = new AchievementBox(aText);
                        }
                    }
                }
            }
        }
        
        //AchievementText *aText = (AchievementText *)(mAchievementTextList.Fetch(gRand.Get(mAchievementTextList.mCount)));
        //if(aText)mAchievementBox = new AchievementBox(aText);
    }
    else
    {
        mAchievementBox->Update();
        if(mAchievementBox->mKilled)
        {
            delete mAchievementBox;
            mAchievementBox = 0;
        }
    }
    */
    
    
}

void GLApp::DrawOver()
{
    
}

void GLApp::Message(FString pMessage, FString pArguments)
{
    Log("==\n==\n{%s}\n==\n==\n", pMessage.c());
    
    if(pMessage == "gc_complete")
    {
        if(mGameCenterMenu)
        {
            mGameCenterMenu->Kill();
            mGameCenterMenu = 0;
        }
    }
}

void GLApp::PauseForIAd()
{
    BaseInactive();
    
    
	//SaveStatic();
    //mStopUpdates = true;
    //mStopDraws = true;
    //SetMusicVolume(0);
}

void GLApp::UnpauseForIAd()
{
    BaseActive();
    
	//mStopUpdates = false;
    //mStopDraws = false;
    //SetMusicVolume(mMusicVolume);
}

void GLApp::SuccessfulPurchase(char* pId)
{
	//Application::SuccessfulPurchase(pId);
    //mPurchased = true;
    //SaveStatic();
}

void GLApp::FailPurchase(char* pId)
{
	//Application::FailPurchase(pId);
}

void GLApp::CancelPurchase(char* pId)
{
	//Application::CancelPurchase(pId);
}

void GLApp::Accelerometer(float x, float y, float z, bool pReverse)
{
    if(mGame)
    {
        mGame->Accelerometer(x, y, z, pReverse);
    }
}



void GLApp::AchProgress(const char *pAchievementName, int pCount)
{
    //Achievement *aAchievement = mAchievementManager.AddProgress(pAchievementName, pCount);
    //if(aAchievement)mRecentAchievementList += aAchievement;
}

void GLApp::AchProgressGroup(const char *pGroupName, int pCount)
{
    //mAchievementManager.AddProgressGroup(pGroupName, &mRecentAchievementList, pCount);
}

void GLApp::ExitGame()
{
    if(mGame)
    {
        mGame->FadeRestart(true);
    }
    else
    {
        ShowMainMenu();
    }
}

void GLApp::ShowOptions()
{
	if(!mOptions)mOptions = new Options();
    gViewController.ModalViewAdd(mOptions);
}

void GLApp::ShowGameOverScreen()
{
	if(!mGameOverScreen)mGameOverScreen = new GameOverScreen();
    gViewController.ModalViewAdd(mGameOverScreen);
}

void GLApp::ShowDialogWindow(FSprite *pFSprite)
{
    mDialogWindow = new DialogWindow();
    mDialogWindow->mTextFSprite = pFSprite;
    
    gViewController.ModalViewAdd(mDialogWindow);
    
    if(mGame)
    {
        float aButtonTop = mGame->mButtonAttack.GetFrame().mY;
        mDialogWindow->mCenterY = (aButtonTop / 2.0f) + (8.0f * gGlobalScale);
    }
}

void GLApp::ShowGameCenterMenu()
{
    if(!mGameCenterMenu)mGameCenterMenu = new GameCenterMenu();
    gViewController.ModalViewAdd(mGameCenterMenu);
}

void GLApp::ShowMainMenu()
{
    if(!mMainMenu)mMainMenu = new MainMenu();
    
    gViewController.ModalViewAdd(mMainMenu);
    mMainMenu->AnimateIn();
    
    if(mGame)
    {
        mGame->mMenuMode = true;
    }
}


void GLApp::ShowStore()
{
    if(!mStore)mStore = new Store();
    gViewController.ModalViewAdd(mStore);
}

void GLApp::PlayGame()
{
    if(mMainMenu)
    {
        mMainMenu->mAnimatingOut = true;
    }
    if(mGame)
    {
        mGame->mMenuMode = false;
    }
}
