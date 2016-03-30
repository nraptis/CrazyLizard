
//  OCTools.m
//  LizDash
//
//  Created by Nick Raptis on 8/2/12.

#import "OCTools.h"
#import "Root.h"

void DisableAccelerometer()
{
    
}

void EnableAccelerometer()
{
    
}

bool AccelerometerEnabled()
{
    bool aReturn = false;
    
    
    return aReturn;
}

void SetWaveText(const char *pWaveText)
{
    //- (void)addWaveText:(NSString *)targetText;
    
    FString aString = FString(pWaveText);
    if(aString.mLength <= 0)aString = "__";
    
    NSString *aSend = [NSString stringWithUTF8String:aString.c()];
    
    [gRoot addWaveText:aSend];
    
    //NSString *aString =
}

void StoreScrollerShow()
{
    [gRoot storeScrollerShow];
}

void StoreScrollerHide()
{
    [gRoot storeScrollerHide];
}
