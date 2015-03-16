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
DecoratorControl(vec2(0,0)),
mDragging(false)
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
            mStart = e.globalPos - n->GlobalPosition();
            mDragging = true;
        }
    };
    
    PointerDrag = [&](const PointerEvent& e) {
        if (Captured(e)) {
            Noc::Ref n = mFollowActive ? Noc::GetActive() : mNoc;
            n->SetGlobalPosition(e.globalPos - mStart);
        }
    };
    
    PointerUp = [&](const PointerEvent& e) {
        if (Captured(e)) {
            mDragging = false;
            Noc::Root()->ApplyToChildren([this, e](Noc::Ref n) {
                if (Noc::GetActive() == n) return;
                vec2 p = n->GlobalPosition();
                Rectf bounds = {p.x - Size.x, p.y - Size.y, p.x, p.y};
                if (bounds.contains(e.globalPos)) {
                    n->InsertNoc(Noc::GetActive());
                }
            });
        }
    };
}

void HandleControl::Draw()
{
    if (mFollowActive && !Noc::GetActive())
        return;
    
    if (mDragging) {
        gl::color(0.1, 0.1, 0.1);
        Noc::Root()->ApplyToChildren([this](Noc::Ref n) {
            if (Noc::GetActive() == n) return;
            vec2 center = n->GlobalPosition() - Size * 0.5f;
            gl::drawSolidCircle(center, Size.x * 0.5f);
        });
    }
    
    gl::color(0.2, 0.2, 0.2);
    vec2 center = Position + Size * 0.5f;
    gl::drawSolidCircle(center, Size.x / 2.0);

}