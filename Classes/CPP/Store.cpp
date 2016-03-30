//
//  Store.cpp
//  LizDash
//
//  Created by Nick Raptis on 12/19/12.
//

//#include "OCTools.h"
#include "Store.h"
#include "Game.h"

Store::Store()
{
	mApp = ((GLApp*)gApp);
    
    float aSpacing = 3.0f * gGlobalScale;
    
    float aButtonWidth = mApp->mMenuButtonBack[0].mWidth;
    float aButtonHeight = mApp->mMenuButtonBack[0].mHeight;
    
    mButtonDone.Setup(gAppWidth2 - (aButtonWidth / 2.0f), MENU_DONE_BUTTON_Y, mApp->mMenuButtonBack, 2, this);
    mButtonDone.SetOverlays(&(mApp->mMenuButtonTextResumeGame));
    
    mButtonDone.mDrawManual = true;
    
    mRingRotation = 0.0f;
    
    
    
    mDragging = 0.0f;
    
    mDragMouseX = 0.0f;
    mDragMouseY = 0.0f;
    
    mDragOffsetY = 0.0f;
    
    
    
    StoreBubble *aBubble = 0;
    
    float aY = 0.0f;
    for(int i=0;i<50;i++)
    {
        aBubble = new StoreBubble();
        
        aBubble->mOffsetY = aY;
        
        aY += 80.0f;
        
        mBubbles += aBubble;
    }
    
    
    //StoreScrollerShow();
}

Store::~Store()
{
	
}

void Store::Update()
{
    
    mRingRotation += 5.0f;
    if(mRingRotation >= 360.0f)mRingRotation -= 360.0f;
    
}

void Store::Draw()
{
    Graphics::SetColor();
    
    mApp->mMenuBackPanel.Center(gAppWidth2, MENU_PANEL_CENTER_Y);
    mButtonDone.Draw();
    
    Graphics::EnableDepth();
    Graphics::ClearDepth();
    
    Graphics::MatrixPush();
    Graphics::Translate(gAppWidth2 - 60.0f * gGlobalScale, gAppHeight2 - 140.0f * gGlobalScale, 0.0f);
    
    Graphics::Scale(gGlobalScale * 30.0f, gGlobalScale * 30.0f, gGlobalScale * 30.0f);
    Graphics::RotateZ(90.0f);
    Graphics::RotateX(mRingRotation);
    
    mApp->mRing.Draw();
    
    Graphics::MatrixPop();
    Graphics::DisableDepth();

    
}

void Store::Touch(int x, int y)
{
	
}

void Store::Drag(int x, int y)
{
	
}

void Store::Release(int x, int y)
{
	
}

void Store::Notify(void *pData)
{
    if(pData==&mButtonDone)
	{
		mApp->mStore=0;
		Kill();
        //StoreScrollerHide();
	}
}

