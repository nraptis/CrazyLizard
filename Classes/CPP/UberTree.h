//
//  UberTree.h
//  LizDash
//
//  Created by Nick Raptis on 2/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef UBER_TREE_H
#define UBER_TREE_H


#include "GLApp.h"
#include "FModelData.h"

class UberTreeSegment
{
public:
    
    UberTreeSegment();
    ~UberTreeSegment();
    
    GLApp                           *mApp;
    
    virtual void                    Update();
    virtual void                    Draw();
    
    void                            GenerateBase();
    void                            Generate(float pStartZ, float pEndZ);
    
    void                            Shift(float pShiftAmount);
    
    float                           mStartZ;
    float                           mEndZ;
    
    FModelDataIndexed                mData;
    FTexture                        *mTexture[4];
    //int                             mBindIndex[4];
    
};

class UberTree
{
public:
    
    UberTree();
    ~UberTree();
    
    virtual void                    Update();
    virtual void                    Draw();
    
    void                            Reset();
    
    void                            Shift(float pShiftAmount);
    
    float                           mTextureV;
    float                           mTextureVSpeed;
    
    float                           BottomZ();
    float                           TopZ();
    
    UberTreeSegment                 *mSegment[SEGMENT_COUNT];
    
    void                            BumpUp();
};

#endif
