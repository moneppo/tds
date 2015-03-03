//
//  DecoratorControl.h
//  cinder02
//
//  Created by Michael Oneppo on 3/1/15.
//
//

#ifndef __cinder02__DecoratorControl__
#define __cinder02__DecoratorControl__

#include <stdio.h>
#include "NocControl.h"

class DecoratorControl : public NocControl {
public:
    typedef std::shared_ptr<DecoratorControl> Ref;

    DecoratorControl(Noc::Ref noc, ci::vec2 offset) :
    mFollowActive(false),
    mNoc(noc),
    mOffset(offset)
    {}
    
    DecoratorControl(ci::vec2 offset = {0,0}) :
    mFollowActive(true),
    mNoc(nullptr),
    mOffset(offset)
    {}
    
    virtual void Update(float t);
    virtual void Draw();
    
protected:
    ci::vec2 mOffset;
    bool mFollowActive;
    Noc::Ref mNoc;
};



#endif /* defined(__cinder02__DecoratorControl__) */
