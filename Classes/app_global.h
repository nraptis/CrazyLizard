//
//  app_global.h
//  Ghibli
//
//  Created by Nick Raptis on 2/12/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#ifndef __Ghibli__app_global__
#define __Ghibli__app_global__

//#include "GLApp.h"

#define RESIZE_MODE 1
#undef RESIZE_MODE

#define GAME_TEST_MODE 1
#undef GAME_TEST_MODE

class GLApp;

extern GLApp *gApp;

void app_global_create_app();

#endif 






