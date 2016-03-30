//  RootViewController.m
//  Gnome
//  Created by Nick Raptis on 6/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.

#import <QuartzCore/QuartzCore.h>

#import "Root.h"

#import "GLView.h"
#import "AppDelegate.h"

#ifdef GAME_TEST_MODE
#import "EditorMenu.h"
#import "Editor.h"
#endif

Root *gRoot;

@implementation Root


#ifdef GAME_TEST_MODE

@synthesize testMenu;
@synthesize editorMenu;
@synthesize editorToolbarMenu;
@synthesize editorMenuSide;
@synthesize cameraMenu;
@synthesize waveNameController;
@synthesize wavePickerController;
@synthesize storeMenuScroller;

#endif


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    gRoot = self;
    
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    gRoot = self;
    
    return self;
}

- (void)cropImage:(NSString *)targetImageName withImageView:(UIImageView*)targetImageView
{
    
}



- (void)go
{
    gRoot = self;
    
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height);
    self.view.frame = CGRectMake(self.view.frame.origin.x, self.view.frame.origin.y, gAppWidth, gAppHeight);
    
    if(glViewController == nil)
    {
        self.glViewController = [[GLViewController alloc] initWithNibName:nil bundle:nil];
        [glViewController load];
    }
}

- (void)begin
{
    [self startGlobalUpdate];
    
    self.ignoreAnimations = YES;
    
    [self pushTo:glViewController];
    
    self.ignoreAnimations = NO;

#ifdef GAME_TEST_MODE
    
    if(gAppWidth > 640.0f)
    {
        
        //
        ////
        //
        
        //self.testMenu = [[GameTestMenu alloc] initWithNibName:nil bundle:nil];
        //[self.view addSubview:testMenu.view];
        //[testMenu collapseAnimated:NO];
        
        if(gEditor == 0)
        {
            //self.cameraMenu = [[QuickCameraMenu alloc] initWithNibName:nil bundle:nil];
            //[self.view addSubview:cameraMenu.view];
        }
    }
    
    if(gEditor != 0)
    {
        self.editorMenu = [[EditorMenu alloc] initWithNibName:nil bundle:nil];
        [self.view addSubview:editorMenu.view];
        
        self.editorToolbarMenu = [[EditorToolbarMenu alloc] initWithNibName:nil bundle:nil];
        [self.view addSubview:editorToolbarMenu.view];
        
        self.editorMenuSide = [[EditorMenuSide alloc] initWithNibName:nil bundle:nil];
        [self.view addSubview:editorMenuSide.view];
        
        //self.wavePickerController = [[WavePickerController alloc] initWithNibName:nil bundle:nil];
        //[self.view addSubview:wavePickerController.view];
        
        [self startGlobalUpdate];
    }
    else
    {
        self.wavePickerController = [[WavePickerController alloc] initWithNibName:nil bundle:nil];
        [self.view addSubview:wavePickerController.view];
    }
    
#endif
    
    [self startAccelerometerWithInterval:(1 / 30.0f)];
    
}


- (void)addWaveText:(NSString *)targetText
{
#ifdef GAME_TEST_MODE
    [waveNameController addText:targetText];
#endif
}

- (void)purchaseSuccessful:(NSString*)targetString
{
    /*
    
    gApp->mPurchased=true;
    gApp->SaveStatic();
    [self killAllAds];
    
    */
    
}

- (void)globalUpdate
{
    [super globalUpdate];
}

- (void)setWaveTitle:(NSString *)targetName
{
    
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	if(interfaceOrientation == UIInterfaceOrientationPortrait)
	{
		gRoot.currentOrientation = interfaceOrientation;
		return YES;
	}
	return NO;
}


@end
