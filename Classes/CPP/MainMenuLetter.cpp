//
//  MainMenuLetter.cpp
//  LizDash
//
//  Created by Nick Raptis on 9/29/12.
//
//

#include "MainMenuLetter.h"

MainMenuLetter::MainMenuLetter()
{
    mData = 0;
    
    mScale = 4.45f;
    
    mRotationBase = 180.0f;
    mRotationOffset = 0.0f;
    
    mWobbleXSin = gRand.GetFloat(360.0f);
    mWobbleXSinSpeed = gRand.GetFloat(-4.0f, 4.0f);
    
    mWobbleYSin = gRand.GetFloat(360.0f);
    mWobbleYSinSpeed = gRand.GetFloat(-4.0f, 4.0f);
    
    mWobbleZSin = gRand.GetFloat(360.0f);
    mWobbleZSinSpeed = gRand.GetFloat(-4.0f, 4.0f);
}

MainMenuLetter::~MainMenuLetter()
{
    
}

void MainMenuLetter::Update()
{
    mWobbleXSin += mWobbleXSinSpeed;
    if(mWobbleXSin >= 360.0f)mWobbleXSin -= 360.0f;
    if(mWobbleXSin < 0)mWobbleXSin += 360.0f;
    
    mWobbleYSin += mWobbleYSinSpeed;
    if(mWobbleYSin >= 360.0f)mWobbleYSin -= 360.0f;
    if(mWobbleYSin < 0)mWobbleYSin += 360.0f;
    
    mWobbleZSin += mWobbleZSinSpeed;
    if(mWobbleZSin >= 360.0f)mWobbleZSin -= 360.0f;
    if(mWobbleZSin < 0)mWobbleZSin += 360.0f;
}

void MainMenuLetter::Draw()
{
    if(mData)
    {
        Graphics::MatrixPush();
        Graphics::Translate(mPos.mX, mPos.mY, mPos.mZ);
        Graphics::Scale(mScale);
        Graphics::Rotate(mRotationBase + Sin(mWobbleZSin) * 4.0f);
        Graphics::RotateX(Sin(mWobbleXSin) * 4.0f);
        Graphics::RotateY(Sin(mWobbleYSin) * 3.0f);
        
        mData->Draw();
        
        Graphics::MatrixPop();
    }
}
