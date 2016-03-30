//
//  app_global.cpp
//  Ghibli
//
//  Created by Nick Raptis on 2/12/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#include "app_global.h"
#include "GLApp.h"

GLApp *gApp = 0;

void app_global_create_app()
{
    if(gApp == 0)
    {
        gApp = new GLApp();
    }
}

