
#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H

#include "GLApp.h"

class DialogWindow : public FView
{
public:
    
	DialogWindow();
	virtual ~DialogWindow();
	
	GLApp                   *mApp;
    
	virtual void            Update();
	virtual void            Draw();
	
	virtual void            Notify(void *pData);
	
	virtual void            Touch(int x, int y);
    
    bool                    mClosing;
    
    float                   mScale;
    float                   mScaleSpeed;
    int                     mScaleDirection;
    
	FButton                 mButtonClose;
    
    float                   mCenterX,mCenterY;
    
    float                   mButtonCloseOffsetX;
    float                   mButtonCloseOffsetY;
    
    FSprite                 *mTextFSprite;
    
};

#endif
