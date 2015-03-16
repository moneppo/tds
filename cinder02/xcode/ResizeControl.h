//
//  ResizeControl.h
//  cinder02
//
//  Created by Michael Oneppo on 3/13/15.
//
//

#ifndef __cinder02__ResizeControl__
#define __cinder02__ResizeControl__

#include <stdio.h>
#include "DecoratorControl.h"

class ResizeControl : public DecoratorControl {
public:
    typedef std::shared_ptr<ResizeControl> Ref;
    
    ResizeControl();
    virtual void Draw();
    
protected:
    ci::vec2 mStart;
};

#endif /* defined(__cinder02__ResizeControl__) */

