//
//  ShuffleBucket.cpp
//  Fiat500
//
//  Created by Nick Raptis on 1/9/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#include "ShuffleBucket.h"

ShuffleBucket::ShuffleBucket()
{
    mLeadCount = 4;
    mShuffleIndex = 2;
    mLeadIndex = 0;
    
    mNodeList = 0;
    
    mListCount = 0;
    mListSize = 0;
}

ShuffleBucket::~ShuffleBucket()
{
    for(int i=0;i<mListCount;i++)
    {
        delete mNodeList[i];
    }
    
    delete[]mNodeList;
    mNodeList = 0;
    
    mListCount = 0;
    mListSize = 0;
}

void ShuffleBucket::AddNode(const char *pNodeName)
{
    ShuffleBucketNode *aNode = new ShuffleBucketNode();
    aNode->mData = pNodeName;
    
    if(mListCount >= mListSize)
    {
        mListSize = (mListCount + mListCount / 2) + 1;
        ShuffleBucketNode **aNewNodeList = new ShuffleBucketNode*[mListSize];
        
        for(int i=0;i<mListCount;i++)aNewNodeList[i] = mNodeList[i];
        delete [] mNodeList;
        mNodeList = aNewNodeList;
    }
    
    mNodeList[mListCount] = aNode;
    mListCount++;
    
    mLeadCount = (mListCount >> 1);
    mShuffleIndex = (mListCount >> 2);
    
}

const char *ShuffleBucket::PopNode()
{
    const char *aReturn = (const char *)0;
    
    if(mLeadIndex < mListCount)
    {
        aReturn = mNodeList[mLeadIndex]->mData.c();
    }
    
    mLeadIndex++;
    if((mLeadIndex>=mLeadCount) || (mLeadIndex>=mLeadCount))
    {
        mLeadIndex = 0;
        
        ShuffleBucketNode *aHoldNode;
        
        int aMax = mLeadCount + mLeadCount;
        if(aMax > mListCount)aMax = mListCount;
        
        int aIndex = 0;
        
        for(aIndex=mLeadCount;aIndex<aMax;aIndex++)
        {
            aHoldNode = mNodeList[aIndex];
            mNodeList[aIndex] = mNodeList[aIndex - mLeadCount];
            mNodeList[aIndex - mLeadCount] = aHoldNode;
        }
        
        int aSwapIndex;
        
        int aRange = (mListCount - mLeadCount);
        
        if(aRange > 1)
        {
            for(aIndex=mShuffleIndex;aIndex<mListCount;aIndex++)
            {
                aSwapIndex = gRand.Get(aRange) + mShuffleIndex;
                
                aHoldNode = mNodeList[aSwapIndex];
                mNodeList[aSwapIndex] = mNodeList[aIndex];
                mNodeList[aIndex] = aHoldNode;
            }
        }
    }
    return aReturn;
}

void ShuffleBucket::Shuffle()
{
    ShuffleBucketNode *aHoldNode;
    
    int aSwapIndex;
    
    for(int aIndex=0;aIndex<mListCount;aIndex++)
    {
        aSwapIndex = gRand.Get(mListCount);
        aHoldNode = mNodeList[aSwapIndex];
        mNodeList[aSwapIndex] = mNodeList[aIndex];
        mNodeList[aIndex] = aHoldNode;
    }
}




