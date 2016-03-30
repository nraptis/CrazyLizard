
#include "DialogWindow.h"
#include "Game.h"

DialogWindow::DialogWindow()
{
    mName = "Dialog Window";
    
	mApp = ((GLApp*)gApp);
    
    mCenterX = gAppWidth2;
    mCenterY = gAppHeight2 - 84.0f;
    
    mTextFSprite = 0;
    
    mScale = 0.0f;
    mScaleSpeed = 0.066f;
    mScaleDirection = 0;
    
    mClosing = false;
    
    mButtonCloseOffsetX = 125.0f * gGlobalScale;
    mButtonCloseOffsetY = -140.0f * gGlobalScale;
    
    float aButtonWidth = mApp->mDialogBoxButtonClose.mWidth;
    float aButtonHeight = mApp->mDialogBoxButtonClose.mHeight;
    
    mButtonClose.Setup(mCenterX + (mButtonCloseOffsetX - aButtonWidth / 2.0f), mCenterY + (mButtonCloseOffsetY - aButtonHeight / 2.0f), &(mApp->mDialogBoxButtonClose), this);
    mButtonClose.mDrawManual = true;
    
}

DialogWindow::~DialogWindow()
{
    
}

void DialogWindow::Update()
{
    if(mClosing)
    {
        mScale -= 0.088f;
        if(mScale <= 0)
        {
            mScale = 0.0f;
            mApp->mDialogWindow=0;
            Kill();
        }
    }
    else
    {
        if(mScaleDirection < 3)
        {
            mScale += mScaleSpeed;
            if(mScaleDirection == 0)
            {
                if(mScale >= 1.0f)
                {
                    mScaleDirection = 1;
                }
            }
            else
            {
                mScaleSpeed -= 0.015f;
                if(mScale <= 1.0f)
                {
                    mScale = 1.0f;
                    mScaleDirection = 999;
                }
            }
        }
    }
}

void DialogWindow::Draw()
{
    Graphics::SetColor();
    
    Graphics::MatrixPush();
    
    Graphics::Translate(mCenterX, mCenterY, 0.0f);
    Graphics::Scale(mScale);
    
    mApp->mDialogBoxBack.Draw();
    if(mTextFSprite)mTextFSprite->Draw();
    
    Graphics::Translate(mButtonCloseOffsetX, mButtonCloseOffsetY, 0.0f);
    
    if(mButtonClose.mTouchDownInside)Graphics::SetColor(0.65f, 0.65f, 0.65f);
    else Graphics::SetColor();
    
    if(mButtonClose.mSpriteUp)
    {
        mButtonClose.mSpriteUp->Draw();
    }
    
    Graphics::MatrixPop();
    
    Graphics::SetColor();
}

void DialogWindow::Touch(int x, int y)
{
    
}

void DialogWindow::Notify(void *pData)
{
	if(pData==&mButtonClose)
	{
        mClosing = true;
	}
}

