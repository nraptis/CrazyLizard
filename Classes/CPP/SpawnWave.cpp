//  SpawnWave.cpp
//  LizDash
//
//  Created by Nick Raptis on 3/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.

#include "SpawnWave.h"
#include "GLApp.h"

SpawnWaveNode::SpawnWaveNode()
{
    mType = 0;
    
    mObjectOrbit = 0.0f;
    mObjectZ = 0.0f;
}

SpawnWaveNode::~SpawnWaveNode()
{
    
}

SpawnWaveNode *SpawnWaveNode::Clone()
{
    SpawnWaveNode *aClone = new SpawnWaveNode();
    
    aClone->mType = mType;
    aClone->mObjectOrbit = mObjectOrbit;
    aClone->mObjectZ = mObjectZ;
    
    return aClone;
}

void SpawnWaveNode::Save(FFile *pBuffer)
{
    pBuffer->WriteChar(mType);
    pBuffer->WriteFloat(mObjectOrbit);
    pBuffer->WriteFloat(mObjectZ);
}

void SpawnWaveNode::Load(FFile *pBuffer)
{
    mType = (int)((unsigned char)(pBuffer->ReadChar()));
    mObjectOrbit = pBuffer->ReadFloat();
    mObjectZ = pBuffer->ReadFloat();
}

SpawnWave::SpawnWave()
{
    mMinZ = 0.0f;
    mMaxZ = 0.0f;
    
    mPaddingStart = 0.0f;
    mPaddingEnd = 0.0f;
    
    mRotationStart1 = 0.0f;
    mRotationStart2 = 0.0f;
    
    mRotationEnd1 = 0.0f;
    mRotationEnd2 = 0.0f;
    
    mSymmetrical = false;
    
    //VERTICAL_SPREAD = 0.05f;
}

SpawnWave::~SpawnWave()
{
    
}

void SpawnWave::Save(const char *pFile)
{
    FFile aBuffer;
    BufferSave(&aBuffer);
    aBuffer.Save(pFile);
}

void SpawnWave::BufferSave(FFile *pBuffer)
{
    pBuffer->WriteInt(mNodeList.mCount);
    
    EnumList(SpawnWaveNode, aNode, mNodeList)
    {
        aNode->Save(pBuffer);
    }
    
    pBuffer->WriteChar(mSymmetrical);
    
    pBuffer->WriteFloat(mMinZ);
    pBuffer->WriteFloat(mMaxZ);
    
    pBuffer->WriteFloat(mRotationStart1);
    pBuffer->WriteFloat(mRotationStart2);
    
    pBuffer->WriteFloat(mRotationEnd1);
    pBuffer->WriteFloat(mRotationEnd2);
    
    pBuffer->WriteFloat(mPaddingStart);
    pBuffer->WriteFloat(mPaddingEnd);
}

void SpawnWave::BufferLoad(FFile *pBuffer)
{
    int aNodeCount = pBuffer->ReadInt();
    
    for(int i=0;i<aNodeCount;i++)
    {
        SpawnWaveNode *aNode = new SpawnWaveNode();
        aNode->Load(pBuffer);
        mNodeList += aNode;
    }
    
    mSymmetrical = pBuffer->ReadChar();
    
    mMinZ = pBuffer->ReadFloat();
    mMaxZ = pBuffer->ReadFloat();
    
    mRotationStart1 = pBuffer->ReadFloat();
    mRotationStart2 = pBuffer->ReadFloat();
    
    mRotationEnd1 = pBuffer->ReadFloat();
    mRotationEnd2 = pBuffer->ReadFloat();
    
    mPaddingStart = pBuffer->ReadFloat();
    mPaddingEnd = pBuffer->ReadFloat();
}


