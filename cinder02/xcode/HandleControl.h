//
//  HandleControl.h
//  cinder02
//
//  Created by Michael Oneppo on 3/1/15.
//
//

#ifndef __cinder02__HandleControl__
#define __cinder02__HandleControl__

#include <stdio.h>
#include "DecoratorControl.h"

class HandleControl : public DecoratorControl {
public:
    typedef std::shared_ptr<HandleControl> Ref;
    
    HandleControl();
    virtual void Draw();
    
protected:
    ci::vec2 mStart;
    bool mDragging;
};

#endif /* defined(__cinder02__HandleControl__) */
