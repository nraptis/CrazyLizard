//
//  ShuffleBucket.h
//  Fiat500
//
//  Created by Nick Raptis on 1/9/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#ifndef SHUFFLE_BUCKET_H
#define SHUFFLE_BUCKET_H

#include "core_includes.h"

class ShuffleBucketNode
{
public:
    
    FString                 mData;
};

class ShuffleBucket
{
public:
    
    ShuffleBucket();
    virtual ~ShuffleBucket();
    
    void                    AddNode(const char *pNodeName);
    void                    AddNode(char *pNodeName){AddNode((const char*)pNodeName);}
    void                    AddNode(FString pNodeName){AddNode((const char*)pNodeName.c());}
    
    void                    Shuffle();
    
    const char              *PopNode();
    
    int                     mLeadCount;
    int                     mLeadIndex;
    int                     mShuffleIndex;
    
    ShuffleBucketNode       **mNodeList;
    
    int                     mListCount;
    int                     mListSize;
    
};

#endif
