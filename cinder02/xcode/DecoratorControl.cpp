//
//  DecoratorControl.cpp
//  cinder02
//
//  Created by Michael Oneppo on 3/1/15.
//
//

#include "DecoratorControl.h"

using namespace ci;
using namespace std;

void DecoratorControl::Update(float t)
{
    Noc::Ref n = mFollowActive ? Noc::GetActive() : mNoc;
    if (!n) return;
    vec2 pos = n->GlobalPosition();
    if (mOffset.x < 0) {
        Position.x = pos.x - mOffset.x + Size.x;
    } else {
        Position.x = pos.x + mOffset.x - Size.x;
    }
    
    if (mOffset.y < 0) {
        Position.y = pos.y - mOffset.y + Size.y;
    } else {
        Position.y = pos.y + mOffset.y - Size.y;
    }
}

void DecoratorControl::Draw()
{
    if (mFollowActive && !Noc::GetActive())
        return;
    
    Rectf outline = Rectf(Position.x,
                          Position.y,
                          Position.x + Size.x,
                          Position.y + Size.y);
    gl::color(0.2, 0.2, 0.2);
    gl::drawSolidRect(outline);
}