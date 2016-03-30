#pragma once

#include "GLApp.h"

#define MM_BUTTON_COUNT 5

class MainMenu : public FView
{
public:
    
	MainMenu();
	virtual ~MainMenu();
	
    virtual void                        PositionContent();
    
	GLApp                               *mApp;
    
    float                               mCameraLeftRightSin;
    float                               mCameraUpDownSin;
    
    float                               mCameraDist;
	
	virtual void                        Update();
	virtual void                        Draw();
	
	virtual void                        Touch(int x, int y);
	virtual void                        Drag(int x, int y);
	virtual void                        Release(int x, int y);
    
    virtual void                        MultiTouch(int x, int y, void *pData);
	virtual void                        MultiRelease(int x, int y, void *pData);
    virtual void                        MultiDrag(int x, int y, void *pData);
    virtual void                        FlushMultiTouch();
    
    
	virtual void                        Notify(void *pData);
    
    void                                RenderLetters();
    
    void                                AnimateIn();
    void                                AnimateOut();
    
    
    bool                                mAnimatingIn;
    bool                                mAnimatingOut;
    
    FButton                             mButtonPlay;
    FButton                             mButtonHighScores;
    FButton                             mButtonAchievements;
    FButton                             mButtonOptions;
	FButton                             mButtonBuy;
    FButton                             mButtonStore;
	FButton                             mButtonGames;
    
    
    FButton                             *mButton[MM_BUTTON_COUNT];
    
    float                               mButtonScale[MM_BUTTON_COUNT];
    float                               mButtonScaleSpeed[MM_BUTTON_COUNT];
    float                               mButtonFade[MM_BUTTON_COUNT];
    float                               mButtonFadeSpeed[MM_BUTTON_COUNT];
    int                                 mButtonAnimationMode[MM_BUTTON_COUNT];
    int                                 mButtonAnimationDelay[MM_BUTTON_COUNT];
    
    
    
    FList                               mLetters;
    
};

extern MainMenu *gMainMenu;
