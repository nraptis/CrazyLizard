//
//  StoreBubble.cpp
//  LizDash
//
//  Created by Nick Raptis on 12/19/12.
//
//

#include "StoreBubble.h"


StoreBubble::StoreBubble()
{
    mApp = gApp;
    mOffsetY = 0.0f;
}

StoreBubble::~StoreBubble()
{
    
}

void StoreBubble::Update()
{
    
}

void StoreBubble::Draw()
{
    mApp->mSnailUVW.Center(gAppWidth2, mOffsetY);
    
}
