//
//  SpawnWave.h
//  LizDash
//
//  Created by Nick Raptis on 3/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SPAWN_WAVE_H
#define SPAWN_WAVE_H

#include "GLApp.h"

class SpawnWaveNode
{
public:
    
    SpawnWaveNode();
    virtual ~SpawnWaveNode();
    
    virtual void                    Save(FFile *pBuffer);
    virtual void                    Load(FFile *pBuffer);
    
    SpawnWaveNode                   *Clone();
    
    int                             mType;
    
    float                           mObjectZ;
    float                           mObjectOrbit;
    
    
};

class SpawnWave
{
public:
    
    SpawnWave();
    virtual ~SpawnWave();
    
    void                            Save(const char *pFile);
    
    void                            BufferSave(FFile *pBuffer);
    void                            BufferLoad(FFile *pBuffer);
    
    FList                           mNodeList;
    
    bool                            mSymmetrical;
    
    float                           mMinZ;
    float                           mMaxZ;
    
    
    float                           mRotationStart1;
    float                           mRotationStart2;
    
    float                           mRotationEnd1;
    float                           mRotationEnd2;
    
    float                           mPaddingStart;
    float                           mPaddingEnd;
};

#endif
