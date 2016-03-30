//
//  WaveGenerator.cpp
//  LizDash
//
//
//
//
//  Created by Nick Raptis on 6/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

//#include "OCTools.h"
#include "WaveGenerator.h"
#include "GameObject.h"
#include "Game.h"

WaveGenerator::WaveGenerator()
{
    mBoostWait = 4;
    
    mBucketFirst.AddNode("wave_start");
    
    
    mBucketBoost.AddNode("wave_boost_arrow_zurps");
    mBucketBoost.AddNode("wave_boost_bomb_diggs");
    mBucketBoost.AddNode("wave_boost_circle_schloop_line");
    mBucketBoost.AddNode("wave_boost_spline_straight");
    mBucketBoost.AddNode("wave_boost_straight_clutter");
    mBucketBoost.AddNode("wave_boost_straight_snails");
    mBucketBoost.AddNode("wave_boost_zany_branch_fest");
    mBucketBoost.AddNode("wave_boost_ziggity_zag_zaggs");
    
    
    
    mBucketEasy.AddNode("wave_easy_flake_storm_sauce");
    mBucketEasy.AddNode("wave_easy_arch_square_jags_stunt");
    mBucketEasy.AddNode("wave_easy_big_small_diamond_stuff");
    mBucketEasy.AddNode("wave_easy_slant_snail_fakeouts");
    mBucketEasy.AddNode("wave_easy_snail_hump_coin_thing");
    mBucketEasy.AddNode("wave_easy_rect_diamond_jags");
    mBucketEasy.AddNode("wave_easy_big_arrow_circles");
    mBucketEasy.AddNode("wave_easy_square_diamond_romp");
    mBucketEasy.AddNode("wave_easy_weave_meanders");
    mBucketEasy.AddNode("wave_easy_shard_diamond_zags");
    mBucketEasy.AddNode("wave_easy_moon_wiggles");
    mBucketEasy.AddNode("wave_easy_shield_squigs");
    mBucketEasy.AddNode("wave_easy_giant_arrow_spline_dash");
    mBucketEasy.AddNode("wave_easy_double_tri_diamond_junk");
    mBucketEasy.AddNode("wave_easy_square_dots");
    mBucketEasy.AddNode("wave_easy_diamond_moon");
    mBucketEasy.AddNode("wave_easy_bone_slants");
    mBucketEasy.AddNode("wave_easy_snail_rect_diamonds");
    mBucketEasy.AddNode("wave_easy_silly_bones");
    mBucketEasy.AddNode("wave_easy_slant_lines");
    mBucketEasy.AddNode("wave_easy_arrow_square_egg");
    mBucketEasy.AddNode("wave_easy_arrowangle_square_boots");
    mBucketEasy.AddNode("wave_easy_cyber_tee_swappums");
    mBucketEasy.AddNode("wave_easy_square_amulet_swash");
    mBucketEasy.AddNode("wave_easy_circle_i_swagger");
    mBucketEasy.AddNode("wave_easy_circle_bomb_helluva");
    mBucketEasy.AddNode("wave_easy_lazy_spline_birdies");
    mBucketEasy.AddNode("wave_easy_cripple_dash_slumps");
    mBucketEasy.AddNode("wave_easy_super_diamond_spline_butter");
    mBucketEasy.AddNode("wave_easy_circle_coin_wanderer");
    mBucketEasy.AddNode("wave_easy_eye_beam_anchor_steam");
    
    
    
    mBucketMedium.AddNode("wave_med_spline_doublehex");
    mBucketMedium.AddNode("wave_med_dense_bogs_t_starts");
    mBucketMedium.AddNode("wave_med_quick_wiggle_snailfest");
    mBucketMedium.AddNode("wave_med_arrow_double_tris_snails");
    mBucketMedium.AddNode("wave_med_straight_dash_trickups");
    mBucketMedium.AddNode("wave_med_octo_swerves");
    mBucketMedium.AddNode("wave_med_ibeam_big_splotch_wigs");
    mBucketMedium.AddNode("wave_med_circ_bomb_switchups");
    mBucketMedium.AddNode("wave_med_spline_big_swaths");
    mBucketMedium.AddNode("wave_med_ibeam_snail_bowties");
    mBucketMedium.AddNode("wave_med_wiggle_snail_splines");
    mBucketMedium.AddNode("wave_med_vader_wag_bomb_zilla");
    mBucketMedium.AddNode("wave_med_ibeam_circle_zags");
    mBucketMedium.AddNode("wave_med_diamond_square_scatter_zigs");
    mBucketMedium.AddNode("wave_med_arch_scatter_misty");
    mBucketMedium.AddNode("wave_med_ziggity_bomb_swerves");
    mBucketMedium.AddNode("wave_med_spline_arch_zerps");
    mBucketMedium.AddNode("wave_med_pinch_twist_snlz");
    mBucketMedium.AddNode("wave_med_square_cyber_jags");
    mBucketMedium.AddNode("wave_med_marauding_wizzerdinks");
    mBucketMedium.AddNode("wave_med_zurp_arcs");
    mBucketMedium.AddNode("wave_med_hex_sloggers");
    mBucketMedium.AddNode("wave_med_hex_snail_derps");
    mBucketMedium.AddNode("wave_med_dmnd_swizzles");
    mBucketMedium.AddNode("wave_med_rect_switchups");
    mBucketMedium.AddNode("wave_diamond_wigs");
    mBucketMedium.AddNode("wave_spaced_out_zigs");
    mBucketMedium.AddNode("wave_diamond_breezy");
    mBucketMedium.AddNode("wave_meandering_cheese");
    mBucketMedium.AddNode("wave_dash_lines_eggs");
    mBucketMedium.AddNode("wave_big_patches_scatter_junk");
    mBucketMedium.AddNode("wave_coin_or_ring");
    mBucketMedium.AddNode("wave_line_fakeouts");
    
    
    mBucketHard.AddNode("wave_hard_triangle_flake_circs");
    mBucketHard.AddNode("wave_hard_big_rect_diamond_swerves");
    mBucketHard.AddNode("wave_hard_hexa_with_outlines");
    mBucketHard.AddNode("wave_hard_crazy_block_snail_soup");
    mBucketHard.AddNode("wave_hard_goofy_scatter_badge_dmds");
    mBucketHard.AddNode("wave_hard_arrow_block_sweeps");
    mBucketHard.AddNode("wave_hard_slanty_dashes");
    mBucketHard.AddNode("wave_hard_big_arrow_narrow_shakes");
    mBucketHard.AddNode("wave_hard_dmd_wags_bags");
    mBucketHard.AddNode("wave_hard_diamond_snail_circle_blockage");
    mBucketHard.AddNode("wave_snail_humps");
    mBucketHard.AddNode("wave_swerve_block");
    mBucketHard.AddNode("wave_snail_blocker_sauce");
    mBucketHard.AddNode("wave_block_snail_jigs");
    mBucketHard.AddNode("wave_snail_orgy");
    mBucketHard.AddNode("wave_arrow_drumps");
    mBucketHard.AddNode("wave_arrow_snail_derps");
    mBucketHard.AddNode("wave_super_squares");
    mBucketHard.AddNode("wave_bomb_weaver");
    mBucketHard.AddNode("wave_big_triangle_shards");
    mBucketHard.AddNode("wave_slats_lucky_break");
    mBucketHard.AddNode("wave_bomb_snail_branch_zigs");
    mBucketHard.AddNode("wave_square_diamond_semi_blocked");
    mBucketHard.AddNode("wave_lazy_spline");
    mBucketHard.AddNode("wave_snail_block_wall_1");
    mBucketHard.AddNode("wave_fancy_silly_wiggle");
    mBucketHard.AddNode("wave_diamond_wiggle");
    mBucketHard.AddNode("wave_hard_higgins_triangle_digfest");
    mBucketHard.AddNode("wave_hard_zags_ultra_branch_dense");
    mBucketHard.AddNode("wave_hard_double_tri_blogfest");
    mBucketHard.AddNode("wave_hard_square_mini_storm");
    mBucketHard.AddNode("wave_hard_lightning_squigs");
    mBucketHard.AddNode("wave_hard_circle_octo_bustaa");
    mBucketHard.AddNode("wave_hard_ultra_arches");
    mBucketHard.AddNode("wave_hard_diamond_sliver_wags");
    mBucketHard.AddNode("wave_hard_super_tight_circles");
    mBucketHard.AddNode("wave_hard_bone_skillet_lightning");
    mBucketHard.AddNode("wave_hard_ultra_swerve_snailz");
    mBucketHard.AddNode("wave_hard_giant_startstop_cappers");
    mBucketHard.AddNode("wave_hard_arrow_storm_dank");
    mBucketHard.AddNode("wave_hard_t_bomber_slumz");
    mBucketHard.AddNode("wave_hard_hexacomb_multiswerve");
    mBucketHard.AddNode("wave_hard_triple_beam_spline_dream");
    mBucketHard.AddNode("wave_hard_triangle_sleeve_rumpus");
    mBucketHard.AddNode("wave_hard_funky_android_face_swishes");
    mBucketHard.AddNode("wave_hard_double_stimpy_branch_slogger");
    mBucketHard.AddNode("wave_hard_ultra_box_doublets");
    mBucketHard.AddNode("wave_hard_circle_weave_double_stumps");
    mBucketHard.AddNode("wave_hard_blocker_node_spline_slurps");
    mBucketHard.AddNode("wave_hard_arrow_higgin_lumps");
    mBucketHard.AddNode("wave_hard_swerve_circle_blocker_splines");
    mBucketHard.AddNode("wave_hard_i_beam_blocker_swings");
    mBucketHard.AddNode("wave_hard_weaver_snail_block_dashes");
    
    
    mBucketBoost.Shuffle();
    mBucketEasy.Shuffle();
    mBucketMedium.Shuffle();
    mBucketHard.Shuffle();
    mBucketFirst.Shuffle();
    
    
    //ConvertWVF(&mBucketBoost);
    //ConvertWVF(&mBucketEasy);
    //ConvertWVF(&mBucketMedium);
    //ConvertWVF(&mBucketHard);
    //ConvertWVF(&mBucketFirst);
    //ConvertWVF("wave_tutorial");
    
    
}

WaveGenerator::~WaveGenerator()
{
    
}

void WaveGenerator::Reset()
{
    
}

SpawnWave *WaveGenerator::Generate(int pIndex)
{
    //pIndex += 500;
    
    if(gApp->mLoopingWaveName.mLength > 0)
    {
        return Load(gApp->mLoopingWaveName.c());
    }
    
    int aRand100 = gRand.Get(100);
    
    ShuffleBucket *aBucket = &mBucketEasy;
    
    bool aIsBoostWave = false;
    
    if(pIndex <= 3)
    {
        mBoostWait = 2;
    }
    else
    {
        if(mBoostWait > 0)
        {
            mBoostWait--;
        }
        else
        {
            if(aRand100 >= 22 && aRand100 <= 37)
            {
                mBoostWait = 4;
                aIsBoostWave = true;
            }
        }
    }
    
    if(aIsBoostWave)
    {
        aBucket = &mBucketBoost;
    }
    else
    {
        if(pIndex <= 0)
        {
            aBucket = &mBucketFirst;
        }
        else if(pIndex < 12)
        {
            aBucket = &mBucketEasy;
        }
        else if(pIndex < 24)
        {
            if(aRand100 < 40)aBucket = &mBucketEasy;
            else aBucket = &mBucketMedium;
        }
        else if(pIndex < 36)
        {
            if(aRand100 < 30)aBucket = &mBucketEasy;
            else aBucket = &mBucketMedium;
        }
        else if(pIndex < 48)
        {
            if(aRand100 < 20)aBucket = &mBucketEasy;
            else if(aRand100 < 40)aBucket = &mBucketMedium;
            else aBucket = &mBucketHard;
        }
        else
        {
            if(aRand100 < 15)aBucket = &mBucketEasy;
            else if(aRand100 < 30)aBucket = &mBucketMedium;
            else aBucket = &mBucketHard;
        }
    }
    
    const char *aWaveName = aBucket->PopNode();
    
    //Log("Wave Info: {%d} = [%s]", pIndex, aWaveName);
    
    return Load(aWaveName);
}

SpawnWave *WaveGenerator::GenerateTrainingWave(int pIndex)
{
    return Load("wave_tutorial");
}

void WaveGenerator::ConvertWVF(ShuffleBucket *pBucket)
{
    for(int aIndex=0;aIndex<pBucket->mListCount;aIndex++)
    {
        ShuffleBucketNode *aNode = pBucket->mNodeList[aIndex];
        
        ConvertWVF(aNode->mData.c());
    }
}

void WaveGenerator::ConvertWVF(const char *pPath)
{
    SpawnWave *aWave = LoadXML(pPath);
    FString aExport = FString("/Users/nraptis/Desktop/Exports/") + FString(pPath) + FString(".wvf");
    aWave->Save(aExport.c());
}


SpawnWave *WaveGenerator::LoadXML(const char *pPath)
{
    //SetWaveText(pPath);
    
    SpawnWave *aSpawnWave = new SpawnWave();
    
    FXML aXML;
    aXML.Load(pPath);
    
    if(aXML.mRoot == 0)
    {
        FString aPath = FString(pPath) + FString(".xml");
        aXML.Load(aPath.c());
    }
    
    //aXML.Print();
    
    FXMLTag *aRootTag = aXML.mRoot;
    if(aRootTag == 0)return aSpawnWave;
    
    //aSpawnWave->VERTICAL_SPREAD = IntToFloat(FString(aRootTag->GetParamValue("vertical_spread")).ToInt());
    //if(aSpawnWave->VERTICAL_SPREAD <= 0.0f)aSpawnWave->VERTICAL_SPREAD = 0.05f;
    
    aSpawnWave->mSymmetrical = FString(aRootTag->GetParamValue("symmetrical")).ToBool();
    
    /*
     float aStartRotation1 = IntToFloat(FString(aRootTag->GetParamValue("start_rotation_1")).ToInt());
     float aEndRotation1 = IntToFloat(FString(aRootTag->GetParamValue("end_rotation_1")).ToInt());
     
     float aStartRotation2 = aStartRotation1;
     float aEndRotation2 = aEndRotation1;
     
     bool aSymmetricalRotation = FString(aRootTag->GetParamValue("rotation_symmetry")).ToBool();
     
     if(aSymmetricalRotation)
     {
     aStartRotation2 = IntToFloat(FString(aRootTag->GetParamValue("start_rotation_2")).ToInt());
     aEndRotation2 = IntToFloat(FString(aRootTag->GetParamValue("end_rotation_2")).ToInt());
     }
     
     //Log("\n\nLoaded Rotations: [%f %f %f %f]\n", aStartRotation1, aEndRotation1, aStartRotation2, aEndRotation2);
     
     aSpawnWave->mRotationStart1 = aStartRotation1 * 360.0f;
     aSpawnWave->mRotationStart2 = aStartRotation2 * 360.0f;
     
     aSpawnWave->mRotationEnd1 = aEndRotation1 * 360.0f;
     aSpawnWave->mRotationEnd2 = aEndRotation2 * 360.0f;
     
     */
    
    float aFlagX = 0.0f;
    float aFlagY = 0.0f;
    
    EnumTagsMatching(aRootTag, aFlagTag, "flag_start_1")
    {
        aFlagX = IntToFloat(FString(aFlagTag->GetParamValue("x")).ToInt());
        aFlagY = IntToFloat(FString(aFlagTag->GetParamValue("y")).ToInt());
    }
    
    aSpawnWave->mRotationStart1 = gGame->GenerateObjectOrbit(aFlagX);
    aSpawnWave->mRotationStart2 = aSpawnWave->mRotationStart1;
    aSpawnWave->mPaddingStart = gGame->GenerateObjectZ(aFlagY);
    
    EnumTagsMatching(aRootTag, aFlagTag, "flag_end_1")
    {
        aFlagX = IntToFloat(FString(aFlagTag->GetParamValue("x")).ToInt());
        aFlagY = IntToFloat(FString(aFlagTag->GetParamValue("y")).ToInt());
    }
    
    aSpawnWave->mRotationEnd1 = gGame->GenerateObjectOrbit(aFlagX);
    aSpawnWave->mRotationEnd2 = aSpawnWave->mRotationEnd1;
    aSpawnWave->mPaddingEnd = gGame->GenerateObjectZ(aFlagY);
    
    EnumTagsMatching(aRootTag, aWaveNodeListTag, "wave_list")
    {
        EnumTagsMatching(aWaveNodeListTag, aNodeTag, "wave_node")
        {
            aSpawnWave->mNodeList += gGame->SpawnNodeFromXML(aNodeTag);
        }
    }
    
    EnumTagsMatching(aRootTag, aSplineNodeListTag, "spline_list")
    {
        EnumTagsMatching(aSplineNodeListTag, aSplineNodeTag, "spline_node")
        {
            EnumTagsMatching(aSplineNodeTag, aSplineWaveNodeListTag, "wave_list")
            {
                EnumTagsMatching(aSplineWaveNodeListTag, aNodeTag, "wave_node")
                {
                    aSpawnWave->mNodeList += gGame->SpawnNodeFromXML(aNodeTag);
                }
            }
        }
    }
    
    EnumTagsMatching(aRootTag, aPatternListTag, "pattern_list")
    {
        EnumTagsMatching(aPatternListTag, aPatternTag, "pattern")
        {
            EnumTagsMatching(aPatternTag, aPatternWaveNodeListTag, "wave_list")
            {
                EnumTagsMatching(aPatternWaveNodeListTag, aNodeTag, "wave_node")
                {
                    aSpawnWave->mNodeList += gGame->SpawnNodeFromXML(aNodeTag);
                }
            }
        }
    }
    
    aSpawnWave->mMaxZ = 0.0f;
    aSpawnWave->mMinZ = 0.0f;
    
    SpawnWaveNode *aFirstNode = (SpawnWaveNode *)aSpawnWave->mNodeList.Fetch(0);
    
    if(aFirstNode)
    {
        aSpawnWave->mMinZ = aFirstNode->mObjectZ;
        aSpawnWave->mMaxZ = aFirstNode->mObjectZ;
    }
    
    EnumList(SpawnWaveNode, aNode, aSpawnWave->mNodeList)
    {
        if(aNode->mObjectZ > aSpawnWave->mMaxZ)aSpawnWave->mMaxZ = aNode->mObjectZ;
        if(aNode->mObjectZ < aSpawnWave->mMinZ)aSpawnWave->mMinZ = aNode->mObjectZ;
    }
    
    
    aSpawnWave->mPaddingEnd = (aSpawnWave->mPaddingEnd - aSpawnWave->mMaxZ);
    aSpawnWave->mPaddingStart = (aSpawnWave->mMinZ - aSpawnWave->mPaddingEnd);
    
    FList aSymmetryList;
    
    if(aSpawnWave->mSymmetrical)
    {
        EnumList(SpawnWaveNode, aNode, aSpawnWave->mNodeList)
        {
            SpawnWaveNode *aClone = aNode->Clone();
            aClone->mObjectOrbit += 180.0f;
            aSymmetryList += aClone;
        }
    }
    
    EnumList(SpawnWaveNode, aNode, aSymmetryList)
    {
        aSpawnWave->mNodeList += aNode;
    }
    
    aSymmetryList.Clear();
    
    return aSpawnWave;
}

SpawnWave *WaveGenerator::LoadWVF(const char *pPath)
{
    FFile aBuffer;
    
    aBuffer.Load(pPath);
    
    if(aBuffer.mLength <= 0)
    {
        FString aPath = FString(pPath) + FString(".wvf");
        aBuffer.Load(aPath);
    }
    
    SpawnWave *aReturn = 0;
    
    if(aBuffer.mLength > 0)
    {
        //aReturn = new SpawnWave();
        
        //aReturn->m
    }
    
    return aReturn;
}

SpawnWave *WaveGenerator::Load(const char *pPath)
{
    FFile aBuffer;
    aBuffer.Load(FString(pPath) + FString(".wvf"));
    
    if(aBuffer.mLength > 0)
    {
        SpawnWave *aWave = new SpawnWave();
        aWave->BufferLoad(&aBuffer);
        return aWave;
    }
    else
    {
        return LoadXML(pPath);
    }
    
}


