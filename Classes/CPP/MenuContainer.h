//
//  MenuContainer.h
//  LizDash
//
//  Created by Nick Raptis on 10/23/12.
//
//

#ifndef LizDash_MenuContainer_h
#define LizDash_MenuContainer_h

#include "GLApp.h"

class MenuContainer : public FView
{
public:
    
	MenuContainer();
	virtual ~MenuContainer();
	
	GLApp			*mApp;
	
	virtual void	Update();
	virtual void	Draw();
    
	virtual void	Notify(void *pData);
};

#endif
