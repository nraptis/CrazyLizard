//
//  RootViewController.h
//  Gnome
//
//  Created by Nick Raptis on 6/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define VIEWHAX(v) (v).frame=CGRectMake((v).frame.origin.x,(v).frame.origin.y,(v).frame.size.width,(v).frame.size.height)
#define VCHAX(v) (v).view.frame=CGRectMake((v).view.frame.origin.x,(v).view.frame.origin.y,(v).view.frame.size.width,(v).view.frame.size.height)

#import <UIKit/UIKit.h>

#import "RootBase.h"
#import <OpenGLES/ES2/glext.h>
#import <AVFoundation/AVFoundation.h>
#import "iAd/ADBannerView.h"
#import "GLApp.h"
#import "Game.h"
#import "GLViewController.h"

#ifdef GAME_TEST_MODE

#import "EditorMenu.h"
#import "EditorToolbarMenu.h"
#import "EditorMenuSide.h"
#import "GameTestMenu.h"
#import "QuickCameraMenu.h"
#import "StoreMenuScroller.h"
#import "WaveNameController.h"
#import "WavePickerController.h"

#endif

#import "FXML.h"

@interface Root : RootBase
{
#ifdef GAME_TEST_MODE
    GameTestMenu            *testMenu;
    EditorMenu              *editorMenu;
    EditorToolbarMenu       *editorToolbarMenu;
    EditorMenuSide          *editorMenuSide;
    QuickCameraMenu         *cameraMenu;
    WaveNameController      *waveNameController;
    WavePickerController    *wavePickerController;
    StoreMenuScroller       *storeMenuScroller;
#endif
}

#ifdef GAME_TEST_MODE

@property (nonatomic, retain) GameTestMenu *testMenu;
@property (nonatomic, retain) EditorMenu *editorMenu;
@property (nonatomic, retain) EditorToolbarMenu *editorToolbarMenu;
@property (nonatomic, retain) EditorMenuSide *editorMenuSide;
@property (nonatomic, retain) QuickCameraMenu *cameraMenu;
@property (nonatomic, retain) WavePickerController *wavePickerController;
@property (nonatomic, retain) WaveNameController *waveNameController;
@property (nonatomic, retain) StoreMenuScroller *storeMenuScroller;

#endif

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil;

- (void)enterBackground;
- (void)enterForeground;

- (void)cropImage:(NSString *)targetImageName withImageView:(UIImageView*)targetImageView;
- (void)go;

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation;

- (void)purchaseSuccessful:(NSString*)targetString;
- (void)globalUpdate;

- (void)setWaveTitle:(NSString *)targetName;
- (void)addWaveText:(NSString *)targetText;

- (void)storeScrollerShow;
- (void)storeScrollerHide;

@end

extern Root *gRoot;


