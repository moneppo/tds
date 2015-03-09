//
//  NocControl.h
//  cinder02
//
//  Created by Michael Oneppo on 3/1/15.
//
//

#ifndef __cinder02__NocControl__
#define __cinder02__NocControl__

#include <stdio.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include <list>
#include <stdio.h>

#include "Noc.h"
#include "EventReceiver.h"

class NocControl : public EventReceiver {
public:
    typedef std::shared_ptr<NocControl> Ref;
    typedef std::list<NocControl::Ref> List;
    
    NocControl() :
    Position(0,0),
    Size(0,0)
    {}
    
    virtual ~NocControl() {}

    virtual void Update(float t) {}
    virtual void Draw() {
        ci::Rectf outline =
            ci::Rectf(Position.x, Position.y, Position.x + Size.x, Position.y + Size.y);
        ci::gl::color(0.2, 0.2, 0.2);
        ci::gl::drawSolidRect(outline);
    }
    
    ci::vec2 Position;
    ci::vec2 Size;
};

#endif /* defined(__cinder02__NocControl__) */
