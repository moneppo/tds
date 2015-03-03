//
//  HandleControl.cpp
//  cinder02
//
//  Created by Michael Oneppo on 3/1/15.
//
//

#include "HandleControl.h"

using namespace ci;
using namespace std;

HandleControl::HandleControl() :
DecoratorControl(vec2(0,0))
{
    Size = vec2(24, 24);
    PointerDown = [&](const PointerEvent& e) {
        Rectf outline = Rectf(Position.x, Position.y,
                                Position.x + Size.x,
                                Position.y + Size.y);
        if (outline.contains(e.globalPos)) {
            Capture(e);
            Noc::Ref n = mFollowActive ? Noc::GetActive() : mNoc;
            mStart = e.globalPos - n->GlobalPosition();
            cout << "down" << endl;
        }
    };
    
    PointerDrag = [&](const PointerEvent& e) {
        Noc::Ref n = mFollowActive ? Noc::GetActive() : mNoc;
        n->SetGlobalPosition(e.globalPos - mStart);
    };
}

void HandleControl::Draw()
{
    if (mFollowActive && !Noc::GetActive())
        return;
    
    gl::color(0.2, 0.2, 0.2);
    vec2 center = Position + Size * 0.5f;
    gl::drawSolidCircle(center, Size.x / 2.0);
}