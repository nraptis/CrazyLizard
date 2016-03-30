/*
 *  GenericClass.h
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 */

#include "GLApp.h"

class GenericClass
{
public:
	GenericClass();
	~GenericClass();
	
	GLApp				*mApp;
	
	virtual void		Draw();
	virtual void		Update();
};