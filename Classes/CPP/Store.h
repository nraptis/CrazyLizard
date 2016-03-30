//
//  Store.h
//  LizDash
//
//  Created by Nick Raptis on 12/19/12.
//

#include "GLApp.h"
#include "StoreBubble.h"

#ifndef STORE_H
#define STORE_H

class Store : public FView
{
public:
	
	Store();
	virtual ~Store();
    
	GLApp			*mApp;
    
	virtual void	Update();
	virtual void	Draw();
	
	virtual void	Touch(int x, int y);
	virtual void	Drag(int x, int y);
	virtual void	Release(int x, int y);
	
	virtual void	Notify(void *pData);
    
    FList            mBubbles;
    
    FButton          mButtonDone;
    
    float           mRingRotation;
    
    float           mScrollOffset;
    float           mScrollHeight;
    
    
    bool            mDragging;
    
    float           mDragMouseX;
    float           mDragMouseY;
    
    float           mDragOffsetY;
    
};

#endif
