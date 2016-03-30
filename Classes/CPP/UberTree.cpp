//
//  UberTree.cpp
//  LizDash
//
//  Created by Nick Raptis on 2/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "UberTree.h"
#include "Game.h"

UberTreeSegment::UberTreeSegment()
{
    mApp = gApp;
    
    mStartZ = 0.0f;
    mEndZ = 0.0f;
    
    mData.Clone(&(mApp->mTreeRing));    
}

UberTreeSegment::~UberTreeSegment()
{
    //
    //
    //delete mData;
    //
    //mData=0;
    //
    //
}

void UberTreeSegment::Update()
{
    
}

void UberTreeSegment::Draw()
{
    
    //return;
    //for(int i=0;i<4;i++)
    //{
    //    mData[i]->mBindIndex = mBindIndex[i];
    //    mData[i]->Draw();
    //}
    
    //int aStartIndex = (gTestSlide1 * ((float)mData.mIndexCount));
    
    float *aXYZ = mData.mXYZ;
    float *aUVW = mData.mUVW;
    float *aNormal = mData.mNormal;
    unsigned short *aIndex = mData.mIndex;
    
    for(int i=0;i<4;i++)
    {
        mTexture[i] = mApp->mTreeBark.mTexture;
        //mBindIndex[i] = mApp->mTreeBarkTest[gTestIndex1].mBindIndex;
    }
    
    //Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex + 0, 48, mBindIndex[0]);
    //Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex + 48, 48, mBindIndex[1]);
    //Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex + 96, 48, mBindIndex[2]);
    //Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex + 144, 48, mBindIndex[3]);
    
    //Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex + 0, 96, mBindIndex[0]);
    //Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex + 96, 96, mBindIndex[1]);
    
    Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex + 0, 48, mTexture[0]);
    Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex + 48, 48, mTexture[1]);
    Graphics::DrawModelIndexed(aXYZ, aUVW, aNormal, aIndex + 96, 48, mTexture[2]);
    
    Graphics::SetColor();
}

void UberTreeSegment::GenerateBase()
{
    
    mStartZ = 0;
    mEndZ = SEGMENT_HEIGHT;
    
    Generate(mStartZ, mEndZ);
}

void UberTreeSegment::Generate(float pStartZ, float pEndZ)
{
    float *aXYZSrc;
    float *aXYZDest;
    int aXYZCount = mApp->mTreeRing.mXYZCount;
    aXYZCount = (aXYZCount + aXYZCount + aXYZCount);
    
    aXYZSrc = mApp->mTreeRing.mXYZ;
    aXYZDest = mData.mXYZ;
    
    for(int k=2;k<aXYZCount;k+=3)
    {
        aXYZDest[k] = (aXYZSrc[k] + pStartZ);
    }
    
    mStartZ = pStartZ;
    mEndZ = pEndZ;
    
    
    /*
    for(int i=0;i<RING_COUNT;i++)
    {
        float aPercent = (float)i / (float)(RING_COUNT);
        float aAngle = aPercent * 360.0f;
        
        FVec2 aDir = AngleToVector(aAngle);
        
        mRingXTop[i] = aDir.mX * SEGMENT_RADIUS;
        mRingYTop[i] = aDir.mY * SEGMENT_RADIUS;
        mRingZTop[i] = pStartZ;
        
        mRingXBot[i] = aDir.mX * SEGMENT_RADIUS;
        mRingYBot[i] = aDir.mY * SEGMENT_RADIUS;
        mRingZBot[i] = pEndZ;
    }
    
    GenerateModel();
     
    */
}

void UberTreeSegment::Shift(float pShiftAmount)
{
    mStartZ += pShiftAmount;
    mEndZ += pShiftAmount;
    
    int aXYZCount = mData.mXYZCount;
    
    float *aXYZSrc = mApp->mTreeRing.mXYZ;
    float *aXYZDest = mData.mXYZ;
    
    aXYZCount = (aXYZCount + aXYZCount + aXYZCount);
    
    aXYZCount = (aXYZCount + aXYZCount + aXYZCount);
    for(int k=2;k<aXYZCount;k+=3)
    {
        aXYZDest[k] = aXYZSrc[k] + mStartZ;
    }
}



void UberTree::Reset()
{
    float aPreviousZ = -SEGMENT_HEIGHT; //0.0f;
    float aCurrentZ = 0.0f; //SEGMENT_HEIGHT;
    
    for(int i=0;i<SEGMENT_COUNT;i++)
    {
        mSegment[i]->Generate(aPreviousZ, aCurrentZ);
        aPreviousZ = aCurrentZ;
        aCurrentZ += SEGMENT_HEIGHT;
    }
}

UberTree::UberTree()
{
    
    float aPreviousZ = -SEGMENT_HEIGHT; //0.0f;
    float aCurrentZ = 0.0f; //SEGMENT_HEIGHT;
    
    for(int i=0;i<SEGMENT_COUNT;i++)
    {
        mSegment[i] = new UberTreeSegment();
        
        /*
        UberTreeSegment *aSegment = new UberTreeSegment();
        for(int k=0;k<4;k++)
        {
            //aSegment->mBindIndex[k] = gApp->mTestTreeUVW[(i & 1)].mBindIndex;
            
            //mTestTreeUVW[0]
            
            
        }
        
        aSegment->Generate(aPreviousZ, aCurrentZ);
        
        
        aPreviousZ = aCurrentZ;
        aCurrentZ += SEGMENT_HEIGHT;
        
        
        mSegment[i] = aSegment;
        
        //= new UberTreeSegment();
        //aPreviousZ
        */
        
    }
    
    Reset();
}

UberTree::~UberTree()
{
    for(int i=0;i<SEGMENT_COUNT;i++)
    {
        delete mSegment[i];
        mSegment[i]=0;
    }
}

void UberTree::Update()
{
    for(int i=0;i<SEGMENT_COUNT;i++)
    {
        mSegment[i]->Update();
    }
    
    
}

void UberTree::Draw()
{
    for(int i=0;i<SEGMENT_COUNT;i++)
    {
        mSegment[i]->Draw();
    }
}

float UberTree::BottomZ()
{
    return mSegment[0]->mStartZ;
}

float UberTree::TopZ()
{
    return mSegment[SEGMENT_COUNT-1]->mEndZ;
}

void UberTree::BumpUp()
{
    
    UberTreeSegment *aFirst = mSegment[0];
    
    UberTreeSegment *aLast = mSegment[SEGMENT_COUNT-1];
    
    for(int i=1;i<SEGMENT_COUNT;i++)
    {
        mSegment[i-1] = mSegment[i];
    }
    aFirst->Generate(aLast->mEndZ, aLast->mEndZ + SEGMENT_HEIGHT);
    mSegment[SEGMENT_COUNT-1] = aFirst;
}

void UberTree::Shift(float pShiftAmount)
{
    for(int i=0;i<SEGMENT_COUNT;i++)
    {
        mSegment[i]->Shift(pShiftAmount);
    }
}

