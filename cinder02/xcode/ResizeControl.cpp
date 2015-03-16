//
//  ResizeControl.cpp
//  cinder02
//
//  Created by Michael Oneppo on 3/13/15.
//
//

#include "ResizeControl.h"

using namespace ci;
using namespace std;

ResizeControl::ResizeControl() :
DecoratorControl(vec2(-0.001,-0.001))
{
    Size = vec2(24, 24);
    PointerDown = [&](const PointerEvent& e) {
        if (mFollowActive && !Noc::GetActive()) return;
        
        Rectf outline = Rectf(Position.x, Position.y,
                              Position.x + Size.x,
                              Position.y + Size.y);
        if (outline.contains(e.globalPos)) {
            Capture(e);
            Noc::Ref n = mFollowActive ? Noc::GetActive() : mNoc;
            mStart = e.localPos - n->Size;
        }
    };
    
    PointerDrag = [&](const PointerEvent& e) {
        if (Captured(e)) {
            Noc::Ref n = mFollowActive ? Noc::GetActive() : mNoc;
            n->Size = e.localPos - mStart;
        }
    };
}

void ResizeControl::Draw()
{
    if (mFollowActive && !Noc::GetActive())
        return;
    
    gl::color(0.2, 0.2, 0.2);
    vec2 center = Position + Size * 0.5f;
    vec2 upper = {center.x, Position.y};
    vec2 lower = {Position.x, center.y};

    gl::drawLine(upper, center);
    gl::drawLine(center, lower);
}