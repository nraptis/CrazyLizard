//
//  WaveGenerator.h
//  LizDash
//
//  Created by Nick Raptis on 6/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef WAVE_GENERATOR_H
#define WAVE_GENERATOR_H

#include "ShuffleBucket.h"

#include "SpawnWave.h"
#include "FXML.h"

class WaveGenerator
{
public:
    
    WaveGenerator();
    ~WaveGenerator();
    
    SpawnWave                           *Generate(int pIndex);
    
    SpawnWave                           *GenerateTrainingWave(int pIndex);
    
    void                                ConvertWVF(ShuffleBucket *pBucket);
    void                                ConvertWVF(const char *pPath);
    
    SpawnWave                           *LoadXML(const char *pPath);
    SpawnWave                           *LoadWVF(const char *pPath);
    
    SpawnWave                           *Load(const char *pPath);
    
    void                                Reset();
    
    int                                 mBoostWait;
    
    ShuffleBucket                       mBucketFirst;
    ShuffleBucket                       mBucketEasy;
    ShuffleBucket                       mBucketMedium;
    ShuffleBucket                       mBucketHard;
    ShuffleBucket                       mBucketBoost;
};

#endif
