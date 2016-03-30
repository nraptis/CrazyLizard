/*
 *  Options.h
 *  Template
 *
 *  Created by Nick Raptis on 11/3/10.
 *  Copyright 2010 Raptisoft LLC. All rights reserved.
 *
 */

#pragma once

#include "GLApp.h"
#include "FSlider.h"

class Options : public FView
{
public:
    
	Options();
	virtual ~Options();
	
	GLApp			*mApp;
	
	virtual void	Update();
	virtual void	Draw();
	
	virtual void	Notify(void *pData);
	
	virtual void	Touch(int x, int y);
    
	FButton         mButtonDone;
    
    FButton         mButtonControl1;
    FButton         mButtonControl2;
    
    void            UpdateControlButtons();
	
	FSlider         mSFXSlider;
	FSlider         mMusicSlider;
    
};